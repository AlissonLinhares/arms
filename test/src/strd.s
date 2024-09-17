.data

buffer:
	.word 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF

.text
.include "sys.l"

.globl _start
_start:
	bl _init_registers

	ldr r12, =buffer + 4
	mov r11, #2

	// Preindex with immediate offset
	strd r0, [r12, #+1]
	strd r2, [r12, #+1]
	strd r4, [r12, #+1]
	strd r6, [r12, #+1]
	strd r8, [r12, #+1]
	bl _print_and_reset
	strd r0, [r12, #-1]
	strd r2, [r12, #-1]
	strd r4, [r12, #-1]
	strd r6, [r12, #-1]
	strd r8, [r12, #-1]
	bl _print_and_reset

	// Preindex writeback with immediate offset
	strd r0, [r12, #+1]!
	strd r2, [r12, #+1]!
	strd r4, [r12, #+1]!
	strd r6, [r12, #+1]!
	strd r8, [r12, #+1]!
	bl _print_and_reset
	strd r0, [r12, #-1]!
	strd r2, [r12, #-1]!
	strd r4, [r12, #-1]!
	strd r6, [r12, #-1]!
	strd r8, [r12, #-1]!
	bl _print_and_reset

	// Preindex with register offset
	strd r0, [r12, r11]
	strd r2, [r12, r11]
	strd r4, [r12, r11]
	strd r6, [r12, r11]
	strd r8, [r12, r11]
	bl _print_and_reset
	strd r0, [r12, -r11]
	strd r2, [r12, -r11]
	strd r4, [r12, -r11]
	strd r6, [r12, -r11]
	strd r8, [r12, -r11]
	bl _print_and_reset

	// Preindex writeback with register offset
	strd r0, [r12, r11]!
	strd r2, [r12, r11]!
	strd r4, [r12, r11]!
	strd r6, [r12, r11]!
	strd r8, [r12, r11]!
	bl _print_and_reset
	strd r0, [r12, -r11]!
	strd r2, [r12, -r11]!
	strd r4, [r12, -r11]!
	strd r6, [r12, -r11]!
	strd r8, [r12, -r11]!
	bl _print_and_reset

	// Immediate postindexed
	ldr r12, =buffer + 4
	strd r0, [r12], #1
	strd r2, [r12], #1
	strd r4, [r12], #1
	strd r6, [r12], #1
	strd r8, [r12], #1
	bl _print_and_reset
	strd r0, [r12], #-1
	strd r2, [r12], #-1
	strd r4, [r12], #-1
	strd r6, [r12], #-1
	strd r8, [r12], #-1
	bl _print_and_reset

	// Register postindexed
	ldr r12, =buffer + 4
	strd r0, [r12], r11
	strd r2, [r12], r11
	strd r4, [r12], r11
	strd r6, [r12], r11
	strd r8, [r12], r11
	bl _print_and_reset
	strd r0, [r12], -r11
	strd r2, [r12], -r11
	strd r4, [r12], -r11
	strd r6, [r12], -r11
	strd r8, [r12], -r11
	bl _print_and_reset

	b _exit

_init_registers:
	mov r0, #1
	mov r1, #2
	mov r2, #3
	mov r3, #4
	mov r4, #5
	mov r5, #6
	mov r6, #7
	mov r7, #8
	mov r8, #9
	mov r9, #10
	mov r10, #11
	mov pc, lr

_print_and_reset:
	push {r0, r1, r2, lr}
	ldr r1, =buffer
	mov r2, #10

	.loop:
		ldr r0, [r1], #0
		bl _print_hex

		mvn r0, #0
		str r0, [r1], #4
	subs r2, r2, #1
	bne .loop

	bl _init_registers
	pop {r0, r1, r2, lr}
	mov pc, lr
