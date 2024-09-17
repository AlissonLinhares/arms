.data
.text
.globl _start
_start:

lui	t1,0x41
srli	t1,t1,0xc
andi	a0,t1,255
.word 0x73531b
andi	t1,t1,30
.word 0x655e3b
neg	t1,t1
.word 0x65153b
or	a0,a0,t3
lui	t1,0x4
srli	t1,t1,0xc
.word 0x4061013b
sw	a0,0(sp)
lui	t1,0x1
srli	t1,t1,0xc
andi	a0,t1,255
.word 0x73531b
andi	t1,t1,30
.word 0x655e3b
neg	t1,t1
.word 0x65153b
or	a0,a0,t3
mv	a1,sp
mv	a2,a0
lui	t1,0x40
srli	t1,t1,0xc
andi	a7,t1,255
.word 0x73531b
andi	t1,t1,30
.word 0x68de3b
neg	t1,t1
.word 0x6898bb
or	a7,a7,t3
ecall
lui	t1,0x4
srli	t1,t1,0xc
andi	t3,t1,255
.word 0x73531b
andi	t1,t1,30
.word 0x6e513b
neg	t1,t1
.word 0x6e133b
or	sp,sp,t1
.word 0x21013b
