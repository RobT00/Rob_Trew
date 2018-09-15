; Start of file BitPattern.s
;
; Copyright 2017 University of Dublin. All Rights Reserved.
;
; Design and write an ARM Assembly Language program that will examine a
; 32-bit value stored in R1 and count the number of contiguous sequences
; of 1s and store this in R0.
; For example, the value 01110001000111101100111000111111 will give 6 in R0.
; 
	AREA	BitPattern, CODE, READONLY
	IMPORT	main
	EXPORT	start
start

	LDR	R1, =2_01110001000111101100111000111111

; Changes above this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.
; ARM syntax requires instructions to be indented by
; at least one space or tab.
; -------------- start cut ------------------------
	LDR r10, =0
	LDR r0, =0
	LDR r8, =1
loop
	CMP r10, #0x20
	BNE else1			;if 0, 32 bits checked
	B breakloop			;all bits checked, exit program
else1
	MOV r3, r1, LSR r10	
	AND r2, r3, #1		;check if curent bit is 1 or 0
	ADD r10, r10, #1	;increment bit count
	CMP r2, r8	
	BNE if1				;a new sequence of 1s is found
	EOR r8, r8, #1		;flip check bit
	CMP r2, #1			;check if 1
	BNE if1
	ADD r0, r0, #1		;increment count of sequences of 1s
	B loop				;back to top
if1						;bit is not a new sequence of 1s
	B loop
breakloop
; -------------- end cut --------------------------
; Changes below this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.

stop	B	stop
	END
;
; End of file BitPattern.s