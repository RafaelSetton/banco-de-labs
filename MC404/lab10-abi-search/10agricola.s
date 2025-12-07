.data
newline:  .ascii "\n"

.text

.globl gets
gets:
    mv a1, a0
    mv t0, a0

    li t1, '\n'       # carrega \n em t1
read_loop:
    li a0, 0  # file descriptor = 0 
    #la a1, input #  buffer to write the data
    li a2, 1  # size 
    li a7, 63 # syscall read (63)
    ecall
    
    lbu t2, 0(a1)
    beq t2, t1, finish_loop

    addi a1, a1, 1  # incrementa o pointer do input
    j read_loop

finish_loop:
    li t2, 0 
    sb t2, 0(a1) # armazena \0 no fim da string
    mv a0, t0 # retorna o pointer do buffer
ret


.globl puts
puts:
    mv a1, a0

print_loop:
    lbu t0, 0(a1)
    beq t0, zero, end_loop

    li a0, 1  # file descriptor = 1
    #la a1, output #  buffer to write the data
    li a2, 1  # size 
    li a7, 64 # syscall read (63)
    ecall

    addi a1, a1, 1  # incrementa o pointer do input
    j print_loop

end_loop:
    li a0, 1  # file descriptor = 1
    la a1, newline #  buffer to write the data
    li a2, 1  # size 
    li a7, 64 # syscall read (63)
    ecall
ret

.globl atoi
atoi: # funcao que recebe a entrada numerica str e retorna int em a0
# args: pointer pro buffer em a0
# return: int em a0
    li t1, 0              # Inicializa t1 como 0 
    li t3, 10             # t3 = '\n'
    li t4, 0              # limpa t4 para operar
    li t5, '-'             # t5 = "-"
    # Verifica se o primeiro caractere é um sinal
    lb t2, 0(a0)          # Carrega o primeiro caractere
    beq t2, t5, negative  
    j convert
negative:
    li t1, 1              # resultado deve ser negativo
    addi a0, a0, 1        # Avança para o próximo caractere
convert:
    lb t2, 0(a0)          # Carrega o caractere atual
    beqz t2, signal       # Se o caractere for '\0', termina a conversão
    addi t2, t2, -48      # t2 = t2 - '0' (converte para inteiro)
    mul t4, t4, t3        # Multiplica o resultado atual por 10
    add t4, t4, t2        # Adiciona o valor do dígito atual
    addi a0, a0, 1        # Avança para o próximo caractere
    j convert             # Repete o laço
signal:
    beq t1, zero, end     # Se não for negativo, pula
    li t0, -1
    mul t4, t4, t0            # Torna o resultado negativo
end:
    mv a0, t4             # carrega o resultado em a0
ret                    

.globl linked_list_search
linked_list_search:
# agrs: pointer pro head_node em a0 e val em a1
# return: resultado em a0 (node se encontrado, -1 se nao)
mv t1, a0       # t1 aponta para o primeiro nó da lista ligada
li a3, 0
loop:
    li t3, 0

    lw t2, 0(t1)
    add t3, t3, t2
    lw t2, 4(t1)
    add t3, t3, t2
    lw t2, 8(t1)

    beq t3, a1, found # if val1 + val2 = val -> found

    beqz t2, not_found # else if t2 = NULL -> not found

    mv t1, t2
    addi a3, a3, 1
    j loop # else loop

found:
    mv a0, a3
    j finish
not_found:
    li a0, -1
finish:
ret

.globl itoa
itoa: # funcao que recebe o valor int e converte em string
# args: valor em a0, pointer pro buffer em a1, base em a2
# return: pointer pro buffer
    li t1, 0                # verificador de numero negativo
    mv t2, a0               # valor
    mv t6, sp               # t6 faz papel de frame pointer
    mv t3, sp               

    bge a0, t1, convert_loop# if positivo -> convert loop
    neg t2, t2              # else -> torna positivo
    li t1, -1               # t1 = -1 -> nmr negativo

convert_loop:
    rem t4, t2, a2      # t4 = ultimo digito
    addi t4, t4, 48     # converte em int
    
    addi sp, sp, -1     # incrementa o stack
    sb t4, 0(sp)        # guarda o byte no stack

    div t2, t2, a2          # t2 = t2 / 10
    bnez t2, convert_loop

    mv t4, a1           # coloca o pointer pro buffer em t4

    beqz t1, reverse_loop # se o numero eh positivo converte
    li t5, 45            # else faz o negativo
    sb t5, 0(t4)        # guarda o sinal no output
    addi t4, t4, 1      # incrementa o pointer
    
reverse_loop:
    lbu t5, 0(sp)        # coleta o byte no buffer
    sb t5, 0(t4)        # posiciona no output
    addi sp, sp, 1     # decrementa o pointer do buffer
    addi t4, t4, 1      # incrementa no output
    blt sp, t3, reverse_loop

    mv sp, t6
    mv a0, a1
ret                 

.globl exit
exit:
# codigo de saida em a0
    li a7, 93              # syscall para sair
    ecall
