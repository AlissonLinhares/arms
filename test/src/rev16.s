.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =#0xAABBCCDD
	rev16 r0, r1
	bl _print_hex

	ldr r1, =#0xEEFF0011
	rev16 r0, r1
	bl _print_hex

	ldr r1, =#0x22334455
	rev16 r0, r1
	bl _print_hex

	ldr r1, =#0x66778899
	rev16 r0, r1
	bl _print_hex

	ldr r1, =#0xFFEEDDCC
	rev16 r0, r1
	bl _print_hex

	mov r1, #0
	rev16 r0, r1
	bl _print_hex
	b _exit
