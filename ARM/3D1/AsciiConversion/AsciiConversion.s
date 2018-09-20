	AREA	AsciiConversion, CODE, READONLY
	IMPORT	main
	EXPORT	start

start
	LDR r7, ='1'
	LDR r6, ='0'
	LDR r5, ='3'
	LDR r4, ='4'
	LDR r3, ='2'
	LDR r2, ='7'
	LDR r1, ='9'
	;Converting from ASCII to hex val
	MOV r8, #0x30
	SUB r7, r7, r8
	SUB r6, r6, r8
	SUB r5, r5, r8
	SUB r4, r4, r8
	SUB r3, r3, r8
	SUB r2, r2, r8
	SUB r1, r1, r8
	;Multiplying by radix
	LDR r8, =10
	MOV r9, r8
	MUL r2, r8, r2
	MUL r8, r9, r8
	MUL r3, r8, r3
	MUL r8, r9, r8
	MUL r4, r8, r4
	MUL r8, r9, r8
	MUL r5, r8, r5
	MUL r8, r9, r8
	MUL r6, r8, r6
	MUL r8, r9, r8
	MUL r7, r8, r7
	;Adding numbers together
	ADD r0, r7, r6
	ADD r0, r5, r0
	ADD r0, r4, r0
	ADD r0, r3, r0
	ADD r0, r2, r0
	ADD r0, r1, r0
 
stop	B	stop

	END	