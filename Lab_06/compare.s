        .data
n:       .word 25
str1:    .asciiz "Less than"
str2:    .asciiz "Less than or equal to"
str3:    .asciiz "Greater than"
str4:    .asciiz "Greater than or equal to"

	.text

main:   li $v0, 5          # Take in user input
        syscall             
        move $t0, $v0       # Store the user input in $t0

        la $s0, n           # Store n in $s0
        lw $s0, 0($s0)

        
        #slt $t1, $t0, $s0   #if $t0 < $s0, then $t1 will get the value of 1.
        #bne $t1, $0, less   #jump to less if $t1 != 0
        #j greq              
        
        slt $t1, $t0, $s0    #if $t0 < $s0, then $t1 will get the value of 1
        bne $t1, $0, leq     #jump to leq if $t1 != 0 
        j great              

less:   la $a0, str1
        j finish

leq:    la $a0, str2
        j finish

great:  la $a0, str3
        j finish

greq:   la $a0, str4
        j finish

finish: li $v0, 4
        syscall
