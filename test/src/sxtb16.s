.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =#0x11223344

	sxtb16 r0, r1
	bl _print_hex
	sxtb16 r0, r1, ror #8
	bl _print_hex
	sxtb16 r0, r1, ror #16
	bl _print_hex
	sxtb16 r0, r1, ror #24
	bl _print_hex

	ldr r1, =#0xAABBCCDD
	sxtb16 r0, r1
	bl _print_hex
	sxtb16 r0, r1, ror #8
	bl _print_hex
	sxtb16 r0, r1, ror #16
	bl _print_hex
	sxtb16 r0, r1, ror #24
	bl _print_hex

	ldr r1, =#0x00112233
	sxtb16 r0, r1
	bl _print_hex
	sxtb16 r0, r1, ror #8
	bl _print_hex
	sxtb16 r0, r1, ror #16
	bl _print_hex
	sxtb16 r0, r1, ror #24
	bl _print_hex
	b _exit
