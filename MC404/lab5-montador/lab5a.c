int read(int __fd, const void *__buf, int __n)
{
    int ret_val;
    __asm__ __volatile__(
        "mv a0, %1           # file descriptor\n"
        "mv a1, %2           # buffer \n"
        "mv a2, %3           # size \n"
        "li a7, 63           # syscall read code (63) \n"
        "ecall               # invoke syscall \n"
        "mv %0, a0           # move return value to ret_val\n"
        : "=r"(ret_val)                   // Output list
        : "r"(__fd), "r"(__buf), "r"(__n) // Input list
        : "a0", "a1", "a2", "a7");
    return ret_val;
}

void write(int __fd, const void *__buf, int __n)
{
    __asm__ __volatile__(
        "mv a0, %0           # file descriptor\n"
        "mv a1, %1           # buffer \n"
        "mv a2, %2           # size \n"
        "li a7, 64           # syscall write (64) \n"
        "ecall"
        :                                 // Output list
        : "r"(__fd), "r"(__buf), "r"(__n) // Input list
        : "a0", "a1", "a2", "a7");
}

void exit(int code)
{
    __asm__ __volatile__(
        "mv a0, %0           # return code\n"
        "li a7, 93           # syscall exit (93) \n"
        "ecall"
        :           // Output list
        : "r"(code) // Input list
        : "a0", "a7");
}

void _start()
{
    int ret_code = main();
    exit(ret_code);
}

#define STDIN_FD 0
#define STDOUT_FD 1

void hex_code(int val)
{
    char hex[11];
    unsigned int uval = (unsigned int)val, aux;

    hex[0] = '0';
    hex[1] = 'x';
    hex[10] = '\n';

    for (int i = 9; i > 1; i--)
    {
        aux = uval % 16;
        if (aux >= 10)
            hex[i] = aux - 10 + 'A';
        else
            hex[i] = aux + '0';
        uval = uval / 16;
    }
    write(1, hex, 11);
}

int extract(int n, int qtd_bits)
{
    int mask = (1 << qtd_bits) - 1;
    return n & mask;
}

int from_str(char *str)
{
    int n = 0;
    for (int i = 1; i < 5; i++)
        n = 10 * n + str[i] - 48;

    if (str[0] == '-')
        n *= -1;
    return n;
}

int main()
{
    char line[50];
    read(STDIN_FD, line, 32);

    int n1 = extract(from_str(line), 3);
    int n2 = extract(from_str(line + 6), 8);
    int n3 = extract(from_str(line + 12), 5);
    int n4 = extract(from_str(line + 18), 5);
    int n5 = extract(from_str(line + 24), 11);

    int n = (n5 << 21) | (n4 << 16) | (n3 << 11) | (n2 << 3) | n1;

    hex_code(n);
}