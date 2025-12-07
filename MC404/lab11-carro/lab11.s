.text

.equ CAR, 0xFFFF0100

.equ STEER, CAR + 0x20
.equ GAS, CAR + 0x21

.globl _start
_start:
    li a0, STEER
    li a1, -15
    sb a1, 0(a0)

    li a0, GAS
    li a1, 1
    sb a1, 0(a0)

    loop:
    nop
    j loop

    li a7, 93
    ecall