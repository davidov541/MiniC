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
addi $sp, 21
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
ldi $k2, -17
// Words: 35
sdw $k0, $fp, $k2
//: loadi *tmp, , 15
// Words: 36
// Words: 37
ldi $k0, 15
//: store z, 0, *tmp
// Words: 38
// Words: 39
ldi $k2, -21
// Words: 40
sdw $k0, $fp, $k2
//: load *tmp, 0, x
// Words: 41
// Words: 42
ldi $k2, -13
// Words: 43
ldw $k0, $fp, $k2
//: push , , *tmp
// Words: 44
addi $sp, 2
// Words: 45
sdw $k0, $sp, $0
// Words: 46
move $sp, $rr
//: load *tmp, 0, y
// Words: 47
// Words: 48
ldi $k2, -17
// Words: 49
ldw $k0, $fp, $k2
//: load *tmp2, 0, z
// Words: 50
// Words: 51
ldi $k2, -21
// Words: 52
ldw $k1, $fp, $k2
//: + *tmp2, *tmp2, *tmp
// Words: 53
add $k0, $k1
// Words: 54
move $k1, $rr
//: pop *tmp, , 
// Words: 55
addi $sp, -2
// Words: 56
move $sp, $rr
// Words: 57
ldw $k0, $sp, $0
//: + *tmp, *tmp2, *tmp
// Words: 58
add $k0, $k1
// Words: 59
move $k0, $rr
//: store a, 0, *tmp
// Words: 60
// Words: 61
ldi $k2, -11
// Words: 62
sdw $k0, $fp, $k2
//: load *tmp, 0, x
// Words: 63
// Words: 64
ldi $k2, -13
// Words: 65
ldw $k0, $fp, $k2
//: load *tmp2, 0, x
// Words: 66
// Words: 67
ldi $k2, -13
// Words: 68
ldw $k1, $fp, $k2
//: + *tmp, *tmp2, *tmp
// Words: 69
add $k0, $k1
// Words: 70
move $k0, $rr
//: push , , *tmp
// Words: 71
addi $sp, 2
// Words: 72
sdw $k0, $sp, $0
// Words: 73
move $sp, $rr
//: load *tmp, 0, y
// Words: 74
// Words: 75
ldi $k2, -17
// Words: 76
ldw $k0, $fp, $k2
//: load *tmp2, 0, z
// Words: 77
// Words: 78
ldi $k2, -21
// Words: 79
ldw $k1, $fp, $k2
//: + *tmp2, *tmp2, *tmp
// Words: 80
add $k0, $k1
// Words: 81
move $k1, $rr
//: pop *tmp, , 
// Words: 82
addi $sp, -2
// Words: 83
move $sp, $rr
// Words: 84
ldw $k0, $sp, $0
//: + *tmp, *tmp2, *tmp
// Words: 85
add $k0, $k1
// Words: 86
move $k0, $rr
//: store b, 0, *tmp
// Words: 87
// Words: 88
ldi $k2, -15
// Words: 89
sdw $k0, $fp, $k2
//: load *tmp, 0, x
// Words: 90
// Words: 91
ldi $k2, -13
// Words: 92
ldw $k0, $fp, $k2
//: load *tmp2, 0, y
// Words: 93
// Words: 94
ldi $k2, -17
// Words: 95
ldw $k1, $fp, $k2
//: + *tmp, *tmp2, *tmp
// Words: 96
add $k0, $k1
// Words: 97
move $k0, $rr
//: push , , *tmp
// Words: 98
addi $sp, 2
// Words: 99
sdw $k0, $sp, $0
// Words: 100
move $sp, $rr
//: load *tmp, 0, y
// Words: 101
// Words: 102
ldi $k2, -17
// Words: 103
ldw $k0, $fp, $k2
//: push , , *tmp
// Words: 104
addi $sp, 2
// Words: 105
sdw $k0, $sp, $0
// Words: 106
move $sp, $rr
//: load *tmp, 0, a
// Words: 107
// Words: 108
ldi $k2, -11
// Words: 109
ldw $k0, $fp, $k2
//: push , , *tmp
// Words: 110
addi $sp, 2
// Words: 111
sdw $k0, $sp, $0
// Words: 112
move $sp, $rr
//: load *tmp, 0, b
// Words: 113
// Words: 114
ldi $k2, -15
// Words: 115
ldw $k0, $fp, $k2
//: load *tmp2, 0, x
// Words: 116
// Words: 117
ldi $k2, -13
// Words: 118
ldw $k1, $fp, $k2
//: + *tmp2, *tmp2, *tmp
// Words: 119
add $k0, $k1
// Words: 120
move $k1, $rr
//: pop *tmp, , 
// Words: 121
addi $sp, -2
// Words: 122
move $sp, $rr
// Words: 123
ldw $k0, $sp, $0
//: + *tmp2, *tmp2, *tmp
// Words: 124
add $k0, $k1
// Words: 125
move $k1, $rr
//: pop *tmp, , 
// Words: 126
addi $sp, -2
// Words: 127
move $sp, $rr
// Words: 128
ldw $k0, $sp, $0
//: + *tmp2, *tmp2, *tmp
// Words: 129
add $k0, $k1
// Words: 130
move $k1, $rr
//: pop *tmp, , 
// Words: 131
addi $sp, -2
// Words: 132
move $sp, $rr
// Words: 133
ldw $k0, $sp, $0
//: + *tmp, *tmp2, *tmp
// Words: 134
add $k0, $k1
// Words: 135
move $k0, $rr
//: store c, 0, *tmp
// Words: 136
// Words: 137
ldi $k2, -19
// Words: 138
sdw $k0, $fp, $k2
//: assembly wp $s0, 0, , 
// Words: 139
// Words: 140
ldi $k2, -19
// Words: 141
ldw $s0, $fp, $k2
// Words: 142
wp $s0, 0
//: move *tmp, , *v
// Words: 143
move $k0, $v
//: loadi *tmp, , 0
// Words: 144
// Words: 145
ldi $k0, 0
//: jr , *tmp, 
// Words: 146
move $v, $k0
// Words: 147
addi $0, -2
// Words: 148
ldw $ra, $fp, $rr
// Words: 149
addi $rr, -3
// Words: 150
addi $rr, -2
// Words: 151
ldw $s0, $fp, $rr
// Words: 152
addi $rr, -2
// Words: 153
ldw $s1, $fp, $rr
// Words: 154
addi $fp, -21
// Words: 155
move $sp, $rr
// Words: 156
// Words: 157
ldi $k0, -4
// Words: 158
ldw $fp, $fp, $k0
// Words: 159
jr $ra
