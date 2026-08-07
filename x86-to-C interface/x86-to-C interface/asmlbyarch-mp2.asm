section .data
	mps dq 0.27777778


section .text
	default rel
	bits 64

	global lf_to_int, calc_accel

lf_to_int:
	; Round double in xmm0 to nearest int in rax

	roundsd xmm0, xmm0, 0x00 ; Round to nearest 
	cvttsd2si rax, xmm0		; xmm0 in param
	ret						; return with value in rax

v_to_mps:
	; Convert kmph to mps
	mulsd xmm1, [mps]	; multiply xmm7 kmph by mps constant
	ret

calc_accel:
	; (Vf - Vi)
	subsd xmm1, xmm0 ; xmm1 = xmm1 - xmm0

	; (Vf - Vi) / t
	call v_to_mps ; convert xmm1 to m/s
	divsd xmm1, xmm2 ; divide xmm1 (param 2 - param 1) by xmm2 (param 3) | output in xmm1

	; move result to xmm0 for return
	movsd xmm0, xmm1
	ret