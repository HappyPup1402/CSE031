	.data
x: 	.word 2
y:	.word 3
z:	.word 4
t:	.word 1
two:	.word 2				

	.text
	
MAIN:		la $t0, x		
		lw $s0, 0($t0)		#s0 = x 
		la $t0, y		
		lw $s1, 0($t0)		#s1 = y 
		la $t0, z
		lw $s2, 0($t0)		#s2 = z 
		la $t0, t
		lw $s5, 0($t0)		#s5 = t (will be used as a counter var for mult)
		
		add $a0, $zero, $s0	#set up input arguments for FOO(p)
		add $a1, $zero, $s1
		add $a2, $zero, $s2
		add $s2, $s2, $s1	#add z and y
		add $s2, $s2, $s0	#s2 will hold the addition of x,y and z
		la $t0, two
		lw $s6, 0($t0)		#s6 = two
		jal FOO	
		
		add $a0, $v0, $s2
		li $v0, 1		 
		syscall	
		
		j END
				
		
FOO:		addi $sp, $sp, -4	
		sw $ra, 0($sp)		#stores ra in the stack
		add $t0, $zero, $a0	#back up m(or x) because its going to be used multiple times
		add $a0, $t0, $a1	#set up input arguments for the first bar call. x and y = a
		add $a1, $a1, $a2   	#add y and z = b
		add $a2, $a2, $t0 	#add z and x = c
		jal BAR
		
		
		sub $s0, $s0, $s0
		add $s0, $zero, $t0	#stores p into s0 
		mul $s0, $s0, $a0	#multiple p's bit shift
		
		la $t0, x		#set up input arguments for FOO(q)
		lw $a0, 0($t0)
		la $t0, y
		lw $a1, 0($t0)
		la $t0, z
		lw $a2, 0($t0)
		
		add $t1, $zero, $a0	#back up m
		add $t2, $zero, $a1	#back up n
		sub $a0, $t1, $a2 	#sub x - y = a
		sub $a1, $a1, $t1 	#y - x = b
		mul $a2, $s6, $t2 	#2 * z = c
		
		jal BAR
		
		sub $s1, $s1, $s1
		add $s1, $zero, $t0 	#stores the q value
		mul $s1, $s1, $a0   	#multiple q's bit shift
		
		add $v0, $s0, $s1 	#output of FOO
		
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
		
	
BAR:		sub $a0, $a2, $a0	#subtract z - x(c - a)
		la $t0, two		#load 2 into the temporary register
		lw $t0, 0($t0)		
		addi $fp, $fp, -4	#save return address to go back to FOO
		sw $ra, 0($fp)
		jal MULT	
		
		lw $ra, 0($fp)		#return to FOO
		addi $fp, $fp, 4
		jr $ra
	
MULT:		la $t7, t		
		lw $t7, 0($t7)	
		beq $a1, $t7, JUMP	#if a1 = 1 then exit to BAR
		mul $t0, $t0, $s6	#else multiple
		addi $s5, $s5, 1	#t++
		bne $s5, $a1, MULT  	#if s5 != a1, bit shift again
		jr $ra 			#jump back to bar
		
JUMP:		jr $ra			#helps jump back to bar while using beq
		
END:
