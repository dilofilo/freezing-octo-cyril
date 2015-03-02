.allc:
	mov r1 , 4096
	mul r13 , r0 , r0
	mul r13 , r13 , 4 /* r13 = 4N*N called over and over again. */
	mul r2 , r13 , 3
	.alloc r1 r2
	ret

.matInit:
	mov r2 , 0 /* ROW */
	.rloopInit:
		cmp r2 , r0
		beq .rbreakInit
		mov r3 , 0 /* COLUMN*/
		.cloopInit:
			cmp r3 , r0
			beq .cbreakInit
			mul r4, r2, r0 /* CALCULATE LOCATION FOR A*/
			mul r4, r4, 4
			mul r5, r3, 4
			add r4, r4, r5
			add r4, r4, r1 /* CALCULATE LOCATION FOR A */
			add r5 , r2 , r3 /* calculate value for A */
			mod r5 , r5 , 17 /* calculate value for A */
			st r5 , [r4] /* STORE A */			
			add r4 , r4 , r13 /* Calculate location for B */
			sub r5, r2, r3 /* calculate value for B*/
			add r5, r5, 64
			mod r5, r5, 6
			mul r6, r2, r3
			mod r6, r6, 8
			add r5, r5, r6 /* Calculate value for B*/
			st r5 , [r4]
			add r3 , r3 , 1
			b .cloopInit
		.cbreakInit:
			add r2 , r2 , 1
			b .rloopInit
	.rbreakInit:
		ret
.matMult:
	mul r10 , r0 , 4
	mov r2 , 0 /* Row Number */
	.rloopMult:
		cmp r2 , r0
		beq .rbreakMult

		mov r3 , 0 /* Column Number */
		.cloopMult:
			cmp r3 , r0
			beq .cbreakMult
			mov r12 , 0 /* c[i][j] */
			mov r14 , 0/* c[i][j+1]  I Dont need the stack pointer. */
			mov r4 , 0 /* iteration number */
			.iloopMult: /* r11 is used as the accumulator */
				cmp r4 , r0
				beq .ibreakMult
				mul r5, r2, r0 /* COLUMN 1 BEGIN Location in A*/
				add r5, r5, r4
				mul r5, r5, 4
				add r5, r5, r1 /* Location of A*/
				mul r7, r4, r0 /* Pointer to B */
				add r7, r7, r3
				mul r7, r7, 4
				add r7, r7, r13
				add r7, r7, r1 /* Pointer to B */
				ld r6 , [r5]
				ld r8 , [r7]
				mul r11 , r6 , r8 /* a[i][k]*b[k][j] */
				add r12 , r12, r11 /* Add it to the c[i][j] */
				add r5 , r5 , 4 /*LOOP UNROLL! */
				ld r6 , [r5]
				add r7 , r7 , r10 /**/
				ld r8 , [r7]
				mul r11 , r6 , r8
				add r12 , r12 , r11 /*LOOP UNROLL 1 ENDED */
				add r5 , r5 , 4 /*LOOP UNROLL 2 BEGIN */
				ld r6 , [r5]
				add r7 ,r7 , r10
				ld r8 , [r7]
				mul r11 , r6 , r8
				add r12 , r12 , r11 /* LOOP UNROLL 2 END*/
				add r5 , r5 , 4 /*LOOP UNROLL 3 BEGIN */
				ld r6 , [r5]
				add r7 ,r7 , r10
				ld r8 , [r7]
				mul r11 , r6 , r8
				add r12 , r12 , r11 /* LOOP UNROLL 3 END*/
				add r4 , r4 , 4 /* COLUMN 1 END */
				add r7 , r7 , 4 /* COLUMN 2 BEGIN */
				/* ld r6 , [r5] */ /* TODO? */
				ld r8 , [r7]
				mul r11 , r6 , r8
				add r14 , r14 , r11 /* Latest iterator */
				sub r5 , r5 , 4
				sub r7 , r7 , r10 /* switched to the previous iterator*/
				ld r6 , [r5]
				ld r8, [r7]
				mul r11 , r6 , r8
				add r14 , r14 , r11 /* third iterator */
				sub r5 , r5 , 4
				sub r7 , r7 , r10 /* switched to the previous iterator*/
				ld r6 , [r5]
				ld r8, [r7]
				mul r11 , r6 , r8
				add r14 , r14 , r11 /* second iterator */
				sub r5 , r5 , 4
				sub r7 , r7 , r10 /* switched to the previous iterator*/
				ld r6 , [r5]
				ld r8, [r7]
				mul r11 , r6 , r8
				add r14 , r14 , r11 /* first iterator */
				b .iloopMult
			.ibreakMult:
				mul r9, r2, r0 /* r9 is pointer to C */
				add r9, r9, r3
				mul r9, r9, 4
				add r9, r9, r13
				add r9, r9, r13
				add r9, r9, r1
				st r12, [r9] /* Store c[i][j] */
				add r9 , r9 , 4 /*OTHER COLUMN*/
				st r14 , [r9]
				add r3, r3, 2 /* Column Number */
				b .cloopMult
		.cbreakMult:
			add r2 , r2 , 1 /* Row number */
			b .rloopMult
	.rbreakMult:
		ret
.matElementSum:
	mov r12 , r1 /* r12 keeps r1. r1 will now keep the sum */
	mov r1 , 0
	mov r2 , 0 /* Row Number */
	.rloopSum:
		cmp r2 , r0
		beq .rbreakSum
		mov r3 , 0 /* Column */
		.cloopSum:
			cmp r3 , r0
			beq .cbreakSum
			mul r4, r2, r0 /* Calculate position */
			add r4, r4, r3
			mul r4, r4, 4
			add r4, r4, r13
			add r4, r4, r13
			add r4, r4, r12
			ld r11 , [r4] /* fetch c[i][j] */
			add r1 , r1 , r11 /* Add it to the sum */
			add r3, r3 , 1
			b .cloopSum
		.cbreakSum:
			add r2 , r2 , 1
			b .rloopSum
	.rbreakSum:
		.print r1
		ret
.main:
	call .allc
	call .matInit
	call .matMult
	call .matElementSum