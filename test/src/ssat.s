.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =#0x11223344

	ssat r0, #1, r1, lsl #7
	bl _print_hex
	ssat r0, #2, r1, asr #1
	bl _print_hex
	ssat r0, #3, r1
	bl _print_hex
	ssat r0, #4, r1, lsl #2
	bl _print_hex
	ssat r0, #5, r1, asr #3
	bl _print_hex
	ssat r0, #6, r1
	bl _print_hex
	ssat r0, #7, r1, lsl #3
	bl _print_hex
	ssat r0, #8, r1, asr #4
	bl _print_hex
	ssat r0, #9, r11
	bl _print_hex
	ssat r0, #10, r1
	bl _print_hex
	ssat r0, #11, r1
	bl _print_hex
	ssat r0, #12, r1
	bl _print_hex
	ssat r0, #13, r1
	bl _print_hex
	ssat r0, #14, r1
	bl _print_hex
	ssat r0, #15, r1
	bl _print_hex
	ssat r0, #16, r1, lsl #4
	bl _print_hex
	ssat r0, #17, r1
	bl _print_hex
	ssat r0, #18, r1
	bl _print_hex
	ssat r0, #19, r1
	bl _print_hex
	ssat r0, #20, r1
	bl _print_hex
	ssat r0, #21, r1
	bl _print_hex
	ssat r0, #22, r1
	bl _print_hex
	ssat r0, #23, r1
	bl _print_hex
	ssat r0, #24, r1
	bl _print_hex
	ssat r0, #25, r1
	bl _print_hex
	ssat r0, #26, r1
	bl _print_hex
	ssat r0, #27, r1
	bl _print_hex
	ssat r0, #28, r1
	bl _print_hex
	ssat r0, #29, r1
	bl _print_hex
	ssat r0, #30, r1, asr #32
	bl _print_hex
	ssat r0, #31, r1
	bl _print_hex
	ssat r0, #32, r1
	bl _print_hex
	b _exit
