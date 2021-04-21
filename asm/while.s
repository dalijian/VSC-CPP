	.file	"while.c"
	.text
	.globl	_fun1          
	.def	_fun1;	.scl	2;	.type	32;	.endef
_fun1:
LFB0:
	.cfi_startproc
	pushl	%ebp 			#  把 调用 者 的 栈 帧 底部 地址 保存 起来 
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp		# 把 调用 者 的 栈 帧 顶部 地址，设置 为 本 栈帧 的 底部 
	.cfi_def_cfa_register 5
	jmp	L2					# 
L3:
	addl	$1, 8(%ebp)		# a++
L2:
	cmpl	$9, 8(%ebp)  	# 比较 参数1 和 立即数 9，比较的结果 会 设置 eflags 寄存器 中 的 相关位 
	jle	L3					# 如果 小于 等于 ，则 跳转 L3 ，根据 EFLAGS中 的 某些 位 计算 出来 
	nop						# 
	popl	%ebp			# 否则 保存 参数 1  
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret						# 返回  
	.cfi_endproc
LFE0:
	.ident	"GCC: (MinGW.org GCC-8.2.0-3) 8.2.0"
