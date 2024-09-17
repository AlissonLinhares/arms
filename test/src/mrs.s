.text
.include "sys.l"

.globl _start
_start:
	mvn r1, #0
	mov r2, #16
	and r1, r1, r1, lsr #4

	msr cpsr_f, #0xF0000000
	mrs r0, cpsr
	bl _print_hex

	_next_value:
		orr r3, r1, r2, lsl #28

		msr cpsr_f, r3

		// testing cpsr_f only
		mrs r0, cpsr
		lsr r0, #28
		bl _print_hex

		subs r2, r2, #1
		bne _next_value
	b _exit
