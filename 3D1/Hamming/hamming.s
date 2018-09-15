; Start of file Hamming.s
;
; Copyright 2017 University of Dublin. All Rights Reserved.
;
; Design and write an assembly language program that 
; generates a 12-bit Hamming Code in R0 from an 8-bit value in R1.
; 
	AREA	Hamming, CODE, READONLY
	IMPORT	main
	EXPORT	start
start

	LDR	r1, =0xAC

; Changes above this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.
; ARM syntax requires instructions to be indented by
; at least one space or tab.
; -------------- start cut ------------------------
	;c0 in 0, calculated on bits 2, 4, 6, 8, 10
	;c1 in 1, calculated on bits 2, 5, 6, 9, 10
	;c2 in 3, calculated on bits 4, 5, 6, 11
	;c3 in 7, calculated on bits 8, 9, 10, 11
	;0xAC == 10101100
	;-> 1010x110x0xx
	;c0 -> (0, 0, 1, 0, 0) => c0 = 1
	;c1 -> (0, 1, 1, 1, 0) => c1 = 1
	;c2 -> (0, 1, 1, 1) => c2 = 1
	;c3 -> (0, 1, 0, 1) => c2 = 0
	
	;Get all needed bits: 2, 4, 5, 6, 8, 9, 10, 11
	;Actually, need: 0, 1, 2, 3, 4, 5, 6, 7
	;0 -> 2
	;1 -> 4
	;2 -> 5
	;3 -> 6
	;4 -> 8
	;5 -> 9
	;6 -> 10
	;7 -> 11
	;LDR r0, =1
	AND r2, r1, #0x1 ;LSB (0)
	;MOV r0, r0, LSL #1
	MOV r3, r1, LSR #1
	AND r3, r3, #0x1; (1)
	;MOV r3, r3, LSR #1; (1)
	;MOV r0, r0, LSL #1
	MOV r4, r1, LSR #2
	AND r4, r4, #0x1; (2)
	;MOV r3, r3, LSR #2; (2)
	;MOV r0, r0, LSL #1
	MOV r5, r1, LSR #3
	AND r5, r5, #0x1; (3)
	;MOV r3, r3, LSR #3; (3)
	;MOV r0, r0, LSL #1
	MOV r6, r1, LSR #4
	AND r6, r6, #0x1; (4)
	;MOV r3, r3, LSR #4; (4)
	;MOV r0, r0, LSL #1
	MOV r7, r1, LSR #5
	AND r7, r7, #0x1; (5)
	;MOV r3, r3, LSR #5; (5)
	;MOV r0, r0, LSL #1
	MOV r8, r1, LSR #6
	AND r8, r8, #0x1; (6)
	;MOV r3, r3, LSR #6; (6)
	;MOV r0, r0, LSL #1
	MOV r9, r1, LSR #7
	AND r9, r9, #0x1;MSB (7)
	;MOV r3, r3, LSR #7; (7)
	
	;Getting c0
	EOR r0, r2, r3;(0), (1) = 0
	EOR r10, r5, r6;(3), (4) = 1
	EOR r11, r10, r8;1, (6) = 1
	EOR r0, r11, r0;0, 1 = 1, c0
	
	;Getting c1
	EOR r10, r2, r4;(0), (2) = 1
	EOR r11, r5, r7;(3), (5) = 0
	EOR r11, r11, r8;0, (6) = 0
	EOR r10, r11, r10;0, 1 = 1, c1
	
	;Getting c2
	EOR r11, r3, r4;(0), (1) = 1
	EOR r12, r5, r9;(1), (1) = 0
	EOR r11, r12, r11;0, 1 = 1, c2
	
	;Getting c3
	EOR r12, r6, r7;(0), (1) = 1
	EOR r2, r8, r9;(0), (1) = 1
	EOR r12, r2, r12;1, 1 = 0, c3
	
	;Resetting r2
	AND r2, r1, #0x1
	
	MOV r9, r9, LSL #1; (11)
	ADD r9, r9, r8; (10)
	MOV r9, r9, LSL #1
	ADD r9, r9, r7; (9)
	MOV r9, r9, LSL #1
	ADD r9, r9, r6; (8)
	MOV r9, r9, LSL #1
	ADD r9, r9, r12; (7) -> c3
	MOV r9, r9, LSL #1
	ADD r9, r9, r5; (6)
	MOV r9, r9, LSL #1
	ADD r9, r9, r4; (5)
	MOV r9, r9, LSL #1
	ADD r9, r9, r3; (4)
	MOV r9, r9, LSL #1
	ADD r9, r9, r11; (3) -> c2
	MOV r9, r9, LSL #1
	ADD r9, r9, r2; (2)
	MOV r9, r9, LSL #1
	ADD r9, r9, r10; (1) -> c1
	MOV r9, r9, LSL #1
	ADD r0, r9, r0; (0) -> c0
	
; -------------- end cut --------------------------
; Changes below this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.

stop	B	stop
	END
;
; End of file Hamming.s
