	.file	"asm.c"
	.text
	.globl	_static_variable
	.data
	.align 4
_static_variable:
	.long	5
	.text
	.globl	_f
	.def	_f;	.scl	2;	.type	32;	.endef
_f:
LFB0:
	.cfi_startproc
	pushl	%ebp      
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	movl	$1, %esi   
	movl	$10, %edi  
	movl	$110, %ebx 
	movl	$1, _a_very_long_name_to_see_how_long_they_can_be
	movl	%edi, 8(%esp)
	movl	%esi, 4(%esp)
	movl	$10, (%esp) 
	call	_func_ret_int 
	call	_func_ret_double 
	fstpl	-32(%ebp) 
	movl	%ebx, (%esp) 
	call	_func_ret_char_ptr 
	movl	%eax, %ebx 
	nop     
	addl	$44, %esp 
	popl	%ebx 
	.cfi_restore 3
	popl	%esi 
	.cfi_restore 6
	popl	%edi 
	.cfi_restore 7
	popl	%ebp 
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret 
	.cfi_endproc
LFE0:
	.globl	_func_ret_int
	.def	_func_ret_int;	.scl	2;	.type	32;	.endef
_func_ret_int:
LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp 
	.cfi_def_cfa_register 5
	subl	$16, %esp 
	movl	12(%ebp), %eax 
	subl	$6, %eax 
	movl	%eax, -4(%ebp) 
	movl	8(%ebp), %edx 
	movl	12(%ebp), %eax 
	addl	%edx, %eax 
	addl	16(%ebp), %eax 
	leave 
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret 
	.cfi_endproc
LFE1:
	.globl	_func_ret_double 
	.def	_func_ret_double;	.scl	2;	.type	32;	.endef
_func_ret_double:
LFB2:
	.cfi_startproc 
	pushl	%ebp 
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp 
	.cfi_def_cfa_register 5
	fldl	LC1 
	popl	%ebp 
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret 
	.cfi_endproc
LFE2:
	.globl	_func_ret_char_ptr
	.def	_func_ret_char_ptr;	.scl	2;	.type	32;	.endef
_func_ret_char_ptr:
LFB3:
	.cfi_startproc
	pushl	%ebp 
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp 
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax 
	addl	$1, %eax 
	popl	%ebp 
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret 
	.cfi_endproc
LFE3:
	.section .rdata,"dr"
	.align 8
LC1:
	.long	1374389535
	.long	1074339512
	.ident	"GCC: (MinGW.org GCC-8.2.0-3) 8.2.0"
