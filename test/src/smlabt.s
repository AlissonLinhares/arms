.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =0x0000FFFF
	ldr r2, =0x7FFFFFFF
	ldr r3, =0x00007FFF
	ldr r4, =0x80000000
	ldr r5, =0x0000FDCB
	ldr r6, =0x12345678
	ldr r7, =0x9ABCDEF0
	ldr r8, =0x87654321
	ldr r9, =0x00000003

	smlabt r0, r1, r2, r9
	bl _print_flags
	smlabt r0, r2, r3, r9
	bl _print_flags
	smlabt r0, r1, r3, r9
	bl _print_flags

	smlabt r0, r4, r4, r9
	bl _print_flags
	smlabt r0, r4, r4, r4
	bl _print_flags
	smlabt r0, r0, r0, r0
	bl _print_flags

	smlabt r0, r5, r6, r9
	bl _print_flags
	smlabt r0, r5, r5, r9
	bl _print_flags

	smlabt r0, r7, r9, r3
	bl _print_flags
	smlabt r0, r8, r7, r0
	bl _print_flags

	smlabt r0, r1, r1, r2
	bl _print_flags

	smlabt r0, r8, r9, r5
	bl _print_flags
	smlabt r0, r9, r9, r9
	bl _print_flags

	eor r1, r1, r1
	smlabt r0, r5, r1, r6
	bl _print_flags
	smlabt r0, r1, r5, r6
	bl _print_flags
	smlabt r0, r1, r1, r6
	bl _print_flags
	smlabt r0, r6, r1, r9
	bl _print_flags
	smlabt r0, r2, r2, r1
	bl _print_flags

	smlabt r0, r1, r2, r4
	bl _print_flags

	b _exit
