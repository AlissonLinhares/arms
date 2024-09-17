.text
.include "sys.l"

.globl _start
_start:
	mov r1, #1
	mvn r0, #1
	bl _print_hex
	mvn r0, r1
	bl _print_hex
	mvn r0, r0, lsl #31
	bl _print_hex
	mvn r0, r0, asr #1
	bl _print_hex
	mvn r0, r0, lsr #1
	bl _print_hex
	mvn r0, r0, ror #15
	bl _print_hex
	mvn r0, r0, lsl r1
	bl _print_hex
	mvn r0, r0, asr r1
	bl _print_hex
	mvn r0, r0, lsr r1
	bl _print_hex
	mvn r0, r0, ror r1
	bl _print_hex
	mvn r0, r0, rrx
	bl _print_hex

	b _exit
