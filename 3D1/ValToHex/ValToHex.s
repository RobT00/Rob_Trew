; Start of file ValToHex.s
;
; Copyright 2017 University of Dublin. All Rights Reserved.
;
; Design and write an ARM assembly language program to 
; convert a 32 bit unsigned value stored in r1
; to it's hexadecimal ASCII string representation.
; Store the resulting string beginning at address 
; 0xA1000400. Your answer should contain 8 characters
; including leading zeros where appropriate, and
; should use uppercase 'A'-'F'.

	AREA	ValToHex, CODE, READONLY
	IMPORT	main
	EXPORT	start
start

	LDR	r1, =0xFEED1234

; Changes above this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.
; ARM syntax requires instructions to be indented by
; at least one space or tab.
; -------------- start cut ------------------------
		LDR r0, =0xA1000400
		LDR r2, =28
		;LDR r4, =0
		B loop
wh1		SUBS r2, #0x4
		CMP r3, #0x9
		BCS endif1
		ADD r3, #0x30
		B hold
endif1 	ADD r3, #0x40
		SUB r3, #0x9
hold	STRB r3, [r0], #1
		;ADD r4, #1
loop 	MOV r3, r1, LSR r2
		AND r3, r3, #0xF
		CMP r2, #0
		BGE wh1 
; -------------- end cut --------------------------
; Changes below this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.

stop	B	stop
	END
;
; End of file ValToHex.s