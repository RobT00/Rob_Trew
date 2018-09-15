; Start of file Parity.s
;
; Copyright 2017 University of Dublin. All Rights Reserved.
;
; Design and write an assembly language program that 
; will calculate the parity bit for a 7 bit value stored in r0. 
; 
; The program should then store the computed parity bit 
; in bit 7 of r0. Assume even parity.
; 
; Using even parity, the parity bit of a value is set such that the 
; number of set bits (1’s) in a value is always even.
; 
	AREA	Parity, CODE, READONLY
	IMPORT	main
	EXPORT	start
start

	LDR	r0, =0x36

; Any changes above this line will prevent CODEMARK
; working. Enter your solution between dashed lines.
; -------------- start cut ------------------------

	MOV r1, r0
	;LDR r2, =0
	
	LDR r11, =0x1
	;AND r11, r1, #0x1 ;Works as intended
	;MOV r11, r0
	;MOV r10, r1, LSR #8
	;EOR r12, r10, r11
	
	MOV r9, r1, LSR #7 ;MSB
	;SUB r2, r9, r10
	;EOR r12, r2, r9
	AND r9, r9, r11
	
	MOV r8, r1, LSR #6
	;SUB r2, r8, r9
	;EOR r12, r2, r8
	AND r8, r8, r11
	EOR r9, r9, r8
	
	MOV r7, r1, LSR #5
	;SUB r2, r7, r8
	;EOR r12, r2, r7
	AND r7, r7, r11
	EOR r9, r9, r7
	
	MOV r6, r1, LSR #4
	;SUB r2, r6, r7
	;EOR r12, r2, r6
	AND r6, r6, r11
	EOR r9, r9, r6
	
	MOV r5, r1, LSR #3
	;SUB r2, r2, r6
	;EOR r12, r2, r5
	AND r5, r5, r11
	EOR r9, r9, r5
	
	MOV r4, r1, LSR #2
	;SUB r2, r4, r5
	;EOR r12, r2, r4
	AND r4, r4, r11
	EOR r9, r9, r4
	
	MOV r3, r1, LSR #1 ;LSB (kind of)
	;SUB r2, r3, r4 ;To give LSB
	;EOR r12, r2, r3
	AND r3, r3, r11
	EOR r9, r9, r3
	
	MOV r10, r9
	LDR r1, =0x80
	MUL r12, r10, r1 
	
	ORR r0, r0, r12
	
		
	;ORR r0, r1, r0
	;EOR r0, r0, r1
	
; -------------- end cut --------------------------
; Any changes below this line will prevent CODEMARK
; working. Enter your solution between dashed lines.

stop	B	stop
	END
;
; End of file Parity.s