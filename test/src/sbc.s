.text
.include "sys.l"

.globl _start
_start:
	mov r1, #3
	movs r1, r1, lsl #31

	sbc r0, r0, #1024
	sbc r0, r0, lsl #31
	sbc r0, r0, asr #1
	sbc r0, r0, lsr #1
	sbc r0, r0, ror #15
	sbc r0, r0, r1
	sbc r0, r0, lsl r1
	sbc r0, r0, asr r1
	sbc r0, r0, lsr r1
	sbc r0, r0, ror r1
	sbc r0, r0, rrx
	bl _print_hex

	sbcs r0, r0, #1
	sbc r0, r0, #1
	bl _print_hex
	b _exit
