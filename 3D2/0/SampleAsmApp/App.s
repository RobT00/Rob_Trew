	AREA	AsmTemplate, CODE, READONLY
	IMPORT	main

; sample program makes the 4 LEDs P1.16, P1.17, P1.18, P1.19 go on and off in sequence
; (c) Mike Brady, 2011.

	EXPORT	start
start

IO1DIR	EQU	0xE0028018
IO1SET	EQU	0xE0028014
IO1CLR	EQU	0xE002801C

	ldr	r1,=IO1DIR
	ldr	r2,=0x000f0000	;select P1.19--P1.16
	str	r2,[r1]		;make them outputs
	ldr	r1,=IO1SET
	str	r2,[r1]		;set them to turn the LEDs off
	ldr	r2,=IO1CLR
; r1 points to the SET register
; r2 points to the CLEAR register
	
	ldr r7,=0
	ldr	r6,=0x00080000	; end when the mask reaches this value
	ldr	r5,=0x00010000		; end when reach this value
	ldr r3,=0x00010000
;wloop1	ldr	r3,=0x00010000	; start with P1.16.
;wloop2	ldr r3, =0x00080000	; start with P1.19
floop	str	r3,[r2]	   	; clear the bit -> turn on the LED

;delay for about a half second
	ldr	r4,=1000000
dloop	subs	r4,r4,#1
	bne	dloop

	str	r3,[r1]				;set the bit -> turn off the LED
	cmp	r7, #0
	beq ltr
	bne rtl
rtl	cmp r3, r6
	ldreq r7, =0
	b inc
ltr	cmp r3, r5
	ldreq r7, =1
	b inc
	
inc cmp r7, #0
	moveq	r3,r3,lsr #1	;shift down to next bit. P1.19 -> P1`.18 etc.
	movne	r3,r3,lsl #1	;shift up to next bit. P1.16 -> P1.17 etc.
	b	floop
stop	B	stop

	END