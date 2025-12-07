.text

.globl node_op
node_op:
    lw t0, (a0)
    lb t1, 4(a0)
    lb t2, 5(a0)
    lh t3, 6(a0)

    add a0, t0, t1
    sub a0, a0, t2
    add a0, a0, t3
    ret
