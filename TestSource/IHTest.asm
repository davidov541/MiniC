//IHvoid: funcdecl 0, , 
IHvoid:// Words: 0
addi $sp, 11
// Words: 1
move $sp, $rr
// Words: 2
addi $0, -2
// Words: 3
sdw $ra, $sp, $rr
// Words: 4
addi $rr, -2
// Words: 5
sdw $fp, $sp, $rr
// Words: 6
move $fp, $sp
// Words: 7
addi $rr, -1
// Words: 8
// Words: 9
ldi $k2, 0
// Words: 10
swn $k2, $fp, $rr
// Words: 11
addi $rr, -2
// Words: 12
sdw $s0, $fp, $rr
// Words: 13
addi $rr, -2
// Words: 14
sdw $s1, $fp, $rr
//: loadi *tmp, , -1
// Words: 15
// Words: 16
ldi $k0, -1
//: store c, 0, *tmp
// Words: 17
// Words: 18
ldi $k2, -11
// Words: 19
sdw $k0, $fp, $k2
//: load *tmp, 0, c
// Words: 20
// Words: 21
ldi $k2, -11
// Words: 22
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 23
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 24
addi $sp, 2
// Words: 25
move $a, $sp
// Words: 26
move $sp, $rr
// Words: 27
// Words: 28
// Words: 29
// Words: 30
// Words: 31
// Words: 32
// Words: 33
la $k2, putcharint
// Words: 34
jalr $k2
// Words: 35
addi $sp, -2
// Words: 36
move $sp, $rr
//: funcend , , 
// Words: 37
addi $0, -2
// Words: 38
ldw $ra, $fp, $rr
// Words: 39
addi $rr, -5
// Words: 40
ldw $s0, $fp, $rr
// Words: 41
addi $rr, -2
// Words: 42
ldw $s1, $fp, $rr
// Words: 43
addi $fp, -11
// Words: 44
move $sp, $rr
// Words: 45
// Words: 46
ldi $k0, -4
// Words: 47
ldw $fp, $fp, $k0
// Words: 48
jr $ra
//mainint: funcdecl 1, , 
mainint:// Words: 49
addi $sp, 4
// Words: 50
move $gp, $rr
// Words: 51
move $sp, $rr
//: loadi *tmp, , -6
global:// Words: 52
// Words: 53
ldi $k0, -6
//: store currx, 0, *tmp
// Words: 54
addi $gp, -2
// Words: 55
sdw $k0, $0, $rr
//: loadi *tmp, , 0
// Words: 56
// Words: 57
ldi $k0, 0
//: store curry, 0, *tmp
// Words: 58
addi $gp, -4
// Words: 59
sdw $k0, $0, $rr
//: loadi *tmp, , 0
L2:// Words: 60
// Words: 61
ldi $k0, 0
//: store i, 0, *tmp
// Words: 62
// Words: 63
ldi $k2, -11
// Words: 64
sdw $k0, $fp, $k2
//: jump , , 
// Words: 65
// Words: 66
// Words: 67
// Words: 68
// Words: 69
// Words: 70
// Words: 71
la $k2, L2
// Words: 72
jr $k2
//: loadi *tmp, , 0
L3:// Words: 73
// Words: 74
ldi $k0, 0
//: jr , *tmp, 
// Words: 75
move $v, $k0
// Words: 76
addi $0, -2
// Words: 77
ldw $ra, $fp, $rr
// Words: 78
addi $rr, -3
// Words: 79
addi $rr, -2
// Words: 80
ldw $s0, $fp, $rr
// Words: 81
addi $rr, -2
// Words: 82
ldw $s1, $fp, $rr
// Words: 83
addi $fp, -11
// Words: 84
move $sp, $rr
// Words: 85
// Words: 86
ldi $k0, -4
// Words: 87
ldw $fp, $fp, $k0
// Words: 88
jr $ra
//putcharint: funcdecl 1, , 
putcharint:// Words: 89
addi $sp, 13
// Words: 90
move $sp, $rr
// Words: 91
addi $0, -2
// Words: 92
sdw $ra, $sp, $rr
// Words: 93
addi $rr, -2
// Words: 94
sdw $fp, $sp, $rr
// Words: 95
move $fp, $sp
// Words: 96
addi $rr, -1
// Words: 97
// Words: 98
ldi $k2, 1
// Words: 99
swn $k2, $fp, $rr
// Words: 100
addi $rr, -2
// Words: 101
sdw $s0, $fp, $rr
// Words: 102
addi $rr, -2
// Words: 103
sdw $s1, $fp, $rr
//: formal c, , 
// Words: 104
ldw $k2, $a, $0
// Words: 105
addi $0, -11
// Words: 106
sdw $k2, $fp, $rr
//: loadi *tmp, , 6
// Words: 107
// Words: 108
ldi $k0, 6
//: store intervalx, 0, *tmp
// Words: 109
// Words: 110
ldi $k2, -13
// Words: 111
sdw $k0, $fp, $k2
//: load *tmp, 0, currx
// Words: 112
addi $gp, -2
// Words: 113
ldw $k0, $0, $rr
//: push , , *tmp
// Words: 114
addi $sp, 2
// Words: 115
sdw $k0, $sp, $0
// Words: 116
move $sp, $rr
//: loadi *tmp, , 255
// Words: 117
// Words: 118
ldi $k0, 255
//: push , , *tmp
// Words: 119
addi $sp, 2
// Words: 120
sdw $k0, $sp, $0
// Words: 121
move $sp, $rr
//: load *tmp, 0, intervalx
// Words: 122
// Words: 123
ldi $k2, -13
// Words: 124
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 125
// Words: 126
ldi $k1, 1
//: << *tmp2, *tmp2, *tmp
// Words: 127
sll $k0, $k1
// Words: 128
move $k1, $rr
//: pop *tmp, , 
// Words: 129
addi $sp, -2
// Words: 130
move $sp, $rr
// Words: 131
ldw $k0, $sp, $0
//: - *tmp2, *tmp2, *tmp
// Words: 132
sub $k0, $k1
// Words: 133
move $k1, $rr
//: pop *tmp, , 
// Words: 134
addi $sp, -2
// Words: 135
move $sp, $rr
// Words: 136
ldw $k0, $sp, $0
//: > *tmp, *tmp2, *tmp
// Words: 137
// Words: 138
// Words: 139
// Words: 140
// Words: 141
// Words: 142
// Words: 143
la $k2, L12
// Words: 144
bgt $k0, $k1, $k2
// Words: 145
// Words: 146
ldi $k0, 0
// Words: 147
// Words: 148
// Words: 149
// Words: 150
// Words: 151
// Words: 152
// Words: 153
la $k2, L13
// Words: 154
jr $k2
// Words: 155
// Words: 156
L12:ldi $k0, 1
L13:
//: push , , *tmp
// Words: 157
addi $sp, 2
// Words: 158
sdw $k0, $sp, $0
// Words: 159
move $sp, $rr
//: load *tmp, 0, c
// Words: 160
// Words: 161
ldi $k2, -11
// Words: 162
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 163
// Words: 164
ldi $k1, 10
//: == *tmp2, *tmp2, *tmp
// Words: 165
// Words: 166
// Words: 167
// Words: 168
// Words: 169
// Words: 170
// Words: 171
la $k2, L14
// Words: 172
beq $k0, $k1, $k2
// Words: 173
// Words: 174
ldi $k1, 0
// Words: 175
// Words: 176
// Words: 177
// Words: 178
// Words: 179
// Words: 180
// Words: 181
la $k2, L15
// Words: 182
jr $k2
// Words: 183
// Words: 184
L14:ldi $k1, 1
L15:
//: pop *tmp, , 
// Words: 185
addi $sp, -2
// Words: 186
move $sp, $rr
// Words: 187
ldw $k0, $sp, $0
//: || *tmp, *tmp2, *tmp
// Words: 188
// Words: 189
// Words: 190
// Words: 191
// Words: 192
// Words: 193
// Words: 194
la $k2, L16
// Words: 195
bne $0, $k0, $k2
// Words: 196
bne $0, $k1, $k2
// Words: 197
move $k0, $0
// Words: 198
// Words: 199
// Words: 200
// Words: 201
// Words: 202
// Words: 203
// Words: 204
la $k2, L17
// Words: 205
jr $k2
// Words: 206
// Words: 207
L16: ldi $k0, 1
// Words: 208
L17: nop
//: if *tmp, , 
// Words: 209
// Words: 210
// Words: 211
// Words: 212
// Words: 213
// Words: 214
// Words: 215
la $k2, L6
// Words: 216
beq $k0, $0, $k2
//: loadi *tmp, , 0
L5:// Words: 217
// Words: 218
ldi $k0, 0
//: store currx, 0, *tmp
// Words: 219
addi $gp, -2
// Words: 220
sdw $k0, $0, $rr
//: load *tmp, 0, curry
// Words: 221
addi $gp, -4
// Words: 222
ldw $k0, $0, $rr
//: loadi *tmp2, , 10
// Words: 223
// Words: 224
ldi $k1, 10
//: + *tmp, *tmp2, *tmp
// Words: 225
add $k0, $k1
// Words: 226
move $k0, $rr
//: store curry, 0, *tmp
// Words: 227
addi $gp, -4
// Words: 228
sdw $k0, $0, $rr
// Words: 229
// Words: 230
// Words: 231
// Words: 232
// Words: 233
// Words: 234
// Words: 235
la $k2, L7
// Words: 236
jr $k2
//: load *tmp, 0, currx
L6:// Words: 237
addi $gp, -2
// Words: 238
ldw $k0, $0, $rr
//: load *tmp2, 0, intervalx
// Words: 239
// Words: 240
ldi $k2, -13
// Words: 241
ldw $k1, $fp, $k2
//: + *tmp, *tmp2, *tmp
// Words: 242
add $k0, $k1
// Words: 243
move $k0, $rr
//: store currx, 0, *tmp
// Words: 244
addi $gp, -2
// Words: 245
sdw $k0, $0, $rr
//: load *tmp, 0, c
L7:// Words: 246
// Words: 247
ldi $k2, -11
// Words: 248
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 249
// Words: 250
ldi $k1, 10
//: beq , *tmp2, *tmp
// Words: 251
// Words: 252
// Words: 253
// Words: 254
// Words: 255
// Words: 256
// Words: 257
la $k2, L11
// Words: 258
beq $k0, $k1, $k2
//: assembly rp $v, 3, , 
L8:// Words: 259
rp $v, 3
//: move *tmp, , *v
// Words: 260
move $k0, $v
//: loadi *tmp2, , 0
// Words: 261
// Words: 262
ldi $k1, 0
//: blte , *tmp2, *tmp
// Words: 263
// Words: 264
// Words: 265
// Words: 266
// Words: 267
// Words: 268
// Words: 269
la $k2, L10
// Words: 270
blt $k0, $k1, $k2
// Words: 271
beq $k0, $k1, $k2
//: jump , , 
L9:// Words: 272
// Words: 273
// Words: 274
// Words: 275
// Words: 276
// Words: 277
// Words: 278
la $k2, L8
// Words: 279
jr $k2
//: assembly ldi $k0, 512;add $k0, $s1;wp $rr, 3;ldi $k0, 1024;add $k0, $s0;wp $rr, 3;ldi $k0, 1543;wp $k0, 3;, , 
L10:// Words: 280
addi $gp, -2
// Words: 281
ldw $s1, $0, $rr
// Words: 282
addi $gp, -4
// Words: 283
ldw $s0, $0, $rr
// Words: 284
ldi $k0, 512
// Words: 285
add $k0, $s1
// Words: 286
wp $rr, 3
// Words: 287
ldi $k0, 1024
// Words: 288
add $k0, $s0
// Words: 289
wp $rr, 3
// Words: 290
ldi $k0, 1543
// Words: 291
wp $k0, 3
//: move *tmp, , *v
// Words: 292
move $k0, $v
//: assembly ldi $s0, 2048;add $s0, $s1;wp $rr, 3, , 
// Words: 293
// Words: 294
ldi $k2, -11
// Words: 295
ldw $s1, $fp, $k2
// Words: 296
ldi $s0, 2048
// Words: 297
add $s0, $s1
// Words: 298
wp $rr, 3
//: move *tmp, , *v
// Words: 299
move $k0, $v
//: load *tmp, 0, c
L11:// Words: 300
// Words: 301
ldi $k2, -11
// Words: 302
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 303
move $v, $k0
// Words: 304
addi $0, -2
// Words: 305
ldw $ra, $fp, $rr
// Words: 306
addi $rr, -3
// Words: 307
addi $rr, -2
// Words: 308
ldw $s0, $fp, $rr
// Words: 309
addi $rr, -2
// Words: 310
ldw $s1, $fp, $rr
// Words: 311
addi $fp, -13
// Words: 312
move $sp, $rr
// Words: 313
// Words: 314
ldi $k0, -4
// Words: 315
ldw $fp, $fp, $k0
// Words: 316
jr $ra
