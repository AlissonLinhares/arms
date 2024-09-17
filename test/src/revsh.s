.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =#0xAABBCCDD
	revsh r0, r1
	bl _print_hex

	ldr r1, =#0xEEFF0011
	revsh r0, r1
	bl _print_hex

	ldr r1, =#0x22334455
	revsh r0, r1
	bl _print_hex

	ldr r1, =#0x66778899
	revsh r0, r1
	bl _print_hex

	ldr r1, =#0xFFEEDDCC
	revsh r0, r1
	bl _print_hex

	mov r1, #0
	revsh r0, r1
	bl _print_hex

	ldr r0, =#0x12345678
	revsh r0, r0
	bl _print_hex

	b _exit
