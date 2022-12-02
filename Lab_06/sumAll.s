    	.data
    input: .asciiz "\nPlease enter a number:  "
    odd_sum: .asciiz "\nSum of odd numbers: "
    even_sum: .asciiz "\nSum of even numbers is: "

    
	.text 
#input
main:  li $v0, 4    #prints input string
    la $a0, input
    syscall
    li $v0, 5    #takes the input from the user
    syscall
    move $t0, $v0    #moves input to t0 register
     
    beq $t0, $zero, terminate    #if the input is zero end the program
     
    srl $s1, $t0, 1        #shift right t0 by 1 and store in s1
    sll $s2, $s1, 1        #shift left s1 by 1 and store in s2
     
    beq $s2, $t0, even    #compare s1 and s2, if equal go to even
     

 odd:    add $t1, $t1, $t0    #add input to odd sum, and store in odd sum
     j main            
     
 even:    add $t2, $t2, $t0    #add input to even sum, and store in even sum
     j main
     
 terminate:    li $v0, 4    #print string even_sum
     la $a0, even_sum
    syscall
    li $v0, 1    
    add $a0, $t2, $zero    # move what is stored in even_sum to a0    
    syscall
    li $v0, 4
     la $a0, odd_sum
    syscall
    li $v0, 1
     add $a0, $t1, $zero    # move what is stored in odd_sum to a0
    syscall
    
    li $v0, 10    #end program
    syscall
