.bss
buffer: .skip 0x40010

.data
input_file: .asciz "image.pgm"

.text

read_file:
    // Open File
    li a0, -100
    la a1, input_file    # address for the file path
    li a2, 0             # flags (0: rdonly, 1: wronly, 2: rdwr)
    // li a3, 0             # mode
    li a7, 56          # syscall open
    ecall

    mv s0, a0
    // Read
    
    la a1, buffer #  buffer to write the data
    li a2, 0x40010  # size (reads  bytes)
    li a7, 63 # syscall read (63)
    ecall

    lb t0, 0(a1)
    lb t1, 1(a1)
    lb t2, 2(a1)

    // Close File
    mv a0, s0
    li a7, 57            # syscall close
    ecall
    ret

print:
    li a0, 1  # file descriptor = 1 (stdout)
    la a1, buffer #  buffer to write the data
    li a2, 10 # 10 bytes
    li a7, 64 # syscall write (64)
    ecall
    ret

make_color:
    // s2 width
    // s3 height
    // s4 row
    // s5 col
    
    addi t3, s3, -1
    addi t2, s2, -1
    beq t3, s4, black
    beq t2, s5, black
    beqz s5, black
    beqz s4, black
    beqz x0, calc
    black:
        li a0, 0xff
        ret
    calc:

    // Multiply matrix
    lbu t0, 0(s1)
    slli a0, t0, 3

    // Mid line
    lbu t0, -1(s1)
    sub a0, a0, t0
    lbu t0, 1(s1)
    sub a0, a0, t0

    // Top line
    sub t1, s1, s2

    lbu t0, -1(t1)
    sub a0, a0, t0
    lbu t0, 0(t1)
    sub a0, a0, t0
    lbu t0, 1(t1)
    sub a0, a0, t0

    // Bottom line
    add t1, s1, s2

    lbu t0, -1(t1)
    sub a0, a0, t0
    lbu t0, 0(t1)
    sub a0, a0, t0
    lbu t0, 1(t1)
    sub a0, a0, t0


    // Mantem entre 0 e 255
    blt a0, x0, zerar
    li t0, 255
    bge a0, t0, full
    beqz x0, skip
    zerar:
    li a0, 0
    beqz x0, skip
    full:
    li a0, 255
    skip:

    // Make color

    mv t0, a0
    
    slli t0, t0, 8
    add t0, t0, a0

    slli t0, t0, 8
    add t0, t0, a0

    slli t0, t0, 8
    addi t0, t0, 0xff

    mv a0, t0
    ret
    

get_num:
    li t2, '\n'
    li t3, ' '
    li a0, 0
    begin:
        lb t0, 0(s1)
        beq t0, t2, end
        beq t0, t3, end
        addi t0, t0, -48
        li t1, 10
        mul a0, a0, t1
        add a0, a0, t0
        addi s1, s1, 1
        beqz x0, begin

    end:
    addi s1, s1, 1
    ret


.globl _start

_start:

    jal read_file
    
    la s1, buffer
    addi s1, s1, 3

    jal get_num
    mv s2, a0 // Width

    jal get_num
    mv s3, a0 // Height

    mv a0, s2
    mv a1, s3
    li a7, 2201
    ecall

    // Começo das cores
    addi s1, s1, 4

    // Main
    li s4, 0
    row_loop:
        li s5, 0
        col_loop:
            jal make_color
            mv a2, a0
            mv a0, s5
            mv a1, s4
            li a7, 2200 # syscall setPixel (2200)
            ecall

            addi s1, s1, 1

            addi s5, s5, 1
            blt s5, s2, col_loop
        addi s4, s4, 1
        blt s4, s3, row_loop       

    li a0, 5
    li a1, 5
    li a7, 2202
    ecall


    jal exit

exit:
    li a0, 0
    li a7, 93
    ecall
