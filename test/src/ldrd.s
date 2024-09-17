.data

values:
	.word 0xFFEEDDCC, 0xBBAA9988, 0x77665544, 0x33221100, 0x00112233, 0x44556677, 0x8899AABB, 0xCCDDEEFF, 0x00000000, 0xFFFFFFFF

.text
.include "sys.l"

.globl _start
_start:
	// load literal
	ldr r3, =values + 4
	mov r2, #2

	// Preindex with immediate offset
	ldrd r0, [r3, #+1]
	bl _print_d
	ldrd r0, [r3, #-1]
	bl _print_d

	// Preindex writeback with immediate offset
	ldrd r0, [r3, #+1]!
	bl _print_d
	ldrd r0, [r3, #-1]!
	bl _print_d

	// Preindex with register offset
	ldrd r0, [r3, r2]
	bl _print_d
	ldrd r0, [r3,-r2]
	bl _print_d

	// Preindex writeback with register offset
	ldrd r0, [r3, r2]!
	bl _print_d
	ldrd r0, [r3,-r2]!
	bl _print_d

	// Immediate postindexed
	ldr r3, =values + 4
	ldrd r0, [r3], #1
	bl _print_d
	ldrd r0, [r3], #-1
	bl _print_d

	// Register postindexed
	ldr r3, =values + 4
	ldrd r0, [r3], r2
	bl _print_d
	ldrd r0, [r3],-r2
	bl _print_d

	ldr r1, =values
	ldrd r0, [r1, r2]
	bl _print_d

	ldr r0, =values
	mov r1, #4
	ldrd r2, [r12, r1]
	ldrd r4, [r12, r1]
	ldrd r6, [r12, r1]
	ldrd r8, [r12, r1]
	ldrd r10, [r12, r1]
	bl _print_all_registers

	ldr r0, =values
	mov r1, #4
	ldrd r2, [r12, r1]!
	ldrd r4, [r12, r1]!
	ldrd r6, [r12, r1]!
	ldrd r8, [r12, r1]!
	ldrd r10, [r12, r1]!
	bl _print_all_registers

	ldr r0, =values
	ldrd r2, [r12, #4]
	ldrd r4, [r12, #4]
	ldrd r6, [r12, #4]
	ldrd r8, [r12, #4]
	ldrd r10, [r12, #4]
	bl _print_all_registers

	ldr r0, =values
	mov r1, #4
	ldrd r2, [r12, #4]!
	ldrd r4, [r12, #4]!
	ldrd r6, [r12, #4]!
	ldrd r8, [r12, #4]!
	ldrd r10, [r12, #4]!
	bl _print_all_registers

	b _exit

_print_d:
	push {lr}
	bl _print_hex
	mov r0, r1
	bl _print_hex
	pop {pc}

