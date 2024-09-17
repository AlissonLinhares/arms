.text
.include "sys.l"

.globl _start
_start:
	mov r1, #2
	mov r2, #3
	mov r3, #1
	mvn r4, #0
	mov r5, #-3

	mla r0, r1, r2, r5
	bl _print_hex
	mla r0, r1, r3, r5
	bl _print_hex
	mla r0, r2, r3, r5
	bl _print_hex

	mla r0, r1, r4, r5
	bl _print_hex
	mla r0, r2, r4, r5
	bl _print_hex
	mla r0, r3, r4, r5
	bl _print_hex

	mla r0, r1, r5, r3
	bl _print_hex
	mla r0, r2, r5, r3
	bl _print_hex
	mla r0, r3, r5, r3
	bl _print_hex
	mla r0, r4, r5, r3
	bl _print_hex
	mla r0, r5, r5, r3
	bl _print_hex

	mla r0, r0, r0, r3
	bl _print_hex

	b _exit
