.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =0x00000001
	ldr r2, =0x00000073
	ldr r3, =0x00007FFF
	ldr r4, =0xFDCB0000
	ldr r5, =0x12345678
	ldr r6, =0x00000000
	ldr r7, =0x9ABCDEF0

	smmul r0, r1, r2
	bl _print_hex
	smmul r0, r2, r3
	bl _print_hex
	smmul r0, r3, r4
	bl _print_hex
	smmul r0, r4, r5
	bl _print_hex
	smmul r0, r5, r6
	bl _print_hex
	smmul r0, r2, r4
	bl _print_hex
	smmul r0, r2, r5
	bl _print_hex
	smmul r0, r0, r0
	bl _print_hex
	smmul r0, r4, r4
	bl _print_hex
	smmul r0, r7, r4
	bl _print_hex
	smmul r0, r7, r7
	bl _print_hex
	smmul r0, r7, r5
	bl _print_hex

	b _exit
