.text

.globl operation
operation:
    lw t0, 20(sp)
    lw t1, 16(sp)
    lw t2, 12(sp)
    lw t3, 8(sp)
    lw t4, 4(sp)
    lw t5, (sp)

    addi sp, sp, -32

    sw a0, 20(sp)
    sw a1, 16(sp)
    sw a2, 12(sp)
    sw a3, 8(sp)
    sw a4, 4(sp)
    sw a5, (sp)
    
    mv a0, t0
    mv a1, t1
    mv a2, t2
    mv a3, t3
    mv a4, t4
    mv a5, t5

    mv t0, a6
    mv a6, a7
    mv a7, t0

    sw ra, 24(sp)
    jal mystery_function
    lw ra, 24(sp)
    addi sp, sp, 32
    ret
