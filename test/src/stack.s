.data

.text
.include "sys.l"

.globl _start
_start:
	mov r0, sp
	push {r0}
	sub r0, r0, sp
	bl _print_hex
	pop {r0}
	sub r0, r0, sp
	bl _print_hex

	mov r0, sp
	push {r0-r14}
	sub r0, r0, sp
	bl _print_hex
	pop {r0-r14}
	sub r0, r0, sp
	bl _print_hex

	b _exit
