.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =#0xAABBCCDD

	sxth r0, r1
	bl _print_hex
	sxth r0, r1, ror #8
	bl _print_hex
	sxth r0, r1, ror #16
	bl _print_hex
	sxth r0, r1, ror #24
	bl _print_hex

	ldr r1, =#0x11223345
	sxth r0, r1
	bl _print_hex
	sxth r0, r1, ror #8
	bl _print_hex
	sxth r0, r1, ror #16
	bl _print_hex
	sxth r0, r1, ror #24
	bl _print_hex
	b _exit
