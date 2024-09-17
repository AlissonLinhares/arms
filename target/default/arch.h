#include <stdint.h>
#include <debug.h>
#include <operations.h>

#ifndef ARCH_H
#define ARCH_H

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

#define _LEI( rd, rt ) \
	_ROR( rd, (rt & 0xFF), ((rt >> 7) & 0x1E) )

#define _LEIS( rd, rt ) \
	uint32_t temp = (rt >> 7) & 0x1E; \
	_ROR( rd, (rt & 0xFF), temp ); \
	if ( temp != 0 ) _CF = rd >> 31

#define _R0 Registers::getInstance()[R0]
#define _R1 Registers::getInstance()[R1]
#define _R2 Registers::getInstance()[R2]
#define _R3 Registers::getInstance()[R3]
#define _R4 Registers::getInstance()[R4]
#define _R5 Registers::getInstance()[R5]
#define _R6 Registers::getInstance()[R6]
#define _R7 Registers::getInstance()[R7]
#define _R8 Registers::getInstance()[R8]
#define _R9 Registers::getInstance()[R9]
#define _R10 Registers::getInstance()[R10]
#define _R11 Registers::getInstance()[R11]
#define _R12 Registers::getInstance()[R12]
#define _SP Registers::getInstance()[SP]
#define _LR Registers::getInstance()[LR]
#define _PC Registers::getInstance()[PC]
#define _IP Registers::getInstance()[IP]

#define _RN_IDX param.rn
#define _RM_IDX param.rm
#define _RD_IDX param.rd
#define _RS_IDX param.rs

#define _OFFSET param.imm12
#define _IMM12 param.imm12
#define _IMM16 param.imm16
#define _ADDR param.imm24
#define _REG_LIST param.rlist
#define _SHIFT param.shift
#define _DISP param.disp

#define _RN Registers::getInstance()[_RN_IDX]
#define _RM Registers::getInstance()[_RM_IDX]
#define _RD Registers::getInstance()[_RD_IDX == 15 ? PC + 1 : _RD_IDX]
#define _RS Registers::getInstance()[_RS_IDX]
#define _RH Registers::getInstance()[_RD_IDX + 1]

#define _CF Flags::getInstance()[CF]
#define _VF Flags::getInstance()[VF]
#define _ZF Flags::getInstance()[ZF]
#define _NF Flags::getInstance()[NF]
#define _QF Flags::getInstance()[QF]
#define _GE Flags::getInstance()[GE]

#define _LD( rd, addr ) rd = Memory::getInstance().load(addr)
#define _LDB( rd, addr ) rd = Memory::getInstance().loadByte(addr)
#define _LDH( rd, addr ) rd = Memory::getInstance().loadShort(addr)
#define _LDBS( rd, addr ) rd = (int8_t) Memory::getInstance().loadByte(addr)
#define _LDHS( rd, addr ) rd = (int16_t) Memory::getInstance().loadShort(addr)
#define _ST( addr, data ) Memory::getInstance().store(addr, data)
#define _STB( addr, data ) Memory::getInstance().storeByte(addr, data)
#define _STH( addr, data ) Memory::getInstance().storeShort(addr, data)
#define _LDI( rd, value ) rd = value
#define _B( target ) _IP = target
#define _BL( target ) _LR = _IP; _IP = target

#define _END }
#define _INSTRUCTION( sign ) void sign ( const tParam &param ) { \
	register uint32_t _RT, _RX;

#define _NOP

#endif
