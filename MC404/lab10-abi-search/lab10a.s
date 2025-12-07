.bss 
input_address: .skip 2
buffer: .skip 10

.text

.globl linked_list_search
.globl puts
.globl gets
.globl atoi
.globl itoa
.globl exit


# int linked_list_search(Node *head_node, int val);
linked_list_search:
    li t6, 0
    1:
        lw t0, 0(a0)
        lw t1, 4(a0)
        lw t2, 8(a0)

        add t0, t0, t1
        beq t0, a1, correct // Found
        
        mv a0, t2 // Update to child
        beqz a0, none 
        addi t6, t6, 1
        beqz x0, 1b

    correct:
        mv a0, t6
        ret
    none:
        li a0, -1
        ret

# void puts ( const char *str );
puts:
    mv t0, a0
    1:
        lbu t1, 0(t0)
        beqz t1, 1f
        addi t0, t0, 1
        j 1b
    1:
    li t1, '\n'
    sb t1, 0(t0)

    mv a1, a0
    li a0, 1  # fd
    sub a2, t0, a1
    addi a2, a2, 1
    li a7, 64 # syscall write (64)
    ecall
    ret

# char *gets ( char *str );
gets:
    mv s1, a0
    mv a1, a0
    1:
        li a0, 0  # file descriptor = 0 (stdin)
        li a2, 1  # size (reads only 1 byte)
        li a7, 63 # syscall read (63)
        ecall

        lbu t0, 0(a1)

        li t1, 0
        li t2, '\n'
        beq t0, t1, 1f
        beq t0, t2, 1f

        addi a1, a1, 1
        beqz x0, 1b
    1:

    sb x0, (a1)

    mv a0, s1
    ret

# int atoi (const char *str);
atoi:
    
    // Skip white spaces
    1:
        lbu t0, 0(a0)
        addi a0, a0, 1

        li t1, 48
        li t2, 58
        blt t0, t1, 1b
        bge t0, t2, 1b
    addi a0, a0, -1

    // Calculate
    li a1, 0
    li a2, 1 // Sinal
    2:
        lb t0, 0(a0)
        addi a0, a0, 1
        li t2, '-'
        beq t0, t2, 3f // Negate
        li t2, '+'
        beq t0, t2, 4f // Normal
        li t2, 48
        blt t0, t2, 2f // Non numeric
        li t2, 58
        bge t0, t2, 2f // Non numeric
        j 4f // Normal
        3:
            li a2, -1
            beqz x0, 2b
        4:
            li t1, 10
            mul a1, a1, t1
            add a1, a1, t0
            addi a1, a1, -48
        j 2b
    2:
    mv a0, a1
    ret

# char *itoa ( int value, char *str, int base );
itoa:
    mv s1, a1
    li t0, 10
    beq a2, t0, handle_negative
    li t0, 16
    beq a2, t0, basic

    handle_negative:
        bge a0, x0, basic
        li t0, '-'
        sb t0, 0(a1)
        addi a1, a1, 1
        
        li t0, 0xffffffff
        sub a0, t0, a0
        addi a0, a0, 1

    basic:    
        li t1, 1
        div t0, a0, a2
        1:
            beqz t0, 1f

            addi t1, t1, 1
            div t0, t0, a2

            beqz x0, 1b
        1:
        // t1 = n of digits
        // t2 = b^(n-1)

        add t2, t1, a1
        sb x0, 0(t2)

        2:
            beqz t1, 2f
            addi t1, t1, -1

            add t2, t1, a1 // t2 = a1 + pos

            rem t3, a0, a2
            div a0, a0, a2


            li t4, 0xa
            bge t3, t4, alpha
            number:
                addi t3, t3, 48
            j store
            alpha:
                addi t3, t3, 55
            store:
            sb t3, 0(t2)

            beqz x0, 2b
        2:
    
    mv a0, s1
    ret

# void exit(int code);
exit:
    li a7, 93
    ecall



