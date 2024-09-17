.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =#0x00112233
	ldr r2, =#0x44556677
	ldr r3, =#0x8899AABB

	pkhbt r0, r1, r2
	bl _print_hex
	pkhbt r0, r2, r1
	bl _print_hex
	pkhbt r0, r3, r1, lsl #1
	bl _print_hex
	pkhbt r0, r3, r1, lsl #2
	bl _print_hex
	pkhbt r0, r3, r1
	bl _print_hex
	pkhbt r0, r3, r3, lsl #3
	bl _print_hex
	pkhbt r0, r3, r3, lsl #4
	bl _print_hex
	pkhbt r0, r1, r3, lsl #5
	bl _print_hex
	pkhbt r0, r1, r3, lsl #0
	bl _print_hex
	pkhbt r0, r1, r1, lsl #31
	bl _print_hex

	pkhtb r0, r1, r2
	bl _print_hex
	pkhtb r0, r2, r1
	bl _print_hex
	pkhtb r0, r3, r1, asr #1
	bl _print_hex
	pkhtb r0, r3, r1, asr #2
	bl _print_hex
	pkhtb r0, r3, r1
	bl _print_hex
	pkhtb r0, r3, r3, asr #3
	bl _print_hex
	pkhtb r0, r3, r3, asr #4
	bl _print_hex
	pkhtb r0, r1, r3, asr #5
	bl _print_hex
	pkhtb r0, r1, r3, asr #0
	bl _print_hex
	pkhtb r0, r1, r1, asr #31
	bl _print_hex
	b _exit
