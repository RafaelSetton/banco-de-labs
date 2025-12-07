.text

.globl operation
operation:
    add a0, a1, a2
    sub a0, a0, a5
    add a0, a0, a7
    lhu t0, 8(sp)
    add a0, a0, t0
    lw t0, 16(sp)
    sub a0, a0, t0
    ret
