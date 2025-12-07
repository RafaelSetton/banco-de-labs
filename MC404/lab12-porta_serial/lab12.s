.bss

buffer: .skip 0x30

.text
.equ SERIAL_PORT, 0xFFFF0100
.equ WRITE, SERIAL_PORT + 0x0
.equ BYTE_TO_WRITE, SERIAL_PORT + 0x1
.equ READ, SERIAL_PORT + 0x2
.equ BYTE_READ, SERIAL_PORT + 0x3


# char read_byte();
read_byte: 
    // Calls Read
    li t0, READ
    li t1, 1
    sb t1, (t0)

    // Waits for byte to be set to 0
    1:
        lbu t1, (t0)
        bnez t1, 1b

    // Loads byte from Serial Port
    li t0, BYTE_READ
    lbu a0, (t0)
    ret

# void write_byte(char c);
write_byte: // Recieves the byte at a0
    // Stores byte in Serial Port
    li t0, BYTE_TO_WRITE
    sb a0, (t0)
    
    // Calls Write
    li t0, WRITE
    li t1, 1
    sb t1, (t0)
    
    // Waits for byte to be set to 0
    1:
        lb t1, (t0)
        bnez t1, 1b
    ret

# char *read_line();
read_line: 
    // Saves ra
    addi sp, sp, -16
    sw ra, (sp)
    sw s1, 4(sp)

    // Reads bytes until '\n'
    la s1, buffer
    1:
        jal read_byte
        sb a0, (s1)
        addi s1, s1, 1
        li t0, '\n'
        bne t0, a0, 1b
    
    // Loads ra, a0 and returns
    lw ra, (sp)
    lw s1, 4(sp)
    addi sp, sp, 16
    la a0, buffer
    ret

# void write_line(char *str)
write_line:
    // Saves ra
    addi sp, sp, -16
    sw ra, (sp)
    sw s1, 4(sp)
    sw s2, 8(sp)

    // Reads bytes until '\n'
    mv s1, a0
    1:
        lbu s2, (s1)
        mv a0, s2
        jal write_byte
        addi s1, s1, 1
        li t0, '\n'
        bne t0, s2, 1b
    
    // Loads ra, a0 and returns
    lw ra, (sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    addi sp, sp, 16
    ret

# char * reverse(char *str);
reverse:
    mv t0, sp
    mv t1, a0
    1:
        lbu t2, (t1)
        addi t1, t1, 1
        li t3, '\n'
        beq t2, t3, 1f
        addi t0, t0, -1
        sb t2, (t0)
        j 1b
    1:
    mv t1, a0
    2:
        lbu t2, (t0)
        sb t2, (t1)
        addi t0, t0, 1
        addi t1, t1, 1
        blt t0, sp, 2b
    ret

# int atoi(char *str);
atoi:
    
    // Skip white spaces
    1:
        lbu t0, 0(a0)
        addi a0, a0, 1

        li t1, '-'
        beq t0, t1, 1f
        li t1, 48
        li t2, 58
        blt t0, t1, 1b
        bge t0, t2, 1b
    1:
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
    mul a0, a1, a2
    ret

# char *itoa(int value, char *str, int base );
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
        li t0, '\n'
        sb t0, 0(t2)

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

# (int, char, int) split(char *str);
split: // Returns (n1, op, n2) in (a0, a1, a2)
    addi sp, sp, -16
    sw ra, 12(sp)
    sw a0, (sp)
    jal atoi
    sw a0, 4(sp)
    lw a0, (sp)

    1:
        lbu t0, (a0)
        addi a0, a0, 1
        li t1, ' '
        bne t0, t1, 1b
    
    lbu t0, (a0) 
    sb t0, 8(sp)

    addi a0, a0, 2
    jal atoi

    mv a2, a0
    lbu a1, 8(sp)
    lw a0, 4(sp)
    lw ra, 12(sp)
    ret

# int compute(int n1, char op, int n2);
compute:
    li t0, '+'
    beq a1, t0, plus
    li t0, '-'
    beq a1, t0, minus
    li t0, '*'
    beq a1, t0, mult
    li t0, '/'
    beq a1, t0, divi

    plus:
        add a0, a0, a2
        ret
    minus:
        sub a0, a0, a2
        ret
    mult:
        mul a0, a0, a2
        ret
    divi:
        div a0, a0, a2
        ret

.globl _start

_start:
    jal read_line
    lbu s1, (a0)
        
    jal read_line

    li t1, '1'
    li t2, '2'
    li t3, '3'
    beq s1, t1, exit
    beq s1, t2, 2f
    beq s1, t3, 3f
    j 4f

    2:
        jal reverse
        jal exit
    3:
        jal atoi
        la a1, buffer
        li a2, 16
        jal itoa
        jal exit
    4:
        jal split
        jal compute
        la a1, buffer
        li a2, 10
        jal itoa
        jal exit

exit:
    jal write_line
    li a0, 0
    li a7, 93
    ecall
