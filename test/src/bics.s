.data

a_table:
	.word 0, 1, 0, 1, -1, -1,  1

b_table:
	.word 0, 0, 1, 1, -1,  1, -1

.text
.include "sys.l"

.globl _start
_start:
	mov r5, #7
	mov r6, #1
	ldr r3, =a_table
	ldr r4, =b_table

	_next_value:
		ldr r1, [r3], #4
		ldr r2, [r4], #4

		bics r0, r1, r2
		bl _print_flags
		bics r0, r1, r2, lsl #1
		bl _print_flags
		bics r0, r1, r2, asr #1
		bl _print_flags
		bics r0, r1, r2, lsr #1
		bl _print_flags
		bics r0, r1, r2, ror #1
		bl _print_flags
		bics r0, r2, r1, lsl r6
		bl _print_flags
		bics r0, r2, r1, asr r6
		bl _print_flags
		bics r0, r2, r1, lsr r6
		bl _print_flags
		bics r0, r2, r1, ror r6
		bl _print_flags
		bics r0, r2, r1, rrx
		bl _print_flags

		subs r5, r5, #1
		bne _next_value

	b _exit
