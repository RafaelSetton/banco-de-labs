.text            
.globl _start       

read_numbers:
    li t0, 0
    li t1, 6

    la s11, numbers

    r_digit:
        li t5, 1
        slt t6, t5, t0 
        
        
        li a0, 0  # file descriptor = 0 (stdin)
        la a1, input_address #  buffer to write the data
        li a2, 6  # size (reads 6 bytes)
        sub a2, a2, t6
        li a7, 63 # syscall read (63)
        ecall

        
        sub a1, a1, t6

        lb t2, 1(a1)
        addi a0, t2, -48
        
        li t3, 10
        mul a0, a0, t3
        lb t2, 2(a1)
        addi t2, t2, -48
        add a0, a0, t2
        
        mul a0, a0, t3
        lb t2, 3(a1)
        addi t2, t2, -48
        add a0, a0, t2

        mul a0, a0, t3
        lb t2, 4(a1)
        addi t2, t2, -48
        add a0, a0, t2

        bnez t6, skip
        lb t2, 0(a1)
        li t3, '-'
        beq t2, t3, negate
        jal x0, skip
        negate:
            li t2, -1
            mul a0, a0, t2
        skip:

        slli t2, t0, 2
        add t2, t2, s11
        sw a0, 0(t2)

        addi t0, t0, 1
        blt t0, t1, r_digit

    ret


print_numbers:
    li t0, 0
    li t1, 2
    p_digit:
        slli t2, t0, 2
        add t2, t2, s11
        
        lw t3, 0(t2)
        
        li t6, 10
        la t5, input_address
        
        // Store sign (+ or -)
        blt t3, x0, negate2
        li t4, '+'
        jal x0, skip2
        negate2:
            li t4, -1
            mul t3, t3, t4
            li t4, '-'
        skip2:
        sb t4, 0(t5)

        // 4th Digit
        rem t2, t3, t6
        addi t2, t2, 48
        sb t2, 4(t5)
        div t3, t3, t6
        
        // 3rd Digit
        rem t2, t3, t6
        addi t2, t2, 48
        sb t2, 3(t5)
        div t3, t3, t6

        // 2nd Digit
        rem t2, t3, t6
        addi t2, t2, 48
        sb t2, 2(t5)
        div t3, t3, t6
        
        // 1st Digit
        rem t2, t3, t6
        addi t2, t2, 48
        sb t2, 1(t5)
        div t3, t3, t6
        
        
        // Adds a ' ' in the first case, and '\n' in the last
        beqz t0, space 
        li a1, '\n'
        jal x0, end
        space:
            li a1, ' '
        end:
        sb a1, 5(t5)

        li a0, 1  # file descriptor = 1 (stdout)
        la a1, input_address #  buffer to write the data
        li a2, 6  # size (writes 6 bytes)
        li a7, 64 # syscall write (64)
        ecall

        addi t0, t0, 1
        blt t0, t1, p_digit

    ret


calculate:
    // (a0, a1, a2, a3, a4, a5) = (yb, xc, ta, tb, tc, t)

    li t0, 3
    li t1, 10

    // da = (t-ta)*3/10 [ a2 = (a5-a2)*t0/t1 ]
    // a2 = da^2
    sub a2, a5, a2
    mul a2, a2, t0
    div a2, a2, t1
    mul a2, a2, a2

    // db = (t-tb)*3/10 [ a3 = (a5-a3)*t0/t1 ]
    // a3 = db^2
    sub a3, a5, a3
    mul a3, a3, t0
    div a3, a3, t1
    mul a3, a3, a3
    
    // dc = (t-tc)*3/10 [ a4 = (a5-a4)*t0/t1 ]
    // a4 = dc^2
    sub a4, a5, a4
    mul a4, a4, t0
    div a4, a4, t1
    mul a4, a4, a4

    // x = (da^2-dc^2+xc^2)/xc/2 [ t0 = (a2-a4+a1*a1) / a1 << 1 ]
    sub t0, a2, a4
    mul t2, a1, a1
    add t0, t0, t2
    div t0, t0, a1
    srai t0, t0, 1

    // y = (da^2-db^2+yb^2)/yb/2 [ t1 = (a2-a3+a0*a0) / a0 << 1 ]
    sub t1, a2, a3
    mul t2, a0, a0
    add t1, t1, t2
    div t1, t1, a0
    srai t1, t1, 1

    // a0 = x; a1 = y
    mv a0, t0
    mv a1, t1
    ret



_start:

    jal read_numbers

    // Perform operations    
    la s0, numbers
    lw a0, 0(s0)
    lw a1, 4(s0)
    lw a2, 8(s0)
    lw a3, 12(s0)
    lw a4, 16(s0)
    lw a5, 20(s0)

    jal calculate

    sw a0, 0(s0)
    sw a1, 4(s0)

    // Print int
    
    jal print_numbers
    
    jal exit
    


exit:
    li a0, 0
    li a7, 93
    ecall


.bss
input_address: .skip 0x10  # buffer
numbers: .skip 0x20