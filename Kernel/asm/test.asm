GLOBAL testeo


section .text


testeo:
  push rbp
  mov rbp, rsp

  xor rax, rax
  mov rsi, string
  mov rdx, 4

  int 80h

  mov rsp, rbp
  pop rbp

  ret

section .bss
string resb 5
