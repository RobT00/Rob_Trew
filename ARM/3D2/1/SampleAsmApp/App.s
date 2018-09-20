	AREA	Segments, CODE, READONLY
	IMPORT	main

; sample program makes the 4 LEDs P1.16, P1.17, P1.18, P1.19 go on and off in sequence

	EXPORT	start
start

IO1DIR		   EQU	   0xE0028018
IO1SET		   EQU	   0xE0028014
IO1CLR		   EQU	   0xE002801C
IO1PIN         EQU     0xE0028010
IO0SET         EQU     0xE0028004
IO0DIR         EQU     0xE0028008
IO0CLR         EQU     0xE002800C
PINMASK		   EQU	   0x00551540
	ldr	r1,=IO0DIR
	ldr r5,=PINMASK
	ldr	r2,=PINMASK	;select P0.08--P0.25
	str	r2,[r1]		;make them outputs
	ldr	r1,=IO0SET
	str	r2,[r1]		;set them to turn the LEDs off
	ldr	r2,=IO0CLR
	ldr r0,=IO1DIR
	ldr r10,=0
	str r10, [r0]
	ldr r0,=IO1PIN
; r1 points to the SET register
; r2 points to the CLEAR register
		
reset	ldr	r3,=pin	; start with F
floop	str	r5,[r2]	   	; clear the bit -> turn on the LED
		ldr r6,=0 ; r6 is the segment bit number
		ldr r7, [r3]  ; r7 = position in pin lookup table
		; set the appropriate pins
iloop	mov r8, #1
		tst r7, r8, LSL r6
		ldr r8, =segment
		ldrne r8, [r8, r6]
		movne r9, #1
		lslne r8, r9, r8
		strne r8, [r1]
		add r6, #1
		cmp r6, #8
		bne iloop
		
;delay for about a half second
;		ldr	r4,=20000000
;dloop	subs	r4,r4,#1
;		bne	dloop
		ldr r4,=0
dloop	ldr r11,=0x00100000
		ldr r10, [r0]
		; count buttons pressed
iiloop	tst r10, r11
		bne check
		ldr	r12,=9000000
sloop	subs	r12,r12,#1
		bne	sloop
		ldr r11,=0x00100000
pass	tst r10, r11
		addeq r4, #1
		lsl r11, #1
		cmp r11, #0x01000000
		bne pass
		b disp
check	lsl r11, #1
		cmp r11, #0x01000000
		bne iiloop
		cmp r4, #0
		beq	dloop
		

disp	cmp r4, #2
		subhi r3, #1
		addle r3, #1
		
		ldr r9, =pinEnd
		cmp r3, r9
		ldreq r3, =pin
		
		ldr r9, =pinBeg
		cmp r3, r9
		ldreq r3, =pinEnd
		subeq r3, #1
		
		b floop

stop	B	stop

	AREA	lookups, DATA, READONLY
segment	DCB 16, 18, 20, 6, 12, 10, 8, 22
pinBeg  DCB 0
		    ; .GFEDCBA
pin		DCB 2_01110001	;F
		DCB 2_01111001	;E
		DCB 2_01011110	;D
		DCB	2_00111001	;C
		DCB 2_01111100	;B
		DCB 2_01110111	;A
		DCB 2_01100111	;9
		DCB 2_01111111	;8
		DCB 2_00000111 	;7
		DCB 2_01111101	;6
		DCB 2_01101101	;5
		DCB 2_01100110	;4
		DCB 2_01001111	;3
		DCB 2_01011011	;2
		DCB 2_00000110	;1
		DCB 2_00111111	;0
pinEnd	DCB 0
	END
;G -> 08 
;F -> 10
;E -> 12
;D -> 06
;A -> 16
;B -> 18
;C -> 20
;dot -> 22


;F -> A, G, F, E
;E -> A, F, G, E, D
;D -> B, G, C, D, E
;C -> A, F, E, D
;B -> F, G, E, D, C
;A -> A, B, C, G, E, F
;9 -> A, F, B, G, C
;8 -> A, B, C, D, E, F, G
;7 -> A, B, C
;6 -> A, F, G, E, D, C
;5 -> A, F, G, C, D
;4 -> F, G, B, C
;3 -> A, B, G, C, D
;2 -> A, B, G, E, D
;1 -> B, C
;0 -> A, B, C, D, E, F
