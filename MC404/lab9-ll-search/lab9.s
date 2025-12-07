.bss 
input_address: .skip 2
buffer: .skip 10

.text
input:
    li s0, 0
    li t1, 1
    digit:
        li a0, 0  # file descriptor = 0 (stdin)
        la a1, input_address #  buffer to write the data
        li a2, 1  # size (reads only 1 byte)
        li a7, 63 # syscall read (63)
        ecall

        lbu t0, 0(a1)
        
        li t2, 40
        blt t0, t2, end_loop
        li t2, 47
        blt t0, t2, neg
        beqz x0, dig
        neg:
            li t1, -1
            beqz x0, digit
        dig:
            li t3, 10
            mul s0, s0, t3
            add s0, s0, t0
            addi s0, s0, -48
        beqz x0, digit
    end_loop:

    mul a0, s0, t1
    ret

print:
    la a1, buffer
    li t0, -1
    beq a0, t0, m1

    addi a1, a1, 8
    li t5, '\n'
    sb t5, 0(a1)

    store_digit:
        addi a1, a1, -1
        li t1, 10
        rem t2, a0, t1
        div a0, a0, t1

        addi t2, t2, 48
        sb t2, 0(a1)

        blt x0, a0, store_digit
    
    la a2, buffer
    sub a2, a2, a1
    addi a2, a2, 9

    li a0, 1  # fd
    // a1 = buffer
    
    li a7, 64 # syscall write (64)
    ecall
    ret


    m1:
        li t0, '-'
        li t1, '1'
        li t2, '\n'
        sb t0, 0(a1)
        sb t1, 1(a1)
        sb t2, 2(a1)
        li a0, 1  # fd
        // a1 = buffer
        li a2, 3 # 3 bytes
        li a7, 64 # syscall write (64)
        ecall
        ret



.globl _start

_start:
    jal input

    la s1, head_node
    li t6, 0

    loop:

        lw t0, 0(s1)
        lw t1, 4(s1)
        lw t2, 8(s1)

        add t0, t0, t1
        beq t0, a0, correct // Found
        
        mv s1, t2 // Update to child
        beqz s1, none 
        addi t6, t6, 1
        beqz x0, loop

    correct:
        mv a0, t6
        jal print
        jal exit
    
    none:
        li a0, -1
        jal print
        jal exit


exit:
    li a0, 0
    li a7, 93
    ecall
