.text
.include "sys.l"

.globl _start
_start:
	mov r0, #0
	movw r0, #65535
	bl _print_hex

	mov r0, #65535
	movw r0, #0
	bl _print_hex

	movw r0, #13579
	bl _print_hex

	b _exit
