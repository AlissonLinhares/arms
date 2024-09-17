.text
.include "sys.l"

.globl _start
_start:
	mov r1, #7
	clz r0, r1
	bl _print_hex

	mvn r1, #0
	clz r0, r1
	bl _print_hex

	ldr r1, =0x80000000
	clz r0, r1
	bl _print_hex

	ldr r1, =0x10000000
	clz r0, r1
	bl _print_hex

	b _exit
