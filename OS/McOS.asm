//InterruptHandlervoid: funcdecl 0, , 
InterruptHandlervoid:// Words: 0
addi $sp, 15
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
// Words: 15
addi $rr, -2
// Words: 16
sdw $s2, $fp, $rr
// Words: 17
addi $rr, -2
// Words: 18
sdw $s3, $fp, $rr
//: assembly mfc0 $v, $cause, , 
// Words: 19
mfc0 $v, $cause
//: move *tmp, , *v
// Words: 20
move $k0, $v
//: store cause, 0, *tmp
// Words: 21
// Words: 22
ldi $k2, -15
// Words: 23
sdw $k0, $fp, $k2
//: load *tmp, 0, cause
// Words: 24
// Words: 25
ldi $k2, -15
// Words: 26
ldw $k0, $fp, $k2
//: loadi *tmp2, , 2
// Words: 27
// Words: 28
ldi $k1, 2
//: bne , *tmp2, *tmp
// Words: 29
// Words: 30
// Words: 31
// Words: 32
// Words: 33
// Words: 34
// Words: 35
la $k2, L2
// Words: 36
bne $k0, $k1, $k2
//: assembly jr $0, , 
L1:// Words: 37
jr $0
//: move *tmp, , *v
// Words: 38
move $k0, $v
// Words: 39
// Words: 40
// Words: 41
// Words: 42
// Words: 43
// Words: 44
// Words: 45
la $k2, L8
// Words: 46
jr $k2
//: load *tmp, 0, cause
L2:// Words: 47
// Words: 48
ldi $k2, -15
// Words: 49
ldw $k0, $fp, $k2
//: loadi *tmp2, , 4
// Words: 50
// Words: 51
ldi $k1, 4
//: bne , *tmp2, *tmp
// Words: 52
// Words: 53
// Words: 54
// Words: 55
// Words: 56
// Words: 57
// Words: 58
la $k2, L4
// Words: 59
bne $k0, $k1, $k2
//: nop , , 
L3:// Words: 60
nop
// Words: 61
// Words: 62
// Words: 63
// Words: 64
// Words: 65
// Words: 66
// Words: 67
la $k2, L8
// Words: 68
jr $k2
//: load *tmp, 0, cause
L4:// Words: 69
// Words: 70
ldi $k2, -15
// Words: 71
ldw $k0, $fp, $k2
//: loadi *tmp2, , 5
// Words: 72
// Words: 73
ldi $k1, 5
//: bne , *tmp2, *tmp
// Words: 74
// Words: 75
// Words: 76
// Words: 77
// Words: 78
// Words: 79
// Words: 80
la $k2, L6
// Words: 81
bne $k0, $k1, $k2
//: assembly rp $v, 5, , 
L5:// Words: 82
rp $v, 5
//: move *tmp, , *v
// Words: 83
move $k0, $v
//: push , , *tmp
// Words: 84
addi $sp, 2
// Words: 85
sdw $k0, $sp, $0
// Words: 86
move $sp, $rr
//: load *tmp, 0, inBuffer
// Words: 87
addi $gp, -2
// Words: 88
ldw $k0, $0, $rr
//: load *tmp2, 0, bufferSize
// Words: 89
addi $gp, -8
// Words: 90
ldw $k1, $0, $rr
//: <<i *tmp2, 1, *tmp2
// Words: 91
slli $k1, 1
// Words: 92
move $k1, $rr
//: + *tmp2, *tmp2, *tmp
// Words: 93
add $k0, $k1
// Words: 94
move $k1, $rr
//: pop *tmp, , 
// Words: 95
addi $sp, -2
// Words: 96
move $sp, $rr
// Words: 97
ldw $k0, $sp, $0
//: storeadd *tmp, , *tmp2
// Words: 98
sdw $k0, $0, $k1
//: load *tmp, 0, bufferSize
// Words: 99
addi $gp, -8
// Words: 100
ldw $k0, $0, $rr
//: loadi *tmp2, , 1
// Words: 101
// Words: 102
ldi $k1, 1
//: + *tmp, *tmp2, *tmp
// Words: 103
add $k0, $k1
// Words: 104
move $k0, $rr
//: store bufferSize, 0, *tmp
// Words: 105
addi $gp, -8
// Words: 106
sdw $k0, $0, $rr
// Words: 107
// Words: 108
// Words: 109
// Words: 110
// Words: 111
// Words: 112
// Words: 113
la $k2, L8
// Words: 114
jr $k2
//: load *tmp, 0, cause
L6:// Words: 115
// Words: 116
ldi $k2, -15
// Words: 117
ldw $k0, $fp, $k2
//: loadi *tmp2, , 32
// Words: 118
// Words: 119
ldi $k1, 32
//: blt , *tmp2, *tmp
// Words: 120
// Words: 121
// Words: 122
// Words: 123
// Words: 124
// Words: 125
// Words: 126
la $k2, L8
// Words: 127
blt $k0, $k1, $k2
//: nop , , 
L7:// Words: 128
nop
//: assembly eni, , 
L8:// Words: 129
eni
//: funcend , , 
// Words: 130
addi $0, -2
// Words: 131
ldw $ra, $fp, $rr
// Words: 132
addi $rr, -5
// Words: 133
ldw $s0, $fp, $rr
// Words: 134
addi $rr, -2
// Words: 135
ldw $s1, $fp, $rr
// Words: 136
addi $rr, -2
// Words: 137
ldw $s2, $fp, $rr
// Words: 138
addi $rr, -2
// Words: 139
ldw $s3, $fp, $rr
// Words: 140
addi $fp, -15
// Words: 141
move $sp, $rr
// Words: 142
// Words: 143
ldi $k0, -4
// Words: 144
ldw $fp, $fp, $k0
// Words: 145
jr $ra
//mainint: funcdecl 1, , 
mainint:// Words: 146
addi $sp, 8
// Words: 147
move $gp, $rr
// Words: 148
move $sp, $rr
//: loadi *tmp, , -6
global:// Words: 149
// Words: 150
ldi $k0, -6
//: store currx, 0, *tmp
// Words: 151
addi $gp, -4
// Words: 152
sdw $k0, $0, $rr
//: loadi *tmp, , 0
// Words: 153
// Words: 154
ldi $k0, 0
//: store curry, 0, *tmp
// Words: 155
addi $gp, -6
// Words: 156
sdw $k0, $0, $rr
//: loadi *tmp, , 0
// Words: 157
// Words: 158
ldi $k0, 0
//: store inBuffer, 0, *tmp
// Words: 159
addi $gp, -2
// Words: 160
sdw $k0, $0, $rr
//: loadi *tmp, , 0
// Words: 161
// Words: 162
ldi $k0, 0
//: store bufferSize, 0, *tmp
// Words: 163
addi $gp, -8
// Words: 164
sdw $k0, $0, $rr
// Words: 165
addi $sp, 17
// Words: 166
move $sp, $rr
// Words: 167
addi $0, -2
// Words: 168
sdw $ra, $sp, $rr
// Words: 169
addi $rr, -2
// Words: 170
sdw $fp, $sp, $rr
// Words: 171
move $fp, $sp
// Words: 172
addi $rr, -1
// Words: 173
// Words: 174
ldi $k2, 2
// Words: 175
swn $k2, $fp, $rr
// Words: 176
addi $rr, -2
// Words: 177
sdw $s0, $fp, $rr
// Words: 178
addi $rr, -2
// Words: 179
sdw $s1, $fp, $rr
// Words: 180
addi $rr, -2
// Words: 181
sdw $s2, $fp, $rr
// Words: 182
addi $rr, -2
// Words: 183
sdw $s3, $fp, $rr
//: la *tmp, , D0
// Words: 184
// Words: 185
// Words: 186
// Words: 187
// Words: 188
// Words: 189
// Words: 190
la $k0, D0
//: store prompt, 0, *tmp
// Words: 191
// Words: 192
ldi $k2, -17
// Words: 193
sdw $k0, $fp, $k2
//: loadi *tmp, , 10
// Words: 194
// Words: 195
ldi $k0, 10
//: param *tmp, , 
// Words: 196
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 197
addi $sp, 2
// Words: 198
move $a, $sp
// Words: 199
move $sp, $rr
// Words: 200
// Words: 201
// Words: 202
// Words: 203
// Words: 204
// Words: 205
// Words: 206
la $k2, putcharint
// Words: 207
jalr $k2
// Words: 208
addi $sp, -2
// Words: 209
move $sp, $rr
//: loadi *tmp, , 10
// Words: 210
// Words: 211
ldi $k0, 10
//: param *tmp, , 
// Words: 212
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 213
addi $sp, 2
// Words: 214
move $a, $sp
// Words: 215
move $sp, $rr
// Words: 216
// Words: 217
// Words: 218
// Words: 219
// Words: 220
// Words: 221
// Words: 222
la $k2, putcharint
// Words: 223
jalr $k2
// Words: 224
addi $sp, -2
// Words: 225
move $sp, $rr
//: load *tmp, 0, prompt
// Words: 226
// Words: 227
ldi $k2, -17
// Words: 228
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 229
sdw $k0, $sp, $0
//: funccall , 1, putsint
// Words: 230
addi $sp, 2
// Words: 231
move $a, $sp
// Words: 232
move $sp, $rr
// Words: 233
// Words: 234
// Words: 235
// Words: 236
// Words: 237
// Words: 238
// Words: 239
la $k2, putsint
// Words: 240
jalr $k2
// Words: 241
addi $sp, -2
// Words: 242
move $sp, $rr
//: assembly wp $s0, 0, , 
// Words: 243
addi $gp, -8
// Words: 244
ldw $s0, $0, $rr
// Words: 245
wp $s0, 0
//: move *tmp, , *v
// Words: 246
move $k0, $v
//: funccall *tmp, 0, getcharchar
L10:// Words: 247
addi $sp, 0
// Words: 248
move $a, $sp
// Words: 249
move $sp, $rr
// Words: 250
// Words: 251
// Words: 252
// Words: 253
// Words: 254
// Words: 255
// Words: 256
la $k2, getcharchar
// Words: 257
jalr $k2
// Words: 258
move $k0, $v
// Words: 259
addi $sp, -0
// Words: 260
move $sp, $rr
//: store c, 0, *tmp
// Words: 261
// Words: 262
ldi $k2, -15
// Words: 263
sdw $k0, $fp, $k2
//: load *tmp, 0, c
// Words: 264
// Words: 265
ldi $k2, -15
// Words: 266
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 267
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 268
addi $sp, 2
// Words: 269
move $a, $sp
// Words: 270
move $sp, $rr
// Words: 271
// Words: 272
// Words: 273
// Words: 274
// Words: 275
// Words: 276
// Words: 277
la $k2, putcharint
// Words: 278
jalr $k2
// Words: 279
addi $sp, -2
// Words: 280
move $sp, $rr
//: load *tmp, 0, c
// Words: 281
// Words: 282
ldi $k2, -15
// Words: 283
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 284
// Words: 285
ldi $k1, 10
//: bne , *tmp2, *tmp
// Words: 286
// Words: 287
// Words: 288
// Words: 289
// Words: 290
// Words: 291
// Words: 292
la $k2, L12
// Words: 293
bne $k0, $k1, $k2
//: load *tmp, 0, prompt
L11:// Words: 294
// Words: 295
ldi $k2, -17
// Words: 296
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 297
sdw $k0, $sp, $0
//: funccall , 1, putsint
// Words: 298
addi $sp, 2
// Words: 299
move $a, $sp
// Words: 300
move $sp, $rr
// Words: 301
// Words: 302
// Words: 303
// Words: 304
// Words: 305
// Words: 306
// Words: 307
la $k2, putsint
// Words: 308
jalr $k2
// Words: 309
addi $sp, -2
// Words: 310
move $sp, $rr
//: jump , , 
L12:// Words: 311
// Words: 312
// Words: 313
// Words: 314
// Words: 315
// Words: 316
// Words: 317
la $k2, L10
// Words: 318
jr $k2
//: loadi *tmp, , 0
L13:// Words: 319
// Words: 320
ldi $k0, 0
//: jr , *tmp, 
// Words: 321
move $v, $k0
// Words: 322
addi $0, -2
// Words: 323
ldw $ra, $fp, $rr
// Words: 324
addi $rr, -3
// Words: 325
addi $rr, -2
// Words: 326
ldw $s0, $fp, $rr
// Words: 327
addi $rr, -2
// Words: 328
ldw $s1, $fp, $rr
// Words: 329
addi $rr, -2
// Words: 330
ldw $s2, $fp, $rr
// Words: 331
addi $rr, -2
// Words: 332
ldw $s3, $fp, $rr
// Words: 333
addi $fp, -17
// Words: 334
move $sp, $rr
// Words: 335
// Words: 336
ldi $k0, -4
// Words: 337
ldw $fp, $fp, $k0
// Words: 338
jr $ra
//putcharint: funcdecl 1, , 
putcharint:// Words: 339
addi $sp, 17
// Words: 340
move $sp, $rr
// Words: 341
addi $0, -2
// Words: 342
sdw $ra, $sp, $rr
// Words: 343
addi $rr, -2
// Words: 344
sdw $fp, $sp, $rr
// Words: 345
move $fp, $sp
// Words: 346
addi $rr, -1
// Words: 347
// Words: 348
ldi $k2, 2
// Words: 349
swn $k2, $fp, $rr
// Words: 350
addi $rr, -2
// Words: 351
sdw $s0, $fp, $rr
// Words: 352
addi $rr, -2
// Words: 353
sdw $s1, $fp, $rr
// Words: 354
addi $rr, -2
// Words: 355
sdw $s2, $fp, $rr
// Words: 356
addi $rr, -2
// Words: 357
sdw $s3, $fp, $rr
//: formal c, , 
// Words: 358
ldw $k2, $a, $0
// Words: 359
addi $0, -15
// Words: 360
sdw $k2, $fp, $rr
//: loadi *tmp, , 6
// Words: 361
// Words: 362
ldi $k0, 6
//: store intervalx, 0, *tmp
// Words: 363
// Words: 364
ldi $k2, -17
// Words: 365
sdw $k0, $fp, $k2
//: load *tmp, 0, currx
// Words: 366
addi $gp, -4
// Words: 367
ldw $k0, $0, $rr
//: push , , *tmp
// Words: 368
addi $sp, 2
// Words: 369
sdw $k0, $sp, $0
// Words: 370
move $sp, $rr
//: loadi *tmp, , 255
// Words: 371
// Words: 372
ldi $k0, 255
//: push , , *tmp
// Words: 373
addi $sp, 2
// Words: 374
sdw $k0, $sp, $0
// Words: 375
move $sp, $rr
//: load *tmp, 0, intervalx
// Words: 376
// Words: 377
ldi $k2, -17
// Words: 378
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 379
// Words: 380
ldi $k1, 1
//: << *tmp2, *tmp2, *tmp
// Words: 381
sll $k0, $k1
// Words: 382
move $k1, $rr
//: pop *tmp, , 
// Words: 383
addi $sp, -2
// Words: 384
move $sp, $rr
// Words: 385
ldw $k0, $sp, $0
//: - *tmp2, *tmp2, *tmp
// Words: 386
sub $k0, $k1
// Words: 387
move $k1, $rr
//: pop *tmp, , 
// Words: 388
addi $sp, -2
// Words: 389
move $sp, $rr
// Words: 390
ldw $k0, $sp, $0
//: > *tmp, *tmp2, *tmp
// Words: 391
// Words: 392
// Words: 393
// Words: 394
// Words: 395
// Words: 396
// Words: 397
la $k2, L30
// Words: 398
bgt $k0, $k1, $k2
// Words: 399
// Words: 400
ldi $k0, 0
// Words: 401
// Words: 402
// Words: 403
// Words: 404
// Words: 405
// Words: 406
// Words: 407
la $k2, L31
// Words: 408
jr $k2
// Words: 409
// Words: 410
L30:ldi $k0, 1
L31:
//: push , , *tmp
// Words: 411
addi $sp, 2
// Words: 412
sdw $k0, $sp, $0
// Words: 413
move $sp, $rr
//: load *tmp, 0, c
// Words: 414
// Words: 415
ldi $k2, -15
// Words: 416
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 417
// Words: 418
ldi $k1, 10
//: == *tmp2, *tmp2, *tmp
// Words: 419
// Words: 420
// Words: 421
// Words: 422
// Words: 423
// Words: 424
// Words: 425
la $k2, L32
// Words: 426
beq $k0, $k1, $k2
// Words: 427
// Words: 428
ldi $k1, 0
// Words: 429
// Words: 430
// Words: 431
// Words: 432
// Words: 433
// Words: 434
// Words: 435
la $k2, L33
// Words: 436
jr $k2
// Words: 437
// Words: 438
L32:ldi $k1, 1
L33:
//: pop *tmp, , 
// Words: 439
addi $sp, -2
// Words: 440
move $sp, $rr
// Words: 441
ldw $k0, $sp, $0
//: || *tmp, *tmp2, *tmp
// Words: 442
// Words: 443
// Words: 444
// Words: 445
// Words: 446
// Words: 447
// Words: 448
la $k2, L34
// Words: 449
bne $0, $k0, $k2
// Words: 450
bne $0, $k1, $k2
// Words: 451
move $k0, $0
// Words: 452
// Words: 453
// Words: 454
// Words: 455
// Words: 456
// Words: 457
// Words: 458
la $k2, L35
// Words: 459
jr $k2
// Words: 460
// Words: 461
L34: ldi $k0, 1
// Words: 462
L35: nop
//: if *tmp, , 
// Words: 463
// Words: 464
// Words: 465
// Words: 466
// Words: 467
// Words: 468
// Words: 469
la $k2, L16
// Words: 470
beq $k0, $0, $k2
//: loadi *tmp, , 0
L15:// Words: 471
// Words: 472
ldi $k0, 0
//: store currx, 0, *tmp
// Words: 473
addi $gp, -4
// Words: 474
sdw $k0, $0, $rr
//: load *tmp, 0, curry
// Words: 475
addi $gp, -6
// Words: 476
ldw $k0, $0, $rr
//: loadi *tmp2, , 10
// Words: 477
// Words: 478
ldi $k1, 10
//: + *tmp, *tmp2, *tmp
// Words: 479
add $k0, $k1
// Words: 480
move $k0, $rr
//: store curry, 0, *tmp
// Words: 481
addi $gp, -6
// Words: 482
sdw $k0, $0, $rr
// Words: 483
// Words: 484
// Words: 485
// Words: 486
// Words: 487
// Words: 488
// Words: 489
la $k2, L17
// Words: 490
jr $k2
//: load *tmp, 0, currx
L16:// Words: 491
addi $gp, -4
// Words: 492
ldw $k0, $0, $rr
//: load *tmp2, 0, intervalx
// Words: 493
// Words: 494
ldi $k2, -17
// Words: 495
ldw $k1, $fp, $k2
//: + *tmp, *tmp2, *tmp
// Words: 496
add $k0, $k1
// Words: 497
move $k0, $rr
//: store currx, 0, *tmp
// Words: 498
addi $gp, -4
// Words: 499
sdw $k0, $0, $rr
//: load *tmp, 0, c
L17:// Words: 500
// Words: 501
ldi $k2, -15
// Words: 502
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 503
// Words: 504
ldi $k1, 10
//: beq , *tmp2, *tmp
// Words: 505
// Words: 506
// Words: 507
// Words: 508
// Words: 509
// Words: 510
// Words: 511
la $k2, L21
// Words: 512
beq $k0, $k1, $k2
//: assembly rp $v, 3, , 
L18:// Words: 513
rp $v, 3
//: move *tmp, , *v
// Words: 514
move $k0, $v
//: loadi *tmp2, , 0
// Words: 515
// Words: 516
ldi $k1, 0
//: blte , *tmp2, *tmp
// Words: 517
// Words: 518
// Words: 519
// Words: 520
// Words: 521
// Words: 522
// Words: 523
la $k2, L20
// Words: 524
blt $k0, $k1, $k2
// Words: 525
beq $k0, $k1, $k2
//: jump , , 
L19:// Words: 526
// Words: 527
// Words: 528
// Words: 529
// Words: 530
// Words: 531
// Words: 532
la $k2, L18
// Words: 533
jr $k2
//: assembly ldi $s0, 512;add $s0, $s1;wp $rr, 3;ldi $s0, 1024;add $s0, $s2;wp $rr, 3;ldi $s0, 1543;wp $s0, 3;ldi $s0, 2048;add $s0, $s3;wp $rr, 3, , 
L20:// Words: 534
addi $gp, -4
// Words: 535
ldw $s1, $0, $rr
// Words: 536
addi $gp, -6
// Words: 537
ldw $s2, $0, $rr
// Words: 538
// Words: 539
ldi $k2, -15
// Words: 540
ldw $s3, $fp, $k2
// Words: 541
ldi $s0, 512
// Words: 542
add $s0, $s1
// Words: 543
wp $rr, 3
// Words: 544
ldi $s0, 1024
// Words: 545
add $s0, $s2
// Words: 546
wp $rr, 3
// Words: 547
ldi $s0, 1543
// Words: 548
wp $s0, 3
// Words: 549
ldi $s0, 2048
// Words: 550
add $s0, $s3
// Words: 551
wp $rr, 3
//: move *tmp, , *v
// Words: 552
move $k0, $v
//: load *tmp, 0, c
L21:// Words: 553
// Words: 554
ldi $k2, -15
// Words: 555
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 556
move $v, $k0
// Words: 557
addi $0, -2
// Words: 558
ldw $ra, $fp, $rr
// Words: 559
addi $rr, -3
// Words: 560
addi $rr, -2
// Words: 561
ldw $s0, $fp, $rr
// Words: 562
addi $rr, -2
// Words: 563
ldw $s1, $fp, $rr
// Words: 564
addi $rr, -2
// Words: 565
ldw $s2, $fp, $rr
// Words: 566
addi $rr, -2
// Words: 567
ldw $s3, $fp, $rr
// Words: 568
addi $fp, -17
// Words: 569
move $sp, $rr
// Words: 570
// Words: 571
ldi $k0, -4
// Words: 572
ldw $fp, $fp, $k0
// Words: 573
jr $ra
//getcharchar: funcdecl 0, , 
getcharchar:// Words: 574
addi $sp, 15
// Words: 575
move $sp, $rr
// Words: 576
addi $0, -2
// Words: 577
sdw $ra, $sp, $rr
// Words: 578
addi $rr, -2
// Words: 579
sdw $fp, $sp, $rr
// Words: 580
move $fp, $sp
// Words: 581
addi $rr, -1
// Words: 582
// Words: 583
ldi $k2, 0
// Words: 584
swn $k2, $fp, $rr
// Words: 585
addi $rr, -2
// Words: 586
sdw $s0, $fp, $rr
// Words: 587
addi $rr, -2
// Words: 588
sdw $s1, $fp, $rr
// Words: 589
addi $rr, -2
// Words: 590
sdw $s2, $fp, $rr
// Words: 591
addi $rr, -2
// Words: 592
sdw $s3, $fp, $rr
//: load *tmp, 0, bufferSize
L23:// Words: 593
addi $gp, -8
// Words: 594
ldw $k0, $0, $rr
//: loadi *tmp2, , 0
// Words: 595
// Words: 596
ldi $k1, 0
//: bne , *tmp2, *tmp
// Words: 597
// Words: 598
// Words: 599
// Words: 600
// Words: 601
// Words: 602
// Words: 603
la $k2, L25
// Words: 604
bne $k0, $k1, $k2
//: jump , , 
L24:// Words: 605
// Words: 606
// Words: 607
// Words: 608
// Words: 609
// Words: 610
// Words: 611
la $k2, L23
// Words: 612
jr $k2
//: load *tmp, 0, inBuffer
L25:// Words: 613
addi $gp, -2
// Words: 614
ldw $k0, $0, $rr
//: push , , *tmp
// Words: 615
addi $sp, 2
// Words: 616
sdw $k0, $sp, $0
// Words: 617
move $sp, $rr
//: load *tmp, 0, bufferSize
// Words: 618
addi $gp, -8
// Words: 619
ldw $k0, $0, $rr
//: loadi *tmp2, , 1
// Words: 620
// Words: 621
ldi $k1, 1
//: - *tmp2, *tmp2, *tmp
// Words: 622
sub $k0, $k1
// Words: 623
move $k1, $rr
//: pop *tmp, , 
// Words: 624
addi $sp, -2
// Words: 625
move $sp, $rr
// Words: 626
ldw $k0, $sp, $0
//: <<i *tmp2, 1, *tmp2
// Words: 627
slli $k1, 1
// Words: 628
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 629
add $k0, $k1
// Words: 630
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 631
ldw $k0, $0, $k0
//: store c, 0, *tmp
// Words: 632
// Words: 633
ldi $k2, -15
// Words: 634
sdw $k0, $fp, $k2
//: load *tmp, 0, bufferSize
// Words: 635
addi $gp, -8
// Words: 636
ldw $k0, $0, $rr
//: loadi *tmp2, , 1
// Words: 637
// Words: 638
ldi $k1, 1
//: - *tmp, *tmp2, *tmp
// Words: 639
sub $k0, $k1
// Words: 640
move $k0, $rr
//: store bufferSize, 0, *tmp
// Words: 641
addi $gp, -8
// Words: 642
sdw $k0, $0, $rr
//: load *tmp, 0, c
// Words: 643
// Words: 644
ldi $k2, -15
// Words: 645
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 646
move $v, $k0
// Words: 647
addi $0, -2
// Words: 648
ldw $ra, $fp, $rr
// Words: 649
addi $rr, -3
// Words: 650
addi $rr, -2
// Words: 651
ldw $s0, $fp, $rr
// Words: 652
addi $rr, -2
// Words: 653
ldw $s1, $fp, $rr
// Words: 654
addi $rr, -2
// Words: 655
ldw $s2, $fp, $rr
// Words: 656
addi $rr, -2
// Words: 657
ldw $s3, $fp, $rr
// Words: 658
addi $fp, -15
// Words: 659
move $sp, $rr
// Words: 660
// Words: 661
ldi $k0, -4
// Words: 662
ldw $fp, $fp, $k0
// Words: 663
jr $ra
//putsint: funcdecl 1, , 
putsint:// Words: 664
addi $sp, 17
// Words: 665
move $sp, $rr
// Words: 666
addi $0, -2
// Words: 667
sdw $ra, $sp, $rr
// Words: 668
addi $rr, -2
// Words: 669
sdw $fp, $sp, $rr
// Words: 670
move $fp, $sp
// Words: 671
addi $rr, -1
// Words: 672
// Words: 673
ldi $k2, 2
// Words: 674
swn $k2, $fp, $rr
// Words: 675
addi $rr, -2
// Words: 676
sdw $s0, $fp, $rr
// Words: 677
addi $rr, -2
// Words: 678
sdw $s1, $fp, $rr
// Words: 679
addi $rr, -2
// Words: 680
sdw $s2, $fp, $rr
// Words: 681
addi $rr, -2
// Words: 682
sdw $s3, $fp, $rr
//: formal s, , 
// Words: 683
ldw $k2, $a, $0
// Words: 684
addi $0, -17
// Words: 685
sdw $k2, $fp, $rr
//: loadi *tmp, , 0
// Words: 686
// Words: 687
ldi $k0, 0
//: store i, 0, *tmp
// Words: 688
// Words: 689
ldi $k2, -15
// Words: 690
sdw $k0, $fp, $k2
//: load *tmp, 0, s
L27:// Words: 691
// Words: 692
ldi $k2, -17
// Words: 693
ldw $k0, $fp, $k2
//: load *tmp2, 0, i
// Words: 694
// Words: 695
ldi $k2, -15
// Words: 696
ldw $k1, $fp, $k2
//: <<i *tmp2, 1, *tmp2
// Words: 697
slli $k1, 1
// Words: 698
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 699
add $k0, $k1
// Words: 700
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 701
ldw $k0, $0, $k0
//: loadi *tmp2, , 0
// Words: 702
// Words: 703
ldi $k1, 0
//: beq , *tmp2, *tmp
// Words: 704
// Words: 705
// Words: 706
// Words: 707
// Words: 708
// Words: 709
// Words: 710
la $k2, L29
// Words: 711
beq $k0, $k1, $k2
//: load *tmp, 0, s
L28:// Words: 712
// Words: 713
ldi $k2, -17
// Words: 714
ldw $k0, $fp, $k2
//: load *tmp2, 0, i
// Words: 715
// Words: 716
ldi $k2, -15
// Words: 717
ldw $k1, $fp, $k2
//: <<i *tmp2, 1, *tmp2
// Words: 718
slli $k1, 1
// Words: 719
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 720
add $k0, $k1
// Words: 721
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 722
ldw $k0, $0, $k0
//: param *tmp, , 
// Words: 723
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 724
addi $sp, 2
// Words: 725
move $a, $sp
// Words: 726
move $sp, $rr
// Words: 727
// Words: 728
// Words: 729
// Words: 730
// Words: 731
// Words: 732
// Words: 733
la $k2, putcharint
// Words: 734
jalr $k2
// Words: 735
addi $sp, -2
// Words: 736
move $sp, $rr
//: load *tmp, 0, i
// Words: 737
// Words: 738
ldi $k2, -15
// Words: 739
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 740
// Words: 741
ldi $k1, 1
//: + *tmp, *tmp2, *tmp
// Words: 742
add $k0, $k1
// Words: 743
move $k0, $rr
//: store i, 0, *tmp
// Words: 744
// Words: 745
ldi $k2, -15
// Words: 746
sdw $k0, $fp, $k2
//: jump , , 
// Words: 747
// Words: 748
// Words: 749
// Words: 750
// Words: 751
// Words: 752
// Words: 753
la $k2, L27
// Words: 754
jr $k2
//: loadi *tmp, , 10
L29:// Words: 755
// Words: 756
ldi $k0, 10
//: param *tmp, , 
// Words: 757
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 758
addi $sp, 2
// Words: 759
move $a, $sp
// Words: 760
move $sp, $rr
// Words: 761
// Words: 762
// Words: 763
// Words: 764
// Words: 765
// Words: 766
// Words: 767
la $k2, putcharint
// Words: 768
jalr $k2
// Words: 769
addi $sp, -2
// Words: 770
move $sp, $rr
//: loadi *tmp, , 0
// Words: 771
// Words: 772
ldi $k0, 0
//: jr , *tmp, 
// Words: 773
move $v, $k0
// Words: 774
addi $0, -2
// Words: 775
ldw $ra, $fp, $rr
// Words: 776
addi $rr, -3
// Words: 777
addi $rr, -2
// Words: 778
ldw $s0, $fp, $rr
// Words: 779
addi $rr, -2
// Words: 780
ldw $s1, $fp, $rr
// Words: 781
addi $rr, -2
// Words: 782
ldw $s2, $fp, $rr
// Words: 783
addi $rr, -2
// Words: 784
ldw $s3, $fp, $rr
// Words: 785
addi $fp, -17
// Words: 786
move $sp, $rr
// Words: 787
// Words: 788
ldi $k0, -4
// Words: 789
ldw $fp, $fp, $k0
// Words: 790
jr $ra
.data
D0:
M
c
O
S
>
>
 
\0
