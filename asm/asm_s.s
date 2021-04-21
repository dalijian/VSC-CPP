	.file	"asm_s.c"
	.text
	.p2align 4,,15
	.globl	_add_a_and_b
	.def	_add_a_and_b;	.scl	2;	.type	32;	.endef
_add_a_and_b:
LFB0:
	.cfi_startproc
	movl	8(%esp), %eax
	addl	4(%esp), %eax
	ret
	.cfi_endproc
LFE0:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section	.text.startup,"x"
	.p2align 4,,15
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB1:
	.cfi_startproc
	# 函数 调用 的 序曲 ， 设置 栈 指针 
	pushl	%ebp #  把调用者的栈帧底部地址保存起来
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8	
	movl	%esp, %ebp  # 把 调用者 的 栈帧顶部地址，设置为本栈帧的底部 
	.cfi_def_cfa_register 5
	andl	$-16, %esp	
	call	___main
	movl	$5, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE1:
	.ident	"GCC: (MinGW.org GCC-8.2.0-3) 8.2.0"
