.text
.include "sys.l"

.globl _start
_start:
	mov r0, #0
	bl _fib
	mov r0, #1
	bl _fib
	mov r0, #2
	bl _fib
	mov r0, #3
	bl _fib
	mov r0, #4
	bl _fib
	mov r0, #5
	bl _fib
	mov r0, #10
	bl _fib
	mov r0, #20
	bl _fib
	b _exit

_fib:
	str lr, [sp], #-4
	mov r1, #0
	mov r2, #1

	__loop__:
		mov r3, r2
		add r2, r1, r2
		mov r1, r3

		subs r0, r0, #1
		bgt __loop__

	mov r0, r2
	bl _print_hex

	ldr pc, [sp, #4]!
