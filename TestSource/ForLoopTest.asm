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
//: loadi *tmp, , 0
// Words: 26
// Words: 27
ldi $k0, 0
//: store i, 0, *tmp
// Words: 28
// Words: 29
ldi $k2, -11
// Words: 30
sdw $k0, $fp, $k2
//: loadi *tmp, , 0
// Words: 31
// Words: 32
ldi $k0, 0
//: store i, 0, *tmp
// Words: 33
// Words: 34
ldi $k2, -11
// Words: 35
sdw $k0, $fp, $k2
//: load *tmp, 0, i
L1:// Words: 36
// Words: 37
ldi $k2, -11
// Words: 38
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 39
// Words: 40
ldi $k1, 10
//: bgte , *tmp2, *tmp
// Words: 41
// Words: 42
// Words: 43
// Words: 44
// Words: 45
// Words: 46
// Words: 47
la $k2, L3
// Words: 48
bgt $k0, $k1, $k2
// Words: 49
beq $k0, $k1, $k2
//: load *tmp, 0, i
L2:// Words: 50
// Words: 51
ldi $k2, -11
// Words: 52
ldw $k0, $fp, $k2
//: loadi *tmp2, , 48
// Words: 53
// Words: 54
ldi $k1, 48
//: + *tmp, *tmp2, *tmp
// Words: 55
add $k0, $k1
// Words: 56
move $k0, $rr
//: param *tmp, , 
// Words: 57
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 58
addi $sp, 2
// Words: 59
move $a, $sp
// Words: 60
move $sp, $rr
// Words: 61
// Words: 62
// Words: 63
// Words: 64
// Words: 65
// Words: 66
// Words: 67
la $k2, putcharint
// Words: 68
jalr $k2
// Words: 69
addi $sp, -2
// Words: 70
move $sp, $rr
//: load *tmp, 0, i
// Words: 71
// Words: 72
ldi $k2, -11
// Words: 73
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 74
// Words: 75
ldi $k1, 1
//: + *tmp, *tmp2, *tmp
// Words: 76
add $k0, $k1
// Words: 77
move $k0, $rr
//: store i, 0, *tmp
// Words: 78
// Words: 79
ldi $k2, -11
// Words: 80
sdw $k0, $fp, $k2
//: jump , , 
// Words: 81
// Words: 82
// Words: 83
// Words: 84
// Words: 85
// Words: 86
// Words: 87
la $k2, L1
// Words: 88
jr $k2
//: loadi *tmp, , 0
L3:// Words: 89
// Words: 90
ldi $k0, 0
//: store i, 0, *tmp
// Words: 91
// Words: 92
ldi $k2, -11
// Words: 93
sdw $k0, $fp, $k2
//: jump , , 
// Words: 94
// Words: 95
// Words: 96
// Words: 97
// Words: 98
// Words: 99
// Words: 100
la $k2, L3
// Words: 101
jr $k2
//: loadi *tmp, , 0
L4:// Words: 102
// Words: 103
ldi $k0, 0
//: jr , *tmp, 
// Words: 104
move $v, $k0
// Words: 105
addi $0, -2
// Words: 106
ldw $ra, $fp, $rr
// Words: 107
addi $rr, -3
// Words: 108
addi $rr, -2
// Words: 109
ldw $s0, $fp, $rr
// Words: 110
addi $rr, -2
// Words: 111
ldw $s1, $fp, $rr
// Words: 112
addi $fp, -11
// Words: 113
move $sp, $rr
// Words: 114
// Words: 115
ldi $k0, -4
// Words: 116
ldw $fp, $fp, $k0
// Words: 117
jr $ra
//putcharint: funcdecl 1, , 
putcharint:// Words: 118
addi $sp, 13
// Words: 119
move $sp, $rr
// Words: 120
addi $0, -2
// Words: 121
sdw $ra, $sp, $rr
// Words: 122
addi $rr, -2
// Words: 123
sdw $fp, $sp, $rr
// Words: 124
move $fp, $sp
// Words: 125
addi $rr, -1
// Words: 126
// Words: 127
ldi $k2, 1
// Words: 128
swn $k2, $fp, $rr
// Words: 129
addi $rr, -2
// Words: 130
sdw $s0, $fp, $rr
// Words: 131
addi $rr, -2
// Words: 132
sdw $s1, $fp, $rr
//: formal c, , 
// Words: 133
ldw $k2, $a, $0
// Words: 134
addi $0, -11
// Words: 135
sdw $k2, $fp, $rr
//: loadi *tmp, , 6
// Words: 136
// Words: 137
ldi $k0, 6
//: store intervalx, 0, *tmp
// Words: 138
// Words: 139
ldi $k2, -13
// Words: 140
sdw $k0, $fp, $k2
//: load *tmp, 0, currx
// Words: 141
addi $gp, -2
// Words: 142
ldw $k0, $0, $rr
//: push , , *tmp
// Words: 143
addi $sp, 2
// Words: 144
sdw $k0, $sp, $0
// Words: 145
move $sp, $rr
//: loadi *tmp, , 255
// Words: 146
// Words: 147
ldi $k0, 255
//: push , , *tmp
// Words: 148
addi $sp, 2
// Words: 149
sdw $k0, $sp, $0
// Words: 150
move $sp, $rr
//: load *tmp, 0, intervalx
// Words: 151
// Words: 152
ldi $k2, -13
// Words: 153
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 154
// Words: 155
ldi $k1, 1
//: << *tmp2, *tmp2, *tmp
// Words: 156
sll $k0, $k1
// Words: 157
move $k1, $rr
//: pop *tmp, , 
// Words: 158
addi $sp, -2
// Words: 159
move $sp, $rr
// Words: 160
ldw $k0, $sp, $0
//: - *tmp2, *tmp2, *tmp
// Words: 161
sub $k0, $k1
// Words: 162
move $k1, $rr
//: pop *tmp, , 
// Words: 163
addi $sp, -2
// Words: 164
move $sp, $rr
// Words: 165
ldw $k0, $sp, $0
//: > *tmp, *tmp2, *tmp
// Words: 166
// Words: 167
// Words: 168
// Words: 169
// Words: 170
// Words: 171
// Words: 172
la $k2, L13
// Words: 173
bgt $k0, $k1, $k2
// Words: 174
// Words: 175
ldi $k0, 0
// Words: 176
// Words: 177
// Words: 178
// Words: 179
// Words: 180
// Words: 181
// Words: 182
la $k2, L14
// Words: 183
jr $k2
// Words: 184
// Words: 185
L13:ldi $k0, 1
L14:
//: push , , *tmp
// Words: 186
addi $sp, 2
// Words: 187
sdw $k0, $sp, $0
// Words: 188
move $sp, $rr
//: load *tmp, 0, c
// Words: 189
// Words: 190
ldi $k2, -11
// Words: 191
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 192
// Words: 193
ldi $k1, 10
//: == *tmp2, *tmp2, *tmp
// Words: 194
// Words: 195
// Words: 196
// Words: 197
// Words: 198
// Words: 199
// Words: 200
la $k2, L15
// Words: 201
beq $k0, $k1, $k2
// Words: 202
// Words: 203
ldi $k1, 0
// Words: 204
// Words: 205
// Words: 206
// Words: 207
// Words: 208
// Words: 209
// Words: 210
la $k2, L16
// Words: 211
jr $k2
// Words: 212
// Words: 213
L15:ldi $k1, 1
L16:
//: pop *tmp, , 
// Words: 214
addi $sp, -2
// Words: 215
move $sp, $rr
// Words: 216
ldw $k0, $sp, $0
//: || *tmp, *tmp2, *tmp
// Words: 217
// Words: 218
// Words: 219
// Words: 220
// Words: 221
// Words: 222
// Words: 223
la $k2, L17
// Words: 224
bne $0, $k0, $k2
// Words: 225
bne $0, $k1, $k2
// Words: 226
move $k0, $0
// Words: 227
// Words: 228
// Words: 229
// Words: 230
// Words: 231
// Words: 232
// Words: 233
la $k2, L18
// Words: 234
jr $k2
// Words: 235
// Words: 236
L17: ldi $k0, 1
// Words: 237
L18: nop
//: if *tmp, , 
// Words: 238
// Words: 239
// Words: 240
// Words: 241
// Words: 242
// Words: 243
// Words: 244
la $k2, L7
// Words: 245
beq $k0, $0, $k2
//: loadi *tmp, , 0
L6:// Words: 246
// Words: 247
ldi $k0, 0
//: store currx, 0, *tmp
// Words: 248
addi $gp, -2
// Words: 249
sdw $k0, $0, $rr
//: load *tmp, 0, curry
// Words: 250
addi $gp, -4
// Words: 251
ldw $k0, $0, $rr
//: loadi *tmp2, , 10
// Words: 252
// Words: 253
ldi $k1, 10
//: + *tmp, *tmp2, *tmp
// Words: 254
add $k0, $k1
// Words: 255
move $k0, $rr
//: store curry, 0, *tmp
// Words: 256
addi $gp, -4
// Words: 257
sdw $k0, $0, $rr
// Words: 258
// Words: 259
// Words: 260
// Words: 261
// Words: 262
// Words: 263
// Words: 264
la $k2, L8
// Words: 265
jr $k2
//: load *tmp, 0, currx
L7:// Words: 266
addi $gp, -2
// Words: 267
ldw $k0, $0, $rr
//: load *tmp2, 0, intervalx
// Words: 268
// Words: 269
ldi $k2, -13
// Words: 270
ldw $k1, $fp, $k2
//: + *tmp, *tmp2, *tmp
// Words: 271
add $k0, $k1
// Words: 272
move $k0, $rr
//: store currx, 0, *tmp
// Words: 273
addi $gp, -2
// Words: 274
sdw $k0, $0, $rr
//: load *tmp, 0, c
L8:// Words: 275
// Words: 276
ldi $k2, -11
// Words: 277
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 278
// Words: 279
ldi $k1, 10
//: beq , *tmp2, *tmp
// Words: 280
// Words: 281
// Words: 282
// Words: 283
// Words: 284
// Words: 285
// Words: 286
la $k2, L12
// Words: 287
beq $k0, $k1, $k2
//: assembly rp $v, 3, , 
L9:// Words: 288
rp $v, 3
//: move *tmp, , *v
// Words: 289
move $k0, $v
//: loadi *tmp2, , 0
// Words: 290
// Words: 291
ldi $k1, 0
//: blte , *tmp2, *tmp
// Words: 292
// Words: 293
// Words: 294
// Words: 295
// Words: 296
// Words: 297
// Words: 298
la $k2, L11
// Words: 299
blt $k0, $k1, $k2
// Words: 300
beq $k0, $k1, $k2
//: jump , , 
L10:// Words: 301
// Words: 302
// Words: 303
// Words: 304
// Words: 305
// Words: 306
// Words: 307
la $k2, L9
// Words: 308
jr $k2
//: assembly ldi $k0, 512;add $k0, $s1;wp $rr, 3;ldi $k0, 1024;add $k0, $s0;wp $rr, 3;ldi $k0, 1543;wp $k0, 3;, , 
L11:// Words: 309
addi $gp, -2
// Words: 310
ldw $s1, $0, $rr
// Words: 311
addi $gp, -4
// Words: 312
ldw $s0, $0, $rr
// Words: 313
ldi $k0, 512
// Words: 314
add $k0, $s1
// Words: 315
wp $rr, 3
// Words: 316
ldi $k0, 1024
// Words: 317
add $k0, $s0
// Words: 318
wp $rr, 3
// Words: 319
ldi $k0, 1543
// Words: 320
wp $k0, 3
//: move *tmp, , *v
// Words: 321
move $k0, $v
//: assembly ldi $s0, 2048;add $s0, $s1;wp $rr, 3, , 
// Words: 322
// Words: 323
ldi $k2, -11
// Words: 324
ldw $s1, $fp, $k2
// Words: 325
ldi $s0, 2048
// Words: 326
add $s0, $s1
// Words: 327
wp $rr, 3
//: move *tmp, , *v
// Words: 328
move $k0, $v
//: load *tmp, 0, c
L12:// Words: 329
// Words: 330
ldi $k2, -11
// Words: 331
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 332
move $v, $k0
// Words: 333
addi $0, -2
// Words: 334
ldw $ra, $fp, $rr
// Words: 335
addi $rr, -3
// Words: 336
addi $rr, -2
// Words: 337
ldw $s0, $fp, $rr
// Words: 338
addi $rr, -2
// Words: 339
ldw $s1, $fp, $rr
// Words: 340
addi $fp, -13
// Words: 341
move $sp, $rr
// Words: 342
// Words: 343
ldi $k0, -4
// Words: 344
ldw $fp, $fp, $k0
// Words: 345
jr $ra
