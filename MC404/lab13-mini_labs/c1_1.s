.data
.globl my_var
my_var: 
    .word 10

.text

.globl increment_my_var
increment_my_var:
    la t0, my_var
    lw t1, (t0)
    addi t1, t1, 1
    sw t1, (t0)
    ret