//mainint: funcdecl 1, , 
mainint:// Words: 0
addi $sp, 6
// Words: 1
move $gp, $rr
// Words: 2
move $sp, $rr
//: loadi *tmp, , -6
global:// Words: 3
// Words: 4
ldi $k0, -6
//: store currx, 0, *tmp
// Words: 5
addi $gp, -2
// Words: 6
sdw $k0, $0, $rr
//: loadi *tmp, , 0
// Words: 7
// Words: 8
ldi $k0, 0
//: store curry, 0, *tmp
// Words: 9
addi $gp, -4
// Words: 10
sdw $k0, $0, $rr
//: loadi *tmp, , 10
// Words: 11
// Words: 12
ldi $k0, 10
//: store additive, 0, *tmp
// Words: 13
addi $gp, -6
// Words: 14
sdw $k0, $0, $rr
// Words: 15
addi $sp, 11
// Words: 16
move $sp, $rr
// Words: 17
addi $0, -2
// Words: 18
sdw $ra, $sp, $rr
// Words: 19
addi $rr, -2
// Words: 20
sdw $fp, $sp, $rr
// Words: 21
move $fp, $sp
// Words: 22
addi $rr, -1
// Words: 23
// Words: 24
ldi $k2, 1
// Words: 25
swn $k2, $fp, $rr
// Words: 26
addi $rr, -2
// Words: 27
sdw $s0, $fp, $rr
// Words: 28
addi $rr, -2
// Words: 29
sdw $s1, $fp, $rr
//: load *tmp, 0, additive
// Words: 30
addi $gp, -6
// Words: 31
ldw $k0, $0, $rr
//: param *tmp, , 
// Words: 32
sdw $k0, $sp, $0
//: funccall *tmp, 1, fooint
// Words: 33
addi $sp, 2
// Words: 34
move $a, $sp
// Words: 35
move $sp, $rr
// Words: 36
// Words: 37
// Words: 38
// Words: 39
// Words: 40
// Words: 41
// Words: 42
la $k2, fooint
// Words: 43
jalr $k2
// Words: 44
move $k0, $v
// Words: 45
addi $sp, -2
// Words: 46
move $sp, $rr
//: store x, 0, *tmp
// Words: 47
// Words: 48
ldi $k2, -11
// Words: 49
sdw $k0, $fp, $k2
//: assembly wp $s0, 0, , 
// Words: 50
// Words: 51
ldi $k2, -11
// Words: 52
ldw $s0, $fp, $k2
// Words: 53
wp $s0, 0
//: move *tmp, , *v
// Words: 54
move $k0, $v
//: loadi *tmp, , 0
// Words: 55
// Words: 56
ldi $k0, 0
//: jr , *tmp, 
// Words: 57
move $v, $k0
// Words: 58
addi $0, -2
// Words: 59
ldw $ra, $fp, $rr
// Words: 60
addi $rr, -3
// Words: 61
addi $rr, -2
// Words: 62
ldw $s0, $fp, $rr
// Words: 63
addi $rr, -2
// Words: 64
ldw $s1, $fp, $rr
// Words: 65
addi $fp, -11
// Words: 66
move $sp, $rr
// Words: 67
// Words: 68
ldi $k0, -4
// Words: 69
ldw $fp, $fp, $k0
// Words: 70
jr $ra
//fooint: funcdecl 1, , 
fooint:// Words: 71
addi $sp, 11
// Words: 72
move $sp, $rr
// Words: 73
addi $0, -2
// Words: 74
sdw $ra, $sp, $rr
// Words: 75
addi $rr, -2
// Words: 76
sdw $fp, $sp, $rr
// Words: 77
move $fp, $sp
// Words: 78
addi $rr, -1
// Words: 79
// Words: 80
ldi $k2, 1
// Words: 81
swn $k2, $fp, $rr
// Words: 82
addi $rr, -2
// Words: 83
sdw $s0, $fp, $rr
// Words: 84
addi $rr, -2
// Words: 85
sdw $s1, $fp, $rr
//: formal x, , 
// Words: 86
ldw $k2, $a, $0
// Words: 87
addi $0, -11
// Words: 88
sdw $k2, $fp, $rr
//: load *tmp, 0, x
// Words: 89
// Words: 90
ldi $k2, -11
// Words: 91
ldw $k0, $fp, $k2
//: load *tmp2, 0, additive
// Words: 92
addi $gp, -6
// Words: 93
ldw $k1, $0, $rr
//: + *tmp, *tmp2, *tmp
// Words: 94
add $k0, $k1
// Words: 95
move $k0, $rr
//: jr , *tmp, 
// Words: 96
move $v, $k0
// Words: 97
addi $0, -2
// Words: 98
ldw $ra, $fp, $rr
// Words: 99
addi $rr, -3
// Words: 100
addi $rr, -2
// Words: 101
ldw $s0, $fp, $rr
// Words: 102
addi $rr, -2
// Words: 103
ldw $s1, $fp, $rr
// Words: 104
addi $fp, -11
// Words: 105
move $sp, $rr
// Words: 106
// Words: 107
ldi $k0, -4
// Words: 108
ldw $fp, $fp, $k0
// Words: 109
jr $ra
