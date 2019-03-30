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
addi $sp, 13
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
//: loadi *tmp, , 5
// Words: 26
// Words: 27
ldi $k0, 5
//: store x, 0, *tmp
// Words: 28
// Words: 29
ldi $k2, -13
// Words: 30
sdw $k0, $fp, $k2
//: loadi *tmp, , 10
// Words: 31
// Words: 32
ldi $k0, 10
//: store y, 0, *tmp
// Words: 33
// Words: 34
ldi $k2, -11
// Words: 35
sdw $k0, $fp, $k2
//: u& *tmp, 0, x
// Words: 36
addi $sp, -13
// Words: 37
move $k0, $rr
//: param *tmp, , 
// Words: 38
sdw $k0, $sp, $0
//: u& *tmp, 0, y
// Words: 39
addi $sp, -11
// Words: 40
move $k0, $rr
//: param *tmp, , 
// Words: 41
// Words: 42
ldi $k2, 2
// Words: 43
sdw $k0, $sp, $k2
//: funccall , 2, swapvoid
// Words: 44
addi $sp, 4
// Words: 45
move $a, $sp
// Words: 46
move $sp, $rr
// Words: 47
// Words: 48
// Words: 49
// Words: 50
// Words: 51
// Words: 52
// Words: 53
la $k2, swapvoid
// Words: 54
jalr $k2
// Words: 55
addi $sp, -4
// Words: 56
move $sp, $rr
//: assembly wp $s0, 0, , 
// Words: 57
// Words: 58
ldi $k2, -13
// Words: 59
ldw $s0, $fp, $k2
// Words: 60
wp $s0, 0
//: move *tmp, , *v
// Words: 61
move $k0, $v
//: loadi *tmp, , 0
// Words: 62
// Words: 63
ldi $k0, 0
//: jr , *tmp, 
// Words: 64
move $v, $k0
// Words: 65
addi $0, -2
// Words: 66
ldw $ra, $fp, $rr
// Words: 67
addi $rr, -3
// Words: 68
addi $rr, -2
// Words: 69
ldw $s0, $fp, $rr
// Words: 70
addi $rr, -2
// Words: 71
ldw $s1, $fp, $rr
// Words: 72
addi $fp, -13
// Words: 73
move $sp, $rr
// Words: 74
// Words: 75
ldi $k0, -4
// Words: 76
ldw $fp, $fp, $k0
// Words: 77
jr $ra
//swapvoid: funcdecl 2, , 
swapvoid:// Words: 78
addi $sp, 15
// Words: 79
move $sp, $rr
// Words: 80
addi $0, -2
// Words: 81
sdw $ra, $sp, $rr
// Words: 82
addi $rr, -2
// Words: 83
sdw $fp, $sp, $rr
// Words: 84
move $fp, $sp
// Words: 85
addi $rr, -1
// Words: 86
// Words: 87
ldi $k2, 2
// Words: 88
swn $k2, $fp, $rr
// Words: 89
addi $rr, -2
// Words: 90
sdw $s0, $fp, $rr
// Words: 91
addi $rr, -2
// Words: 92
sdw $s1, $fp, $rr
//: formal a, , 
// Words: 93
ldw $k2, $a, $0
// Words: 94
addi $0, -11
// Words: 95
sdw $k2, $fp, $rr
//: formal b, , 
// Words: 96
// Words: 97
ldi $k2, 2
// Words: 98
ldw $k2, $a, $k2
// Words: 99
addi $0, -13
// Words: 100
sdw $k2, $fp, $rr
//: load *tmp, 0, a
// Words: 101
// Words: 102
ldi $k2, -11
// Words: 103
ldw $k0, $fp, $k2
//: u* *tmp, , *tmp
// Words: 104
ldw $k0, $0, $k0
//: store tmp, 0, *tmp
// Words: 105
// Words: 106
ldi $k2, -15
// Words: 107
sdw $k0, $fp, $k2
//: load *tmp, 0, b
// Words: 108
// Words: 109
ldi $k2, -13
// Words: 110
ldw $k0, $fp, $k2
//: u* *tmp, , *tmp
// Words: 111
ldw $k0, $0, $k0
//: load *tmp2, 0, a
// Words: 112
// Words: 113
ldi $k2, -11
// Words: 114
ldw $k1, $fp, $k2
//: storeadd *tmp, , *tmp2
// Words: 115
sdw $k0, $0, $k1
//: load *tmp, 0, tmp
// Words: 116
// Words: 117
ldi $k2, -15
// Words: 118
ldw $k0, $fp, $k2
//: load *tmp2, 0, b
// Words: 119
// Words: 120
ldi $k2, -13
// Words: 121
ldw $k1, $fp, $k2
//: storeadd *tmp, , *tmp2
// Words: 122
sdw $k0, $0, $k1
//: funcend , , 
// Words: 123
addi $0, -2
// Words: 124
ldw $ra, $fp, $rr
// Words: 125
addi $rr, -5
// Words: 126
ldw $s0, $fp, $rr
// Words: 127
addi $rr, -2
// Words: 128
ldw $s1, $fp, $rr
// Words: 129
addi $fp, -15
// Words: 130
move $sp, $rr
// Words: 131
// Words: 132
ldi $k0, -4
// Words: 133
ldw $fp, $fp, $k0
// Words: 134
jr $ra
