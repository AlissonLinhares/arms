#ifndef ARCH_H
#define ARCH_H

#include <stdint.h>
#include <debug.h>

#define DEBUG_ENABLE          0
#define SHOW_REGISTERS        0
#define SINGLE_STEP           0
#define SHOW_STATISTICS       0
#define ASSERT_ENABLE         0

#define B0_MASK 0x000000FF
#define B1_MASK 0x0000FF00
#define B2_MASK 0x00FF0000
#define B3_MASK 0xFF000000
#define W0_MASK 0x0000FFFF
#define W1_MASK 0xFFFF0000

#define _B0( reg ) ((uint8_t) ((reg & 0x000000FF)      ))
#define _B1( reg ) ((uint8_t) ((reg & 0x0000FF00) >> 8 ))
#define _B2( reg ) ((uint8_t) ((reg & 0x00FF0000) >> 16))
#define _B3( reg ) ((uint8_t) ((reg & 0xFF000000) >> 24))

#define _LOW( reg ) (reg & 0x0000FFFF)
#define _HIGH( reg ) ((reg & 0xFFFF0000) >> 16)

#define EXTEND( VAR, CSIZE, TSIZE ) ((uint ## TSIZE ## _t)((int ## CSIZE ## _t) (VAR)))
#define UINT64( value ) ((uint64_t)(value))
#define UINT32( value ) ((uint32_t) value)
#define UINT16( value ) ((uint16_t) value)
#define UINT8( value ) ((uint8_t) value)
#define SINT64( value ) ((int64_t)((int32_t)(value)))
#define SINT32( value ) ((int32_t) value)
#define SINT16( value ) ((int16_t) value)
#define SINT8( value ) ((int8_t) value)

#define _LSL( result, value, shift ) \
	result = UINT32(value) << shift

#define _ASR( result, value, shift ) \
	result = SINT32(value) >> shift

#define _LSR( result, value, shift ) \
	result = UINT32(value) >> shift

#define _ROR( result, value, shift ) \
	result = ((UINT32(value) >> shift) | (UINT32(value) << (32 - shift)))

#define _RRX( result, value ) \
	result = ((UINT32(value) >> 1) | _CF << 31)

#define _RRXS( result, value ) \
	bool tmp = value & 1; \
	result = ((UINT32(value) >> 1) | _CF << 31); \
	_CF = tmp;

#define _LSLS( result, value, shift ) \
	_CF = (value >> (32 - shift)) & 1; \
	_LSL( result, value, shift )

#define _ASRS( result, value, shift ) \
	_CF = (value >> (shift - 1)) & 1; \
	_ASR( result, value, shift )

#define _LSRS( result, value, shift ) \
	_CF = (value >> (shift - 1)) & 1; \
	_LSR( result, value, shift )

#define _RORS( result, value, shift ) \
	_CF = (value >> (shift - 1)) & 1; \
	_ROR( result, value, shift )

#define _UPDATE_FLAGS( value ) \
	_ZF = (UINT32(value) == 0); \
	_NF = (SINT32(UINT32(value)) < 0);

#define _UPDATE_FLAGS64( value ) \
	_ZF = (UINT64(value) == 0); \
	_NF = (((int64_t) UINT64(value)) < 0);

#define _LEI( rd, imm ) \
	_LDI( rd, imm ); \
	_ROR( rd, (rd & 0xFF), ((rd >> 7) & 0x1E) )

#define _LEIS( rd, imm ) \
	_LDI( rd, imm ); \
	uint32_t temp = (rd >> 7) & 0x1E; \
	_ROR( rd, (rd & 0xFF), temp ); \
	if ( temp != 0 ) _CF = rd >> 31

register volatile uint32_t _LR  asm("ra");  // x1
register volatile uint32_t _SP  asm("sp");  // x2
register volatile uint32_t _R0  asm("a0");  // x10
register volatile uint32_t _R1  asm("a1");  // x11
register volatile uint32_t _R2  asm("a2");  // x12
register volatile uint32_t _R3  asm("a3");  // x13
register volatile uint32_t _R4  asm("a4");  // x14
register volatile uint32_t _R5  asm("a5");  // x15
register volatile uint32_t _R6  asm("a6");  // x16
register volatile uint32_t _R7  asm("a7");  // x17
register volatile uint32_t _R8  asm("gp");  // x3
register volatile uint32_t _R9  asm("tp");  // x4
register volatile uint32_t _R10 asm("t0");  // x5
register volatile uint32_t _R11 asm("s0");  // x8
register volatile uint32_t _R12 asm("s1");  // x9
register volatile uint32_t _PC  asm("s2");  // x18
register volatile uint32_t _IP  asm("s3");  // x19

register volatile bool _CF  asm("s4"); // x20
register volatile bool _VF  asm("s5"); // x21
register volatile bool _ZF  asm("s6"); // x22
register volatile bool _NF  asm("s7"); // x23
#define _QF _CF
#define _GE _CF

register uint32_t _RN asm("s8");  // x24
register uint32_t _RM asm("s9");  // x25
register uint32_t _RS asm("s10"); // x26
register uint32_t _RD asm("s11"); // x27
#define _RH _RD

#define _RN_IDX 0
#define _RM_IDX 0
#define _RD_IDX 0
#define _RS_IDX 0

#define _SHIFT    0x80001 // param.shift
#define _DISP     0x80002 // param.disp
#define _OFFSET   0x80003 // param.imm12
#define _IMM12    0x80003 // param.imm12
#define _IMM16    0x80004 // param.imm16
#define _REG_LIST 0x80005 // param.rlist
#define _ADDR     0x80006 // param.imm24

#define _LD( rd, addr ) asm volatile ( "lw %0, 0(%1)" : "=r"(rd) : "r"(addr) );
#define _LDB( rd, addr ) asm volatile ( "lbu %0, 0(%1)" : "=r"(rd) : "r"(addr) );
#define _LDH( rd, addr ) asm volatile ( "lhu %0, 0(%1)" : "=r"(rd) : "r"(addr) );
#define _LDBS( rd, addr ) asm volatile ( "lb %0, 0(%1)" : "=r"(rd) : "r"(addr) );
#define _LDHS( rd, addr ) asm volatile ( "lh %0, 0(%1)" : "=r"(rd) : "r"(addr) );
#define _ST( addr, data ) asm volatile ( "sw %1, 0(%0)" : : "r"(addr), "r"(data) );
#define _STB( addr, data ) asm volatile ( "sb %1, 0(%0)" : : "r"(addr), "r"(data) );
#define _STH( addr, data ) asm volatile ( "sh %1, 0(%0)" : : "r"(addr), "r"(data) );
#define _LDI( rd, value )  asm volatile ( "auipc %0, %1" : "=r"(rd) : "i"(value) );
#define _B( target ) asm volatile ( "jalr x0, %0, 0" : : "r"(target) );
#define _BL( target ) asm volatile ( "jalr %0, %1, 0" : "=r"(_LR) : "r"(target) );

#define _END __builtin_unreachable(); }
#define _INSTRUCTION( sign ) \
	void sign () asm(#sign); \
	void sign () { \
	register uint32_t _RT, _RX;

#define _NOP asm volatile("nop")

_INSTRUCTION( _svc )
	asm volatile("ecall");
_END
#endif
