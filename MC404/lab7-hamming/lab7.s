.text            
.globl _start       

read_number:
    addi t0, a0, 1
    
    li a0, 0  # file descriptor = 0 (stdin)
    la a1, input_address #  buffer to write the data
    mv a2, t0  # size (reads a0+1 bytes)
    li a7, 63 # syscall read (63)
    ecall
    
    li a0, 0
    li t1, 1
    digit_loop:
        slli a0, a0, 1
        lb t2, 0(a1)
        addi t2, t2, -48
        add a0, a0, t2

        addi a1, a1, 1

        addi t1, t1, 1
        blt t1, t0, digit_loop

    ret


print_number:
    // a0 = number to print
    // a1 = n of bits

    // Sets a2 to last pos of buffer
    la a2, input_address
    add a2, a2, a1

    li t0, '\n'
    sb t0, 0(a2)

    li t0, 0
    p_loop:
        addi a2, a2, -1
        
        andi t1, a0, 1
        addi t1, t1, 48
        sb t1, 0(a2)

        srai a0, a0, 1
        addi t0, t0, 1
        blt t0, a1, p_loop
        
    li a0, 1  # file descriptor = 1 (stdout)
    addi a2, a1, 1
    la a1, input_address #  buffer to write the data
    li a7, 64 # syscall write (64)
    ecall

    ret

encode:
    srai t0, a0, 3
    
    andi t1, a0, 4
    srai t1, t1, 2

    andi t2, a0, 2
    srai t2, t2, 1
    
    andi t3, a0, 1

    xor t4, t0, t1
    xor t4, t4, t3

    xor t5, t0, t2
    xor t5, t5, t3

    xor t6, t1, t2
    xor t6, t6, t3

    mv a0, t4
    slli a0, a0, 1
    add a0, a0, t5
    slli a0, a0, 1
    add a0, a0, t0
    slli a0, a0, 1
    add a0, a0, t6
    slli a0, a0, 1
    add a0, a0, t1
    slli a0, a0, 1
    add a0, a0, t2
    slli a0, a0, 1
    add a0, a0, t3
        
    ret


decode:
    andi t3, a0, 1
    srai a0, a0, 1
    andi t2, a0, 1
    srai a0, a0, 1
    andi t1, a0, 1
    srai a0, a0, 1
    andi t6, a0, 1
    srai a0, a0, 1
    andi t0, a0, 1
    srai a0, a0, 1
    andi t5, a0, 1
    srai a0, a0, 1
    andi t4, a0, 1

    mv a0, t0
    slli a0, a0, 1
    add a0, a0, t1
    slli a0, a0, 1
    add a0, a0, t2
    slli a0, a0, 1
    add a0, a0, t3

    xor a2, t4, t0
    xor a3, t1, t3
    xor a2, a2, a3

    mv a1, a2

    xor a2, t5, t0
    xor a3, t2, t3
    xor a2, a2, a3

    or a1, a1, a2

    xor a2, t6, t1
    xor a3, t2, t3
    xor a2, a2, a3

    or a1, a1, a2

    ret

_start:

    // Reads 4 bits and encodes
    li a0, 4
    jal read_number
    jal encode
    
    // Prints encoded 7 bits
    li a1, 7
    jal print_number


    // Reads 7 bits and decodes
    li a0, 7
    jal read_number
    jal decode
    
    // Reserves error digit
    mv s0, a1
    
    // Prints 4 bits and 
    li a1, 4
    jal print_number

    // Prints error digit
    mv a0, s0
    li a1, 1
    jal print_number

    jal exit
    
exit:
    li a0, 0
    li a7, 93
    ecall


.bss
input_address: .skip 0x10  # buffer