.data

values:
	.word 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, _return, _print_all_registers
ptr = .

.text
.include "sys.l"

.globl _start
_start:
	ldr r1, =ptr

	str sp, [r1, #-12]
	ldmdb r1, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc}
_return:

	ldr r1, =ptr
	str r1, [r1, #-12]
	ldmdb r1!, {r2, r4, r5, r6, r7, r8, r9, r10, r11, r12 }
	bl _print_all_registers

	b _exit