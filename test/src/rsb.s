.text
.include "sys.l"

.globl _start
_start:
	mov r1, #1
	rsb r0, r1, #1024
	bl _print_hex
	rsb r0, r0, lsl #31
	bl _print_hex
	rsb r0, r0, asr #1
	bl _print_hex
	rsb r0, r0, lsr #1
	bl _print_hex
	rsb r0, r0, ror #15
	bl _print_hex
	rsb r0, r0, rrx
	bl _print_hex
	b _exit
