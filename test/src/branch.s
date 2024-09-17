.text
.include "sys.l"

.globl _start
_start:
	mov r0, #0
	bl _print_hex

	ldr r0,=_bl_addr
	blx r0
	b _exit

_bl_addr:
	mov r0, lr
	bl _print_hex
	bx r0
