	.text
	.globl main
	.type main, @function
main:
	pushl %ebp	#ebp é o "frame pointer"
	movl %esp, %ebp 	#rsp é o ponteiro de pilha
	movl $3, %eax
	movl %ebp, %esp
	popl %ebp
	ret
