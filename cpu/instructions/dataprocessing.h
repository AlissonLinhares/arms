#include <arch.h>

#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#define _TST( rs1, rs2 ) _UPDATE_FLAGS( rs1 & rs2 )
#define _TEQ( rs1, rs2 ) _UPDATE_FLAGS( rs1 ^ rs2 )
#define _CMP( rs1, rs2 ) _subtraction( rs1, rs2, 0 )
#define _CMN( rs1, rs2 ) _addition( rs1, rs2, 0 )
#define _AND( rd0, rs1, rs2 ) rd0 = rs1 & rs2
#define _EOR( rd0, rs1, rs2 ) rd0 = rs1 ^ rs2
#define _SUB( rd0, rs1, rs2 ) rd0 = rs1 - rs2
#define _RSB( rd0, rs1, rs2 ) _SUB( rd0, rs2, rs1 )
#define _ADD( rd0, rs1, rs2 ) rd0 = rs1 + rs2
#define _ADC( rd0, rs1, rs2 ) rd0 = rs1 + rs2 + _CF
#define _SBC( rd0, rs1, rs2 ) rd0 = rs1 - rs2 - !_CF
#define _RSC( rd0, rs1, rs2 ) _SBC( rd0, rs2, rs1 )
#define _ORR( rd0, rs1, rs2 ) rd0 = rs1 | rs2
#define _MOV( rd0,      rs2 ) rd0 = rs2
#define _BIC( rd0, rs1, rs2 ) rd0 = rs1 & ~(rs2)
#define _MVN( rd0,      rs2 ) rd0 = ~(rs2)
#define _ANDS( rd0, rs1, rs2 ) _AND( rd0, rs1, rs2 ); _UPDATE_FLAGS( rd0 );
#define _EORS( rd0, rs1, rs2 ) _EOR( rd0, rs1, rs2 ); _UPDATE_FLAGS( rd0 );
#define _SUBS( rd0, rs1, rs2 ) rd0 = _subtraction( rs1, rs2, 0 )
#define _RSBS( rd0, rs1, rs2 ) rd0 = _subtraction( rs2, rs1, 0 )
#define _ADDS( rd0, rs1, rs2 ) rd0 = _addition( rs1, rs2, 0 )
#define _ADCS( rd0, rs1, rs2 ) rd0 = _addition( rs1, rs2, _CF )
#define _SBCS( rd0, rs1, rs2 ) rd0 = _subtraction( rs1, rs2, !_CF )
#define _RSCS( rd0, rs1, rs2 ) rd0 = _subtraction( rs2, rs1, !_CF )
#define _ORRS( rd0, rs1, rs2 ) _ORR( rd0, rs1, rs2 ); _UPDATE_FLAGS( rd0 );
#define _MOVS( rd0,      rs2 ) _MOV( rd0,      rs2 ); _UPDATE_FLAGS( rd0 );
#define _BICS( rd0, rs1, rs2 ) _BIC( rd0, rs1, rs2 ); _UPDATE_FLAGS( rd0 );
#define _MVNS( rd0,      rs2 ) _MVN( rd0,      rs2 ); _UPDATE_FLAGS( rd0 );

#define _inline __attribute__((always_inline)) inline

namespace arm2x {
	_inline const uint32_t _addition( const uint64_t reg, const uint64_t value, const unsigned carry ) {
		uint64_t result = reg + value + carry;

		bool a = reg & 0x80000000;
		bool b = value & 0x80000000;
		bool c = result & 0x80000000;

		_VF = (a == b) & (c != a);
		_CF = result > 0xFFFFFFFF;

		_UPDATE_FLAGS( (uint32_t) result );
		return (uint32_t) result;
	}

	_inline const uint32_t _subtraction( const uint64_t reg, const uint64_t value, const unsigned carry ) {
		uint64_t result = reg - value - carry;

		bool a = reg & 0x80000000;
		bool b = value & 0x80000000;
		bool c = result & 0x80000000;

		_VF = (b == c) & (c != a);
		_CF = result <= 0xFFFFFFFF;

		_UPDATE_FLAGS( (uint32_t) result );
		return (uint32_t) result;
	}

	_INSTRUCTION( _tst )
		_TST( _RN, _RM );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _tst_imm )
		_LEIS( _RT, _IMM12 );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _tst_lsl )
		_LSLS( _RT, _RM, _RS );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _tst_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSLS( _RT, _RM, _RT );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _tst_lsr )
		_LSRS( _RT, _RM, _RS );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _tst_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSRS( _RT, _RM, _RT );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _tst_asr )
		_ASRS( _RT, _RM, _RS );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _tst_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASRS( _RT, _RM, _RT );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _tst_ror )
		_RORS( _RT, _RM, _RS );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _tst_rrx )
		_RRXS( _RT, _RM );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _tst_ror_imm )
		_LDI( _RT, _SHIFT );
		_RORS( _RT, _RM, _RT );
		_TST( _RN, _RT );
		_LOG( "tst r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _teq )
		_TEQ( _RN, _RM );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _teq_imm )
		_LEIS( _RT, _IMM12 );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _teq_lsl )
		_LSLS( _RT, _RM, _RS );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _teq_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSLS( _RT, _RM, _RT );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _teq_lsr )
		_LSRS( _RT, _RM, _RS );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _teq_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSRS( _RT, _RM, _RT );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _teq_asr )
		_ASRS( _RT, _RM, _RS );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _teq_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASRS( _RT, _RM, _RT );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _teq_ror )
		_RORS( _RT, _RM, _RS );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _teq_rrx )
		_RRXS( _RT, _RM );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _teq_ror_imm )
		_LDI( _RT, _SHIFT );
		_RORS( _RT, _RM, _RT );
		_TEQ( _RN, _RT );
		_LOG( "teq r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _cmp )
		_CMP( _RN, _RM );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _cmp_imm )
		_LEI( _RT, _IMM12 );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _cmp_lsl )
		_LSL( _RT, _RM, _RS );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _cmp_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _cmp_lsr )
		_LSR( _RT, _RM, _RS );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _cmp_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _cmp_asr )
		_ASR( _RT, _RM, _RS );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _cmp_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _cmp_ror )
		_ROR( _RT, _RM, _RS );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _cmp_rrx )
		_RRX( _RT, _RM );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _cmp_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_CMP( _RN, _RT );
		_LOG( "cmp r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _cmn )
		_CMN( _RN, _RM );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _cmn_imm )
		_LEI( _RT, _IMM12 );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _cmn_lsl )
		_LSL( _RT, _RM, _RS );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _cmn_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _cmn_lsr )
		_LSR( _RT, _RM, _RS );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _cmn_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _cmn_asr )
		_ASR( _RT, _RM, _RS );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _cmn_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _cmn_ror )
		_ROR( _RT, _RM, _RS );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _cmn_rrx )
		_RRX( _RT, _RM );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _cmn_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_CMN( _RN, _RT );
		_LOG( "cmn r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _and )
		_AND( _RD, _RN, _RM );
		_LOG( "and r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _ands )
		_ANDS( _RD, _RN, _RM );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _and_imm )
		_LEI( _RT, _IMM12 );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _ands_imm )
		_LEIS( _RT, _IMM12 );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _and_lsl )
		_LSL( _RT, _RM, _RS );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _ands_lsl )
		_LSLS( _RT, _RM, _RS );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _and_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _ands_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSLS( _RT, _RM, _RT );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _and_lsr )
		_LSR( _RT, _RM, _RS );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _ands_lsr )
		_LSRS( _RT, _RM, _RS );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _and_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _ands_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSRS( _RT, _RM, _RT );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _and_asr )
		_ASR( _RT, _RM, _RS );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _ands_asr )
		_ASRS( _RT, _RM, _RS );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _and_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _ands_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASRS( _RT, _RM, _RT );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _and_ror )
		_ROR( _RT, _RM, _RS );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _and_rrx )
		_RRX( _RT, _RM );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _ands_ror )
		_RORS( _RT, _RM, _RS );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _ands_rrx )
		_RRXS( _RT, _RM );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _and_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_AND( _RD, _RN, _RT );
		_LOG( "and r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _ands_ror_imm )
		_LDI( _RT, _SHIFT );
		_RORS( _RT, _RM, _RT );
		_ANDS( _RD, _RN, _RT );
		_LOG( "ands r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _eor )
		_EOR( _RD, _RN, _RM );
		_LOG( "eor r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _eors )
		_EORS( _RD, _RN, _RM );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _eor_imm )
		_LEI( _RT, _IMM12 );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r"  << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _eors_imm )
		_LEIS( _RT, _IMM12 );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _eor_lsl )
		_LSL( _RT, _RM, _RS );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _eors_lsl )
		_LSLS( _RT, _RM, _RS );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _eor_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _eors_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSLS( _RT, _RM, _RT );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT )
	_END

	_INSTRUCTION( _eor_lsr )
		_LSR( _RT, _RM, _RS );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _eors_lsr )
		_LSRS( _RT, _RM, _RS );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _eor_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _eors_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSRS( _RT, _RM, _RT );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _eor_asr )
		_ASR( _RT, _RM, _RS );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _eors_asr )
		_ASRS( _RT, _RM, _RS );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _eor_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _eors_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASRS( _RT, _RM, _RT );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _eor_ror )
		_ROR( _RT, _RM, _RS );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _eor_rrx )
		_RRX( _RT, _RM );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _eors_ror )
		_RORS( _RT, _RM, _RS );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _eors_rrx )
		_RRXS( _RT, _RM );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _eor_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_EOR( _RD, _RN, _RT );
		_LOG( "eor r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _eors_ror_imm )
		_LDI( _RT, _SHIFT );
		_RORS( _RT, _RM, _RT );
		_EORS( _RD, _RN, _RT );
		_LOG( "eors r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _sub )
		_SUB( _RD, _RN, _RM );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _subs )
		_SUBS( _RD, _RN, _RM );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _sub_imm )
		_LEI( _RT, _IMM12 );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _subs_imm )
		_LEI( _RT, _IMM12 );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _sub_lsl )
		_LSL( _RT, _RM, _RS );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _subs_lsl )
		_LSL( _RT, _RM, _RS );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _sub_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _subs_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _sub_lsr )
		_LSR( _RT, _RM, _RS );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _subs_lsr )
		_LSR( _RT, _RM, _RS  );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _sub_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _subs_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _sub_asr )
		_ASR( _RT, _RM, _RS );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _subs_asr )
		_ASR( _RT, _RM, _RS );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _sub_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _subs_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _sub_ror )
		_ROR( _RT, _RM, _RS );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _sub_rrx )
		_RRX( _RT, _RM );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _subs_ror )
		_ROR( _RT, _RM, _RS );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _subs_rrx )
		_RRX( _RT, _RM );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" << _RS_IDX );
	_END

	_INSTRUCTION( _sub_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_SUB( _RD, _RN, _RT );
		_LOG( "sub r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _subs_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_SUBS( _RD, _RN, _RT );
		_LOG( "subs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _rsb )
		_RSB( _RD, _RN, _RM );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _rsbs )
		_RSBS( _RD, _RN, _RM );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _rsb_imm )
		_LEI( _RT, _IMM12 );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _rsbs_imm )
		_LEI( _RT, _IMM12 );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _rsb_lsl )
		_LSL( _RT, _RM, _RS );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsbs_lsl )
		_LSL( _RT, _RM, _RS );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsb_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _rsbs_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _rsb_lsr )
		_LSR( _RT, _RM, _RS );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsbs_lsr )
		_LSR( _RT, _RM, _RS );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsb_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _rsbs_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _rsb_asr )
		_ASR( _RT, _RM, _RS );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsbs_asr )
		_ASR( _RT, _RM, _RS );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsb_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _rsbs_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _rsb_ror )
		_ROR( _RT, _RM, _RS );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsb_rrx )
		_RRX( _RT, _RM );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _rsbs_ror )
		_ROR( _RT, _RM, _RS );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsbs_rrx )
		_RRX( _RT, _RM );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _rsb_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RSB( _RD, _RN, _RT );
		_LOG( "rsb r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _rsbs_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RSBS( _RD, _RN, _RT );
		_LOG( "rsbs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _add )
		_ADD( _RD, _RN, _RM );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _adds )
		_ADDS( _RD, _RN, _RM );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _add_imm )
		_LEI( _RT, _IMM12 );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _adds_imm )
		_LEI( _RT, _IMM12 );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _add_lsl )
		_LSL( _RT, _RM, _RS );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _adds_lsl )
		_LSL( _RT, _RM, _RS );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _add_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _adds_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _add_lsr )
		_LSR( _RT, _RM, _RS );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _adds_lsr )
		_LSR( _RT, _RM, _RS );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _add_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _adds_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _add_asr )
		_ASR( _RT, _RM, _RS );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _adds_asr )
		_ASR( _RT, _RM, _RS );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _add_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _adds_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _add_ror )
		_ROR( _RT, _RM, _RS );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _add_rrx )
		_RRX( _RT, _RM );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _adds_ror )
		_ROR( _RT, _RM, _RS );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _adds_rrx )
		_RRX( _RT, _RM );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _add_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_ADD( _RD, _RN, _RT );
		_LOG( "add r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _adds_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_ADDS( _RD, _RN, _RT );
		_LOG( "adds r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _adc )
		_ADC( _RD, _RN, _RM );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _adcs )
		_ADCS( _RD, _RN, _RM );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _adc_imm )
		_LEI( _RT, _IMM12 );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _adcs_imm )
		_LEI( _RT, _IMM12 );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _adc_lsl )
		_LSL( _RT, _RM, _RS );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _adcs_lsl )
		_LSL( _RT, _RM, _RS );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _adc_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _adcs_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _adc_lsr )
		_LSR( _RT, _RM, _RS );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _adcs_lsr )
		_LSR( _RT, _RM, _RS );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _adc_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _adcs_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _adc_asr )
		_ASR( _RT, _RM, _RS );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _adcs_asr )
		_ASR( _RT, _RM, _RS );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _adc_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _adcs_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _adc_ror )
		_ROR( _RT, _RM, _RS );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _adc_rrx )
		_RRX( _RT, _RM );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _adcs_ror )
		_ROR( _RT, _RM, _RS );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _adcs_rrx )
		_RRX( _RT, _RM );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _adc_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_ADC( _RD, _RN, _RT );
		_LOG( "adc r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _adcs_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_ADCS( _RD, _RN, _RT );
		_LOG( "adcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _sbc )
		_SBC( _RD, _RN, _RM );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _sbcs )
		_SBCS( _RD, _RN, _RM );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _sbc_imm )
		_LEI( _RT, _IMM12 );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _sbcs_imm )
		_LEI( _RT, _IMM12 );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _sbc_lsl )
		_LSL( _RT, _RM, _RS );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _sbcs_lsl )
		_LSL( _RT, _RM, _RS );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _sbc_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _sbcs_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _sbc_lsr )
		_LSR( _RT, _RM, _RS );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _sbcs_lsr )
 		_LSR( _RT, _RM, _RS );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _sbc_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _sbcs_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _sbc_asr )
		_ASR( _RT, _RM, _RS );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _sbcs_asr )
		_ASR( _RT, _RM, _RS );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _sbc_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _sbcs_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _sbc_ror )
		_ROR( _RT, _RM, _RS );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _sbc_rrx )
		_RRX( _RT, _RM );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _sbcs_ror )
		_ROR( _RT, _RM, _RS );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _sbcs_rrx )
		_RRX( _RT, _RM );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _sbc_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_SBC( _RD, _RN, _RT );
		_LOG( "sbc r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _sbcs_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_SBCS( _RD, _RN, _RT );
		_LOG( "sbcs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _rsc )
		_RSC( _RD, _RN, _RM );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _rscs )
		_RSCS( _RD, _RN, _RM );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _rsc_imm )
		_LEI( _RT, _IMM12 );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _rscs_imm )
		_LEI( _RT, _IMM12 );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _rsc_lsl )
		_LSL( _RT, _RM, _RS );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _rscs_lsl )
		_LSL( _RT, _RM, _RS );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsc_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _rscs_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _rsc_lsr )
		_LSR( _RT, _RM, _RS );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _rscs_lsr )
		_LSR( _RT, _RM, _RS );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsc_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _rscs_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _rsc_asr )
		_ASR( _RT, _RM, _RS );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _rscs_asr )
		_ASR( _RT, _RM, _RS );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsc_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _rscs_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _rsc_ror )
		_ROR( _RT, _RM, _RS );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _rsc_rrx )
		_RRX( _RT, _RM );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _rscs_ror )
		_ROR( _RT, _RM, _RS );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _rscs_rrx )
		_RRX( _RT, _RM );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _rsc_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RSC( _RD, _RN, _RT );
		_LOG( "rsc r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _rscs_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RSCS( _RD, _RN, _RT );
		_LOG( "rscs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _orr )
		_ORR( _RD, _RN, _RM );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _orrs )
		_ORRS( _RD, _RN, _RM );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _orr_imm )
		_LEI( _RT, _IMM12 );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _orrs_imm )
		_LEIS( _RT, _IMM12 );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _orr_lsl )
		_LSL( _RT, _RM, _RS );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _orrs_lsl )
		_LSLS( _RT, _RM, _RS );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _orr_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _orrs_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSLS( _RT, _RM, _RT );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _orr_lsr )
		_LSR( _RT, _RM, _RS );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _orrs_lsr )
		_LSRS( _RT, _RM, _RS );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _orr_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _orrs_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSRS( _RT, _RM, _RT );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _orr_asr )
		_ASR( _RT, _RM, _RS );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _orrs_asr )
		_ASRS( _RT, _RM, _RS );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _orr_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _orrs_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASRS( _RT, _RM, _RT );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _orr_ror )
		_ROR( _RT, _RM, _RS );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _orr_rrx )
		_RRX( _RT, _RM );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _orrs_ror )
		_RORS( _RT, _RM, _RS );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _orrs_rrx )
		_RRXS( _RT, _RM );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _orr_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_ORR( _RD, _RN, _RT );
		_LOG( "orr r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _orrs_ror_imm )
		_LDI( _RT, _SHIFT );
		_RORS( _RT, _RM, _RT );
		_ORRS( _RD, _RN, _RT );
		_LOG( "orrs r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _mov )
		_MOV( _RD, _RM );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _movs )
		_MOVS( _RD, _RM );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _mov_imm )
		_LEI( _RT, _IMM12 );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _movs_imm )
		_LEIS( _RT, _IMM12 );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _mov_lsl )
		_LSL( _RT, _RM, _RS );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _movs_lsl )
		_LSLS( _RT, _RM, _RS );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _mov_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _movs_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSLS( _RT, _RM, _RT );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _mov_lsr )
		_LSR( _RT, _RM, _RS );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _movs_lsr )
		_LSRS( _RT, _RM, _RS );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _mov_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _movs_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSRS( _RT, _RM, _RT );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _mov_asr )
		_ASR( _RT, _RM, _RS );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _movs_asr )
		_ASRS( _RT, _RM, _RS );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _mov_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _movs_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASRS( _RT, _RM, _RT );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _mov_ror )
		_ROR( _RT, _RM, _RS );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _mov_rrx )
		_RRX( _RT, _RM );
		_MOV( _RD, _RT );
		_LOG( "mov r" << _RD_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _movs_ror )
		_RORS( _RT, _RM, _RS );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _movs_rrx )
		_RRXS( _RT, _RM );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _mov_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_MOV( _RD, _RT );
		_LOG( "mov r"  << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _movs_ror_imm )
		_LDI( _RT, _SHIFT );
		_RORS( _RT, _RM, _RT );
		_MOVS( _RD, _RT );
		_LOG( "movs r" << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _bic )
		_BIC( _RD, _RN, _RM );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _bics )
		_BICS( _RD, _RN, _RM );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _bic_imm )
		_LEI( _RT, _IMM12 );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _bics_imm )
		_LEIS( _RT, _IMM12 );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _bic_lsl )
		_LSL( _RT, _RM, _RS );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _bics_lsl )
		_LSLS( _RT, _RM, _RS );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _bic_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _bics_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSLS( _RT, _RM, _RT );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _bic_lsr )
		_LSR( _RT, _RM, _RS );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _bics_lsr )
		_LSRS( _RT, _RM, _RS );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _bic_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _bics_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSRS( _RT, _RM, _RT );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _bic_asr )
		_ASR( _RT, _RM, _RS );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _bics_asr )
		_ASRS( _RT, _RM, _RS );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _bic_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _bics_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASRS( _RT, _RM, _RT );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _bic_ror )
		_ROR( _RT, _RM, _RS );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _bic_rrx )
		_RRX( _RT, _RM );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _bics_ror )
		_RORS( _RT,_RM, _RS );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _bics_rrx )
		_RRXS( _RT,_RM );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _bic_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_BIC( _RD, _RN, _RT );
		_LOG( "bic r"  << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _bics_ror_imm )
		_LDI( _RT, _SHIFT );
		_RORS( _RT, _RM, _RT );
		_BICS( _RD, _RN, _RT );
		_LOG( "bics r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _mvn )
		_MVN( _RD, _RM );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _mvns )
		_MVNS( _RD, _RM );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _mvn_imm )
		_LEI( _RT, _IMM12 );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _mvns_imm )
		_LEIS( _RT, _IMM12 );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", #" << _RT );
	_END

	_INSTRUCTION( _mvn_lsl )
		_LSL( _RT, _RM, _RS );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _mvns_lsl )
		_LSLS( _RT, _RM, _RS );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", lsl r" << _RS_IDX );
	_END

	_INSTRUCTION( _mvn_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _mvns_lsl_imm )
		_LDI( _RT, _SHIFT );
		_LSLS( _RT, _RM, _RT );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _mvn_lsr )
 		_LSR( _RT, _RM, _RS );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _mvns_lsr )
		_LSRS( _RT, _RM, _RS );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", lsr r" << _RS_IDX );
	_END

	_INSTRUCTION( _mvn_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _mvns_lsr_imm )
		_LDI( _RT, _SHIFT );
		_LSRS( _RT, _RM, _RT );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _mvn_asr )
		_ASR( _RT, _RM, _RS );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _mvns_asr )
		_ASRS( _RT, _RM, _RS );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", asr r" << _RS_IDX );
	_END

	_INSTRUCTION( _mvn_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _mvns_asr_imm )
		_LDI( _RT, _SHIFT );
		_ASRS( _RT, _RM, _RT );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _mvn_ror )
		_ROR( _RT, _RM, _RS );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _mvn_rrx )
		_RRX( _RT, _RM );
		_MVN( _RD, _RT );
		_LOG( "mvn r" << _RD_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _mvns_ror )
		_RORS( _RT, _RM, _RS );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", ror r" << _RS_IDX );
	_END

	_INSTRUCTION( _mvns_rrx )
		_RRXS( _RT, _RM );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", rrx" );
	_END

	_INSTRUCTION( _mvn_ror_imm )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_MVN( _RD, _RT );
		_LOG( "mvn r"  << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _mvns_ror_imm )
		_LDI( _RT, _SHIFT );
		_RORS( _RT, _RM, _RT );
		_MVNS( _RD, _RT );
		_LOG( "mvns r" << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END
};

#endif
