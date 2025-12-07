.text
.globl user_main
user_main:
  jal control_logic
infinite_loop:
  j infinite_loop
