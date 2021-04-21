	.file	"asm_simple.c"
	.text
	.p2align 4,,15
	.globl	_fun1
	.def	_fun1;	.scl	2;	.type	32;	.endef
_fun1:
LFB15:
	.cfi_startproc
	movl	8(%esp), %eax  	# 将 %esp 寄存器 + 8 ， 加载到 %eax 
	addl	4(%esp), %eax	# 将 %esp 寄存器 +4 + %eax 赋值给 %eax 寄存器 
	addl	$10, %eax		# 将 10 + 到 %eax 寄存器 
	ret						# 弹出 返回 地址 
	.cfi_endproc
LFE15:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "fun1:%d\12\0"
	.section	.text.startup,"x"
	.p2align 4,,15
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB16:
	.cfi_startproc
	pushl	%ebp  				# %ebp寄存器 由 被调用者负责保护， 把调用者的栈帧底部地址保存起来 
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp			# 将%esp寄存器 的 值 移动到 %ebp 中 ,恢复 %ebp的地址， 调用者的栈帧顶部地址，设置为本栈帧的底部
	.cfi_def_cfa_register 5
	andl	$-16, %esp			# 将 本 栈帧 扩展 16 字节 
	subl	$16, %esp			# 扩展 栈  扩展 16 字节 
	call	___main				# 调用 __main 主函数 
	movl	$13, 4(%esp)		# 变量 c 赋值 
	movl	$LC0, (%esp)		# 
	call	_printf				# 调用 _printf 函数 
	xorl	%eax, %eax			# 异或 %eax,%eax 
	leave						# 函数 结束 
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret							# 弹出返回地址 
	.cfi_endproc
LFE16:
	.ident	"GCC: (MinGW.org GCC-8.2.0-3) 8.2.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
