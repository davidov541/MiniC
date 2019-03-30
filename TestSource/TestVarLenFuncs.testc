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
addi $sp, 11
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
//: param *tmp, , 
// Words: 28
sdw $k0, $sp, $0
//: loadi *tmp, , 10
// Words: 29
// Words: 30
ldi $k0, 10
//: param *tmp, , 
// Words: 31
// Words: 32
ldi $k2, 2
// Words: 33
sdw $k0, $sp, $k2
//: loadi *tmp, , 15
// Words: 34
// Words: 35
ldi $k0, 15
//: param *tmp, , 
// Words: 36
// Words: 37
ldi $k2, 4
// Words: 38
sdw $k0, $sp, $k2
//: loadi *tmp, , 20
// Words: 39
// Words: 40
ldi $k0, 20
//: param *tmp, , 
// Words: 41
// Words: 42
ldi $k2, 6
// Words: 43
sdw $k0, $sp, $k2
//: funccall *tmp, 4, fooint
// Words: 44
addi $sp, 8
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
la $k2, fooint
// Words: 54
jalr $k2
// Words: 55
move $k0, $v
// Words: 56
addi $sp, -8
// Words: 57
move $sp, $rr
//: store a, 0, *tmp
// Words: 58
// Words: 59
ldi $k2, -11
// Words: 60
sdw $k0, $fp, $k2
//: assembly wp $s0, 0, , 
// Words: 61
// Words: 62
ldi $k2, -11
// Words: 63
ldw $s0, $fp, $k2
// Words: 64
wp $s0, 0
//: move *tmp, , *v
// Words: 65
move $k0, $v
//: loadi *tmp, , 0
// Words: 66
// Words: 67
ldi $k0, 0
//: jr , *tmp, 
// Words: 68
move $v, $k0
// Words: 69
addi $0, -2
// Words: 70
ldw $ra, $fp, $rr
// Words: 71
addi $rr, -3
// Words: 72
addi $rr, -2
// Words: 73
ldw $s0, $fp, $rr
// Words: 74
addi $rr, -2
// Words: 75
ldw $s1, $fp, $rr
// Words: 76
addi $fp, -11
// Words: 77
move $sp, $rr
// Words: 78
// Words: 79
ldi $k0, -4
// Words: 80
ldw $fp, $fp, $k0
// Words: 81
jr $ra
//fooint: funcdecl 1, , 
fooint:// Words: 82
addi $sp, 17
// Words: 83
move $sp, $rr
// Words: 84
addi $0, -2
// Words: 85
sdw $ra, $sp, $rr
// Words: 86
addi $rr, -2
// Words: 87
sdw $fp, $sp, $rr
// Words: 88
move $fp, $sp
// Words: 89
addi $rr, -1
// Words: 90
// Words: 91
ldi $k2, 1
// Words: 92
swn $k2, $fp, $rr
// Words: 93
addi $rr, -2
// Words: 94
sdw $s0, $fp, $rr
// Words: 95
addi $rr, -2
// Words: 96
sdw $s1, $fp, $rr
//: formal x, , 
// Words: 97
ldw $k2, $a, $0
// Words: 98
addi $0, -17
// Words: 99
sdw $k2, $fp, $rr
//: loadi *tmp, , 0
// Words: 100
// Words: 101
ldi $k0, 0
//: store ap, 0, *tmp
// Words: 102
// Words: 103
ldi $k2, -15
// Words: 104
sdw $k0, $fp, $k2
//: assembly ldi $s0, -3;lwn $s0, $fp, $s0;add $s0, $a, , 
// Words: 105
ldi $s0, -3
// Words: 106
lwn $s0, $fp, $s0
// Words: 107
add $s0, $a
// Words: 108
// Words: 109
ldi $k2, -15
// Words: 110
sdw $rr, $fp, $k2
//: move *tmp, , *v
// Words: 111
move $k0, $v
//: assembly lwn $v, $s0, $0;addi $s0, 1, , 
// Words: 112
// Words: 113
ldi $k2, -15
// Words: 114
ldw $s0, $fp, $k2
// Words: 115
lwn $v, $s0, $0
// Words: 116
addi $s0, 1
// Words: 117
// Words: 118
ldi $k2, -15
// Words: 119
sdw $rr, $fp, $k2
//: move *tmp, , *v
// Words: 120
move $k0, $v
//: store y, 0, *tmp
// Words: 121
// Words: 122
ldi $k2, -11
// Words: 123
sdw $k0, $fp, $k2
//: assembly lwn $v, $s0, $0;addi $s0, 1, , 
// Words: 124
// Words: 125
ldi $k2, -15
// Words: 126
ldw $s0, $fp, $k2
// Words: 127
lwn $v, $s0, $0
// Words: 128
addi $s0, 1
// Words: 129
// Words: 130
ldi $k2, -15
// Words: 131
sdw $rr, $fp, $k2
//: move *tmp, , *v
// Words: 132
move $k0, $v
//: store z, 0, *tmp
// Words: 133
// Words: 134
ldi $k2, -13
// Words: 135
sdw $k0, $fp, $k2
//: load *tmp, 0, z
// Words: 136
// Words: 137
ldi $k2, -13
// Words: 138
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 139
move $v, $k0
// Words: 140
addi $0, -2
// Words: 141
ldw $ra, $fp, $rr
// Words: 142
addi $rr, -3
// Words: 143
addi $rr, -2
// Words: 144
ldw $s0, $fp, $rr
// Words: 145
addi $rr, -2
// Words: 146
ldw $s1, $fp, $rr
// Words: 147
addi $fp, -17
// Words: 148
move $sp, $rr
// Words: 149
// Words: 150
ldi $k0, -4
// Words: 151
ldw $fp, $fp, $k0
// Words: 152
jr $ra
