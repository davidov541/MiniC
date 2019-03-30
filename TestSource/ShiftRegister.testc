//mainint: funcdecl 1, , 
mainint:// Words: 0
addi $sp, 4
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
// Words: 11
addi $sp, 15
// Words: 12
move $sp, $rr
// Words: 13
addi $0, -2
// Words: 14
sdw $ra, $sp, $rr
// Words: 15
addi $rr, -2
// Words: 16
sdw $fp, $sp, $rr
// Words: 17
move $fp, $sp
// Words: 18
addi $rr, -1
// Words: 19
// Words: 20
ldi $k2, 1
// Words: 21
swn $k2, $fp, $rr
// Words: 22
addi $rr, -2
// Words: 23
sdw $s0, $fp, $rr
// Words: 24
addi $rr, -2
// Words: 25
sdw $s1, $fp, $rr
//: loadi *tmp, , 0
// Words: 26
// Words: 27
ldi $k0, 0
//: store p, 0, *tmp
// Words: 28
// Words: 29
ldi $k2, -11
// Words: 30
sdw $k0, $fp, $k2
//: loadi *tmp, , 0
// Words: 31
// Words: 32
ldi $k0, 0
//: store p, 1, *tmp
// Words: 33
// Words: 34
ldi $k2, -9
// Words: 35
sdw $k0, $fp, $k2
//: load *tmp, 0, p
L1:// Words: 36
// Words: 37
ldi $k2, -11
// Words: 38
ldw $k0, $fp, $k2
//: store p, 1, *tmp
// Words: 39
// Words: 40
ldi $k2, -9
// Words: 41
sdw $k0, $fp, $k2
//: assembly rp $v, 2, , 
// Words: 42
rp $v, 2
//: move *tmp, , *v
// Words: 43
move $k0, $v
//: store p, 0, *tmp
// Words: 44
// Words: 45
ldi $k2, -11
// Words: 46
sdw $k0, $fp, $k2
//: load *tmp, 1, p
// Words: 47
// Words: 48
ldi $k2, -9
// Words: 49
ldw $k0, $fp, $k2
//: store displayValue, 0, *tmp
// Words: 50
// Words: 51
ldi $k2, -13
// Words: 52
sdw $k0, $fp, $k2
//: assembly wp $s0, 0, , 
// Words: 53
// Words: 54
ldi $k2, -13
// Words: 55
ldw $s0, $fp, $k2
// Words: 56
wp $s0, 0
//: move *tmp, , *v
// Words: 57
move $k0, $v
//: assembly rp $v, 2, , 
// Words: 58
rp $v, 2
//: move *tmp, , *v
// Words: 59
move $k0, $v
//: store currVal, 0, *tmp
// Words: 60
// Words: 61
ldi $k2, -15
// Words: 62
sdw $k0, $fp, $k2
//: load *tmp, 0, currVal
L2:// Words: 63
// Words: 64
ldi $k2, -15
// Words: 65
ldw $k0, $fp, $k2
//: load *tmp2, 0, p
// Words: 66
// Words: 67
ldi $k2, -11
// Words: 68
ldw $k1, $fp, $k2
//: bne , *tmp2, *tmp
// Words: 69
// Words: 70
// Words: 71
// Words: 72
// Words: 73
// Words: 74
// Words: 75
la $k2, L4
// Words: 76
bne $k0, $k1, $k2
//: assembly rp $v, 2, , 
L3:// Words: 77
rp $v, 2
//: move *tmp, , *v
// Words: 78
move $k0, $v
//: store currVal, 0, *tmp
// Words: 79
// Words: 80
ldi $k2, -15
// Words: 81
sdw $k0, $fp, $k2
//: jump , , 
// Words: 82
// Words: 83
// Words: 84
// Words: 85
// Words: 86
// Words: 87
// Words: 88
la $k2, L2
// Words: 89
jr $k2
//: jump , , 
L4:// Words: 90
// Words: 91
// Words: 92
// Words: 93
// Words: 94
// Words: 95
// Words: 96
la $k2, L1
// Words: 97
jr $k2
//: loadi *tmp, , 0
L5:// Words: 98
// Words: 99
ldi $k0, 0
//: jr , *tmp, 
// Words: 100
move $v, $k0
// Words: 101
addi $0, -2
// Words: 102
ldw $ra, $fp, $rr
// Words: 103
addi $rr, -3
// Words: 104
addi $rr, -2
// Words: 105
ldw $s0, $fp, $rr
// Words: 106
addi $rr, -2
// Words: 107
ldw $s1, $fp, $rr
// Words: 108
addi $fp, -15
// Words: 109
move $sp, $rr
// Words: 110
// Words: 111
ldi $k0, -4
// Words: 112
ldw $fp, $fp, $k0
// Words: 113
jr $ra
