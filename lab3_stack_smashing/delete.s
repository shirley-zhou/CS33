	.file	"delete.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	delete
	.type	delete, @function
delete:
.LFB5:
	.cfi_startproc
#APP
# 6 "delete.c" 1
			movq $0x57, %rax
		movq $0x7fffffffcfd5, %rdi
		syscall
	
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE5:
	.size	delete, .-delete
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.ident	"GCC: (GNU) 5.2.0"
	.section	.note.GNU-stack,"",@progbits
