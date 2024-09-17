_print_hex:
	push {r0, r1, r2, r7, lr}
	mov r2, #8

	// New line
	mov r1, #10
	strb r1, [sp, #-1]!

	__next_char__:
		and r1, r0, #15

		cmp r1, #9
		addgt r1, r1, #55
		addle r1, r1, #48

		strb r1, [sp, #-1]!

		mov r0, r0, lsr #4
		subs r2, r2, #1
		bne __next_char__

	// Write syscall
	mov r0, #1
	mov r1, sp
	mov r2, #9
	mov r7, #4
	svc #0x00000000

	add sp, sp, #9
	pop {r0, r1, r2, r7, pc}

_print_flags:
	push {r0, lr}
	mrs r0, cpsr
	bl _print_hex
	pop {r0}
	bl _print_hex
	pop {pc}

_print_all_registers:
	push {r0, lr}

	bl _print_hex
	mov r0, r1
	bl _print_hex
	mov r0, r2
	bl _print_hex
	mov r0, r3
	bl _print_hex
	mov r0, r4
	bl _print_hex
	mov r0, r5
	bl _print_hex
	mov r0, r6
	bl _print_hex
	mov r0, r7
	bl _print_hex
	mov r0, r8
	bl _print_hex
	mov r0, r9
	bl _print_hex
	mov r0, r10
	bl _print_hex
	mov r0, r11
	bl _print_hex
	mov r0, r12
	bl _print_hex

	pop {r0, pc}

_exit:
	mov r0, #0
	mov r7, #1
	svc #0x00000000
