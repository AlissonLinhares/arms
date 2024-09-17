.text
.include "sys.l"

.globl _start
_start:
	mov r0, #1
	mov r1, r0

	bl _print_hex
	mov r0, r0, lsl #31
	bl _print_hex
	mov r0, r0, asr #1
	bl _print_hex
	mov r0, r0, lsr #1
	bl _print_hex
	mov r0, r0, ror #15
	bl _print_hex
	mov r0, r0, lsl r1
	bl _print_hex
	mov r0, r0, asr r1
	bl _print_hex
	mov r0, r0, lsr r1
	bl _print_hex
	mov r0, r0, ror r1
	bl _print_hex
	mov r0, pc, lsl r1
	bl _print_hex
	mov r0, pc, asr r1
	bl _print_hex
	mov r0, pc, lsr r1
	bl _print_hex
	mov r0, pc, ror r1
	bl _print_hex
	mov r0, pc, rrx
	bl _print_hex

	b _exit
