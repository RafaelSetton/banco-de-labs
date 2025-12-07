# example.o: example.c lib.h
# 	clang --target=riscv32 -g -march=rv32g -mabi=ilp32d -mno-relax example.c -c -o lab10a.o

# lab10a.o: lab10a.s
#  	clang --target=riscv32 -g -march=rv32g -mabi=ilp32d -mno-relax lab10a.s -c -o lab10a.o

# lab10a.elf : lab10a.o
#  	ld.lld -g lab10a.o example.o -o lab10a.elf

%.o : %.s
	clang --target=riscv32 -g -march=rv32g -mabi=ilp32d -mno-relax $< -c -o $@
%.elf : %.o
	ld.lld -g $< -o $@

