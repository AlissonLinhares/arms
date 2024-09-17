.text
.include "sys.l"

.globl _start
_start:
	eor r0, r0, r0
	adr r0, _start
	bl _print_hex
	adr r0, _l0
	bl _print_hex
_l0:
	adr r0, _l0
	bl _print_hex
	adr r0, _exit
	bl _print_hex
	adr r0, _print_hex
	bl _print_hex
	b _exit
