.text
.include "sys.l"

.globl _start
_start:
	mov r0, #1
	mov r1, #-2
	mov r2, #3
	mov r3, #1
	mov r4, #1024
	mov r5, #-1
	mov r6, #0

	smlal r0, r1, r2, r4
	bl _print_hex
	mov r0, r1
	bl _print_hex

	smlal r0, r4, r1, r2
	bl _print_hex
	mov r0, r4
	bl _print_hex

	smlal r0, r5, r5, r5
	bl _print_hex
	mov r0, r5
	bl _print_hex

	smlal r0, r6, r6, r3
	bl _print_hex
	mov r0, r6
	bl _print_hex

	b _exit
