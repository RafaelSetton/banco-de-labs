.set STACKSIZE, 0x10000

.bss

program_stack: .skip STACKSIZE
system_stack: .skip STACKSIZE

.data


.globl _system_time
_system_time: .word 0
gpt_address: .word 0xFFFF0100
midi_address: .word 0xFFFF0300

.text


.globl _start
_start:
    // Initialize System Stack
    la sp, system_stack
    addi sp, sp, STACKSIZE
    csrw mscratch, sp
    
    // Initialize Program Stack
    la sp, program_stack
    addi sp, sp, STACKSIZE

    // Configurar mtvec
    csrr t0, gpt_interrupt_handler
    csrw mtvec, t0

    // Enable Interruptions
    li t0, 0x8
    csrs mstatus, t0

    // Configurar MIE
    li t0, 0x800
    csrs mie, t0

    # Configurar GPT
    LW t0, gpt_address
    li t1, 1
    sw t1, (t0) # Ativa

    li t1, 0x12c
    sw t1, 8(t0) # 300ms

    jal main

    li a0, 0
    li a7, 93
    ecall


.globl gpt_interrupt_handler
gpt_interrupt_handler:
    csrrw sp, mscratch, sp

    addi sp, sp, -8

    sw t0, (sp)
    sw t1, 4(sp)

    # Atualiza o endereço da proxima instrução
    csrr t0, mepc
    addi t0, t0, 4
    csrw mepc, t0

    LW t0, _system_time
    addi t0, t0, 0x12c
    SW t0, _system_time, t1

    LW t0, gpt_address
    li t1, 1
    sw t1, (t0) # Ativa

    li t1, 0x12c
    sw t1, 8(t0) # 300ms

    lw t0, 0(sp)
    lw t1, 4(sp)
    addi sp, sp, 8

    csrrw sp, mscratch, sp

    mret


.globl play_note
play_note:
    LW t0, midi_address

    sw a0, (t0)
    sh a1, 2(t0)
    sb a2, 4(t0)
    sb a3, 5(t0)
    sw a4, 6(t0)

    ret
