.text

.globl my_function
my_function:
    // Stores Context
    addi sp, sp, -32
    sw a0, (sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw ra, 16(sp)

    // SUM 1
    add a0, a0, a1

    // CALL 1
    lw a1, (sp)
    jal mystery_function
    
    // DIFF 1
    lw t0, 4(sp)
    sub a0, t0, a0

    // SUM 2
    lw t0, 8(sp)
    add a0, a0, t0
    sw a0, 12(sp)
    
    // CALL 2
    lw a1, 4(sp)
    jal mystery_function

    // DIFF 2
    lw t0, 8(sp)
    sub a0, t0, a0

    // SUM 3
    lw a1, 12(sp)
    add a0, a0, a1
    
    lw ra, 16(sp)
    addi sp, sp, 32
    ret
