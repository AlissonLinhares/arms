.data
.text

.globl _start

.include "sys.l"

_start:
	mov %r0, $0
	bl _print_hex
	mov %r0, $9
	bl _print_hex
	mov %r0, $10
	bl _print_hex
	mov %r0, $16
	bl _print_hex
	mov %r0, $255
	bl _print_hex
	mov %r0, $4294967295
	bl _print_hex
	b _exit
