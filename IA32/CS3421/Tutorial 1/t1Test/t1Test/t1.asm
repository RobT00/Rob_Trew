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

public		p						; make sure function name is exported
; Function to return minimum of 4 integer arguments and global (g), calls min as helper function

public		gcd						; make sure function name is exported
; Function to return greatest common denominator of 2 integer arguments

end

; EOF