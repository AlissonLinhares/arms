.text
.include "sys.l"

.globl _start
_start:
	mov r1, #1
	orr r0, pc, pc
	bl _print_hex
	orr r0, pc, #1024
	bl _print_hex
	orr r0, pc, pc, lsl #1
	bl _print_hex
	orr r0, pc, pc, lsr #1
	bl _print_hex
	orr r0, pc, pc, lsr #1
	bl _print_hex
	orr r0, pc, pc, ror #1
	bl _print_hex
	orr r0, pc, pc, lsl r1
	bl _print_hex
	orr r0, pc, pc, asr r1
	bl _print_hex
	orr r0, pc, pc, lsr r1
	bl _print_hex
	orr r0, pc, pc, ror r1
	bl _print_hex
	orr r0, pc, pc, rrx
	bl _print_hex

	b _exit
