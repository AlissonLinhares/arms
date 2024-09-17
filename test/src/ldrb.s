.data

values:
	.word 0xFFEEDDCC, 0xBBAA9988, 0x77665544, 0x33221100, 0x00112233, 0x44556677, 0x8899AABB, 0xCCDDEEFF, 0x00000000, 0xFFFFFFFF

.text
.include "sys.l"

.globl _start
_start:
	// load literal
	ldr r1, =values + 4
	mov r2, #2

	// Preindex with immediate offset
	ldrb r0, [r1, #+1]
	bl _print_hex
	ldrb r0, [r1, #-1]
	bl _print_hex

	// Preindex writeback with immediate offset
	ldrb r0, [r1, #+1]!
	bl _print_hex
	ldrb r0, [r1, #-1]!
	bl _print_hex

	// Preindex with register offset
	ldrb r0, [r1, r2]
	bl _print_hex
	ldrb r0, [r1,-r2]
	bl _print_hex

	// Preindex writeback with register offset
	ldrb r0, [r1, r2]!
	bl _print_hex
	ldrb r0, [r1,-r2]!
	bl _print_hex

	// Preindex with scaled register offset
	ldr r1, =values + 4
	ldrb r0, [r1, r2, LSL #1]
	bl _print_hex
	ldrb r0, [r1,-r2, LSL #1]
	bl _print_hex

	ldr r1, =values + 4
	ldrb r0, [r1, r2, LSR #1]
	bl _print_hex
	ldrb r0, [r1,-r2, LSR #1]
	bl _print_hex

	ldr r1, =values + 4
	ldrb r0, [r1, r2, ASR #1]
	bl _print_hex
	ldrb r0, [r1,-r2, ASR #1]
	bl _print_hex

	ldr r1, =values + 4
	ldrb r0, [r1, r2, ROR #1]
	bl _print_hex
	ldrb r0, [r1,-r2, ROR #1]
	bl _print_hex

	// Preindex writeback with scaled register offset
	ldr r1, =values + 4
	ldrb r0, [r1, r2, LSL #1]!
	bl _print_hex
	ldrb r0, [r1,-r2, LSL #1]!
	bl _print_hex

	ldr r1, =values + 4
	ldrb r0, [r1, r2, LSR #1]!
	bl _print_hex
	ldrb r0, [r1,-r2, LSR #1]!
	bl _print_hex

	ldr r1, =values + 4
	ldrb r0, [r1, r2, ASR #1]!
	bl _print_hex
	ldrb r0, [r1,-r2, ASR #1]!
	bl _print_hex

	ldr r1, =values + 4
	ldrb r0, [r1, r2, ROR #1]!
	bl _print_hex
	ldrb r0, [r1,-r2, ROR #1]!
	bl _print_hex

	// Immediate postindexed
	ldr r1, =values + 4
	ldrb r0, [r1], #1
	bl _print_hex
	ldrb r0, [r1], #-1
	bl _print_hex

	// Register postindexed
	ldr r1, =values + 4
	ldrb r0, [r1], r2
	bl _print_hex
	ldrb r0, [r1],-r2
	bl _print_hex

	// Scaled registers postindexed
	ldr r1, =values + 4
	ldrb r0, [r1], r2, LSL #1
	bl _print_hex
	ldrb r0, [r1], r2, LSR #1
	bl _print_hex
	ldrb r0, [r1], r2, ASR #1
	bl _print_hex
	ldrb r0, [r1], r2, ROR #1
	bl _print_hex
	ldrb r0, [r1],-r2, LSL #1
	bl _print_hex
	ldrb r0, [r1],-r2, LSR #1
	bl _print_hex
	ldrb r0, [r1],-r2, ASR #1
	bl _print_hex
	ldrb r0, [r1],-r2, ROR #1
	bl _print_hex

	b _exit
