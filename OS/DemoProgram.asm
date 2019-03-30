//mainint: funcdecl 1, , 
mainint:// Words: 0
addi $sp, 10
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
addi $gp, -4
// Words: 6
sdw $k0, $0, $rr
//: loadi *tmp, , 0
// Words: 7
// Words: 8
ldi $k0, 0
//: store curry, 0, *tmp
// Words: 9
addi $gp, -6
// Words: 10
sdw $k0, $0, $rr
//: loadi *tmp, , 7
// Words: 11
// Words: 12
ldi $k0, 7
//: store currcolor, 0, *tmp
// Words: 13
addi $gp, -8
// Words: 14
sdw $k0, $0, $rr
//: loadi *tmp, , 0
// Words: 15
// Words: 16
ldi $k0, 0
//: store inBuffer, 0, *tmp
// Words: 17
addi $gp, -2
// Words: 18
sdw $k0, $0, $rr
//: loadi *tmp, , 0
// Words: 19
// Words: 20
ldi $k0, 0
//: store bufferSize, 0, *tmp
// Words: 21
addi $gp, -10
// Words: 22
sdw $k0, $0, $rr
// Words: 23
addi $sp, 23
// Words: 24
move $sp, $rr
// Words: 25
addi $0, -2
// Words: 26
sdw $ra, $sp, $rr
// Words: 27
addi $rr, -2
// Words: 28
sdw $fp, $sp, $rr
// Words: 29
move $fp, $sp
// Words: 30
addi $rr, -1
// Words: 31
// Words: 32
ldi $k2, 1
// Words: 33
swn $k2, $fp, $rr
// Words: 34
addi $rr, -2
// Words: 35
sdw $s0, $fp, $rr
// Words: 36
addi $rr, -2
// Words: 37
sdw $s1, $fp, $rr
//: la *tmp, , D0
// Words: 38
// Words: 39
// Words: 40
// Words: 41
// Words: 42
// Words: 43
// Words: 44
la $k0, D0
//: store str, 0, *tmp
// Words: 45
// Words: 46
ldi $k2, -13
// Words: 47
sdw $k0, $fp, $k2
//: loadi *tmp, , 10
// Words: 48
// Words: 49
ldi $k0, 10
//: param *tmp, , 
// Words: 50
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 51
addi $sp, 2
// Words: 52
move $a, $sp
// Words: 53
move $sp, $rr
// Words: 54
// Words: 55
// Words: 56
// Words: 57
// Words: 58
// Words: 59
// Words: 60
la $k2, putcharint
// Words: 61
jalr $k2
// Words: 62
addi $sp, -2
// Words: 63
move $sp, $rr
//: loadi *tmp, , 10
// Words: 64
// Words: 65
ldi $k0, 10
//: param *tmp, , 
// Words: 66
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 67
addi $sp, 2
// Words: 68
move $a, $sp
// Words: 69
move $sp, $rr
// Words: 70
// Words: 71
// Words: 72
// Words: 73
// Words: 74
// Words: 75
// Words: 76
la $k2, putcharint
// Words: 77
jalr $k2
// Words: 78
addi $sp, -2
// Words: 79
move $sp, $rr
//: load *tmp, 0, str
// Words: 80
// Words: 81
ldi $k2, -13
// Words: 82
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 83
sdw $k0, $sp, $0
//: funccall , 1, putsint
// Words: 84
addi $sp, 2
// Words: 85
move $a, $sp
// Words: 86
move $sp, $rr
// Words: 87
// Words: 88
// Words: 89
// Words: 90
// Words: 91
// Words: 92
// Words: 93
la $k2, putsint
// Words: 94
jalr $k2
// Words: 95
addi $sp, -2
// Words: 96
move $sp, $rr
//: loadi *tmp, , 0
// Words: 97
// Words: 98
ldi $k0, 0
//: store isPressed, 0, *tmp
// Words: 99
// Words: 100
ldi $k2, -15
// Words: 101
sdw $k0, $fp, $k2
//: loadi *tmp, , 0
L1:// Words: 102
// Words: 103
ldi $k0, 0
//: store poses, 0, *tmp
// Words: 104
// Words: 105
ldi $k2, -23
// Words: 106
sdw $k0, $fp, $k2
//: loadi *tmp, , 0
// Words: 107
// Words: 108
ldi $k0, 0
//: store posx, 0, *tmp
// Words: 109
// Words: 110
ldi $k2, -17
// Words: 111
sdw $k0, $fp, $k2
//: loadi *tmp, , 0
// Words: 112
// Words: 113
ldi $k0, 0
//: store posy, 0, *tmp
// Words: 114
// Words: 115
ldi $k2, -11
// Words: 116
sdw $k0, $fp, $k2
//: loadi *tmp, , 0
// Words: 117
// Words: 118
ldi $k0, 0
//: store constant, 0, *tmp
// Words: 119
// Words: 120
ldi $k2, -21
// Words: 121
sdw $k0, $fp, $k2
//: assembly rp $s0, 6;ldl $s1, -1, , 
// Words: 122
rp $s0, 6
// Words: 123
ldl $s1, -1
// Words: 124
// Words: 125
ldi $k2, -23
// Words: 126
sdw $s0, $fp, $k2
// Words: 127
// Words: 128
ldi $k2, -21
// Words: 129
sdw $s1, $fp, $k2
//: load *tmp, 0, poses
// Words: 130
// Words: 131
ldi $k2, -23
// Words: 132
ldw $k0, $fp, $k2
//: load *tmp2, 0, constant
// Words: 133
// Words: 134
ldi $k2, -21
// Words: 135
ldw $k1, $fp, $k2
//: & *tmp, *tmp2, *tmp
// Words: 136
and $k0, $k1
// Words: 137
move $k0, $rr
//: store posx, 0, *tmp
// Words: 138
// Words: 139
ldi $k2, -17
// Words: 140
sdw $k0, $fp, $k2
//: load *tmp, 0, poses
// Words: 141
// Words: 142
ldi $k2, -23
// Words: 143
ldw $k0, $fp, $k2
//: loadi *tmp2, , 16
// Words: 144
// Words: 145
ldi $k1, 16
//: >> *tmp, *tmp2, *tmp
// Words: 146
neg $k2, $k1
// Words: 147
sll $k0, $k2
// Words: 148
move $k0, $rr
//: store posy, 0, *tmp
// Words: 149
// Words: 150
ldi $k2, -11
// Words: 151
sdw $k0, $fp, $k2
//: load *tmp, 0, posx
// Words: 152
// Words: 153
ldi $k2, -17
// Words: 154
ldw $k0, $fp, $k2
//: loadi *tmp2, , 256
// Words: 155
// Words: 156
ldi $k1, 256
//: < *tmp, *tmp2, *tmp
// Words: 157
// Words: 158
// Words: 159
// Words: 160
// Words: 161
// Words: 162
// Words: 163
la $k2, L22
// Words: 164
blt $k0, $k1, $k2
// Words: 165
// Words: 166
ldi $k0, 0
// Words: 167
// Words: 168
// Words: 169
// Words: 170
// Words: 171
// Words: 172
// Words: 173
la $k2, L23
// Words: 174
jr $k2
// Words: 175
// Words: 176
L22:ldi $k0, 1
L23:
//: push , , *tmp
// Words: 177
addi $sp, 2
// Words: 178
sdw $k0, $sp, $0
// Words: 179
move $sp, $rr
//: load *tmp, 0, posy
// Words: 180
// Words: 181
ldi $k2, -11
// Words: 182
ldw $k0, $fp, $k2
//: loadi *tmp2, , 256
// Words: 183
// Words: 184
ldi $k1, 256
//: < *tmp2, *tmp2, *tmp
// Words: 185
// Words: 186
// Words: 187
// Words: 188
// Words: 189
// Words: 190
// Words: 191
la $k2, L24
// Words: 192
blt $k0, $k1, $k2
// Words: 193
// Words: 194
ldi $k1, 0
// Words: 195
// Words: 196
// Words: 197
// Words: 198
// Words: 199
// Words: 200
// Words: 201
la $k2, L25
// Words: 202
jr $k2
// Words: 203
// Words: 204
L24:ldi $k1, 1
L25:
//: pop *tmp, , 
// Words: 205
addi $sp, -2
// Words: 206
move $sp, $rr
// Words: 207
ldw $k0, $sp, $0
//: && *tmp, *tmp2, *tmp
// Words: 208
// Words: 209
// Words: 210
// Words: 211
// Words: 212
// Words: 213
// Words: 214
la $k2, L26
// Words: 215
beq $0, $k0, $k2
// Words: 216
beq $0, $k1, $k2
// Words: 217
// Words: 218
ldi $k0, 1
// Words: 219
// Words: 220
// Words: 221
// Words: 222
// Words: 223
// Words: 224
// Words: 225
la $k2, L27
// Words: 226
jr $k2
// Words: 227
L26: move $k0, $0
// Words: 228
L27: nop
//: if *tmp, , 
// Words: 229
// Words: 230
// Words: 231
// Words: 232
// Words: 233
// Words: 234
// Words: 235
la $k2, L3
// Words: 236
beq $k0, $0, $k2
//: load *tmp, 0, isPressed
L2:// Words: 237
// Words: 238
ldi $k2, -15
// Words: 239
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 240
// Words: 241
ldi $k1, 1
//: + *tmp, *tmp2, *tmp
// Words: 242
add $k0, $k1
// Words: 243
move $k0, $rr
//: store isPressed, 0, *tmp
// Words: 244
// Words: 245
ldi $k2, -15
// Words: 246
sdw $k0, $fp, $k2
// Words: 247
// Words: 248
// Words: 249
// Words: 250
// Words: 251
// Words: 252
// Words: 253
la $k2, L8
// Words: 254
jr $k2
//: load *tmp, 0, isPressed
L3:// Words: 255
// Words: 256
ldi $k2, -15
// Words: 257
ldw $k0, $fp, $k2
//: loadi *tmp2, , 500
// Words: 258
// Words: 259
ldi $k1, 500
//: blte , *tmp2, *tmp
// Words: 260
// Words: 261
// Words: 262
// Words: 263
// Words: 264
// Words: 265
// Words: 266
la $k2, L8
// Words: 267
blt $k0, $k1, $k2
// Words: 268
beq $k0, $k1, $k2
//: load *tmp, 0, currcolor
L4:// Words: 269
addi $gp, -8
// Words: 270
ldw $k0, $0, $rr
//: loadi *tmp2, , 7
// Words: 271
// Words: 272
ldi $k1, 7
//: bne , *tmp2, *tmp
// Words: 273
// Words: 274
// Words: 275
// Words: 276
// Words: 277
// Words: 278
// Words: 279
la $k2, L6
// Words: 280
bne $k0, $k1, $k2
//: loadi *tmp, , 1
L5:// Words: 281
// Words: 282
ldi $k0, 1
//: store currcolor, 0, *tmp
// Words: 283
addi $gp, -8
// Words: 284
sdw $k0, $0, $rr
//: load *tmp, 0, str
// Words: 285
// Words: 286
ldi $k2, -13
// Words: 287
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 288
sdw $k0, $sp, $0
//: funccall , 1, putsint
// Words: 289
addi $sp, 2
// Words: 290
move $a, $sp
// Words: 291
move $sp, $rr
// Words: 292
// Words: 293
// Words: 294
// Words: 295
// Words: 296
// Words: 297
// Words: 298
la $k2, putsint
// Words: 299
jalr $k2
// Words: 300
addi $sp, -2
// Words: 301
move $sp, $rr
// Words: 302
// Words: 303
// Words: 304
// Words: 305
// Words: 306
// Words: 307
// Words: 308
la $k2, L7
// Words: 309
jr $k2
//: load *tmp, 0, currcolor
L6:// Words: 310
addi $gp, -8
// Words: 311
ldw $k0, $0, $rr
//: loadi *tmp2, , 1
// Words: 312
// Words: 313
ldi $k1, 1
//: + *tmp, *tmp2, *tmp
// Words: 314
add $k0, $k1
// Words: 315
move $k0, $rr
//: store currcolor, 0, *tmp
// Words: 316
addi $gp, -8
// Words: 317
sdw $k0, $0, $rr
//: load *tmp, 0, str
// Words: 318
// Words: 319
ldi $k2, -13
// Words: 320
ldw $k0, $fp, $k2
//: param *tmp, , 
// Words: 321
sdw $k0, $sp, $0
//: funccall , 1, putsint
// Words: 322
addi $sp, 2
// Words: 323
move $a, $sp
// Words: 324
move $sp, $rr
// Words: 325
// Words: 326
// Words: 327
// Words: 328
// Words: 329
// Words: 330
// Words: 331
la $k2, putsint
// Words: 332
jalr $k2
// Words: 333
addi $sp, -2
// Words: 334
move $sp, $rr
//: loadi *tmp, , 0
L7:// Words: 335
// Words: 336
ldi $k0, 0
//: store isPressed, 0, *tmp
// Words: 337
// Words: 338
ldi $k2, -15
// Words: 339
sdw $k0, $fp, $k2
//: assembly rp $v, 2, , 
L8:// Words: 340
rp $v, 2
//: move *tmp, , *v
// Words: 341
move $k0, $v
//: store j, 0, *tmp
// Words: 342
// Words: 343
ldi $k2, -19
// Words: 344
sdw $k0, $fp, $k2
//: load *tmp, 0, posy
// Words: 345
// Words: 346
ldi $k2, -11
// Words: 347
ldw $k0, $fp, $k2
//: loadi *tmp2, , 16
// Words: 348
// Words: 349
ldi $k1, 16
//: << *tmp, *tmp2, *tmp
// Words: 350
sll $k0, $k1
// Words: 351
move $k0, $rr
//: load *tmp2, 0, posx
// Words: 352
// Words: 353
ldi $k2, -17
// Words: 354
ldw $k1, $fp, $k2
//: + *tmp, *tmp2, *tmp
// Words: 355
add $k0, $k1
// Words: 356
move $k0, $rr
//: store poses, 0, *tmp
// Words: 357
// Words: 358
ldi $k2, -23
// Words: 359
sdw $k0, $fp, $k2
//: assembly wp $s0, 0, , 
// Words: 360
// Words: 361
ldi $k2, -23
// Words: 362
ldw $s0, $fp, $k2
// Words: 363
wp $s0, 0
//: jump , , 
// Words: 364
// Words: 365
// Words: 366
// Words: 367
// Words: 368
// Words: 369
// Words: 370
la $k2, L1
// Words: 371
jr $k2
//: loadi *tmp, , 0
L9:// Words: 372
// Words: 373
ldi $k0, 0
//: jr , *tmp, 
// Words: 374
move $v, $k0
// Words: 375
addi $0, -2
// Words: 376
ldw $ra, $fp, $rr
// Words: 377
addi $rr, -3
// Words: 378
addi $rr, -2
// Words: 379
ldw $s0, $fp, $rr
// Words: 380
addi $rr, -2
// Words: 381
ldw $s1, $fp, $rr
// Words: 382
addi $fp, -23
// Words: 383
move $sp, $rr
// Words: 384
// Words: 385
ldi $k0, -4
// Words: 386
ldw $fp, $fp, $k0
// Words: 387
jr $ra
//putcharint: funcdecl 1, , 
putcharint:// Words: 388
addi $sp, 13
// Words: 389
move $sp, $rr
// Words: 390
addi $0, -2
// Words: 391
sdw $ra, $sp, $rr
// Words: 392
addi $rr, -2
// Words: 393
sdw $fp, $sp, $rr
// Words: 394
move $fp, $sp
// Words: 395
addi $rr, -1
// Words: 396
// Words: 397
ldi $k2, 1
// Words: 398
swn $k2, $fp, $rr
// Words: 399
addi $rr, -2
// Words: 400
sdw $s0, $fp, $rr
// Words: 401
addi $rr, -2
// Words: 402
sdw $s1, $fp, $rr
//: formal c, , 
// Words: 403
ldw $k2, $a, $0
// Words: 404
addi $0, -11
// Words: 405
sdw $k2, $fp, $rr
//: loadi *tmp, , 6
// Words: 406
// Words: 407
ldi $k0, 6
//: store intervalx, 0, *tmp
// Words: 408
// Words: 409
ldi $k2, -13
// Words: 410
sdw $k0, $fp, $k2
//: load *tmp, 0, currx
// Words: 411
addi $gp, -4
// Words: 412
ldw $k0, $0, $rr
//: push , , *tmp
// Words: 413
addi $sp, 2
// Words: 414
sdw $k0, $sp, $0
// Words: 415
move $sp, $rr
//: loadi *tmp, , 255
// Words: 416
// Words: 417
ldi $k0, 255
//: push , , *tmp
// Words: 418
addi $sp, 2
// Words: 419
sdw $k0, $sp, $0
// Words: 420
move $sp, $rr
//: load *tmp, 0, intervalx
// Words: 421
// Words: 422
ldi $k2, -13
// Words: 423
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 424
// Words: 425
ldi $k1, 1
//: << *tmp2, *tmp2, *tmp
// Words: 426
sll $k0, $k1
// Words: 427
move $k1, $rr
//: pop *tmp, , 
// Words: 428
addi $sp, -2
// Words: 429
move $sp, $rr
// Words: 430
ldw $k0, $sp, $0
//: - *tmp2, *tmp2, *tmp
// Words: 431
sub $k0, $k1
// Words: 432
move $k1, $rr
//: pop *tmp, , 
// Words: 433
addi $sp, -2
// Words: 434
move $sp, $rr
// Words: 435
ldw $k0, $sp, $0
//: > *tmp, *tmp2, *tmp
// Words: 436
// Words: 437
// Words: 438
// Words: 439
// Words: 440
// Words: 441
// Words: 442
la $k2, L28
// Words: 443
bgt $k0, $k1, $k2
// Words: 444
// Words: 445
ldi $k0, 0
// Words: 446
// Words: 447
// Words: 448
// Words: 449
// Words: 450
// Words: 451
// Words: 452
la $k2, L29
// Words: 453
jr $k2
// Words: 454
// Words: 455
L28:ldi $k0, 1
L29:
//: push , , *tmp
// Words: 456
addi $sp, 2
// Words: 457
sdw $k0, $sp, $0
// Words: 458
move $sp, $rr
//: load *tmp, 0, c
// Words: 459
// Words: 460
ldi $k2, -11
// Words: 461
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 462
// Words: 463
ldi $k1, 10
//: == *tmp2, *tmp2, *tmp
// Words: 464
// Words: 465
// Words: 466
// Words: 467
// Words: 468
// Words: 469
// Words: 470
la $k2, L30
// Words: 471
beq $k0, $k1, $k2
// Words: 472
// Words: 473
ldi $k1, 0
// Words: 474
// Words: 475
// Words: 476
// Words: 477
// Words: 478
// Words: 479
// Words: 480
la $k2, L31
// Words: 481
jr $k2
// Words: 482
// Words: 483
L30:ldi $k1, 1
L31:
//: pop *tmp, , 
// Words: 484
addi $sp, -2
// Words: 485
move $sp, $rr
// Words: 486
ldw $k0, $sp, $0
//: || *tmp, *tmp2, *tmp
// Words: 487
// Words: 488
// Words: 489
// Words: 490
// Words: 491
// Words: 492
// Words: 493
la $k2, L32
// Words: 494
bne $0, $k0, $k2
// Words: 495
bne $0, $k1, $k2
// Words: 496
move $k0, $0
// Words: 497
// Words: 498
// Words: 499
// Words: 500
// Words: 501
// Words: 502
// Words: 503
la $k2, L33
// Words: 504
jr $k2
// Words: 505
// Words: 506
L32: ldi $k0, 1
// Words: 507
L33: nop
//: if *tmp, , 
// Words: 508
// Words: 509
// Words: 510
// Words: 511
// Words: 512
// Words: 513
// Words: 514
la $k2, L12
// Words: 515
beq $k0, $0, $k2
//: loadi *tmp, , 0
L11:// Words: 516
// Words: 517
ldi $k0, 0
//: store currx, 0, *tmp
// Words: 518
addi $gp, -4
// Words: 519
sdw $k0, $0, $rr
//: load *tmp, 0, curry
// Words: 520
addi $gp, -6
// Words: 521
ldw $k0, $0, $rr
//: loadi *tmp2, , 10
// Words: 522
// Words: 523
ldi $k1, 10
//: + *tmp, *tmp2, *tmp
// Words: 524
add $k0, $k1
// Words: 525
move $k0, $rr
//: store curry, 0, *tmp
// Words: 526
addi $gp, -6
// Words: 527
sdw $k0, $0, $rr
// Words: 528
// Words: 529
// Words: 530
// Words: 531
// Words: 532
// Words: 533
// Words: 534
la $k2, L13
// Words: 535
jr $k2
//: load *tmp, 0, currx
L12:// Words: 536
addi $gp, -4
// Words: 537
ldw $k0, $0, $rr
//: load *tmp2, 0, intervalx
// Words: 538
// Words: 539
ldi $k2, -13
// Words: 540
ldw $k1, $fp, $k2
//: + *tmp, *tmp2, *tmp
// Words: 541
add $k0, $k1
// Words: 542
move $k0, $rr
//: store currx, 0, *tmp
// Words: 543
addi $gp, -4
// Words: 544
sdw $k0, $0, $rr
//: load *tmp, 0, c
L13:// Words: 545
// Words: 546
ldi $k2, -11
// Words: 547
ldw $k0, $fp, $k2
//: loadi *tmp2, , 10
// Words: 548
// Words: 549
ldi $k1, 10
//: beq , *tmp2, *tmp
// Words: 550
// Words: 551
// Words: 552
// Words: 553
// Words: 554
// Words: 555
// Words: 556
la $k2, L17
// Words: 557
beq $k0, $k1, $k2
//: assembly rp $v, 3, , 
L14:// Words: 558
rp $v, 3
//: move *tmp, , *v
// Words: 559
move $k0, $v
//: loadi *tmp2, , 0
// Words: 560
// Words: 561
ldi $k1, 0
//: blte , *tmp2, *tmp
// Words: 562
// Words: 563
// Words: 564
// Words: 565
// Words: 566
// Words: 567
// Words: 568
la $k2, L16
// Words: 569
blt $k0, $k1, $k2
// Words: 570
beq $k0, $k1, $k2
//: jump , , 
L15:// Words: 571
// Words: 572
// Words: 573
// Words: 574
// Words: 575
// Words: 576
// Words: 577
la $k2, L14
// Words: 578
jr $k2
//: assembly ldi $k0, 512;add $k0, $s1;wp $rr, 3;ldi $k0, 1024;add $k0, $s0;wp $rr, 3, , 
L16:// Words: 579
addi $gp, -4
// Words: 580
ldw $s1, $0, $rr
// Words: 581
addi $gp, -6
// Words: 582
ldw $s0, $0, $rr
// Words: 583
ldi $k0, 512
// Words: 584
add $k0, $s1
// Words: 585
wp $rr, 3
// Words: 586
ldi $k0, 1024
// Words: 587
add $k0, $s0
// Words: 588
wp $rr, 3
//: assembly ldi $k0, 1536; add $k0, $s0; wp $rr, 3;ldi $k0, 2048;add $k0, $s1;wp $rr, 3, , 
// Words: 589
// Words: 590
ldi $k2, -11
// Words: 591
ldw $s1, $fp, $k2
// Words: 592
addi $gp, -8
// Words: 593
ldw $s0, $0, $rr
// Words: 594
ldi $k0, 1536
// Words: 595
 add $k0, $s0
// Words: 596
 wp $rr, 3
// Words: 597
ldi $k0, 2048
// Words: 598
add $k0, $s1
// Words: 599
wp $rr, 3
//: load *tmp, 0, c
L17:// Words: 600
// Words: 601
ldi $k2, -11
// Words: 602
ldw $k0, $fp, $k2
//: jr , *tmp, 
// Words: 603
move $v, $k0
// Words: 604
addi $0, -2
// Words: 605
ldw $ra, $fp, $rr
// Words: 606
addi $rr, -3
// Words: 607
addi $rr, -2
// Words: 608
ldw $s0, $fp, $rr
// Words: 609
addi $rr, -2
// Words: 610
ldw $s1, $fp, $rr
// Words: 611
addi $fp, -13
// Words: 612
move $sp, $rr
// Words: 613
// Words: 614
ldi $k0, -4
// Words: 615
ldw $fp, $fp, $k0
// Words: 616
jr $ra
//putsint: funcdecl 1, , 
putsint:// Words: 617
addi $sp, 13
// Words: 618
move $sp, $rr
// Words: 619
addi $0, -2
// Words: 620
sdw $ra, $sp, $rr
// Words: 621
addi $rr, -2
// Words: 622
sdw $fp, $sp, $rr
// Words: 623
move $fp, $sp
// Words: 624
addi $rr, -1
// Words: 625
// Words: 626
ldi $k2, 1
// Words: 627
swn $k2, $fp, $rr
// Words: 628
addi $rr, -2
// Words: 629
sdw $s0, $fp, $rr
// Words: 630
addi $rr, -2
// Words: 631
sdw $s1, $fp, $rr
//: formal s, , 
// Words: 632
ldw $k2, $a, $0
// Words: 633
addi $0, -13
// Words: 634
sdw $k2, $fp, $rr
//: loadi *tmp, , 0
// Words: 635
// Words: 636
ldi $k0, 0
//: store i, 0, *tmp
// Words: 637
// Words: 638
ldi $k2, -11
// Words: 639
sdw $k0, $fp, $k2
//: load *tmp, 0, s
L19:// Words: 640
// Words: 641
ldi $k2, -13
// Words: 642
ldw $k0, $fp, $k2
//: load *tmp2, 0, i
// Words: 643
// Words: 644
ldi $k2, -11
// Words: 645
ldw $k1, $fp, $k2
//: <<i *tmp2, 1, *tmp2
// Words: 646
slli $k1, 1
// Words: 647
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 648
add $k0, $k1
// Words: 649
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 650
ldw $k0, $0, $k0
//: loadi *tmp2, , 0
// Words: 651
// Words: 652
ldi $k1, 0
//: beq , *tmp2, *tmp
// Words: 653
// Words: 654
// Words: 655
// Words: 656
// Words: 657
// Words: 658
// Words: 659
la $k2, L21
// Words: 660
beq $k0, $k1, $k2
//: load *tmp, 0, s
L20:// Words: 661
// Words: 662
ldi $k2, -13
// Words: 663
ldw $k0, $fp, $k2
//: load *tmp2, 0, i
// Words: 664
// Words: 665
ldi $k2, -11
// Words: 666
ldw $k1, $fp, $k2
//: <<i *tmp2, 1, *tmp2
// Words: 667
slli $k1, 1
// Words: 668
move $k1, $rr
//: + *tmp, *tmp2, *tmp
// Words: 669
add $k0, $k1
// Words: 670
move $k0, $rr
//: u* *tmp, , *tmp
// Words: 671
ldw $k0, $0, $k0
//: param *tmp, , 
// Words: 672
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 673
addi $sp, 2
// Words: 674
move $a, $sp
// Words: 675
move $sp, $rr
// Words: 676
// Words: 677
// Words: 678
// Words: 679
// Words: 680
// Words: 681
// Words: 682
la $k2, putcharint
// Words: 683
jalr $k2
// Words: 684
addi $sp, -2
// Words: 685
move $sp, $rr
//: load *tmp, 0, i
// Words: 686
// Words: 687
ldi $k2, -11
// Words: 688
ldw $k0, $fp, $k2
//: loadi *tmp2, , 1
// Words: 689
// Words: 690
ldi $k1, 1
//: + *tmp, *tmp2, *tmp
// Words: 691
add $k0, $k1
// Words: 692
move $k0, $rr
//: store i, 0, *tmp
// Words: 693
// Words: 694
ldi $k2, -11
// Words: 695
sdw $k0, $fp, $k2
//: jump , , 
// Words: 696
// Words: 697
// Words: 698
// Words: 699
// Words: 700
// Words: 701
// Words: 702
la $k2, L19
// Words: 703
jr $k2
//: loadi *tmp, , 10
L21:// Words: 704
// Words: 705
ldi $k0, 10
//: param *tmp, , 
// Words: 706
sdw $k0, $sp, $0
//: funccall , 1, putcharint
// Words: 707
addi $sp, 2
// Words: 708
move $a, $sp
// Words: 709
move $sp, $rr
// Words: 710
// Words: 711
// Words: 712
// Words: 713
// Words: 714
// Words: 715
// Words: 716
la $k2, putcharint
// Words: 717
jalr $k2
// Words: 718
addi $sp, -2
// Words: 719
move $sp, $rr
//: loadi *tmp, , 0
// Words: 720
// Words: 721
ldi $k0, 0
//: jr , *tmp, 
// Words: 722
move $v, $k0
// Words: 723
addi $0, -2
// Words: 724
ldw $ra, $fp, $rr
// Words: 725
addi $rr, -3
// Words: 726
addi $rr, -2
// Words: 727
ldw $s0, $fp, $rr
// Words: 728
addi $rr, -2
// Words: 729
ldw $s1, $fp, $rr
// Words: 730
addi $fp, -13
// Words: 731
move $sp, $rr
// Words: 732
// Words: 733
ldi $k0, -4
// Words: 734
ldw $fp, $fp, $k0
// Words: 735
jr $ra
.data
D0:
H
e
l
l
o
 
W
o
r
l
d
!
\0
