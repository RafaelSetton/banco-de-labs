.data
base:     .word 0xFFFF0100
newline:    .byte 10

.bss
buffer:     .skip   0x30

.text

.globl _start
_start:


main:
    jal read_op         # le o codigo da operacao
    mv s1, a0           # guarda o codigo da operacao em s1
    jal read_line       # le a operacao
    # switch de selecao da rotina de operacao
    li t0, '1'
    beq s1, t0, op1_b

    li t0, '2'
    beq s1, t0, op2_b

    li t0, '3'
    beq s1, t0, op3_b

    li t0, '4'
    beq s1, t0, op4_b

op1_b:
    jal op1
    j exit

op2_b:
    jal op2
    j exit

op3_b:
    jal op3
    j exit

op4_b:
    jal op4
    j exit

exit:
    la a1, buffer
    jal write_line

    li a0, 0
    li a7, 93              # syscall para sair
    ecall

# fim da main


read_op:
    # rotina de leitura de operacao
    # retorna op (str) em a0
    li a0, 0  # file descriptor = 0 
    addi sp, sp, -4 # abre espaco no stack
    mv a1, sp # guarda o enredeco do stack
    li a2, 2  # size 
    li a7, 63 # syscall read (63)
    ecall

    lbu a0, 0(sp)
    addi sp, sp, 4

    ret


read_line:
    # rotina de leitura de linha
    # armazena a string na pilha
    # retorna o numero de bytes lidos em a0
    li t3, 0
    read_op_loop:
        li a0, 0  # file descriptor = 0 
        addi sp, sp, -4 # abre espaco no stack
        mv a1, sp # guarda o enredeco do stack
        li a2, 1  # size 
        li a7, 63 # syscall read (63)
        ecall
    addi t3, t3, 1
    lbu t0, 0(sp)
    li t1, '\n'
    bne t0, t1, read_op_loop # se o caractere lido for '\n'
    addi sp, sp, 4          # descarta o \n
    #addi t3, t3, -1         # descarta o \n do contador de caracteres
    slli a0, t3, 2
    # o a0 nao conta o \n
    ret

write_line:
    # a0 = numero de bytes
    # a1 = endereço do buffer

    # Com Syscall
    srli a2, a0, 2
    li a0, 1
    li a7, 64
    ecall

    li a0, 1
    la a1, newline
    li a2, 1
    ecall
        
    # Com Serial Port
    # mv t0, a0
    # li t1, 0
    # li t2, 1
    # LW t4, base
    # 1:
    #     // Carrega o byte para t3
    #     lbu t3, (a1)
    #     addi a1, a1, 1
        
    #     // Escreve
    #     sb t3, 0x03(t4)     # escreve na saida
    #     sb t2, 0x02(t4)     # comando de write
        
    #     // Atualiza a iteração
    #     addi t1, t1, 1
    #     blt t1, t0, 1b
    
    # li t3, '\n'
    # sb t3, 0x03(a1)     # escreve na saida
    # sb t2, 0x02(a1)     # comando de write
    ret

op1:
    # rotina de execucao da operacao 1
    # args: recebe numero de caracteres da string em a0
    LW t0, base
    la t4, buffer
    
    add t2, sp, a0       # posiciona t2 no ultimo caractere do frame anterior
    addi t2, t2, -4      # posiciona t2 no primeiro caractere do frame atual

    op1_loop:
        lbu t3, 0(t2)       # le o byte do stack
        sb t3, 0(t4)        # escreve no buffer
        addi t2, t2, -4     # move t2 pro proximo caractere
        addi t4, t4, 1      # move t4 para o prox byte do buffer
        bne t2, sp, op1_loop 
        lbu t3, 0(t2)       # le o ultimo byte do stack
        sb t3, 0(t4)        # escreve no buffer
    ret


op2:
    # rotina de execucao da operacao 1
    # args: recebe numero de caracteres da string em a0
    LW t0, base
    la t4, buffer
    srli t2, a0, 2

    op2_loop:
        lbu t3, 0(sp)       # le o byte do stack
        sb t3, 0(t4)        # guarda no buffer
        addi sp, sp, 4      # desempilha o byte lido
        addi t2, t2, -1     # decrementa o counter
        addi t4, t4, 1      # move o byte do buffer
        bnez t2, op2_loop

    ret


op3:
    # rotina de execucao da operacao 3
    # args: recebe numero de caracteres da string em a0
    li t0, 10           # t0 eh a base
    li t1, 0            # t1 vai ser o acumulador
    mv t2, a0           # t2 eh o conta digitos
    li t3, 0            # t3 eh o intermediario
    # desempilhamos convertendo em decimal
    op3_loop:
        lbu t3, 0(sp)       # carrega o digito em t3
        addi t3, t3, -48    # transforma em int
        mul t1, t1, t0      # shifta o acumulador
        add t1, t1, t3      # soma o digito
        addi sp, sp, 4      # desempilha o byte lido
        addi t2, t2, -1     # decrementa o conta digitos
    bnez t2, op3_loop

    li t0, 16           # t0 eh a base
    li t2, 0            # t2 eh o intermediario
    li t3, 0            # t3 eh o conta digitos
    li t4, 10
    # armazenamos o numero no stack como string (ao contrario)
    op3_loop2:          
        rem t2, t1, t0      # t2 <- resto de numero/base

        blt t2, t4, dmin    # analisa se eh digito <10
        addi t2, t2, 55     # digito <10 soma 48
        j cont
        dmin:
        addi t2, t2, 48     # digito >=10 soma 55
        cont:

        addi sp, sp, -4     # abre o stack
        sb t2, 0(sp)        # guarda o dígito no stack
        addi t3, t3, 1      # soma no conta digitos
        div t1, t1, t0      # t1 <- t1/base
    bnez t1, op3_loop2
    # movemos para o buffer
    LW t0, base
    la t4, buffer
    mv t2, a0
    add t2, sp, a0      # posiciona t2 no primeiro caractere do stack

    op3_loop3:
        lbu t3, 0(sp)       # le o byte do stack
        sb t3, 0(t4)     # escreve no buffer
        addi t2, t2, -4     # move t2 pro proximo caractere
        addi t4, t4, 1      # move t4 para o prox byte
        bne t2, sp, op3_loop3 

    ret


op4:
    # rotina de execucao da operacao 4
    # args: recebe numero de caracteres da string em a0
    li t0, ' '          # identificar o fim do numero pelo espaco
    li t1, 0            # t1 eh o acumulador
    li t4, 10           # t4 eh a base
    addi sp, sp, 4      # ignora o '\n' do stack
    add t2, sp, a0      # posiciona t2 no primeiro caractere do stack
    # calcula o primeiro numero
    op4_loop1:
        lbu t3, 0(t2)       # le o byte do stack
        addi t2, t2, -4     # aponta pro proximo byte
        beq t3, t0, id_op1  # repete ate encontrar o espaco
        addi t3, t3, -48    # converte em inteiro
        mul t1, t1, t4      # multiplica pela base
        add t1, t1, t3      # soma o novo digito
    j op4_loop1
    # o primeiro numero esta em t1 e t2 aponta pro operador
    # id_op1 salva o operador em a2
    id_op1:
    mv a1, t1
    li t1, 0
    li t0, '\n'

    lbu a2, 0(t2)
    addi t2, t2, -4
    # calcula o segundo numero
    op4_loop2:
        lbu t3, 0(t2)       # le o byte do stack
        addi t2, t2, -4     # aponta pro proximo byte
        beq t3, t0, id_op2  # repete ate encontrar o \n
        addi t3, t3, -48    # converte em inteiro
        mul t1, t1, t4      # multiplica pela base
        add t1, t1, t3      # soma o novo digito
    j op4_loop2
    # o segundo numero esta em t1 e t2 aponta pro \n
    # id_op2 identifica o operador. (+=43, -=45, /=47)
    id_op2:
        mv a3, t1
        li t1, 0
        # numero1 -> a1, operador -> a2, numero2 -> a3
        li t1, '-'
        blt a2, t1, ad
        beq a2, t1, su
        blt t1, a2, dv
    ad:
        add t1,a1, a3
        j end_op
    su:
        sub t1, a1, a3
        j end_op
    dv:
        div t1, a1, a3
    end_op:
        # o resultado da operacao (int) esta em t1
        li t0, 10
        LW t3, base
        la t6, buffer
        op4_loop3:
            rem t2, t1, t0
            addi t2, t2, 48
            sb t2, 0(t6)        # guarda no buffer
            addi t6, t6, 1      # move o pointer do buffer
            div t1, t1, t0
            beqz t1, op4_finish
            j op4_loop3
            op4_finish:
    ret