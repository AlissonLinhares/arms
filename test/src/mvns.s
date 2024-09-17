.text
.include "sys.l"

.globl _start
_start:
	mov r1, #-8
	mov r2, #5

	mvns r0, r1
	bl _print_flags
	mvns r0, r1, lsl #31
	bl _print_flags
	mvns r0, r1, asr #8
	bl _print_flags
	mvns r0, r1, lsr #8
	bl _print_flags
	mvns r0, r1, ror #8
	bl _print_flags
	mvns r0, r1, lsl r2
	bl _print_flags
	mvns r0, r1, asr r2
	bl _print_flags
	mvns r0, r1, lsr r2
	bl _print_flags
	mvns r0, r1, ror r2
	bl _print_flags
	mvns r0, r1, rrx
	bl _print_flags

	mvns r2, #0
	bl _print_flags
	mvns r2, #0x000000FF
	bl _print_flags
	mvns r2, #0x0000FF00
	bl _print_flags
	mvns r2, #0x00FF0000
	bl _print_flags
	mvns r2, #0xFF000000
	bl _print_flags
	mvns r2, #0xF000000F
	bl _print_flags

	b _exit
