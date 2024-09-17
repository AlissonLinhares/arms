.text
.include "sys.l"

.globl _start
_start:
	mvn r1, #0
	mov r2, #16
	and r1, r1, r1, lsr #4

	_next_value:
		orr r0, r1, r2, lsl #28
		msr cpsr_f, r0
		bl _print_flags

		subs r2, r2, #1
		bne _next_value

	msr cpsr_f, #0x00000000
	bl _print_flags
	msr cpsr_f, #0x10000000
	bl _print_flags
	msr cpsr_f, #0x20000000
	bl _print_flags
	msr cpsr_f, #0x30000000
	bl _print_flags
	msr cpsr_f, #0x40000000
	bl _print_flags
	msr cpsr_f, #0x50000000
	bl _print_flags
	msr cpsr_f, #0x60000000
	bl _print_flags
	msr cpsr_f, #0x70000000
	bl _print_flags
	msr cpsr_f, #0x80000000
	bl _print_flags
	msr cpsr_f, #0x90000000
	bl _print_flags
	msr cpsr_f, #0xA0000000
	bl _print_flags
	msr cpsr_f, #0xB0000000
	bl _print_flags
	msr cpsr_f, #0xC0000000
	bl _print_flags
	msr cpsr_f, #0xD0000000
	bl _print_flags
	msr cpsr_f, #0xE0000000
	bl _print_flags
	msr cpsr_f, #0xF0000000
	bl _print_flags
	b _exit
