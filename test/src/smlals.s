.data

a_table:
	.word 1, 0, 1, -1, -1,  1, 857, 0xFFFFFFFE, 0

b_table:
	.word 0, 1, 1, -1,  1, -1, 997, 2, 0

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

		smlals r0, r1, r2, r5
		bl _print_flags

		subs r5, r5, #1
		bne _next_value

	b _exit
