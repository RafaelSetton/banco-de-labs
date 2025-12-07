.equ STACKSIZE, 0x1000
.equ CAR_BASE_ADDRESS, 0xFFFF0100
.bss

program_stack: .skip STACKSIZE
system_stack: .skip STACKSIZE

.text

.equ STEER, CAR_BASE_ADDRESS + 0x20
.equ GAS, CAR_BASE_ADDRESS + 0x21

.align 4

int_handler:
  # Salvar Contexto
  csrrw sp, mscratch, sp
  addi sp, sp, -16

  sw t0, (sp)
  sw t1, 4(sp)

  # Atualizar MEPC
  csrr t0, mepc  
  addi t0, t0, 4 
  csrw mepc, t0  

  # Verifica se é uma ecall
  csrr t0, mcause
  bltz t0, end # É interrupção Externa
  andi t0, t0, 0x3f # Isola EXCCODE
  li t1, 8
  beq t0, t1, trata_ecall # EXCCODE == 8: ecall
  j end

  # Trata a chamada
  trata_ecall:
    li t0, 10
    beq a7, t0, set_engine_and_steering
    li a0, -1
    j end
  
  set_engine_and_steering:
    li t0, GAS
    sb a0, (t0)
    li t0, STEER
    sb a1, (t0)
    li a0, 0
    j end

  end:
  # Recuperar Contexto
  lw t0, (sp)
  lw t1, 4(sp)

  addi sp, sp, 16
  csrrw sp, mscratch, sp

  mret           


.globl _start
_start:  
  li t0, STACKSIZE

  // Initialize System Stack
  la sp, system_stack
  add sp, sp, t0
  csrw mscratch, sp
  
  // Initialize Program Stack
  la sp, program_stack
  add sp, sp, t0

  // Configurar mtvec
  la t0, int_handler
  csrw mtvec, t0

  // Enable Interruptions
  li t0, 0x8
  csrs mstatus, t0

  la t0, user_main
  csrw mepc, t0

  mret

.globl control_logic
control_logic:
  li a0, 1
  li a1, -15
  li a7, 10
  ecall
  j control_logic
