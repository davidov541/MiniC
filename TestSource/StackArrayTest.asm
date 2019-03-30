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
addi $sp, 17
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
//: loadi *tmp, , 12
// Words: 26
// Words: 27
ldi $k0, 12
//: store arrLen, 0, *tmp
// Words: 28
// Words: 29
ldi $k2, -13
// Words: 30
sdw $k0, $fp, $k2
//: load *tmp, 0, arrLen
// Words: 31
// Words: 32
ldi $k2, -13
// Words: 33
ldw $k0, $fp, $k2
//: <<i *tmp, 1, *tmp
// Words: 34
slli $k0, 1
// Words: 35
move $k0, $rr
//: pusharr *tmp, , *tmp
// Words: 36
add $sp, $k0
// Words: 37
move $k0, $sp
// Words: 38
move $sp, $rr
//: store str, 0, *tmp
// Words: 39
// Words: 40
ldi $k2, -15
// Words: 41
sdw $k0, $fp, $k2
//: loadi *tmp, , 72
// Words: 42
// Words: 43
ldi $k0, 72
//: push , , *tmp
// Words: 44
addi $sp, 2
// Words: 45
sdw $k0, $sp, $0
// Words: 46
move $sp, $rr
//: load *tmp, 0, str
// Words: 47
// Words: 48
ldi $k2, -15
// Words: 49
ldw $k0, $fp, $k2
//: loadi *tmp2, , 0
// Words: 50
// Words: 51
ldi $k1, 0
//: <<i *tmp2, 1, *tmp2
// Words: 52
slli $k1, 1
// Words: 53
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 54
add $k0, $k1
// Words: 55
move $k1, $rr
//: pop *tmp, , 
// Words: 56
addi $sp, -2
// Words: 57
move $sp, $rr
// Words: 58
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 59
sdw $k0, $0, $k1
//: loadi *tmp, , 101
// Words: 60
// Words: 61
ldi $k0, 101
//: push , , *tmp
// Words: 62
addi $sp, 2
// Words: 63
sdw $k0, $sp, $0
// Words: 64
move $sp, $rr
//: load *tmp, 0, str
// Words: 65
// Words: 66
ldi $k2, -15
// Words: 67
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 68
// Words: 69
ldi $k1, 1
//: <<i *tmp2, 1, *tmp2
// Words: 70
slli $k1, 1
// Words: 71
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 72
add $k0, $k1
// Words: 73
move $k1, $rr
//: pop *tmp, , 
// Words: 74
addi $sp, -2
// Words: 75
move $sp, $rr
// Words: 76
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 77
sdw $k0, $0, $k1
//: loadi *tmp, , 108
// Words: 78
// Words: 79
ldi $k0, 108
//: push , , *tmp
// Words: 80
addi $sp, 2
// Words: 81
sdw $k0, $sp, $0
// Words: 82
move $sp, $rr
//: load *tmp, 0, str
// Words: 83
// Words: 84
ldi $k2, -15
// Words: 85
ldw $k0, $fp, $k2
//: loadi *tmp2, , 2
// Words: 86
// Words: 87
ldi $k1, 2
//: <<i *tmp2, 1, *tmp2
// Words: 88
slli $k1, 1
// Words: 89
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 90
add $k0, $k1
// Words: 91
move $k1, $rr
//: pop *tmp, , 
// Words: 92
addi $sp, -2
// Words: 93
move $sp, $rr
// Words: 94
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 95
sdw $k0, $0, $k1
//: loadi *tmp, , 108
// Words: 96
// Words: 97
ldi $k0, 108
//: push , , *tmp
// Words: 98
addi $sp, 2
// Words: 99
sdw $k0, $sp, $0
// Words: 100
move $sp, $rr
//: load *tmp, 0, str
// Words: 101
// Words: 102
ldi $k2, -15
// Words: 103
ldw $k0, $fp, $k2
//: loadi *tmp2, , 3
// Words: 104
// Words: 105
ldi $k1, 3
//: <<i *tmp2, 1, *tmp2
// Words: 106
slli $k1, 1
// Words: 107
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 108
add $k0, $k1
// Words: 109
move $k1, $rr
//: pop *tmp, , 
// Words: 110
addi $sp, -2
// Words: 111
move $sp, $rr
// Words: 112
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 113
sdw $k0, $0, $k1
//: loadi *tmp, , 111
// Words: 114
// Words: 115
ldi $k0, 111
//: push , , *tmp
// Words: 116
addi $sp, 2
// Words: 117
sdw $k0, $sp, $0
// Words: 118
move $sp, $rr
//: load *tmp, 0, str
// Words: 119
// Words: 120
ldi $k2, -15
// Words: 121
ldw $k0, $fp, $k2
//: loadi *tmp2, , 4
// Words: 122
// Words: 123
ldi $k1, 4
//: <<i *tmp2, 1, *tmp2
// Words: 124
slli $k1, 1
// Words: 125
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 126
add $k0, $k1
// Words: 127
move $k1, $rr
//: pop *tmp, , 
// Words: 128
addi $sp, -2
// Words: 129
move $sp, $rr
// Words: 130
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 131
sdw $k0, $0, $k1
//: loadi *tmp, , 32
// Words: 132
// Words: 133
ldi $k0, 32
//: push , , *tmp
// Words: 134
addi $sp, 2
// Words: 135
sdw $k0, $sp, $0
// Words: 136
move $sp, $rr
//: load *tmp, 0, str
// Words: 137
// Words: 138
ldi $k2, -15
// Words: 139
ldw $k0, $fp, $k2
//: loadi *tmp2, , 5
// Words: 140
// Words: 141
ldi $k1, 5
//: <<i *tmp2, 1, *tmp2
// Words: 142
slli $k1, 1
// Words: 143
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 144
add $k0, $k1
// Words: 145
move $k1, $rr
//: pop *tmp, , 
// Words: 146
addi $sp, -2
// Words: 147
move $sp, $rr
// Words: 148
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 149
sdw $k0, $0, $k1
//: loadi *tmp, , 87
// Words: 150
// Words: 151
ldi $k0, 87
//: push , , *tmp
// Words: 152
addi $sp, 2
// Words: 153
sdw $k0, $sp, $0
// Words: 154
move $sp, $rr
//: load *tmp, 0, str
// Words: 155
// Words: 156
ldi $k2, -15
// Words: 157
ldw $k0, $fp, $k2
//: loadi *tmp2, , 6
// Words: 158
// Words: 159
ldi $k1, 6
//: <<i *tmp2, 1, *tmp2
// Words: 160
slli $k1, 1
// Words: 161
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 162
add $k0, $k1
// Words: 163
move $k1, $rr
//: pop *tmp, , 
// Words: 164
addi $sp, -2
// Words: 165
move $sp, $rr
// Words: 166
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 167
sdw $k0, $0, $k1
//: loadi *tmp, , 111
// Words: 168
// Words: 169
ldi $k0, 111
//: push , , *tmp
// Words: 170
addi $sp, 2
// Words: 171
sdw $k0, $sp, $0
// Words: 172
move $sp, $rr
//: load *tmp, 0, str
// Words: 173
// Words: 174
ldi $k2, -15
// Words: 175
ldw $k0, $fp, $k2
//: loadi *tmp2, , 7
// Words: 176
// Words: 177
ldi $k1, 7
//: <<i *tmp2, 1, *tmp2
// Words: 178
slli $k1, 1
// Words: 179
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 180
add $k0, $k1
// Words: 181
move $k1, $rr
//: pop *tmp, , 
// Words: 182
addi $sp, -2
// Words: 183
move $sp, $rr
// Words: 184
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 185
sdw $k0, $0, $k1
//: loadi *tmp, , 114
// Words: 186
// Words: 187
ldi $k0, 114
//: push , , *tmp
// Words: 188
addi $sp, 2
// Words: 189
sdw $k0, $sp, $0
// Words: 190
move $sp, $rr
//: load *tmp, 0, str
// Words: 191
// Words: 192
ldi $k2, -15
// Words: 193
ldw $k0, $fp, $k2
//: loadi *tmp2, , 8
// Words: 194
// Words: 195
ldi $k1, 8
//: <<i *tmp2, 1, *tmp2
// Words: 196
slli $k1, 1
// Words: 197
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 198
add $k0, $k1
// Words: 199
move $k1, $rr
//: pop *tmp, , 
// Words: 200
addi $sp, -2
// Words: 201
move $sp, $rr
// Words: 202
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 203
sdw $k0, $0, $k1
//: loadi *tmp, , 108
// Words: 204
// Words: 205
ldi $k0, 108
//: push , , *tmp
// Words: 206
addi $sp, 2
// Words: 207
sdw $k0, $sp, $0
// Words: 208
move $sp, $rr
//: load *tmp, 0, str
// Words: 209
// Words: 210
ldi $k2, -15
// Words: 211
ldw $k0, $fp, $k2
//: loadi *tmp2, , 9
// Words: 212
// Words: 213
ldi $k1, 9
//: <<i *tmp2, 1, *tmp2
// Words: 214
slli $k1, 1
// Words: 215
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 216
add $k0, $k1
// Words: 217
move $k1, $rr
//: pop *tmp, , 
// Words: 218
addi $sp, -2
// Words: 219
move $sp, $rr
// Words: 220
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 221
sdw $k0, $0, $k1
//: loadi *tmp, , 100
// Words: 222
// Words: 223
ldi $k0, 100
//: push , , *tmp
// Words: 224
addi $sp, 2
// Words: 225
sdw $k0, $sp, $0
// Words: 226
move $sp, $rr
//: load *tmp, 0, str
// Words: 227
// Words: 228
ldi $k2, -15
// Words: 229
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 230
// Words: 231
ldi $k1, 10
//: <<i *tmp2, 1, *tmp2
// Words: 232
slli $k1, 1
// Words: 233
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 234
add $k0, $k1
// Words: 235
move $k1, $rr
//: pop *tmp, , 
// Words: 236
addi $sp, -2
// Words: 237
move $sp, $rr
// Words: 238
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 239
sdw $k0, $0, $k1
//: loadi *tmp, , 0
// Words: 240
// Words: 241
ldi $k0, 0
//: push , , *tmp
// Words: 242
addi $sp, 2
// Words: 243
sdw $k0, $sp, $0
// Words: 244
move $sp, $rr
//: load *tmp, 0, str
// Words: 245
// Words: 246
ldi $k2, -15
// Words: 247
ldw $k0, $fp, $k2
//: loadi *tmp2, , 11
// Words: 248
// Words: 249
ldi $k1, 11
//: <<i *tmp2, 1, *tmp2
// Words: 250
slli $k1, 1
// Words: 251
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 252
add $k0, $k1
// Words: 253
move $k1, $rr
//: pop *tmp, , 
// Words: 254
addi $sp, -2
// Words: 255
move $sp, $rr
// Words: 256
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 257
sdw $k0, $0, $k1
//: loadi *tmp, , 0
// Words: 258
// Words: 259
ldi $k0, 0
//: store i, 0, *tmp
// Words: 260
// Words: 261
ldi $k2, -17
// Words: 262
sdw $k0, $fp, $k2
//: load *tmp, 0, str
// Words: 263
// Words: 264
ldi $k2, -15
// Words: 265
ldw $k0, $fp, $k2
//: load *tmp2, 0, i
// Words: 266
// Words: 267
ldi $k2, -17
// Words: 268
ldw $k1, $fp, $k2
//: <<i *tmp2, 1, *tmp2
// Words: 269
slli $k1, 1
// Words: 270
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 271
add $k0, $k1
// Words: 272
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 273
ldw $k0, $0, $k0
//: store currChar, 0, *tmp
// Words: 274
// Words: 275
ldi $k2, -11
// Words: 276
sdw $k0, $fp, $k2
//: loadi *tmp, , 10
// Words: 277
// Words: 278
ldi $k0, 10
//: param *tmp, , 
// Words: 279
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 280
addi $sp, 2
// Words: 281
move $a, $sp
// Words: 282
move $sp, $rr
// Words: 283
// Words: 284
// Words: 285
// Words: 286
// Words: 287
// Words: 288
// Words: 289
la $k2, putcharint
// Words: 290
jalr $k2
// Words: 291
addi $sp, -2
// Words: 292
move $sp, $rr
//: loadi *tmp, , 10
// Words: 293
// Words: 294
ldi $k0, 10
//: param *tmp, , 
// Words: 295
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 296
addi $sp, 2
// Words: 297
move $a, $sp
// Words: 298
move $sp, $rr
// Words: 299
// Words: 300
// Words: 301
// Words: 302
// Words: 303
// Words: 304
// Words: 305
la $k2, putcharint
// Words: 306
jalr $k2
// Words: 307
addi $sp, -2
// Words: 308
move $sp, $rr
//: load *tmp, 0, str
// Words: 309
// Words: 310
ldi $k2, -15
// Words: 311
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 312
sdw $k0, $sp, $0
//: funccall , 1, putsint
// Words: 313
addi $sp, 2
// Words: 314
move $a, $sp
// Words: 315
move $sp, $rr
// Words: 316
// Words: 317
// Words: 318
// Words: 319
// Words: 320
// Words: 321
// Words: 322
la $k2, putsint
// Words: 323
jalr $k2
// Words: 324
addi $sp, -2
// Words: 325
move $sp, $rr
//: assembly rp $v, 2, , 
L1:// Words: 326
rp $v, 2
//: move *tmp, , *v
// Words: 327
move $k0, $v
//: load *tmp2, 0, i
// Words: 328
// Words: 329
ldi $k2, -17
// Words: 330
ldw $k1, $fp, $k2
//: bne , *tmp2, *tmp
// Words: 331
// Words: 332
// Words: 333
// Words: 334
// Words: 335
// Words: 336
// Words: 337
la $k2, L3
// Words: 338
bne $k0, $k1, $k2
//: jump , , 
L2:// Words: 339
// Words: 340
// Words: 341
// Words: 342
// Words: 343
// Words: 344
// Words: 345
la $k2, L1
// Words: 346
jr $k2
//: assembly rp $v, 2, , 
L3:// Words: 347
rp $v, 2
//: move *tmp, , *v
// Words: 348
move $k0, $v
//: store i, 0, *tmp
// Words: 349
// Words: 350
ldi $k2, -17
// Words: 351
sdw $k0, $fp, $k2
//: load *tmp, 0, i
// Words: 352
// Words: 353
ldi $k2, -17
// Words: 354
ldw $k0, $fp, $k2
//: load *tmp2, 0, arrLen
// Words: 355
// Words: 356
ldi $k2, -13
// Words: 357
ldw $k1, $fp, $k2
//: bgte , *tmp2, *tmp
// Words: 358
// Words: 359
// Words: 360
// Words: 361
// Words: 362
// Words: 363
// Words: 364
la $k2, L5
// Words: 365
bgt $k0, $k1, $k2
// Words: 366
beq $k0, $k1, $k2
//: load *tmp, 0, str
L4:// Words: 367
// Words: 368
ldi $k2, -15
// Words: 369
ldw $k0, $fp, $k2
//: load *tmp2, 0, i
// Words: 370
// Words: 371
ldi $k2, -17
// Words: 372
ldw $k1, $fp, $k2
//: <<i *tmp2, 1, *tmp2
// Words: 373
slli $k1, 1
// Words: 374
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 375
add $k0, $k1
// Words: 376
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 377
ldw $k0, $0, $k0
//: store currChar, 0, *tmp
// Words: 378
// Words: 379
ldi $k2, -11
// Words: 380
sdw $k0, $fp, $k2
//: load *tmp, 0, currChar
L5:// Words: 381
// Words: 382
ldi $k2, -11
// Words: 383
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 384
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 385
addi $sp, 2
// Words: 386
move $a, $sp
// Words: 387
move $sp, $rr
// Words: 388
// Words: 389
// Words: 390
// Words: 391
// Words: 392
// Words: 393
// Words: 394
la $k2, putcharint
// Words: 395
jalr $k2
// Words: 396
addi $sp, -2
// Words: 397
move $sp, $rr
//: jump , , 
// Words: 398
// Words: 399
// Words: 400
// Words: 401
// Words: 402
// Words: 403
// Words: 404
la $k2, L1
// Words: 405
jr $k2
//: loadi *tmp, , 0
L6:// Words: 406
// Words: 407
ldi $k0, 0
//: jr , *tmp, 
// Words: 408
move $v, $k0
// Words: 409
addi $0, -2
// Words: 410
ldw $ra, $fp, $rr
// Words: 411
addi $rr, -3
// Words: 412
addi $rr, -2
// Words: 413
ldw $s0, $fp, $rr
// Words: 414
addi $rr, -2
// Words: 415
ldw $s1, $fp, $rr
// Words: 416
addi $fp, -17
// Words: 417
move $sp, $rr
// Words: 418
// Words: 419
ldi $k0, -4
// Words: 420
ldw $fp, $fp, $k0
// Words: 421
jr $ra
//putcharint: funcdecl 1, , 
putcharint:// Words: 422
addi $sp, 13
// Words: 423
move $sp, $rr
// Words: 424
addi $0, -2
// Words: 425
sdw $ra, $sp, $rr
// Words: 426
addi $rr, -2
// Words: 427
sdw $fp, $sp, $rr
// Words: 428
move $fp, $sp
// Words: 429
addi $rr, -1
// Words: 430
// Words: 431
ldi $k2, 1
// Words: 432
swn $k2, $fp, $rr
// Words: 433
addi $rr, -2
// Words: 434
sdw $s0, $fp, $rr
// Words: 435
addi $rr, -2
// Words: 436
sdw $s1, $fp, $rr
//: formal c, , 
// Words: 437
ldw $k2, $a, $0
// Words: 438
addi $0, -11
// Words: 439
sdw $k2, $fp, $rr
//: loadi *tmp, , 6
// Words: 440
// Words: 441
ldi $k0, 6
//: store intervalx, 0, *tmp
// Words: 442
// Words: 443
ldi $k2, -13
// Words: 444
sdw $k0, $fp, $k2
//: load *tmp, 0, currx
// Words: 445
addi $gp, -2
// Words: 446
ldw $k0, $0, $rr
//: push , , *tmp
// Words: 447
addi $sp, 2
// Words: 448
sdw $k0, $sp, $0
// Words: 449
move $sp, $rr
//: loadi *tmp, , 255
// Words: 450
// Words: 451
ldi $k0, 255
//: push , , *tmp
// Words: 452
addi $sp, 2
// Words: 453
sdw $k0, $sp, $0
// Words: 454
move $sp, $rr
//: load *tmp, 0, intervalx
// Words: 455
// Words: 456
ldi $k2, -13
// Words: 457
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 458
// Words: 459
ldi $k1, 1
//: << *tmp2, *tmp2, *tmp
// Words: 460
sll $k0, $k1
// Words: 461
move $k1, $rr
//: pop *tmp, , 
// Words: 462
addi $sp, -2
// Words: 463
move $sp, $rr
// Words: 464
ldw $k0, $sp, $0
//: - *tmp2, *tmp2, *tmp
// Words: 465
sub $k0, $k1
// Words: 466
move $k1, $rr
//: pop *tmp, , 
// Words: 467
addi $sp, -2
// Words: 468
move $sp, $rr
// Words: 469
ldw $k0, $sp, $0
//: > *tmp, *tmp2, *tmp
// Words: 470
// Words: 471
// Words: 472
// Words: 473
// Words: 474
// Words: 475
// Words: 476
la $k2, L19
// Words: 477
bgt $k0, $k1, $k2
// Words: 478
// Words: 479
ldi $k0, 0
// Words: 480
// Words: 481
// Words: 482
// Words: 483
// Words: 484
// Words: 485
// Words: 486
la $k2, L20
// Words: 487
jr $k2
// Words: 488
// Words: 489
L19:ldi $k0, 1
L20:
//: push , , *tmp
// Words: 490
addi $sp, 2
// Words: 491
sdw $k0, $sp, $0
// Words: 492
move $sp, $rr
//: load *tmp, 0, c
// Words: 493
// Words: 494
ldi $k2, -11
// Words: 495
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 496
// Words: 497
ldi $k1, 10
//: == *tmp2, *tmp2, *tmp
// Words: 498
// Words: 499
// Words: 500
// Words: 501
// Words: 502
// Words: 503
// Words: 504
la $k2, L21
// Words: 505
beq $k0, $k1, $k2
// Words: 506
// Words: 507
ldi $k1, 0
// Words: 508
// Words: 509
// Words: 510
// Words: 511
// Words: 512
// Words: 513
// Words: 514
la $k2, L22
// Words: 515
jr $k2
// Words: 516
// Words: 517
L21:ldi $k1, 1
L22:
//: pop *tmp, , 
// Words: 518
addi $sp, -2
// Words: 519
move $sp, $rr
// Words: 520
ldw $k0, $sp, $0
//: || *tmp, *tmp2, *tmp
// Words: 521
// Words: 522
// Words: 523
// Words: 524
// Words: 525
// Words: 526
// Words: 527
la $k2, L23
// Words: 528
bne $0, $k0, $k2
// Words: 529
bne $0, $k1, $k2
// Words: 530
move $k0, $0
// Words: 531
// Words: 532
// Words: 533
// Words: 534
// Words: 535
// Words: 536
// Words: 537
la $k2, L24
// Words: 538
jr $k2
// Words: 539
// Words: 540
L23: ldi $k0, 1
// Words: 541
L24: nop
//: if *tmp, , 
// Words: 542
// Words: 543
// Words: 544
// Words: 545
// Words: 546
// Words: 547
// Words: 548
la $k2, L9
// Words: 549
beq $k0, $0, $k2
//: loadi *tmp, , 0
L8:// Words: 550
// Words: 551
ldi $k0, 0
//: store currx, 0, *tmp
// Words: 552
addi $gp, -2
// Words: 553
sdw $k0, $0, $rr
//: load *tmp, 0, curry
// Words: 554
addi $gp, -4
// Words: 555
ldw $k0, $0, $rr
//: loadi *tmp2, , 10
// Words: 556
// Words: 557
ldi $k1, 10
//: + *tmp, *tmp2, *tmp
// Words: 558
add $k0, $k1
// Words: 559
move $k0, $rr
//: store curry, 0, *tmp
// Words: 560
addi $gp, -4
// Words: 561
sdw $k0, $0, $rr
// Words: 562
// Words: 563
// Words: 564
// Words: 565
// Words: 566
// Words: 567
// Words: 568
la $k2, L10
// Words: 569
jr $k2
//: load *tmp, 0, currx
L9:// Words: 570
addi $gp, -2
// Words: 571
ldw $k0, $0, $rr
//: load *tmp2, 0, intervalx
// Words: 572
// Words: 573
ldi $k2, -13
// Words: 574
ldw $k1, $fp, $k2
//: + *tmp, *tmp2, *tmp
// Words: 575
add $k0, $k1
// Words: 576
move $k0, $rr
//: store currx, 0, *tmp
// Words: 577
addi $gp, -2
// Words: 578
sdw $k0, $0, $rr
//: load *tmp, 0, c
L10:// Words: 579
// Words: 580
ldi $k2, -11
// Words: 581
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 582
// Words: 583
ldi $k1, 10
//: beq , *tmp2, *tmp
// Words: 584
// Words: 585
// Words: 586
// Words: 587
// Words: 588
// Words: 589
// Words: 590
la $k2, L14
// Words: 591
beq $k0, $k1, $k2
//: assembly rp $v, 3, , 
L11:// Words: 592
rp $v, 3
//: move *tmp, , *v
// Words: 593
move $k0, $v
//: loadi *tmp2, , 0
// Words: 594
// Words: 595
ldi $k1, 0
//: blte , *tmp2, *tmp
// Words: 596
// Words: 597
// Words: 598
// Words: 599
// Words: 600
// Words: 601
// Words: 602
la $k2, L13
// Words: 603
blt $k0, $k1, $k2
// Words: 604
beq $k0, $k1, $k2
//: jump , , 
L12:// Words: 605
// Words: 606
// Words: 607
// Words: 608
// Words: 609
// Words: 610
// Words: 611
la $k2, L11
// Words: 612
jr $k2
//: assembly ldi $k0, 512;add $k0, $s1;wp $rr, 3;ldi $k0, 1024;add $k0, $s0;wp $rr, 3;ldi $k0, 1543;wp $k0, 3;, , 
L13:// Words: 613
addi $gp, -2
// Words: 614
ldw $s1, $0, $rr
// Words: 615
addi $gp, -4
// Words: 616
ldw $s0, $0, $rr
// Words: 617
ldi $k0, 512
// Words: 618
add $k0, $s1
// Words: 619
wp $rr, 3
// Words: 620
ldi $k0, 1024
// Words: 621
add $k0, $s0
// Words: 622
wp $rr, 3
// Words: 623
ldi $k0, 1543
// Words: 624
wp $k0, 3
//: move *tmp, , *v
// Words: 625
move $k0, $v
//: assembly ldi $s0, 2048;add $s0, $s1;wp $rr, 3, , 
// Words: 626
// Words: 627
ldi $k2, -11
// Words: 628
ldw $s1, $fp, $k2
// Words: 629
ldi $s0, 2048
// Words: 630
add $s0, $s1
// Words: 631
wp $rr, 3
//: move *tmp, , *v
// Words: 632
move $k0, $v
//: load *tmp, 0, c
L14:// Words: 633
// Words: 634
ldi $k2, -11
// Words: 635
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 636
move $v, $k0
// Words: 637
addi $0, -2
// Words: 638
ldw $ra, $fp, $rr
// Words: 639
addi $rr, -3
// Words: 640
addi $rr, -2
// Words: 641
ldw $s0, $fp, $rr
// Words: 642
addi $rr, -2
// Words: 643
ldw $s1, $fp, $rr
// Words: 644
addi $fp, -13
// Words: 645
move $sp, $rr
// Words: 646
// Words: 647
ldi $k0, -4
// Words: 648
ldw $fp, $fp, $k0
// Words: 649
jr $ra
//putsint: funcdecl 1, , 
putsint:// Words: 650
addi $sp, 13
// Words: 651
move $sp, $rr
// Words: 652
addi $0, -2
// Words: 653
sdw $ra, $sp, $rr
// Words: 654
addi $rr, -2
// Words: 655
sdw $fp, $sp, $rr
// Words: 656
move $fp, $sp
// Words: 657
addi $rr, -1
// Words: 658
// Words: 659
ldi $k2, 1
// Words: 660
swn $k2, $fp, $rr
// Words: 661
addi $rr, -2
// Words: 662
sdw $s0, $fp, $rr
// Words: 663
addi $rr, -2
// Words: 664
sdw $s1, $fp, $rr
//: formal s, , 
// Words: 665
ldw $k2, $a, $0
// Words: 666
addi $0, -13
// Words: 667
sdw $k2, $fp, $rr
//: loadi *tmp, , 0
// Words: 668
// Words: 669
ldi $k0, 0
//: store i, 0, *tmp
// Words: 670
// Words: 671
ldi $k2, -11
// Words: 672
sdw $k0, $fp, $k2
//: load *tmp, 0, s
L16:// Words: 673
// Words: 674
ldi $k2, -13
// Words: 675
ldw $k0, $fp, $k2
//: load *tmp2, 0, i
// Words: 676
// Words: 677
ldi $k2, -11
// Words: 678
ldw $k1, $fp, $k2
//: <<i *tmp2, 1, *tmp2
// Words: 679
slli $k1, 1
// Words: 680
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 681
add $k0, $k1
// Words: 682
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 683
ldw $k0, $0, $k0
//: loadi *tmp2, , 0
// Words: 684
// Words: 685
ldi $k1, 0
//: beq , *tmp2, *tmp
// Words: 686
// Words: 687
// Words: 688
// Words: 689
// Words: 690
// Words: 691
// Words: 692
la $k2, L18
// Words: 693
beq $k0, $k1, $k2
//: load *tmp, 0, s
L17:// Words: 694
// Words: 695
ldi $k2, -13
// Words: 696
ldw $k0, $fp, $k2
//: load *tmp2, 0, i
// Words: 697
// Words: 698
ldi $k2, -11
// Words: 699
ldw $k1, $fp, $k2
//: <<i *tmp2, 1, *tmp2
// Words: 700
slli $k1, 1
// Words: 701
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 702
add $k0, $k1
// Words: 703
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 704
ldw $k0, $0, $k0
//: param *tmp, , 
// Words: 705
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 706
addi $sp, 2
// Words: 707
move $a, $sp
// Words: 708
move $sp, $rr
// Words: 709
// Words: 710
// Words: 711
// Words: 712
// Words: 713
// Words: 714
// Words: 715
la $k2, putcharint
// Words: 716
jalr $k2
// Words: 717
addi $sp, -2
// Words: 718
move $sp, $rr
//: load *tmp, 0, i
// Words: 719
// Words: 720
ldi $k2, -11
// Words: 721
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 722
// Words: 723
ldi $k1, 1
//: + *tmp, *tmp2, *tmp
// Words: 724
add $k0, $k1
// Words: 725
move $k0, $rr
//: store i, 0, *tmp
// Words: 726
// Words: 727
ldi $k2, -11
// Words: 728
sdw $k0, $fp, $k2
//: jump , , 
// Words: 729
// Words: 730
// Words: 731
// Words: 732
// Words: 733
// Words: 734
// Words: 735
la $k2, L16
// Words: 736
jr $k2
//: loadi *tmp, , 10
L18:// Words: 737
// Words: 738
ldi $k0, 10
//: param *tmp, , 
// Words: 739
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 740
addi $sp, 2
// Words: 741
move $a, $sp
// Words: 742
move $sp, $rr
// Words: 743
// Words: 744
// Words: 745
// Words: 746
// Words: 747
// Words: 748
// Words: 749
la $k2, putcharint
// Words: 750
jalr $k2
// Words: 751
addi $sp, -2
// Words: 752
move $sp, $rr
//: loadi *tmp, , 0
// Words: 753
// Words: 754
ldi $k0, 0
//: jr , *tmp, 
// Words: 755
move $v, $k0
// Words: 756
addi $0, -2
// Words: 757
ldw $ra, $fp, $rr
// Words: 758
addi $rr, -3
// Words: 759
addi $rr, -2
// Words: 760
ldw $s0, $fp, $rr
// Words: 761
addi $rr, -2
// Words: 762
ldw $s1, $fp, $rr
// Words: 763
addi $fp, -13
// Words: 764
move $sp, $rr
// Words: 765
// Words: 766
ldi $k0, -4
// Words: 767
ldw $fp, $fp, $k0
// Words: 768
jr $ra
