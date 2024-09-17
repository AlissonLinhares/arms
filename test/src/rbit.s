.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =#0x12345678
	rbit r0, r1
	bl _print_hex

	ldr r1, =#0x9ABCDEF0
	rbit r0, r1
	bl _print_hex

	ldr r1, =#0xFFFFFFFF
	rbit r0, r1
	bl _print_hex

	ldr r1, =#0x00000000
	rbit r0, r1
	bl _print_hex

	ldr r0, =#0xABCD0000
	rbit r0, r0
	bl _print_hex

	b _exit
