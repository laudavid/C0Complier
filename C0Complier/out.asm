.data
global_var: .space 4808
str_0: .asciiz "Test start:"
str_1: .asciiz "Test printf:"
str_2: .asciiz "This is a string."
str_3: .asciiz "X*2+x/3 "
str_4: .asciiz "Test scanf:"
str_5: .asciiz "Please input int a:"
str_6: .asciiz "int a is "
str_7: .asciiz "Please in\tput char x:"
str_8: .asciiz "char x is "
str_9: .asciiz "Test charcomp:"
str_10: .asciiz "Test calculate:"
str_11: .asciiz "a: "
str_12: .asciiz "b: "
str_13: .asciiz "a b add: "
str_14: .asciiz "a b sub: "
str_15: .asciiz "a b mul: "
str_16: .asciiz "a b div: "
str_17: .asciiz "Test strrev:"
str_18: .asciiz "Please input N, n:"
str_19: .asciiz "Test factorial N: "
str_20: .asciiz "Test fibonacci n: "
str_21: .asciiz "Please input 10 numbers:"
str_22: .asciiz "Test sort:"
str_23: .asciiz "Test finished."


.text
addiu $fp, $sp, -4
addiu $sp, $sp, -28
jal func_9
li $v0, 10
syscall


func_1:
li $t0, 0
sw $t0, -0($fp)
label_0:
lw $t0, -0($fp)
li $t1, 100
li $t2, 2
div $t1, $t1, $t2
li $t2, 1
addu $t1, $t1, $t2
slt $t0, $t0, $t1
beq $t0, $0, label_1
lw $t0, -0($fp)
li $t1, 0
sll $t0, $t0, 2
sw $t1, global_var+8($t0)
li $t0, 100
li $t1, 1
subu $t0, $t0, $t1
lw $t1, -0($fp)
subu $t0, $t0, $t1
li $t1, 0
sll $t0, $t0, 2
sw $t1, global_var+8($t0)
lw $t0, -0($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -0($fp)
j label_0
label_1:
jr $ra


func_2:
lw $t0, -0($fp)
li $t1, 0
seq $t1, $t0, $t1
beq $t1, $0, label_3
li $t0, 0
move $v0, $t0
jr $ra
j label_2
label_3:
li $t1, 1
seq $t1, $t0, $t1
beq $t1, $0, label_4
li $t0, 1
move $v0, $t0
jr $ra
j label_2
label_4:
lw $t0, -0($fp)
sll $t0, $t0, 2
lw $t0, global_var+8($t0)
li $t1, 0
seq $t0, $t0, $t1
beq $t0, $0, label_5
lw $t0, -0($fp)
lw $t1, -0($fp)
li $t2, 1
subu $t1, $t1, $t2
addiu $sp, $sp, -4
sw $t1, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 8
jal func_2
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 12
move $t1, $v0
lw $t2, -0($fp)
li $t3, 2
subu $t2, $t2, $t3
addiu $sp, $sp, -4
sw $t2, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 8
jal func_2
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 12
move $t2, $v0
addu $t1, $t1, $t2
sll $t0, $t0, 2
sw $t1, global_var+8($t0)
label_5:
lw $t0, -0($fp)
sll $t0, $t0, 2
lw $t0, global_var+8($t0)
move $v0, $t0
jr $ra
label_2:
jr $ra


func_3:
lw $t0, -0($fp)
li $t1, 0
seq $t0, $t0, $t1
beq $t0, $0, label_6
li $t0, 1
move $v0, $t0
jr $ra
label_6:
lw $t0, -0($fp)
lw $t1, -0($fp)
li $t2, 1
subu $t1, $t1, $t2
addiu $sp, $sp, -4
sw $t1, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 8
jal func_3
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 12
move $t1, $v0
mul $t0, $t0, $t1
move $v0, $t0
jr $ra
jr $ra


func_4:
lw $t0, -0($fp)
sll $t0, $t0, 2
lw $t0, global_var+408($t0)
sw $t0, -8($fp)
lw $t0, -0($fp)
lw $t1, -4($fp)
sll $t1, $t1, 2
lw $t1, global_var+408($t1)
sll $t0, $t0, 2
sw $t1, global_var+408($t0)
lw $t0, -4($fp)
lw $t1, -8($fp)
sll $t0, $t0, 2
sw $t1, global_var+408($t0)
jr $ra
jr $ra


func_5:
lw $t0, -0($fp)
lw $t1, -4($fp)
sge $t0, $t0, $t1
beq $t0, $0, label_7
jr $ra
label_7:
lw $t0, -0($fp)
sw $t0, -8($fp)
lw $t0, -0($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -12($fp)
label_8:
lw $t0, -12($fp)
lw $t1, -4($fp)
sle $t0, $t0, $t1
beq $t0, $0, label_9
lw $t0, -12($fp)
sll $t0, $t0, 2
lw $t0, global_var+408($t0)
lw $t1, -0($fp)
sll $t1, $t1, 2
lw $t1, global_var+408($t1)
slt $t0, $t0, $t1
beq $t0, $0, label_10
lw $t0, -8($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -8($fp)
lw $t0, -8($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -12($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -12
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 16
jal func_4
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 20
label_10:
lw $t0, -12($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -12($fp)
j label_8
label_9:
lw $t0, -0($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -8($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -12
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 16
jal func_4
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 20
lw $t0, -0($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -8($fp)
li $t1, 1
subu $t0, $t0, $t1
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -16
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 20
jal func_5
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 24
lw $t0, -8($fp)
li $t1, 1
addu $t0, $t0, $t1
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -4($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -16
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 20
jal func_5
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 24
jr $ra


func_6:
lb $t0, -8($fp)
li $t1, 43
seq $t1, $t0, $t1
beq $t1, $0, label_12
lw $t0, -0($fp)
lw $t1, -4($fp)
addu $t0, $t0, $t1
move $v0, $t0
jr $ra
j label_11
label_12:
li $t1, 45
seq $t1, $t0, $t1
beq $t1, $0, label_13
lw $t0, -0($fp)
lw $t1, -4($fp)
subu $t0, $t0, $t1
move $v0, $t0
jr $ra
j label_11
label_13:
li $t1, 42
seq $t1, $t0, $t1
beq $t1, $0, label_14
lw $t0, -0($fp)
lw $t1, -4($fp)
mul $t0, $t0, $t1
move $v0, $t0
jr $ra
j label_11
label_14:
li $t1, 47
seq $t1, $t0, $t1
beq $t1, $0, label_15
lw $t0, -0($fp)
lw $t1, -4($fp)
div $t0, $t0, $t1
move $v0, $t0
jr $ra
j label_11
label_15:
label_11:
li $t0, 0
move $v0, $t0
jr $ra
jr $ra


func_7:
li $t0, 0
sw $t0, -12($fp)
lw $t0, -8($fp)
li $t1, 1
seq $t1, $t0, $t1
beq $t1, $0, label_17
lb $t0, -0($fp)
lb $t1, -4($fp)
slt $t0, $t0, $t1
beq $t0, $0, label_18
li $t0, 1
sw $t0, -12($fp)
label_18:
j label_16
label_17:
li $t1, 2
seq $t1, $t0, $t1
beq $t1, $0, label_19
lb $t0, -0($fp)
lb $t1, -4($fp)
sle $t0, $t0, $t1
beq $t0, $0, label_20
li $t0, 1
sw $t0, -12($fp)
label_20:
j label_16
label_19:
li $t1, 3
seq $t1, $t0, $t1
beq $t1, $0, label_21
lb $t0, -0($fp)
lb $t1, -4($fp)
sgt $t0, $t0, $t1
beq $t0, $0, label_22
li $t0, 1
sw $t0, -12($fp)
label_22:
j label_16
label_21:
li $t1, 4
seq $t1, $t0, $t1
beq $t1, $0, label_23
lb $t0, -0($fp)
lb $t1, -4($fp)
sge $t0, $t0, $t1
beq $t0, $0, label_24
li $t0, 1
sw $t0, -12($fp)
label_24:
j label_16
label_23:
li $t1, 5
seq $t1, $t0, $t1
beq $t1, $0, label_25
lb $t0, -0($fp)
lb $t1, -4($fp)
sne $t0, $t0, $t1
beq $t0, $0, label_26
li $t0, 1
sw $t0, -12($fp)
label_26:
j label_16
label_25:
li $t1, 6
seq $t1, $t0, $t1
beq $t1, $0, label_27
lb $t0, -0($fp)
lb $t1, -4($fp)
seq $t0, $t0, $t1
beq $t0, $0, label_28
li $t0, 1
sw $t0, -12($fp)
label_28:
j label_16
label_27:
li $t0, 0
sw $t0, -12($fp)
label_16:
lw $t0, -12($fp)
move $v0, $t0
jr $ra
jr $ra


func_8:
label_29:
lw $t0, -0($fp)
lw $t1, -4($fp)
slt $t0, $t0, $t1
beq $t0, $0, label_30
lw $t0, -0($fp)
sll $t0, $t0, 2
lb $t0, global_var+808($t0)
sb $t0, -8($fp)
lw $t0, -0($fp)
lw $t1, -4($fp)
sll $t1, $t1, 2
lb $t1, global_var+808($t1)
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
lw $t0, -4($fp)
lb $t1, -8($fp)
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
lw $t0, -0($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -0($fp)
lw $t0, -4($fp)
li $t1, 1
subu $t0, $t0, $t1
sw $t0, -4($fp)
j label_29
label_30:
jr $ra


func_9:
la $t0,str_0
move $a0, $t0
li $v0, 4
syscall
la $t0,str_1
move $a0, $t0
li $v0, 4
syscall
la $t0,str_2
move $a0, $t0
li $v0, 4
syscall
li $t0, 95
move $a0, $t0
li $v0, 11
syscall
li $t0, 49
move $a0, $t0
li $v0, 11
syscall
li $t0, 1024
neg $t0, $t0
move $a0, $t0
li $v0, 1
syscall
li $t0, 0
move $a0, $t0
li $v0, 1
syscall
li $t0, 0
move $a0, $t0
li $v0, 1
syscall
li $t0, 2
move $a0, $t0
li $v0, 1
syscall
li $t0, 3
move $a0, $t0
li $v0, 1
syscall
li $t0, -5
move $a0, $t0
li $v0, 1
syscall
li $t0, 88
move $a0, $t0
li $v0, 11
syscall
li $t0, 120
move $a0, $t0
li $v0, 11
syscall
li $t0, 88
move $a0, $t0
li $v0, 11
syscall
li $t0, 120
move $a0, $t0
li $v0, 11
syscall
li $t0, 88
move $a0, $t0
li $v0, 11
syscall
la $t0,str_3
move $a0, $t0
li $v0, 4
syscall
li $t0, 88
li $t1, 2
mul $t0, $t0, $t1
li $t1, 120
li $t2, 3
div $t1, $t1, $t2
addu $t0, $t0, $t1
move $a0, $t0
li $v0, 1
syscall
la $t0,str_4
move $a0, $t0
li $v0, 4
syscall
la $t0,str_5
move $a0, $t0
li $v0, 4
syscall
li $v0, 5
syscall
sw $v0, -4($fp)
la $t0,str_6
move $a0, $t0
li $v0, 4
syscall
lw $t0, -4($fp)
move $a0, $t0
li $v0, 1
syscall
la $t0,str_7
move $a0, $t0
li $v0, 4
syscall
li $v0, 12
syscall
sb $v0, -24($fp)
la $t0,str_8
move $a0, $t0
li $v0, 4
syscall
lb $t0, -24($fp)
move $a0, $t0
li $v0, 11
syscall
la $t0,str_9
move $a0, $t0
li $v0, 4
syscall
li $t0, 1
sw $t0, -16($fp)
label_31:
lw $t0, -16($fp)
li $t1, 6
sle $t0, $t0, $t1
beq $t0, $0, label_32
li $t0, 65
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 97
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -16($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -12
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 20
jal func_7
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 24
move $t0, $v0
move $a0, $t0
li $v0, 1
syscall
li $t0, 97
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 97
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -16($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -12
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 20
jal func_7
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 24
move $t0, $v0
move $a0, $t0
li $v0, 1
syscall
li $t0, 97
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 65
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -16($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -12
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 20
jal func_7
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 24
move $t0, $v0
move $a0, $t0
li $v0, 1
syscall
lw $t0, -16($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -16($fp)
j label_31
label_32:
la $t0,str_10
move $a0, $t0
li $v0, 4
syscall
li $t0, 123
li $t1, 456
mul $t0, $t0, $t1
neg $t0, $t0
li $t1, -987
li $t2, 321
div $t1, $t1, $t2
li $t2, 2
li $t3, 1
subu $t2, $t2, $t3
mul $t1, $t1, $t2
addu $t0, $t0, $t1
sw $t0, -4($fp)
lw $t0, -4($fp)
li $t1, 1
mul $t0, $t0, $t1
neg $t0, $t0
li $t1, 0
li $t2, 156
mul $t1, $t1, $t2
addu $t0, $t0, $t1
li $t1, 123
div $t0, $t0, $t1
sw $t0, -8($fp)
li $t0, 1
li $t1, 2
li $t2, 3
li $t3, 4
li $t4, 5
li $t5, 6
li $t6, 7
li $t7, 8
addu $t6, $t6, $t7
addu $t5, $t5, $t6
addu $t4, $t4, $t5
addu $t3, $t3, $t4
addu $t2, $t2, $t3
addu $t1, $t1, $t2
addu $t0, $t0, $t1
sw $t0, -12($fp)
la $t0,str_11
move $a0, $t0
li $v0, 4
syscall
lw $t0, -4($fp)
move $a0, $t0
li $v0, 1
syscall
la $t0,str_12
move $a0, $t0
li $v0, 4
syscall
lw $t0, -8($fp)
move $a0, $t0
li $v0, 1
syscall
lw $t0, -4($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -8($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 43
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 16
jal func_6
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 20
move $t0, $v0
sw $t0, -0($fp)
la $t0,str_13
move $a0, $t0
li $v0, 4
syscall
lw $t0, -0($fp)
move $a0, $t0
li $v0, 1
syscall
lw $t0, -4($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -8($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 45
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 16
jal func_6
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 20
move $t0, $v0
sw $t0, -0($fp)
la $t0,str_14
move $a0, $t0
li $v0, 4
syscall
lw $t0, -0($fp)
move $a0, $t0
li $v0, 1
syscall
lw $t0, -4($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -8($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 42
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 16
jal func_6
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 20
move $t0, $v0
sw $t0, -0($fp)
la $t0,str_15
move $a0, $t0
li $v0, 4
syscall
lw $t0, -0($fp)
move $a0, $t0
li $v0, 1
syscall
la $t0,str_16
move $a0, $t0
li $v0, 4
syscall
lw $t0, -4($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
lw $t0, -8($fp)
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 47
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 16
jal func_6
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 20
move $t0, $v0
move $a0, $t0
li $v0, 1
syscall
la $t0,str_17
move $a0, $t0
li $v0, 4
syscall
li $t0, 0
li $t1, 72
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 1
li $t1, 101
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 2
li $t1, 108
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 3
li $t1, 108
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 4
li $t1, 111
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 5
li $t1, 95
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 6
li $t1, 49
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 7
li $t1, 50
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 8
li $t1, 51
sll $t0, $t0, 2
sb $t1, global_var+808($t0)
li $t0, 0
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 8
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -12
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 16
jal func_8
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 20
li $t0, 0
sw $t0, -16($fp)
label_33:
lw $t0, -16($fp)
li $t1, 9
slt $t0, $t0, $t1
beq $t0, $0, label_34
lw $t0, -16($fp)
sll $t0, $t0, 2
lb $t0, global_var+808($t0)
move $a0, $t0
li $v0, 11
syscall
lw $t0, -16($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -16($fp)
j label_33
label_34:
la $t0,str_18
move $a0, $t0
li $v0, 4
syscall
li $v0, 5
syscall
sw $v0, global_var+0
li $v0, 5
syscall
sw $v0, global_var+4
la $t0,str_19
move $a0, $t0
li $v0, 4
syscall
lw $t0, global_var+0
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 8
jal func_3
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 12
move $t0, $v0
move $a0, $t0
li $v0, 1
syscall
addiu $sp, $sp, -12
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 8
jal func_1
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 12
la $t0,str_20
move $a0, $t0
li $v0, 4
syscall
lw $t0, global_var+4
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -8
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 8
jal func_2
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 12
move $t0, $v0
move $a0, $t0
li $v0, 1
syscall
la $t0,str_21
move $a0, $t0
li $v0, 4
syscall
li $t0, 0
sw $t0, -16($fp)
label_35:
lw $t0, -16($fp)
li $t1, 10
slt $t0, $t0, $t1
beq $t0, $0, label_36
li $v0, 5
syscall
sw $v0, -20($fp)
lw $t0, -16($fp)
lw $t1, -20($fp)
sll $t0, $t0, 2
sw $t1, global_var+408($t0)
lw $t0, -16($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -16($fp)
j label_35
label_36:
li $t0, 0
addiu $sp, $sp, -4
sw $t0, 0($sp)
li $t0, 9
addiu $sp, $sp, -4
sw $t0, 0($sp)
addiu $sp, $sp, -16
sw $fp, 4($sp)
sw $ra, 0($sp)
addiu $fp, $sp, 20
jal func_5
lw $fp, 4($sp)
lw $ra, 0($sp)
addiu $sp, $sp, 24
la $t0,str_22
move $a0, $t0
li $v0, 4
syscall
li $t0, 0
sw $t0, -16($fp)
label_37:
lw $t0, -16($fp)
li $t1, 10
slt $t0, $t0, $t1
beq $t0, $0, label_38
lw $t0, -16($fp)
sll $t0, $t0, 2
lw $t0, global_var+408($t0)
move $a0, $t0
li $v0, 1
syscall
lw $t0, -16($fp)
li $t1, 1
addu $t0, $t0, $t1
sw $t0, -16($fp)
j label_37
label_38:
la $t0,str_23
move $a0, $t0
li $v0, 4
syscall
jr $ra
jr $ra
