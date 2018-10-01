option casemap:none             ; case sensitive

includelib	legacy_stdio_definitions.lib
extrn		printf:near
;
; t2.asm
;

.data
	public	g
	g		QWORD	4

.code
public		min                     ; export function name
; Function to return minimum of 3 numbers
min:		mov		rax, rcx		; v = a
			cmp		rdx, rax		; if (b < v)
			jge		b_ge_v			; jump if b >= v
			mov		rax, rdx		; v = b
b_ge_v:		cmp		r8, rax			; if (c < v)
			jge		c_ge_v			; jump if c >= v
			mov		rax, r8			; v = c
c_ge_v:		ret						; return v

public		p						; export function name
; Function to return mimum of 4 numbers, plus g, using min function
p:			sub		rsp, 32			; allocate shadow space
			mov		[rsp+64], r9	; place r9 (4th argument) in shadow space
			mov		[rsp+56], r8	; place r8 (3rd argument) in shaow space
			mov		r8, rdx			; move rdx (2nd argument) to r8 for use in min
			mov		rdx, rcx		; move rcx (1st argument) to rdx for use in min
			mov		rcx, [g]		; move g (global variable) to rcx for use in min
			call	min				; min(g, i, j) == min(g, <1st>, <2nd>)
			mov		rcx, rax		; rax is result of min(g, i, j), place in rcx for next min call
			mov		rdx, [rsp+56]	; restore 3rd argument from shadow space for next min call
			mov		r8, [rsp+64]	; restore 4th argument from shadow space for next min call
			call	min				; min(min(g, <1st>, <2nd>), <3rd>, <4th>) == min(min(g, i, j), k, l)
			add		rsp, 32			; deallocate shadow space
			ret						; return minimum of all variables in function

public		gcd						; export function name
; Function to return gcd of 2 variables
gcd:		test	rdx, rdx		; if (b == 0)
			jne		b_ne_0			; jump if b != 0
			mov		rax, rcx		; set a for return
			jmp		ret_gcd			; jump to return statement
b_ne_0:		mov		rax, rcx		; move a into rax (for next call)
			mov		rcx, rdx		; move b into rcx (for next call)
			cqo						; sign extend rax (a)
			idiv	rcx				; modulus result of a % b stored in rbx
			call	gcd				; call gcd(b, a % b), with rbx and rcx
ret_gcd:	ret						; return the gcd

q_str		db		"a = %I64d, b = %I64d, c = %I64d, d = %I64d, e = %I64d, sum = %I64d", 0AH, 00H
; string to be printed by q function
public		q						; export function name
; Function using the printf function, with 5 input parameters
q:			sub		rsp, 64			; allocate shadow space
			lea		rax, [rcx + rdx]; rax = <1> + <2>
			add		rax, r8			; rax += <3>
			add		rax, r9			; rax += <4>
			;mov		r10, 64			; set r10 = 64
			;mov		r11, 8			;
			;imul	r11, 5			;
			;add		r10, [r10 + r11];
			;mov		r11, [rsp + r10]; move <5> into r10
			mov		r10, [rsp + 104]; 104 = 64 + (8*5), index for <5>
			add		rax, r10		; rax += <5>
			mov		[rsp+56], rax	; save sum (rax) in shadow space
			mov		[rsp+48], rax	; store sum as printf paramter 7 in shadow space
			mov		[rsp+40], r10	; store <5> as printf parameter 6 in shadow space
			mov		[rsp+32], r9	; store <4> as printf parameter 5 in shadow space
			mov		r9, r8			; store <3> as printf parameter 4 in r9
			mov		r8, rdx			; store <2> as printf paramter 3 in r8
			mov		rdx, rcx		; store <1> as printf parameter 2 in rdx
			lea		rcx, q_str		; store print string as printf parameter 1 in rcx
			call	printf			; printf function call
			add		rsp, 56			; deallocate some shadow space (leaving sum intact)
			pop		rax				; pop sum from stack (remaining shadow space)
			ret						; return the sum

qns_str		db		"qns", 0AH, 00H
; string to be printed by qns function
public		qns						; export function name

qns:		lea		rcx, qns_str	; rax = string to be printed (no shadow space)
			sub		rsp, 32			; allocate shadow space
			call	printf			; call to printf function
			add		rsp, 32			; deallocate shadow space
			xor		rax, rax		; set to return 0
			ret						; return 0

            end
; EOF