.data

.text
.include "sys.l"

.globl _start
_start:
	mov lr, #0xFF
	push {lr, pc}
	pop {r0}
	bl _print_hex
	pop {r0}
	bl _print_hex

	bl _push_link
	bl _push_return
	bl _push_label
_return:
	bl _arithmetic_jump
	add pc, pc, #0
	bl _print_hex // should not execute

_jump_zero:
	mov r0, pc
	bl _print_hex
	bl _push_link // Jump zero ( pc = pc + 0 );
	b _exit

_push_link:
	push {lr, pc}
	pop {r1}
	mov r0, r1
	bl _print_hex
	pop {r0}
	bl _print_hex
	mov pc, r1

_push_return:
	push {lr}
	mov r0, lr
	bl _print_hex
	mvn r0, pc
	bl _print_hex
	pop {pc}

_push_label:
	ldr r0,=_return
	push {r0}
	bl _print_hex
	pop {pc}

_arithmetic_jump:
	ldr r0,=_return
	bl _print_hex
	add pc, r0, #4
