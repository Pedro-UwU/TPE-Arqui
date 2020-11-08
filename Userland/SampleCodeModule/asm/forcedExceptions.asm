GLOBAL forceDivZero

section .text

forceDivZero:
push rbp
mov rbp, rsp

xor rdx, rdx
xor rax, rax
div rdx

mov rsp, rbp
pop rbp
ret
