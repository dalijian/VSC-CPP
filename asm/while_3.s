	.file	"while.c"
	.text
	.globl	_fun1
	.def	_fun1;	.scl	2;	.type	32;	.endef
_fun1:
LFB0:
	.cfi_startproc
	movl	4(%esp), %eax
	cmpl	$9, %eax
	jg	L1
L3:
	addl	$1, %eax
	cmpl	$10, %eax
	jne	L3
L1:
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (MinGW.org GCC-8.2.0-3) 8.2.0"
