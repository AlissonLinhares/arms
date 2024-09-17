.data
string:
	.ascii "0000000000000000000000000000000000000000000000000000000000000000\n"
ptr = .

.text
.include "sys.l"

.globl _start
_start:
	ldr r0,=ptr
	ldr r1,=#0x64636261
	ldr r2,=#0x68676665
	ldr r3,=#0x6c6b6a69
	ldr r4,=#0x706f6e6d
	ldr r5,=#0x74737271
	ldr r6,=#0x78777675
	ldr r7,=#0x42417a79
	ldr r8,=#0x46454443
	ldr r9,=#0x4a494847
	ldr r10,=#0x4e4d4c4b
	ldr r11,=#0x5251504f
	ldr r12,=#0x56555453

	stmdb r0, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}

	mov r0, #1
	ldr r1, =string
	mov r2, #64
	mov r7, #4
	swi #0

	ldr r0,=ptr
	stmdb r0!, {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}
	bl _print_hex

	mov r0, #1
	ldr r1, =string
	mov r2, #64
	mov r7, #4
	swi #0

	b _exit
