#$t0 = $s0 
#$t1 = $t0 - 1 
#$t2 = $t1 + $t0 
#$t3 = $t2 - 3 
#$t4 = $t3 + $t2 
#$t5 = $t4 - 5 
#$t6 = $t5 + $t4 
#$t7 = $t6 - 7 

main: 
	add $t0, $s0, $zero
	addi $t1, $t0, -1
	add $t2, $t1, $t0
	addi $t3, $t2, -3
	add $t4, $t3, $t2
	addi $t5, $t4, -5
	add $t6, $t5, $t4
	addi $t7, $t6, -7
