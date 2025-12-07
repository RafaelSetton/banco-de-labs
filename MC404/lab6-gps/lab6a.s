.data
newline: .string "\n"
string:  .string "Hello! It works!!!\n"

.text            
.globl _start       

read_numbers:
    li t0, 0
    li t1, 4

    la s11, numbers

    r_digit:
        li a0, 0  # file descriptor = 0 (stdin)
        la a1, input_address #  buffer to write the data
        li a2, 5  # size (reads only 1 byte)
        li a7, 63 # syscall read (63)
        ecall
        lb t2, 0(a1)
        addi a0, t2, -48
        
        li t3, 10
        mul a0, a0, t3
        lb t2, 1(a1)
        addi t2, t2, -48
        add a0, a0, t2
        
        mul a0, a0, t3
        lb t2, 2(a1)
        addi t2, t2, -48
        add a0, a0, t2

        mul a0, a0, t3
        lb t2, 3(a1)
        addi t2, t2, -48
        add a0, a0, t2

        slli t2, t0, 2
        
        add t2, t2, s11
        sw a0, 0(t2)

        addi t0, t0, 1
        blt t0, t1, r_digit

    ret


print_numbers:
    li t0, 0
    li t1, 4
    p_digit:
        slli t2, t0, 2
        add t2, t2, s11
        
        lw t3, 0(t2)
        
        li t6, 10
        la t5, input_address
        
        // 4th Digit
        rem t2, t3, t6
        addi t2, t2, 48
        sb t2, 3(t5)
        div t3, t3, t6
        
        // 3rd Digit
        rem t2, t3, t6
        addi t2, t2, 48
        sb t2, 2(t5)
        div t3, t3, t6

        // 2nd Digit
        rem t2, t3, t6
        addi t2, t2, 48
        sb t2, 1(t5)
        div t3, t3, t6
        
        // 1st Digit
        rem t2, t3, t6
        addi t2, t2, 48
        sb t2, 0(t5)
        div t3, t3, t6
        

        li t6, 3
        
        // Adds a ' ' in the first 3 cases, and '\n' in the last
        blt t0, t6, space 
        li a1, '\n'
        jal x0, end
        space:
            li a1, ' '
        end:
        sb a1, 4(t5)

        li a0, 1  # file descriptor = 1 (stdout)
        la a1, input_address #  buffer to write the data
        li a2, 5  # size (reads only 1 byte)
        li a7, 64 # syscall read (64)
        ecall

        addi t0, t0, 1
        blt t0, t1, p_digit

    ret

// 1234 5678 9123 4567
_start:

    jal read_numbers

    // Perform operations
    li s0, 0
    li s1, 4
    main:
        slli t0, s0, 2
        la t1, numbers
        add s2, t0, t1
        lw a0, 0(s2)

        beqz a0, next

        li t0, 0
        li t1, 15
        srai t2, a0, 1
        for:
            div t3, a0, t2
            add t2, t2, t3
            srai t2, t2, 1

            addi t0, t0, 1
            blt t0, t1, for

        mv a0, t2

        next:
        sw a0, 0(s2)
        addi s0, s0, 1
        blt s0, s1, main

    // Print int
    
    jal print_numbers
    
    jal exit
    


exit:
    li a0, 0
    li a7, 93
    ecall


.bss
input_address: .skip 0x10  # buffer
numbers: .skip 0x10