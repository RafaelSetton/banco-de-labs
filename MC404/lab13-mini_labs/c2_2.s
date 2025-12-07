.text

.globl middle_value_int
middle_value_int:
    srai a1, a1, 1
    slli a1, a1, 2
    add a0, a0, a1
    lw a0, (a0)
    ret

.globl middle_value_short
middle_value_short:
    srai a1, a1, 1
    slli a1, a1, 1
    add a0, a0, a1
    lw a0, (a0)
    ret

.globl middle_value_char
middle_value_char:
    srai a1, a1, 1
    add a0, a0, a1
    lw a0, (a0)
    ret

.globl value_matrix
value_matrix:
    li t0, 42
    mul a1, a1, t0
    add a1, a1, a2
    slli a1, a1, 2
    add a0, a0, a1
    lw a0, (a0)
    ret


