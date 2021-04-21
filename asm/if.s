	.file	"if.c"
	.text
	.globl	_fun1
	.def	_fun1;	.scl	2;	.type	32;	.endef
_fun1:
LFB0:
	.cfi_startproc
	pushl	%ebp 			
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	cmpl	$10, 8(%ebp)   	# 将 参数 与 10 比较 
	jle	L2					# 小于 等于 则 跳转 
	movl	$4, %eax       	# 否则就 给 a 赋值 为 4 
	jmp	L3
L2:
	movl	$8, %eax		# 将 a 赋值 为 8 
L3:
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (MinGW.org GCC-8.2.0-3) 8.2.0"
