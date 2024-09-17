.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =#0x11223344
	ldr r2, =#0xAABBCCDD

	uxtab r0, r1, r2
	bl _print_hex
	uxtab r0, r1, r2, ror #8
	bl _print_hex
	uxtab r0, r1, r2, ror #16
	bl _print_hex
	uxtab r0, r1, r3, ror #24
	bl _print_hex

	ldr r1, =#0xAABBCCDD
	ldr r2, =#0x11223344
	uxtab r0, r1, r2
	bl _print_hex
	uxtab r0, r1, r2, ror #8
	bl _print_hex
	uxtab r0, r1, r2, ror #16
	bl _print_hex
	uxtab r0, r1, r2, ror #24
	bl _print_hex

	mov r2, #0
	uxtab r0, r1, r2, ror #8
	bl _print_hex
	uxtab r0, r2, r1, ror #16
	bl _print_hex
	b _exit
