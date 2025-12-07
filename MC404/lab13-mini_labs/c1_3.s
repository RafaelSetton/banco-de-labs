.text

.globl operation
operation:
    li a0, 1
    li a1, -2
    li a2, 3
    li a3, -4
    li a4, 5
    li a5, -6
    li a6, 7
    li a7, -8
    addi sp, sp, -32

    li t0, 9
    sw t0, (sp)
    
    li t0, -10
    sw t0, 4(sp)
    
    li t0, 11
    sw t0, 8(sp)
    
    li t0, -12
    sw t0, 12(sp)
    
    li t0, 13
    sw t0, 16(sp)
    
    li t0, -14
    sw t0, 20(sp)

    sw ra, 24(sp)
    jal mystery_function

    lw ra, 24(sp)
    addi sp, sp, 32
    ret
