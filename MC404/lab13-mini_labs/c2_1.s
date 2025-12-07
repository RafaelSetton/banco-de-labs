.text

.globl swap_int
swap_int:
    lw t0, (a0)
    lw t1, (a1)

    sw t0, (a1)
    sw t1, (a0)

    li a0, 0
    ret
.globl swap_short
swap_short:
    lh t0, (a0)
    lh t1, (a1)

    sh t0, (a1)
    sh t1, (a0)

    li a0, 0
    ret
.globl swap_char
swap_char:
    lb t0, (a0)
    lb t1, (a1)

    sb t0, (a1)
    sb t1, (a0)

    li a0, 0
    ret

