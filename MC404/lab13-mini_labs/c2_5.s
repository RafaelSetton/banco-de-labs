.text

.globl node_creation
node_creation:
   addi sp, sp, -16
   sw ra, 8(sp)
   
   li t0, 30
   sw t0, (sp)
   
   li t0, 25
   sb t0, 4(sp)
   
   li t0, 64
   sb t0, 5(sp)
   
   li t0, -12
   sh t0, 6(sp)

   mv a0, sp
   jal mystery_function

   lw ra, 8(sp)
   addi sp, sp, 16
   ret