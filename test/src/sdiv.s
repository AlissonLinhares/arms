.data

a_table:
	.word 0, 1, -1, -1,  1, 3, 9, -3, -4, 8

b_table:
	.word 1, 1, -1,  1, -1, 9, 3, -2, 5, 4

.text
.include "sys.l"

.globl _start
_start:
	mov r5, #10
	mov r6, #1
	ldr r3, =a_table
	ldr r4, =b_table

	_next_value:
		ldr r1, [r3], #1
		ldr r2, [r4], #1

		sdiv r0, r1, r2
		bl _print_hex

		subs r5, r5, #1
		bne _next_value

	mvn r1, #0
	mov r2, #32

	.loop:
		sdiv r0, r1, r2
		bl _print_hex
		sdiv r0, r2, r1
		bl _print_hex
		lsr r1, #1
	subs r2, r2, #1
	bne .loop
	b _exit
