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
	ldrsh r0, [r1, #+1]
	bl _print_hex
	ldrsh r0, [r1, #-1]
	bl _print_hex

	// Preindex writeback with immediate offset
	ldrsh r0, [r1, #+1]!
	bl _print_hex
	ldrsh r0, [r1, #-1]!
	bl _print_hex

	// Preindex with register offset
	ldrsh r0, [r1, r2]
	bl _print_hex
	ldrsh r0, [r1,-r2]
	bl _print_hex

	// Preindex writeback with register offset
	ldrsh r0, [r1, r2]!
	bl _print_hex
	ldrsh r0, [r1,-r2]!
	bl _print_hex

	// Immediate postindexed
	ldr r1, =values + 4
	ldrsh r0, [r1], #1
	bl _print_hex
	ldrsh r0, [r1], #-1
	bl _print_hex

	// Register postindexed
	ldr r1, =values + 4
	ldrsh r0, [r1], r2
	bl _print_hex
	ldrsh r0, [r1],-r2
	bl _print_hex

	ldrsh r0, =values
	bl _print_hex

	b _exit
