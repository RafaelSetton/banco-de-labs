.text

.globl fill_array_int
fill_array_int:
    addi sp, sp, -400

    li t0, 0 // Offset (in bytes)
    li t1, 0 // i
    li t2, 100 // max
    2: 
        add t3, sp, t0
        sw t1, (t3)

        addi t0, t0, 4
        addi t1, t1, 1
        blt t1, t2, 2b

    mv a0, sp
    addi sp, sp, -16
    sw ra, (sp)
    jal mystery_function_int
    lw ra, (sp)
    addi sp, sp, 16
    addi sp, sp, 400
    ret

.globl fill_array_short
fill_array_short:
    addi sp, sp, -200

    li t0, 0 // Offset (in bytes)
    li t1, 0 // i
    li t2, 100 // max
    2: 
        add t3, sp, t0
        sw t1, (t3)

        addi t0, t0, 2
        addi t1, t1, 1
        blt t1, t2, 2b

    mv a0, sp
    addi sp, sp, -16
    sw ra, (sp)
    jal mystery_function_short
    lw ra, (sp)
    addi sp, sp, 16
    addi sp, sp, 200
    ret

.globl fill_array_char
fill_array_char:
    addi sp, sp, -100

    li t0, 0 // Offset (in bytes)
    li t1, 0 // i
    li t2, 100 // max
    2: 
        add t3, sp, t0
        sw t1, (t3)

        addi t0, t0, 1
        addi t1, t1, 1
        blt t1, t2, 2b

    mv a0, sp
    addi sp, sp, -16
    sw ra, (sp)
    jal mystery_function_char
    lw ra, (sp)
    addi sp, sp, 16
    addi sp, sp, 100
    ret
