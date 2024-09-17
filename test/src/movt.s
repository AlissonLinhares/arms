.text
.include "sys.l"

.globl _start
_start:
	movw r0, #65535
	movt r0, #65535
	bl _print_hex

	mvn r0, #0
	movt r0, #0
	bl _print_hex

	movw r0, #1357
	movt r0, #7531
	bl _print_hex

	b _exit
