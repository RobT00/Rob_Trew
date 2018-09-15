; Start of file HexToVal.s
;
; Copyright 2017 University of Dublin. All Rights Reserved.
;
; Design and write an assembly language program that
; will convert an ASCII representation of a hexadecimal
; value to a value. TestStr is a NULL-terminated string 
; in memory and the converted value should be stored in 
; register r0.
	AREA	HexToVal, CODE, READONLY
	IMPORT	main
	EXPORT	start
start

; Changes above this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.
; ARM syntax requires instructions to be indented by
; at least one space or tab.
; -------------- start cut ------------------------
		LDR r1, =TestStr
		LDR r0, =0
		LDR r3, =0
		LDR r4, =0
		B loop
wh1		MOV r0, r0, LSL r4
		CMP r3, #'9'
		BHI endif1
		BIC r3, #0x30
		B ins
endif1	CMP r3, #'O'
		BHI endif2
		BIC r3, #0x40
		B lett
endif2	CMP r3, #'Z'
		BHI endif3
		BIC r3, #0x50
		B lett
endif3	CMP r3, #'o'
		BHI endif4
		BIC r3, #0x60
		B lett
endif4	BIC r3, #0x70
lett	ADD r3, #0xA
		SUB r3, #1
ins		ADD r0, r3
		CMP r4, #0x0
		BNE loop
		ADD r4, #4
loop	LDRB r3, [r1], #1
		CMP r3, #0
		BNE wh1 ;while not a null character
 ; -------------- end cut --------------------------
; Changes below this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.

stop	B	stop
	AREA	HexToVal, DATA, READWRITE
TestStr	DCB	"123aBc12",0
	END
;
; End of file HexToVal.s