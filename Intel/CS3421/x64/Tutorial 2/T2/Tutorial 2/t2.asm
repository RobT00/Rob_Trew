option casemap:none             ; case sensitive

;
; t2.asm
;

.data
	public	g
	g		DWORD	4

.code
public		min                     ; export function name

min:		mov		rax, rcx
			ret

public		p

p:			mov		rax, rcx
			ret

public		gcd

gcd:		mov		rax, rcx
			ret

public		q

q:			mov		rax, rcx
			ret


            end
; EOF    