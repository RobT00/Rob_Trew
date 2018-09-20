; Start of file Hamming2.s
;
; Copyright 2017 University of Dublin. All Rights Reserved.
;
; Design and write an assembly language program that will detect and correct single 
; bit errors in a 12-bit Hamming Code in R0. Your program should begin by clearing 
; and then re-calculating the check bits using the same assembly language program 
; that was used to generate the original Hamming Code. Your program should then 
; compare the original and re-calculated values and should finally correct any 
; single bit error and store the correct 8 bit number in R0.
; 
	AREA	Hamming2, CODE, READONLY
	IMPORT	main
	EXPORT	start
start

	LDR	r0, =0xb6b

; Changes above this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.
; ARM syntax requires instructions to be indented by
; at least one space or tab.
; -------------- start cut ------------------------
	;isolate bits of 8-bit number
	MOV r1, r0, LSR #2
	AND r1, r1, #0x1 ;bit 2 (0)
	MOV r2, r0, LSR #4
	AND r2, r2, #0x1 ;bit 4 (1)
	MOV r3, r0, LSR #5 
	AND r3, r3, #0x1 ;bit 5 (2)
	MOV r4, r0, LSR #6
	AND r4, r4, #0x1 ;bit 6 (3)
	MOV r5, r0, LSR #8
	AND r5, r5, #0x1 ;bit 8 (4)
	MOV r6, r0, LSR #9
	AND r6, r6, #0x1 ;bit 9 (5)
	MOV r7, r0, LSR #10
	AND r7, r7, #0x1 ;bit 10 (6)
	MOV r8, r0, LSR #11
	AND r8, r8, #0x1 ;bit 11 (7)
	;calculate hamming code for isolated bits
	;c0 (2, 4, 6, 8, 10)
	EOR r9, r1, r2
	EOR r10, r4, r5
	EOR r11, r10, r7
	EOR r9, r11, r9;
	;c1 (2, 5, 6, 9, 10)
	EOR r10, r1, r3
	EOR r11, r4, r6
	EOR r11, r11, r7
	EOR r10, r10, r11
	;c2 (4, 5, 6, 11)
	EOR r11, r2, r3
	EOR r12, r4, r8
	EOR r11, r11, r12
	;c3 (8, 9, 10, 11)
	EOR r1, r5, r6
	EOR r12, r7, r8
	EOR r12, r1, r12
	;resetting r2
	MOV r2, r0, LSR #4
	AND r2, r2, #0x1 ; bit 4 (2)
	;recombine to form 12-bit hamming result
	MOV r8, r8, LSL #1; (11)
	ADD r8, r8, r7; (10)
	MOV r8, r8, LSL #1
	ADD r8, r8, r6; (9)
	MOV r8, r8, LSL #1
	ADD r8, r8, r5; (8)
	MOV r8, r8, LSL #1
	ADD r8, r8, r12; (7) -> c3
	MOV r8, r8, LSL #1
	ADD r8, r8, r4; (6)
	MOV r8, r8, LSL #1
	ADD r8, r8, r3; (5)
	MOV r8, r8, LSL #1
	ADD r8, r8, r2; (4)
	MOV r8, r8, LSL #1
	ADD r8, r8, r11; (3) 0-> c2
	MOV r8, r8, LSL #1 
	ADD r8, r8, r1; (2)
	MOV r8, r8, LSL #1
	ADD r8, r8, r10; (1) -> c1
	MOV r8, r8, LSL #1
	ADD r8, r8, r9; (0) -> c0
	;EOR r8 and r0, find difference
	EOR r1, r8, r0
	;isolate leeft over check bits
	AND r2, r1, #1; c0
	MOV r3, r1, LSR #1
	AND r3, r3, #1; c1
	MOV r4, r1, LSR #3
	AND r4, r4, #1; c2
	MOV r5, r1, LSR #7
	AND r5, r5, #1; c3
	;recombine check bits
	MOV r5, r5, LSL #1; (3)
	ADD r5, r5, r4; (2)
	MOV r5, r5, LSL #1
	ADD r5, r5, r3; (1)
	MOV r5, r5, LSL #1
	ADD r5, r5, r2; (0)
	;check bits value -1
	SUB r1, r5, #1
	;r1 coresponds to position of corrupted bit
	LDR r2, =1
	MOV r2, r2, LSL r1
	EOR r0, r0, r2 ;Correct 12-bit number
	;Reconvert 12-bit hamming code to original 8-bit number
	MOV r1, r0, LSR #2
	AND r1, r1, #1; 2 (0)
	MOV r2, r0, LSR #4
	AND r2, r2, #1; 4 (1)
	MOV r3, r0, LSR #5
	AND r3, r3, #1; 5 (2)
	MOV r4, r0, LSR #6
	AND r4, r4, #1; 6 (3)
	MOV r5, r0, LSR #8
	AND r5, r5, #1; 8 (4)
	MOV r6, r0, LSR #9
	AND r6, r6, #1; 9 (5)
	MOV r7, r0, LSR #10
	AND r7, r7, #1; 10 (6)
	MOV r8, r0, LSR #11 
	AND r8, r8, #1; 11 (7)
	;Recombine original 8-bit number
	MOV r8, r8, LSL #1; 7
	ADD r8, r8, r7; 6
	MOV r8, r8, LSL #1
	ADD r8, r8, r6; 5
	MOV r8, r8, LSL #1
	ADD r8, r8, r5; 4
	MOV r8, r8, LSL #1
	ADD r8, r8, r4; 3
	MOV r8, r8, LSL #1
	ADD r8, r8, r3; 2
	MOV r8, r8, LSL #1
	ADD r8, r8, r2; 1
	MOV r8, r8, LSL #1
	ADD r0, r8, r1; 0
; -------------- end cut --------------------------
; Changes below this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.

stop	B	stop
	END
;
; End of file Hamming2.s