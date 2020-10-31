GLOBAL testeo


section .text


testeo:
  push rbp
  mov rbp, rsp

  mov rax, 3
  mov rbx, 4
  mov r9, 1
  mov r8, 1
  mov r15, 3
  mov rsi, 0ffffffh

  int 80h

  mov rsp, rbp
  pop rbp

  ret

section .bss
string resb 5
