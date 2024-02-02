#!/usr/bin/python
# -*- coding: utf-8 -*-

import argparse
import os
import re
import sys
from os import listdir
from os.path import isfile, join
from subprocess import PIPE, TimeoutExpired, run


def get_parser():
    parser = argparse.ArgumentParser(description="Testa tarefa.")
    parser.add_argument("only", nargs="*", help="apenas unidades contendo essa string")
    parser.add_argument(
        "-f", action="store_true", help="Força continuar mesmo que anteriores falhem"
    )
    parser.add_argument(
        "-t", "--test", action="append", help="testa apenas o arquivo especificado"
    )
    parser.add_argument(
        "-d",
        "--dry-run",
        action="store_true",
        help="não executa os testes, apenas compara",
    )
    parser.add_argument(
        "-v",
        "--valgrind",
        action="store_true",
        help="executa o valgrind",
    )
    parser.add_argument(
        "-c",
        "--comp",
        action="store_true",
        help="apenas compila o binário",
    )
    return parser

ERRORS = False # global variable to check if there were errors

class BaseTask:
    TIME_LIMIT_SECONDS = 2
    SPACES_RE = re.compile(r"\s+", re.M)
    CFLAGS = ["-std=c99", "-Wall", "-Werror", "-Werror=vla", "-g"]
    LDFLAGS = ["-lm"]

    def __init__(self, continue_on_error=True, only_matching=None, dry_run=False):
        self.continue_on_error = continue_on_error
        self.only_matching = only_matching
        self.dry_run = dry_run
        self.compiled_binaries = set()
        self.tested_cases = set()
        self.passed_cases = set()
        self.tested_units = set()
        self.passed_units = set()
        self.show_all_errors = False

    def strip_spaces(self, text):
        return self.SPACES_RE.sub(" ", text.strip())

    def read_file_utf8(self, file_name):
        assert isfile(file_name), f"Não existe o arquivo {file_name}"
        try:
            with open(file_name, encoding="utf-8", errors="strict") as f:
                return f.read()
        except ValueError:
            assert False, f"Enconding inválido em {file_name}. Por favor, use UTF-8."
        except Exception as e:  # noqa
            assert False, f"Falha ao ler arquivo {file_name}"

    def compare_stripped(self, left, right):
        return self.strip_spaces(left) == self.strip_spaces(right)

    def compare_files(self, out, res):
        left = self.read_file_utf8(out)
        right = self.read_file_utf8(res)
        return self.compare_stripped(left, right)

    def compare_sorted_files(self, out, res):
        left = "\n".join(sorted(self.read_file_utf8(out).split("\n")))
        right = "\n".join(sorted(self.read_file_utf8(res).split("\n")))
        return self.strip_spaces(left) == self.strip_spaces(right)

    def exists(self, file_name):
        assert isfile(file_name), f"você deve criar um arquivo {file_name}"

    def normalize_binary_name(self, binary):
        if os.name == "nt":
            binary += ".exe"
        return join(".", binary)

    def make(self, binary):
        norm_binary = self.normalize_binary_name(binary)
        if binary not in self.compiled_binaries:
            if isfile(norm_binary):
                os.remove(norm_binary)
            self.compiled_binaries.add(binary)
            self.exists("Makefile")
            p = run(["make", binary])
            assert p.returncode == 0, f"falha ao criar {norm_binary} com Makefile"
        assert isfile(norm_binary), f"o Makefile não criou um arquivo {norm_binary}"
        return norm_binary

    def compile(self, sources=None, binary=None):
        if sources is None:
            sources = sorted([f for f in listdir(".") if f.endswith(".c")])
        if binary is None:
            binary = sources[0][
                :-2
            ]  # binário padrão é primeiro arquivo sem extensão .c
        norm_binary = self.normalize_binary_name(binary)
        if binary not in self.compiled_binaries:
            if isfile(norm_binary):
                os.remove(norm_binary)
            self.compiled_binaries.add(binary)
            for source in sources:
                self.exists(source)
            compile_cmd = (
                ["gcc"] + self.CFLAGS + sources + ["-o", binary] + self.LDFLAGS
            )
            p = run(compile_cmd)
            assert p.returncode == 0, f"falha ao compilar {norm_binary}"
        assert isfile(norm_binary), f"não foi possível compilar {norm_binary}"
        return norm_binary

    def generate_binary(self, binary):
        """
        Wrapper to decide wheter to compile by ourselves or use Makefile.
        """
        if isfile("Makefile"):
            return self.make(binary)
        else:
            return self.compile(binary=binary)

    def run_binary_inner(self, cmd, stdin, stdout, input):
        if input is None:
            p = run(
                cmd,
                stdin=stdin,
                stdout=stdout,
                encoding="utf8",
                errors="ignore",
                timeout=self.TIME_LIMIT_SECONDS,
            )
        else:
            p = run(
                cmd,
                input=input,
                stdout=stdout,
                encoding="utf8",
                errors="ignore",
                timeout=self.TIME_LIMIT_SECONDS,
            )
        assert p.returncode == 0, f"código de saída é {p.returncode}"
        return p

    def run_binary(
        self,
        cmd,
        stdin,
        stdout,
        input=None,
        in_filename=None,
        out_filename=None,
    ):
        cmd_str = " ".join([c if " " not in c and c != "" else f'"{c}"' for c in cmd])
        if in_filename:
            cmd_str += f" < {in_filename}"
        if out_filename:
            cmd_str += f" > {out_filename}"
        if input:
            cmd_str += f' com entrada "{input}"'
        try:
            return self.run_binary_inner(cmd, stdin, stdout, input)
        except AssertionError as e:
            assert False, f"falha ao executar {cmd_str} : {e}"
        except TimeoutExpired:
            assert (
                False
            ), f"falha ao executar {cmd_str} : tempo limite de {self.TIME_LIMIT_SECONDS}s excedido"

    def test_one_case(self, binary, in_filename_name):
        out_filename_name = in_filename_name.replace(".in", ".out")
        res_file_name = in_filename_name.replace(".in", ".res")
        if not self.dry_run:
            with open(in_filename_name) as i, open(out_filename_name, "w") as o:
                self.run_binary(
                    [binary],
                    i,
                    o,
                    in_filename=in_filename_name,
                    out_filename=out_filename_name,
                )
        assert self.compare_files(
            out_filename_name, res_file_name
        ), f'execute diff "{out_filename_name}" "{res_file_name}"'

    def run_valgrind(self, binary, in_filename_name):
        self.TIME_LIMIT_SECONDS = 200
        out_filename_name = in_filename_name.replace(".in", ".out")
        res_file_name = in_filename_name.replace(".in", ".res")
        if not self.dry_run:
            with open(in_filename_name) as i, open(out_filename_name, "w") as o:
                self.run_binary(
                    ["valgrind", "-v","--leak-check=full","--show-leak-kinds=all","--error-exitcode=1", binary],
                    i,
                    o,
                    in_filename=in_filename_name,
                    out_filename=out_filename_name,
                )
        assert self.compare_files(
            out_filename_name, res_file_name
        ), f'execute diff "{out_filename_name}" "{res_file_name}"'

    def test_cases(self, binary, in_filename_names, folder="testes"):
        assert (
            type(in_filename_names) != str
        ), "erro no caso de teste, deveria ser lista de strings"
        errors = []
        for in_filename_name in in_filename_names:
            in_filename_name = join(folder, in_filename_name)
            try:
                self.tested_cases.add(in_filename_name)
                self.test_one_case(binary, in_filename_name)
                self.passed_cases.add(in_filename_name)
                print(f"  -> ✅ {in_filename_name} passou")
            except AssertionError as e:
                print(f"  -> ❌ {in_filename_name} falhou -> {e}")
                errors.append(f"{e}")
                if not self.continue_on_error:
                    # exit(1)
                    break
        if errors:
            # print("\n  -> ".join(errors))
            global ERRORS
            ERRORS = True

    def input_output(self, binary, input_content, expected_output):
        p = self.run_binary([binary], None, PIPE, input=input_content)
        assert self.compare_stripped(
            p.stdout, expected_output
        ), f'para entrada "{input_content}", a saída é "{p.stdout.strip()}", mas era esperado "{expected_output}"'

    def should_test(self, name):
        if not name.startswith("teste_"):
            return False
        if not self.only_matching:
            return True
        for pattern in self.only_matching:
            if pattern in name:
                return True
        return False

    def test_units(self):
        for name in sorted(dir(self)):
            if not self.should_test(name):
                continue
            print()
            print(f"Executando {name}...")
            sys.stderr.flush()
            sys.stdout.flush()
            try:
                test = getattr(self, name)
                self.tested_units.add(name)
                test()
                self.passed_units.add(name)
                print(f"{name}: OK")
            except AssertionError as e:
                print(f"{name}: FALHOU")
                if "privado" not in name or self.show_all_errors:
                    print(f"  -> {e}\n")
                if not self.continue_on_error:
                    break

    def case_range(self, input_template, start, end):
        input_files = []
        for i in range(start, end + 1):
            input_files.append(input_template.format(i))
        return input_files


# ===== Configuration of each lab =====
binary = "livros"
valgrind_test_case = "testes/teste2.in"

class Task(BaseTask):
    """
    Cada grupo de teste é definido por um método que começa com teste_.
    Cada teste precisa compilar o binário, seja pelo método compile ou pelo Makefile.
    """

    def teste_1_pequenos(self):
        global binary
        binary = self.generate_binary(binary=binary)
        self.test_cases(binary, self.case_range("teste{}.in", 1, 3))

    def teste_2_medios(self):
        global binary
        binary = self.generate_binary(binary=binary)
        self.test_cases(binary, self.case_range("teste{}.in", 4, 6))

    def teste_3_grandes(self):
        global binary
        binary = self.generate_binary(binary=binary)
        self.test_cases(binary, self.case_range("teste{}.in", 7, 9))

    def teste_4_gigante(self):
        global binary
        binary = self.generate_binary(binary=binary)
        self.test_cases(binary, self.case_range("teste{}.in", 10, 10))


# TODO run valgrind

if __name__ == "__main__":
    args = get_parser().parse_args()
    t = Task(args.f, args.only, args.dry_run)
    if args.comp:
        # Quando a flag --comp é usada, o binário é compilado e não executado
        t.generate_binary(binary=binary)
    elif args.valgrind:
        binary = t.generate_binary(binary=binary)
        t.run_valgrind(binary, valgrind_test_case)
    elif args.test is not None:
        # Quando a flag --test é usada, o binário é compilado e executado
        # apenas para o caso de teste especificado
        # TODO Permitir que o caso teste seja especificado por path, nome ou número.
        t.test_cases(t.generate_binary(binary=binary), args.test)

    else:
        t.test_units()

    if ERRORS:
        exit(1)
