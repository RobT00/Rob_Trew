; Start of file ReversePolish.s
;
; Copyright 2017 University of Dublin. All Rights Reserved.
;
; Design, implement, test an ARM Assembly Language program that
; evaluates Reverse Polish Notation (RPN) expressions. Your solution 
; should use problem decomposition with appropriate subroutines.
; Use memory addresses descending from 0xA1000400 for stack operations.
; 
; Your program should evaluate a single RPN expression, rpnexp, stored 
; as a NULL-terminated ASCII string in memory and store the result in r0.
; You may assume that the string contains only operands, operators and 
; spaces. Operators and operands are seperated by a single space character 
; (0x20). You may also assume that the RPN expression represented in the 
; string is valid.
; 

	AREA	ReversePolish, CODE, READONLY
	IMPORT	main
	EXPORT	start
start

; Changes above this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.
; ARM syntax requires instructions to be indented by
; at least one space or tab.
; -------------- start cut ------------------------
		LDR r0, =0
		LDR r8, =2 ;space flag, 0 means no prev space
		LDR r2, =rpnexp 
		LDR r1, =0xA1000400
		B loop
wh1		CMP r3, #'n'
		BEQ negate
		CMP r3, #'!'
		BEQ fact
		CMP r3, #'^'
		BEQ op
		CMP r3, #0x30
		BHS num
		B op
num		SUB r3, #0x30
		;push to stack (descending)
		CMP r8, #0 ;no prev space
		BNE norm ;no space prev
		LDR r4, [r1]
		LDR r5, =0xA
		MUL r4, r5, r4
		ADD r3, r4, r3
		STR r3, [r1]
		B loop
norm	SUB r1, #4
		STR r3, [r1]
		LDR r8, =0
		B loop
negate	LDR r4, [r1]
		MVN r4, r4
		ADD r4, #1
		STR r4, [r1]
		LDR r8, =0
		B loop
fact	LDR r3, [r1]
		MOV r4, #1
		MOVS r5, r3
wh4		CMP r5, #1
		BLS endwh4
		MUL r4, r5, r4
		SUBS r5, #1
		B wh4
endwh4	STR r4, [r1]
		B loop
loop	LDRB r3, [r2], #1
		CMP r3, #0
		BEQ fin
		CMP r3, #0x20
		BEQ flip
		B wh1
flip	LDR r8, =1 ;have a space
		B loop
		;need to pull from stack for operation
op		LDR r4, [r1]
		ADD r1, #4
		LDR r5, [r1]
		ADD r1, #4
		CMP r3, #'*'
		BEQ times
		CMP r3, #'+'
		BEQ plus
		CMP r3, #'-'
		BEQ minus
		CMP r3, #'^'
		BEQ pow
		CMP r3, #'/'
		BEQ divide
times	MUL r6, r5, r4 ;multiply function
		B endop
plus	ADDS r6, r5, r4 ;add function
		B endop
minus	SUBS r6, r5, r4 ;subtract function
		B endop
pow		MOV r6, #1 ;looped multiplication (power)
		MOVS r5, r5
wh3		
		BEQ endop
		MUL r6, r5, r6
		SUBS r4, #1
		B wh3
divide	LDR r6, =0;looped subtraction (division)
		MOVS r5, r5
wh2		
		BEQ endop
		SUBS r5, r4
		BMI endop
		ADD r6, #1
		B wh2
endop	SUB r1, #4
		STR r6, [r1]
		B loop
fin		LDR r0, [r1];end of running, should only be one number on stack 
; -------------- end cut --------------------------
; Changes below this line are discarded by CODEMARK.
; Enter your solution between dashed lines only.

stop	B	stop
	AREA	ReversePolish, DATA, READWRITE
rpnexp	DCB	"2 5 ! 10 + *",0
	END
;
; End of file ReversePolish.s