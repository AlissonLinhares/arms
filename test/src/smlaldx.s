.text
.include "sys.l"

.globl _start
_start:
	mov r0, #0
	mov r1, #0
	ldr r2, =0x7FFFFFFF
	ldr r3, =0x00007FFF
	ldr r4, =0xFDCB0000
	ldr r5, =0x80000000
	ldr r6, =0x12345678
	ldr r7, =0x9ABCDEF0
	ldr r8, =0x87654321
	ldr r9, =0x00000000

	smlaldx r0, r1, r2, r3
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlaldx r0, r1, r2, r4
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlaldx r0, r1, r4, r3
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlaldx r0, r1, r5, r4
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlaldx r0, r1, r8, r9
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlaldx r0, r1, r7, r8
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlaldx r0, r1, r7, r9
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlaldx r0, r6, r6, r6
	bl _print_hex
	mov r0, r6
	bl _print_hex

	smlaldx r7, r0, r7, r7
	bl _print_hex
	mov r0, r7
	bl _print_hex

	add r9, r9, #1
	eor r0, r0, r0
	mov r1, r0

	smlaldx r0, r1, r8, r9
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlaldx r0, r1, r9, r8
	bl _print_hex
	mov r0, r1
	bl _print_hex

	b _exit
