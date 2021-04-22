	.file	"float.c"
	.text
	.p2align 4,,15
	.globl	_fun1
	.def	_fun1;	.scl	2;	.type	32;	.endef
_fun1:4
LFB0:
	.cfi_startproc
	flds	8(%esp)  # 浮点 数 传参 用 XMM 寄存器 
	fadds	4(%esp)   
	fadds	LC0			
	ret
	.cfi_endproc
LFE0:
	.section .rdata,"dr"
	.align 4
LC0:
	.long	1073741824     # float 2 常量 
	.ident	"GCC: (MinGW.org GCC-8.2.0-3) 8.2.0"
