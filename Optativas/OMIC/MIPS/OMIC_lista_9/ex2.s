# constantes
  .equ FD_STDIN, 0
  .equ FD_STDOUT, 1
  .equ SYSCALL_READ, 0
  .equ SYSCALL_WRITE, 1
  .equ SYSCALL_EXIT, 60

  .equ LOCAL_SIZE, -16
  .equ LIMITE, 15
  .equ POS_PTR, -15

  .text
  .globl __start
  .type __start, @function
__start:
  pushq %rbp
  movq %rsp, %rbp
  addq $LOCAL_SIZE, %rsp

  # read(int fd, void *buf, size_t size);
  # rdi rsi rdx rcx r8 r9
  movl $FD_STDIN, %edi
  leaq POS_PTR(%rbp), %rsi
  movl $LIMITE, %edx
  movq $SYSCALL_READ, %rax
  syscall 

loop:
  cmpq $0, %rax              # compara se numero de caracteres a serem convertidos e 0 
  je print

  cmpb $0, (%rsi)
  je print

  cmpb $97, (%rsi)    # 'a' = 97     #compara tabela ascii 
  jl avanca
  cmpb $122, (%rsi)   # 'z' = 122    
  jg avanca
  addq $-32, (%rsi)  # 'a' - 'A' = 32

  decq %rax
  jmp avanca

avanca:
  addq $1, %rsi
  jmp loop

print:
  # write(int fd, char *buf, size_t len)
  movl $FD_STDOUT, %edi
  leaq POS_PTR(%rbp), %rsi
  movl $LIMITE, %edx
  movq $SYSCALL_WRITE, %rax
  syscall

  movq %rbp, %rsp
  popq %rbp
  movq $SYSCALL_EXIT, %rax
  syscall
