.686                                ; create 32 bit code
.model flat, C                      ; 32 bit memory model
option casemap:none					; case sensitive

;
; t1.asm
;

.data								;start of data section
		public	g					;export variable g
		g		DWORD	4			;declare global varibale g, initialised to 4


.code								;start of code section


public      min						; make sure function name is exported
; Function to return minimum of 3 integer arguments
; Version 1
min:		push	ebp				; push frame pointer
			mov		ebp, esp		; update frame pointer with stack pointer
			sub		esp, 4			; make room on stack for v (minimum value to be returned)

			mov		eax, [ebp+8]	; set v = a (first argument)
			mov		[ebp-4], eax	; place on stack

			mov		eax, [ebp+12]	; checking b (second argument)
			cmp		eax, [ebp-4]	; if b < v
			jge		b_ge_v			; will jump if b >= v
			mov		eax, [ebp+12]	; b < v -> v = b (second argument)
			mov		[ebp-4], eax	; place on stack

b_ge_v:		mov		eax, [ebp+16]	; checking c (third argument)
			cmp		eax, [ebp-4]	; if c < v
			jge		c_ge_v			; will jump if c >= v
			mov		eax, [ebp+16]	; c < v -> v = c (third argument)
			mov		[ebp-4], eax	; place on stack

c_ge_v:		mov		eax, [ebp-4]	; set v for returning

			mov		esp, ebp		; restore esp (stack pointer) to ebp (frame pointer)
			pop		ebp				; pop (old) frame pointer

			ret						; return

public		p						; make sure function name is exported
; Function to return minimum of 4 integer arguments and global (g), calls min as helper function
; Version 1
p:			push	ebp				; push frame pointer
			mov		ebp, esp		; update frame pointer with stack pointer
			sub		esp, 4			; make room on stack for v (value to be returned)

			push	[ebp+20]		; push l (4th argument)
			push	[ebp+16]		; push k (3rd argument)
			push	[ebp+12]		; push j (2nd argument)
			push	[ebp+8]			; push i (1st argument)
			push	[g]				; push g (global variable) [likely g = 4]
			
			call	min				; call the function min(g, i, j)
			
			add		esp, 12			; add to stack pointer, popping parameters (g, i, j)
			push	eax				; eax holds the result of the first "min" call, place on stack (v)

			call	min				; call min(v, k, l)
			add		esp, 12			; pop from stack (v, k, l)

			mov		esp, ebp		; restore esp (stack pointer) to ebp (frame pointer)
			pop		ebp				; pop (old) frame pointer
			ret						; return

public		gcd						; make sure function name is exported
; Function to return greatest common denominator of 2 integer arguments
;Version 1
gcd:		push	ebp				; push frame pointer
			mov		ebp, esp		; update frame pointer with stack pointer
			sub		esp, 4			; make room on stack for v (value to be returned)

			mov		eax, [ebp+12]	; checking b (second argument)
			cmp		eax, 0			; checking if b is negative (will get absolute)
			jge		positive		; if less than 0, continue, else jump
			neg		eax				; negate, i.e. make positive		
positive:	cmp		eax, 0			; check if b (second argument) is 0
			jne		not_0			; will jump if b > 0
			mov		eax, [ebp+8]	; return a (first argument), as b is 0
			mov		[ebp-4], eax	; place return value on stack
			jmp		fin				; jump to end of function (unconditional)

not_0:		mov		eax, [ebp+8]	; checking a (first argument)
			cdq						; sign extended (eax)
			mov		ebx, [ebp+12]	; move b (second argument) into ebx
			idiv	ebx				; divide eax (a) by ebx (b) (i.e. eax/ebx), result in eax, remainder in edx
			push	edx				; push edx (remainder) onto stack
			push	[ebp+12]		; push 2nd argument onto stack
			call	gcd				; call gcd(b, (a % b))
			mov		[ebp-4], eax	; store result on stack
			add		esp, 8			; pop calling arguments from stack

fin:		mov		eax, [ebp-4]	; set eax for return
			mov		ebx, ebp
			mov		ecx, esp
			sub		ebx, ecx
			mov		esp, ebp		; restore esp (stack pointer) to ebp (frame pointer)
			pop		ebp				; pop (old) frame pointer
			ret						; return

end

; EOF