.data

a_table:
	.word 0, 1, 0, 1, -1, -1,  1, 857, 0xFFFFFFFE

b_table:
	.word 0, 0, 1, 1, -1,  1, -1, 997, 2

.text
.include "sys.l"

.globl _start
_start:
	mov r5, #9
	mov r6, #1
	ldr r3, =a_table
	ldr r4, =b_table

	_next_value:
		ldr r1, [r3], #4
		ldr r2, [r4], #4

		muls r0, r1, r2
		bl _print_flags

		subs r5, r5, #1
		bne _next_value

	b _exit
