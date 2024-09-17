.data
.text
.globl _start

_start:
	mov r0, #65
	push {r0}
	
	mov r0, #1
	mov r1, sp
	mov r2, r0
	mov r7, #64
	svc 0x00000000

	add sp, sp, #4
	
	/* mov r0, #0 */
	/* mov r7, #93 */
	/* svc 0x00000000 */
