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
//: loadi *tmp, , 0
// Words: 26
// Words: 27
ldi $k0, 0
//: store c, 0, *tmp
// Words: 28
// Words: 29
ldi $k2, -11
// Words: 30
sdw $k0, $fp, $k2
//: assembly rp $v, 2, , 
L1:// Words: 31
rp $v, 2
//: move *tmp, , *v
// Words: 32
move $k0, $v
//: store c, 0, *tmp
// Words: 33
// Words: 34
ldi $k2, -11
// Words: 35
sdw $k0, $fp, $k2
//: load *tmp, 0, c
// Words: 36
// Words: 37
ldi $k2, -11
// Words: 38
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 39
sdw $k0, $sp, $0
//: funccall *tmp, 1, relPrimeint
// Words: 40
addi $sp, 2
// Words: 41
move $a, $sp
// Words: 42
move $sp, $rr
// Words: 43
// Words: 44
// Words: 45
// Words: 46
// Words: 47
// Words: 48
// Words: 49
la $k2, relPrimeint
// Words: 50
jalr $k2
// Words: 51
move $k0, $v
// Words: 52
addi $sp, -2
// Words: 53
move $sp, $rr
//: store x, 0, *tmp
// Words: 54
// Words: 55
ldi $k2, -13
// Words: 56
sdw $k0, $fp, $k2
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
//: jump , , 
// Words: 62
// Words: 63
// Words: 64
// Words: 65
// Words: 66
// Words: 67
// Words: 68
la $k2, L1
// Words: 69
jr $k2
//: loadi *tmp, , 0
L2:// Words: 70
// Words: 71
ldi $k0, 0
//: jr , *tmp, 
// Words: 72
move $v, $k0
// Words: 73
addi $0, -2
// Words: 74
ldw $ra, $fp, $rr
// Words: 75
addi $rr, -3
// Words: 76
addi $rr, -2
// Words: 77
ldw $s0, $fp, $rr
// Words: 78
addi $rr, -2
// Words: 79
ldw $s1, $fp, $rr
// Words: 80
addi $fp, -13
// Words: 81
move $sp, $rr
// Words: 82
// Words: 83
ldi $k0, -4
// Words: 84
ldw $fp, $fp, $k0
// Words: 85
jr $ra
//gcdint: funcdecl 2, , 
gcdint:// Words: 86
addi $sp, 13
// Words: 87
move $sp, $rr
// Words: 88
addi $0, -2
// Words: 89
sdw $ra, $sp, $rr
// Words: 90
addi $rr, -2
// Words: 91
sdw $fp, $sp, $rr
// Words: 92
move $fp, $sp
// Words: 93
addi $rr, -1
// Words: 94
// Words: 95
ldi $k2, 2
// Words: 96
swn $k2, $fp, $rr
// Words: 97
addi $rr, -2
// Words: 98
sdw $s0, $fp, $rr
// Words: 99
addi $rr, -2
// Words: 100
sdw $s1, $fp, $rr
//: formal a, , 
// Words: 101
ldw $k2, $a, $0
// Words: 102
addi $0, -11
// Words: 103
sdw $k2, $fp, $rr
//: formal b, , 
// Words: 104
// Words: 105
ldi $k2, 2
// Words: 106
ldw $k2, $a, $k2
// Words: 107
addi $0, -13
// Words: 108
sdw $k2, $fp, $rr
//: load *tmp, 0, a
// Words: 109
// Words: 110
ldi $k2, -11
// Words: 111
ldw $k0, $fp, $k2
//: loadi *tmp2, , 0
// Words: 112
// Words: 113
ldi $k1, 0
//: bne , *tmp2, *tmp
// Words: 114
// Words: 115
// Words: 116
// Words: 117
// Words: 118
// Words: 119
// Words: 120
la $k2, L5
// Words: 121
bne $k0, $k1, $k2
//: load *tmp, 0, b
L4:// Words: 122
// Words: 123
ldi $k2, -13
// Words: 124
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 125
move $v, $k0
// Words: 126
addi $0, -2
// Words: 127
ldw $ra, $fp, $rr
// Words: 128
addi $rr, -3
// Words: 129
addi $rr, -2
// Words: 130
ldw $s0, $fp, $rr
// Words: 131
addi $rr, -2
// Words: 132
ldw $s1, $fp, $rr
// Words: 133
addi $fp, -13
// Words: 134
move $sp, $rr
// Words: 135
// Words: 136
ldi $k0, -4
// Words: 137
ldw $fp, $fp, $k0
// Words: 138
jr $ra
//: load *tmp, 0, b
L5:// Words: 139
// Words: 140
ldi $k2, -13
// Words: 141
ldw $k0, $fp, $k2
//: loadi *tmp2, , 0
// Words: 142
// Words: 143
ldi $k1, 0
//: beq , *tmp2, *tmp
// Words: 144
// Words: 145
// Words: 146
// Words: 147
// Words: 148
// Words: 149
// Words: 150
la $k2, L10
// Words: 151
beq $k0, $k1, $k2
//: load *tmp, 0, a
L6:// Words: 152
// Words: 153
ldi $k2, -11
// Words: 154
ldw $k0, $fp, $k2
//: load *tmp2, 0, b
// Words: 155
// Words: 156
ldi $k2, -13
// Words: 157
ldw $k1, $fp, $k2
//: blte , *tmp2, *tmp
// Words: 158
// Words: 159
// Words: 160
// Words: 161
// Words: 162
// Words: 163
// Words: 164
la $k2, L8
// Words: 165
blt $k0, $k1, $k2
// Words: 166
beq $k0, $k1, $k2
//: load *tmp, 0, a
L7:// Words: 167
// Words: 168
ldi $k2, -11
// Words: 169
ldw $k0, $fp, $k2
//: load *tmp2, 0, b
// Words: 170
// Words: 171
ldi $k2, -13
// Words: 172
ldw $k1, $fp, $k2
//: - *tmp, *tmp2, *tmp
// Words: 173
sub $k0, $k1
// Words: 174
move $k0, $rr
//: store a, 0, *tmp
// Words: 175
// Words: 176
ldi $k2, -11
// Words: 177
sdw $k0, $fp, $k2
// Words: 178
// Words: 179
// Words: 180
// Words: 181
// Words: 182
// Words: 183
// Words: 184
la $k2, L9
// Words: 185
jr $k2
//: load *tmp, 0, b
L8:// Words: 186
// Words: 187
ldi $k2, -13
// Words: 188
ldw $k0, $fp, $k2
//: load *tmp2, 0, a
// Words: 189
// Words: 190
ldi $k2, -11
// Words: 191
ldw $k1, $fp, $k2
//: - *tmp, *tmp2, *tmp
// Words: 192
sub $k0, $k1
// Words: 193
move $k0, $rr
//: store b, 0, *tmp
// Words: 194
// Words: 195
ldi $k2, -13
// Words: 196
sdw $k0, $fp, $k2
//: jump , , 
L9:// Words: 197
// Words: 198
// Words: 199
// Words: 200
// Words: 201
// Words: 202
// Words: 203
la $k2, L5
// Words: 204
jr $k2
//: load *tmp, 0, a
L10:// Words: 205
// Words: 206
ldi $k2, -11
// Words: 207
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 208
move $v, $k0
// Words: 209
addi $0, -2
// Words: 210
ldw $ra, $fp, $rr
// Words: 211
addi $rr, -3
// Words: 212
addi $rr, -2
// Words: 213
ldw $s0, $fp, $rr
// Words: 214
addi $rr, -2
// Words: 215
ldw $s1, $fp, $rr
// Words: 216
addi $fp, -13
// Words: 217
move $sp, $rr
// Words: 218
// Words: 219
ldi $k0, -4
// Words: 220
ldw $fp, $fp, $k0
// Words: 221
jr $ra
//relPrimeint: funcdecl 1, , 
relPrimeint:// Words: 222
addi $sp, 13
// Words: 223
move $sp, $rr
// Words: 224
addi $0, -2
// Words: 225
sdw $ra, $sp, $rr
// Words: 226
addi $rr, -2
// Words: 227
sdw $fp, $sp, $rr
// Words: 228
move $fp, $sp
// Words: 229
addi $rr, -1
// Words: 230
// Words: 231
ldi $k2, 1
// Words: 232
swn $k2, $fp, $rr
// Words: 233
addi $rr, -2
// Words: 234
sdw $s0, $fp, $rr
// Words: 235
addi $rr, -2
// Words: 236
sdw $s1, $fp, $rr
//: formal n, , 
// Words: 237
ldw $k2, $a, $0
// Words: 238
addi $0, -13
// Words: 239
sdw $k2, $fp, $rr
//: loadi *tmp, , 2
// Words: 240
// Words: 241
ldi $k0, 2
//: store m, 0, *tmp
// Words: 242
// Words: 243
ldi $k2, -11
// Words: 244
sdw $k0, $fp, $k2
//: load *tmp, 0, n
L12:// Words: 245
// Words: 246
ldi $k2, -13
// Words: 247
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 248
sdw $k0, $sp, $0
//: load *tmp, 0, m
// Words: 249
// Words: 250
ldi $k2, -11
// Words: 251
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 252
// Words: 253
ldi $k2, 2
// Words: 254
sdw $k0, $sp, $k2
//: funccall *tmp, 2, gcdint
// Words: 255
addi $sp, 4
// Words: 256
move $a, $sp
// Words: 257
move $sp, $rr
// Words: 258
// Words: 259
// Words: 260
// Words: 261
// Words: 262
// Words: 263
// Words: 264
la $k2, gcdint
// Words: 265
jalr $k2
// Words: 266
move $k0, $v
// Words: 267
addi $sp, -4
// Words: 268
move $sp, $rr
//: loadi *tmp2, , 1
// Words: 269
// Words: 270
ldi $k1, 1
//: beq , *tmp2, *tmp
// Words: 271
// Words: 272
// Words: 273
// Words: 274
// Words: 275
// Words: 276
// Words: 277
la $k2, L14
// Words: 278
beq $k0, $k1, $k2
//: load *tmp, 0, m
L13:// Words: 279
// Words: 280
ldi $k2, -11
// Words: 281
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 282
// Words: 283
ldi $k1, 1
//: + *tmp, *tmp2, *tmp
// Words: 284
add $k0, $k1
// Words: 285
move $k0, $rr
//: store m, 0, *tmp
// Words: 286
// Words: 287
ldi $k2, -11
// Words: 288
sdw $k0, $fp, $k2
//: jump , , 
// Words: 289
// Words: 290
// Words: 291
// Words: 292
// Words: 293
// Words: 294
// Words: 295
la $k2, L12
// Words: 296
jr $k2
//: load *tmp, 0, m
L14:// Words: 297
// Words: 298
ldi $k2, -11
// Words: 299
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 300
move $v, $k0
// Words: 301
addi $0, -2
// Words: 302
ldw $ra, $fp, $rr
// Words: 303
addi $rr, -3
// Words: 304
addi $rr, -2
// Words: 305
ldw $s0, $fp, $rr
// Words: 306
addi $rr, -2
// Words: 307
ldw $s1, $fp, $rr
// Words: 308
addi $fp, -13
// Words: 309
move $sp, $rr
// Words: 310
// Words: 311
ldi $k0, -4
// Words: 312
ldw $fp, $fp, $k0
// Words: 313
jr $ra
