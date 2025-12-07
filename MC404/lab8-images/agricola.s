.data
newline:    .asciz "\n"            # Nova linha para saída
space:      .asciz " "             # Espaço usado como delimitador
input_file: .asciz "image.pgm"     # Nome do arquivo
error_msg: .asciz "Erro ao abrir arquivo\n"

.bss
buffer:     .skip 262160           # Buffer para armazenar a entrada (512 * 512)
output:     .skip 1048640          # buffer para armazenar a saida (4 * 512 * 512)
type:       .skip 4
sizex:      .skip 4
sizey:      .skip 4
alpha:      .skip 4

.text
.global _start
_start: # Início do programa
    la s3, buffer                  # Carregar endereço do buffer para a leitura da imagem

    # Chama rotina para abrir o arquivo
    jal open                       # Abre o arquivo

    # Verifica se o arquivo foi aberto corretamente
    bltz a0, error_open            # Se a0 < 0, erro ao abrir o arquivo

    # Salva o descritor de arquivo (fd) retornado pela syscall open
    mv s0, a0                      # Armazena o descritor de arquivo (fd) em s0
    # Chama rotina de leitura
    jal read                       # Lê os dados do arquivo

    # Chama rotina para fechar o arquivo
    mv a0, s0                      # Passa o descritor de arquivo para o fechamento
    jal close                      # Fecha o arquivo

    # converte as strings de size em inteiros
    jal convert_int

    jal rgba_translate

    # chama rotina para imprimir o arquivo
    jal print

# Finaliza o programa
li a7, 93                      # Código de saída (syscall exit)
li a0, 0                       # Código de saída 0
ecall                          # Chama o sistema operacional para encerrar

error_open:
    # Exibe mensagem de erro
    li a0, 1                       # Saída padrão (stdout)
    la a1, error_msg               # Carrega a mensagem de erro
    li a2, 19                      # Comprimento da mensagem de erro
    li a7, 64                      # Syscall write para escrever a mensagem
    ecall                          # Chama o sistema operacional
    j exit_program                 # Sai do programa

exit_program:
    li a7, 93                      # Syscall exit
    ecall                          # Termina o programa

# Rotina de leitura dos dados do arquivo
read:
    # Leitura do tipo de arquivo
    mv a0, s0                      # Carrega o descritor de arquivo (fd)
    la a1, type                    # Carrega o endereço do buffer para o tipo de arquivo
    li a2, 3                       # Lê 3 bytes (P5)
    li a7, 63                      # Chamada de sistema para read (syscall read)
    ecall                          # Invoca o sistema operacional

    # Leitura do tamanho X
    mv a0, s0                      # Carrega o descritor de arquivo (fd)
    la a1, sizex                   # Carrega o endereço do buffer para o sizex
    li a2, 4                       # Lê 4 bytes do sizex
    li a7, 63                      # Syscall read
    ecall

    # Leitura do tamanho Y
    mv a0, s0                      # Carrega o descritor de arquivo (fd)
    la a1, sizey                   # Carrega o endereço do buffer para o sizey
    li a2, 4                       # Lê 4 bytes do sizey
    li a7, 63                      # Syscall read
    ecall

    # Leitura do valor alpha
    mv a0, s0                      # Carrega o descritor de arquivo (fd)
    la a1, alpha                   # Carrega o endereço do buffer para o alpha
    li a2, 4                       # Lê 4 bytes do alpha (por exemplo, valor 255)
    li a7, 63                      # Syscall read
    ecall

    # Leitura da imagem
    mv a0, s0                      # Carrega o descritor de arquivo (fd)
    la a1, buffer                  # Carrega o endereço do buffer para os dados da imagem
    li a2, 262160                  # Lê 512 * 512 bytes da imagem
    li a7, 63                      # Syscall read
    ecall
ret


convert_int:
# converte os valores em inteiros e salva
li t1, 10
li t2, 100
    li t4, 0
    la t0, sizex        # carrega o endereco do tamanho x em t0

    lb t3, 2(t0)        # carrega a unidade em t3
    addi t4, t3, -48    # converte em int e salva em t4

    lb t3, 1(t0)        # carrega a dezena em t3
    addi t3, t3, -48    # converte em int
    mul t3, t3, t1      # multiplica por 10
    add t4, t3, t4      # soma em t4

    lb t3, 0(t0)        # carrega a centena em t3
    addi t3, t3, -48    # converte em int
    mul t3, t3, t2      # multiplica por 100 
    add t4, t3, t4      # soma em t4
mv s1, t4           # salva o tamanho x em s1

    li t4, 0
    la t0, sizey        # carrega o endereco do tamanho y em t0
    lb t3, 2(t0)        # carrega a unidade em t3
    addi t4, t3, -48    # converte em int e salva em t4

    lb t3, 1(t0)        # carrega a dezena em t3
    addi t3, t3, -48    # converte em int
    mul t3, t3, t1      # multiplica por 10
    add t4, t3, t4      # soma em t4

    lb t3, 0(t0)        # carrega a centena em t3
    addi t3, t3, -48    # converte em int
    mul t3, t3, t2      # multiplica por 100 
    add t4, t3, t4      # soma em t4
mv s2, t4           # salva o tamaho y em s2

    li t4, 0
    la t0, alpha        # carrega o endereco do alpha em t0

    lb t3, 2(t0)        # carrega a unidade em t3
    addi t4, t3, -48    # converte em int e salva em t4

    lb t3, 1(t0)        # carrega a dezena em t3
    addi t3, t3, -48    # converte em int
    mul t3, t3, t1      # multiplica por 10
    add t4, t3, t4      # soma em t4

    lb t3, 0(t0)        # carrega a centena em t3
    addi t3, t3, -48    # converte em int
    mul t3, t3, t2      # multiplica por 100 
    add t4, t3, t4      # soma em t4
mv s4, t4           # salva o alpha em s4
# s1: sizex, s2: sizey, s3: buffer, s4: alpha
ret


rgba_translate:
    la t0, buffer       # carrega o endereço do buffer. ponteiro para os bytes da entrada
    la t1, output       # carrega o endereço do output
    mul t4, s1, s2      # número máximo de caracteres do buffer

store_loop:
    li t3, 0            # zera t3

    lbu t2, 0(t0)       # carrega o byte unsigned do buffer em t2 (R, G e B são iguais)
    
    # Monta o valor RGBA
    slli t2, t2, 8      # forma B
    or t3, t3, t2       # adiciona B em t3

    # Carrega o mesmo valor para G
    slli t2, t2, 8      # forma G
    or t3, t3, t2       # adiciona G em t3

    # Carrega o mesmo valor para B
    slli t2, t2, 8      # forma R
    or t3, t3, t2       # adiciona R em t3

    # Define o valor de Alpha 
    ori t3, t3, 0x000000FF  # adiciona A em t3

    sw t3, 0(t1)        # armazena o valor RGBA em output

    addi t0, t0, 1      # incrementa o contador de caracteres do buffer
    addi t1, t1, 4      # incrementa o contador de caracteres do output

blt t0, t4, store_loop  # verifica se ainda há bytes a processar
ret


print: # rotina de retorno de pixel
# set canvas size - coordenadas x e y em a0 e a1 - valor do pixel em a2
mv a0, s1 
mv a1, s2 
li a7, 2201
ecall

# print pixels - s1: comprimento da linha, s2: numero de linhas.
la t0, output       # carrega o endereco do output em t0

li t2, 0            # contador de linhas

print_line:
    li t3, 0            # contador de caracteres

    print_pixel: # subrotina que imprime o pixel apontado por t4
        
        # realiza a impressao do byte apontado
        mv a0, t3 #coordx
        mv a1, t2 #coordy
        lw a2, 0(t0) #output
        li a7, 2200
        ecall

        addi t0, t0, 4      # incrementa o ponteiro do output
        addi t3, t3, 1      # incrementa o contador de caracteres
    blt t3, s1, print_pixel # se x < numero de caracteres -> print prox pixel
    addi t2, t2, 1      # incrementa o contador do numero de linhas
blt t2, s2, print_line # se y < numero de linhas -> print prox linha

# Set scaling
li a0, 2 #horizontal scaling
li a1, 2 #vertical scaling
li a7, 2202 #(syscall number)
ecall

ret


# Rotina de abertura de arquivo
open:
    la a0, input_file              # Endereço do caminho do arquivo
    li a1, 0                       # Flags (0: rdonly)
    li a2, 0                       # Modo (não utilizado para leitura)
    li a7, 1024                    # Syscall open 
    ecall                          
ret


# Rotina de fechamento de arquivo
close:
    li a7, 57                      # Syscall close
    ecall                          # Fecha o arquivo
ret