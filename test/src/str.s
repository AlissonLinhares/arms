.data

buffer:
	.word 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF

.text
.include "sys.l"

.globl _start
_start:
	// load literal
	ldr r0, =#0xEDCBA987
	ldr r1, =buffer + 4
	mov r2, #2

	// Preindex with immediate offset
	str r0, [r1, #+1]
	bl _print_and_reset
	str r0, [r1, #-1]
	bl _print_and_reset

	// Preindex writeback with immediate offset
	str r0, [r1, #+1]!
	bl _print_and_reset
	str r0, [r1, #-1]!
	bl _print_and_reset

	// Preindex with register offset
	str r0, [r1, r2]
	bl _print_and_reset
	str r0, [r1,-r2]
	bl _print_and_reset

	// Preindex writeback with register offset
	str r0, [r1, r2]!
	bl _print_and_reset
	str r0, [r1,-r2]!
	bl _print_and_reset

	// Preindex with scaled register offset
	ldr r1, =buffer + 4
	str r0, [r1, r2, lsl #1]
	bl _print_and_reset
	str r0, [r1,-r2, lsl #1]
	bl _print_and_reset

	ldr r1, =buffer + 4
	str r0, [r1, r2, lsr #1]
	bl _print_and_reset
	str r0, [r1,-r2, lsr #1]
	bl _print_and_reset

	ldr r1, =buffer + 4
	str r0, [r1, r2, asr #1]
	bl _print_and_reset
	str r0, [r1,-r2, asr #1]
	bl _print_and_reset

	ldr r1, =buffer + 4
	str r0, [r1, r2, ror #1]
	bl _print_and_reset
	str r0, [r1,-r2, ror #1]
	bl _print_and_reset

	// Preindex writeback with scaled register offset
	ldr r1, =buffer + 4
	str r0, [r1, r2, lsl #1]!
	bl _print_and_reset
	str r0, [r1,-r2, lsl #1]!
	bl _print_and_reset

	ldr r1, =buffer + 4
	str r0, [r1, r2, lsr #1]!
	bl _print_and_reset
	str r0, [r1,-r2, lsr #1]!
	bl _print_and_reset

	ldr r1, =buffer + 4
	str r0, [r1, r2, asr #1]!
	bl _print_and_reset
	str r0, [r1,-r2, asr #1]!
	bl _print_and_reset

	ldr r1, =buffer + 4
	str r0, [r1, r2, ror #1]!
	bl _print_and_reset
	str r0, [r1,-r2, ror #1]!
	bl _print_and_reset

	// Immediate postindexed
	ldr r1, =buffer + 4
	str r0, [r1], #1
	bl _print_and_reset
	str r0, [r1], #-1
	bl _print_and_reset

	// Register postindexed
	ldr r1, =buffer + 4
	str r0, [r1], r2
	bl _print_and_reset
	str r0, [r1],-r2
	bl _print_and_reset

	// Scaled registers postindexed
	ldr r1, =buffer + 4
	str r0, [r1], r2, lsl #1
	bl _print_and_reset
	str r0, [r1], r2, lsr #1
	bl _print_and_reset
	str r0, [r1], r2, asr #1
	bl _print_and_reset
	str r0, [r1], r2, ror #1
	bl _print_and_reset
	str r0, [r1],-r2, lsl #1
	bl _print_and_reset
	str r0, [r1],-r2, lsr #1
	bl _print_and_reset
	str r0, [r1],-r2, asr #1
	bl _print_and_reset
	str r0, [r1],-r2, ror #1
	bl _print_and_reset

	b _exit

_print_and_reset:
	push {r0, r1, r2, lr}
	ldr r1, =buffer
	mov r2, #10

	loop:
		ldr r0, [r1], #0
		bl _print_hex

		mvn r0, #0
		str r0, [r1], #4
	subs r2, r2, #1
	bne loop
	pop {r0, r1, r2, lr}
	mov pc, lr
