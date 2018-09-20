; Definitions  -- references to 'UM' are to the User Manual.

; Timer Stuff -- UM, Table 173

T0	equ	0xE0004000		; Timer 0 Base Address
T1	equ	0xE0008000

IR	equ	0			; Add this to a timer's base address to get actual register address
TCR	equ	4
MCR	equ	0x14
MR0	equ	0x18

TimerCommandReset	equ	2
TimerCommandRun	equ	1
TimerModeResetAndInterrupt	equ	3
TimerResetTimer0Interrupt	equ	1
TimerResetAllInterrupts	equ	0xFF

; VIC Stuff -- UM, Table 41
VIC	equ	0xFFFFF000		; VIC Base Address
IntEnable	equ	0x10
VectAddr	equ	0x30
VectAddr0	equ	0x100
VectCtrl0	equ	0x200

Timer0ChannelNumber	equ	4	; UM, Table 63
Timer0Mask	equ	1<<Timer0ChannelNumber	; UM, Table 63
IRQslot_en	equ	5		; UM, Table 58

IO1DIR	EQU	0xE0028018
IO1SET	EQU	0xE0028014
IO1CLR	EQU	0xE002801C

	AREA	InitialisationAndMain, CODE, READONLY
	IMPORT	main

; (c) Mike Brady, 2014–2016.

	EXPORT	start
start
; initialisation code
	
; Initialise the VIC
	ldr	r0,=VIC			; looking at you, VIC!

	ldr	r1,=irqhan
	str	r1,[r0,#VectAddr0] 	; associate our interrupt handler with Vectored Interrupt 0

	mov	r1,#Timer0ChannelNumber+(1<<IRQslot_en)
	str	r1,[r0,#VectCtrl0] 	; make Timer 0 interrupts the source of Vectored Interrupt 0

	mov	r1,#Timer0Mask
	str	r1,[r0,#IntEnable]	; enable Timer 0 interrupts to be recognised by the VIC

	mov	r1,#0
	str	r1,[r0,#VectAddr]   	; remove any pending interrupt (may not be needed)

; Initialise Timer 0
	ldr	r0,=T0			; looking at you, Timer 0!

	mov	r1,#TimerCommandReset
	str	r1,[r0,#TCR]

	mov	r1,#TimerResetAllInterrupts
	str	r1,[r0,#IR]

	ldr	r1,=(14745600/200)-1	 ; 5 ms = 1/200 second
	str	r1,[r0,#MR0]

	mov	r1,#TimerModeResetAndInterrupt
	str	r1,[r0,#MCR]

	mov	r1,#TimerCommandRun
	str	r1,[r0,#TCR]

;from here, initialisation is finished, so it should be the main body of the main program
	mrs r2, cpsr
	bic r3, r2, #0x1f
	orr r3, #0x10
	msr cpsr_cxsf, r2
wloop	b	wloop  		; branch always
;main program execution will never drop below the statement above.

	AREA	InterruptStuff, CODE, READONLY
irqhan	sub	lr,lr,#4
	stmfd	sp!,{r0-r1,lr}	; the lr will be restored to the pc

;this is the body of the interrupt handler
	ldr r0,=time ;update time, add 5ms
	ldr r1,[r0]
	add r1,#5
	str r1,[r0]
	cmp r1, #5
	ble skip
;here you'd put the unique part of your interrupt handler
;all the other stuff is "housekeeping" to save registers and acknowledge interrupts
	;saving registers
	ldr r1,=curr_th
	ldr r1,[r1]
	cmp r1,#0
	ldreq r0,=thread0_reg
	ldrne r0,=thread1_reg
	ldr r1,[sp]
	str r1,[r0],#4
	ldr r1,[sp, #4]
	str r1,[r0],#4
	stmia r0!, {r2-r12}
	
	mrs r2, cpsr
	orr r3, r2, #0xf
	msr cpsr_cxsf, r3
	mov r4, sp
	mov r5, lr
	msr cpsr_cxsf, r2
	str r4, [r0], #4
	str r5, [r0], #4
	str lr, [r0], #4
	mrs r2, spsr
	str r2, [r0], #4
	
	;loading registers
skip
	ldr r1,=curr_th
	ldr r1,[r1]
	cmp r1,#0
	addeq r1,#1
	subne r1,#1
	ldr r0,=curr_th
	str r1,[r0]
	;
	ldreq r0,=thread1_reg
	ldrne r0,=thread0_reg
	ldr r2, [r0], #4
	ldr r3, [r0], #4
	str r2, [sp]
	str r3, [sp, #4]
	
	add r0, #(thread0_sp-thread0_reg-8)
	mrs r2, cpsr
	orr r3, r2, #0xf
	msr cpsr_cxsf, r3
	ldr sp, [r0], #4
	ldr lr, [r0], #4
	msr cpsr_cxsf, r2
	ldr lr, [r0], #4
	str lr, [sp, #8]
	ldr r4, [r0], #4
	msr spsr_csxf, r4
	
	sub r0, #(thread1_reg-thread0_reg-8)
	ldmia r0!, {r2-r12}
;this is where we stop the timer from making the interrupt request to the VIC
;i.e. we 'acknowledge' the interrupt
	ldr	r0,=T0
	mov	r1,#TimerResetTimer0Interrupt
	str	r1,[r0,#IR]	   	; remove MR0 interrupt request from timer

;here we stop the VIC from making the interrupt request to the CPU:
	ldr	r0,=VIC
	mov	r1,#0
	str	r1,[r0,#VectAddr]	; reset VIC

	ldmfd	sp!,{r0-r1,pc}^	; return from interrupt, restoring pc from lr
				; and also restoring the CPSR

	AREA	Subroutines, CODE, READONLY
lights
	ldr r9,=IO1DIR
	ldr r10,=0x000f0000
	str r10,[r9]
	ldr r9,=IO1SET
	str r10,[r9]
	ldr r10,=IO1CLR
	bx	lr

	AREA Thread0, Code, READONLY ;run at 1Hz flash, P1.16
thread0_begin
		bl lights
thread0_run		
		ldr r4,=0x00010000
		ldr r5,=time
		ldr r5,[r5]
		ldr r6,=((1<<10)-1)
		and r5,r5,r6
		ldr r6,=(1<<9)
		cmp r5,r6
		strge r4,[r10]
		strlo r4,[r9]
	b thread0_run
	
	AREA Thread1, Code, READONLY ;run at 2Hz flash, P1.19
thread1_begin
	bl lights
thread1_run
		ldr r4,=(1<<19)
		ldr r5,=time
		ldr r5,[r5]
		ldr r6,=((1<<9)-1)
		and r5,r5,r6
		ldr r6,=(1<<8)
		cmp r5,r6
		strge r4,[r10]
		strlo r4,[r9]
	b thread1_run
	
	AREA	Stuff, DATA, READWRITE
time			SPACE 4 
curr_th 		SPACE 4
thread0_reg		SPACE 52
thread0_sp		DCD thread0_stack
thread0_lr		SPACE 4
thread0_pc		DCD thread0_begin	
thread0_cpsr	FILL 4, 0x10, 4
thread1_reg		SPACE 52
thread1_sp		DCD thread1_stack
thread1_lr		SPACE 4
thread1_pc		DCD thread1_begin	
thread1_cpsr	FILL 4, 0x10, 4
				SPACE 1024
thread0_stack	
				SPACE 1024
thread1_stack	
	END