.bss
stack:   .skip 1024
program_stack:   .skip 1024

.text
.align 4
int_handler:
  # ##### Syscall and Interrupts handler ######

  # <= Implement your syscall handler here
  # Salvar o contexto atual
  csrrw sp, mscratch, sp
  addi sp, sp, -16
  sw t0, 0(sp)
  sw t1, 4(sp)

  # guarda o endereço da proxima instrução após a interrupção
  csrr t0, mepc
  addi t0, t0, 4
  csrw mepc, t0

  # direciona para tratar a excessão
  li t0, 10
  beq a7, t0, set_engine_and_steering

  li a0, -1                 # excessão não tratada
  j finish

  # trata a excessão
  set_engine_and_steering:
  li t0, 0xFFFF0100          # carrega o endereço 
  sb a1, 0x20(t0)            # Escreve a1 no endereço base + 0x20 (conf volante)
  sb a0, 0x21(t0)            # Escreve a0 no endereço base + 0x21 (conf acel)

  li a0, 0                  # excessão tratada com sucesso
  j finish

  finish:
  # recupera o contexto
  lw t0, 0(sp)
  lw t1, 4(sp)
  addi sp, sp, 16
  csrrw sp, mscratch, sp
  mret           # Recover remaining context (pc <- mepc)


.globl _start
_start:

  la t0, int_handler  # Load the address of the routine that will handle interrupts
  csrw mtvec, t0      # (and syscalls) on the register MTVEC to set
                      # the interrupt array.

  # Write here the code to change to user mode and call the function
  # user_main (defined in another file). Remember to initialize
  # the user stack so that your program can use it.

  # inicializa o stack
  la sp, stack          # inicializa o sp
  addi sp, sp, 1023     # posiciona sp no fim do stack

  # inicializa o program stack
  la t0, program_stack
  addi t0, t0, 1023
  csrw mscratch, t0

  # configurar mtvec
  la t0, int_handler      # carrega o endereço base
  csrw mtvec, t0

  # Configurar mstatus 
  csrr t0, mstatus
  ori t0, t0, 0x8         # seta MIE = 1
  csrw mstatus, t0        # salva em mstatus

  la t0, user_main
  csrw mepc, t0

  mret



.globl control_logic
control_logic:
  # implement your control logic here, using only the defined syscalls
  loop:
  li a0, 1
  li a1, -17
  li a7, 10
  ecall
  j loop

