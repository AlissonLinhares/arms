.text
.include "sys.l"

.globl _start
_start:
	mov r1, #3
	movs r1, r1, lsl #31

	rsc r0, r0, #1024
	rsc r0, r0, lsl #31
	rsc r0, r0, asr #1
	rsc r0, r0, lsr #1
	rsc r0, r0, ror #15
	rsc r0, r0, r1
	rsc r0, r0, lsl r1
	rsc r0, r0, asr r1
	rsc r0, r0, lsr r1
	rsc r0, r0, ror r1
	rsc r0, r0, rrx
	bl _print_hex

	rscs r0, r0, #1
	rsc r0, r0, #1
	bl _print_hex
	b _exit
