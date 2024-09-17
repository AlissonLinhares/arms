#ifndef LOADSTORE_H
#define LOADSTORE_H

#include <arch.h>

#define _LDR( rd0, rs1, rs2 )  _LD(rd0, rs1); rs1 = rs1 - rs2
#define _LDR_U( rd0, rs1, rs2 ) _LD(rd0, rs1); rs1 = rs1 + rs2
#define _LDR_P( rd0, rs1, rs2 ) _LD(rd0, rs1 - rs2)
#define _LDR_UP( rd0, rs1, rs2 ) _LD(rd0, rs1 + rs2)
#define _LDR_WP( rd0, rs1, rs2 ) rs1 = rs1 - rs2; _LD(rd0, rs1)
#define _LDR_WUP( rd0, rs1, rs2 ) rs1 = rs1 + rs2; _LD(rd0, rs1)
#define _LDR_B( rd0, rs1, rs2 ) _LDB(rd0, rs1); rs1 = rs1 - rs2
#define _LDR_BU( rd0, rs1, rs2 ) _LDB(rd0, rs1); rs1 = rs1 + rs2
#define _LDR_BP( rd0, rs1, rs2 ) _LDB(rd0, rs1 - rs2)
#define _LDR_BUP( rd0, rs1, rs2 ) _LDB(rd0, rs1 + rs2)
#define _LDR_WBP( rd0, rs1, rs2 ) rs1 = rs1 - rs2; _LDB(rd0, rs1)
#define _LDR_WBUP( rd0, rs1, rs2 ) rs1 = rs1 + rs2; _LDB(rd0, rs1)

#define _STR( rd0, rs1, rs2 ) _ST(rs1, rd0); rs1 = rs1 - rs2
#define _STR_U( rd0, rs1, rs2 ) _ST(rs1, rd0); rs1 = rs1 + rs2
#define _STR_P( rd0, rs1, rs2 ) _ST(rs1 - rs2, rd0)
#define _STR_UP( rd0, rs1, rs2 ) _ST(rs1 + rs2, rd0)
#define _STR_WP( rd0, rs1, rs2 ) rs1 = rs1 - rs2; _ST(rs1, rd0)
#define _STR_WUP( rd0, rs1, rs2 ) rs1 = rs1 + rs2; _ST(rs1, rd0)
#define _STR_B( rd0, rs1, rs2 ) _STB(rs1, rd0); rs1 = rs1 - rs2
#define _STR_BU( rd0, rs1, rs2 ) _STB(rs1, rd0); rs1 = rs1 + rs2
#define _STR_BP( rd0, rs1, rs2 ) _STB(rs1 - rs2, rd0)
#define _STR_BUP( rd0, rs1, rs2 ) _STB(rs1 + rs2, rd0)
#define _STR_WBP( rd0, rs1, rs2 ) rs1 = rs1 - rs2; _STB(rs1, rd0)
#define _STR_WBUP( rd0, rs1, rs2 ) rs1 = rs1 + rs2; _STB(rs1, rd0)

namespace arm2x {
	_INSTRUCTION( _ldr )
		_LDR( _RD, _RN, _RM );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldr_u )
		_LDR_U( _RD, _RN, _RM );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldr_p )
		_LDR_P( _RD, _RN, _RM );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldr_up )
		_LDR_UP( _RD, _RN, _RM );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldr_wp )
		_LDR_WP( _RD, _RN, _RM );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldr_wup )
		_LDR_WUP( _RD, _RN, _RM );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldr_b )
		_LDR_B( _RD, _RN, _RM );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldr_bu )
		_LDR_BU( _RD, _RN, _RM );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _ldr_bp )
		_LDR_BP( _RD, _RN, _RM );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldr_bup )
		_LDR_BUP( _RD, _RN, _RM );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _ldr_wbp )
		_LDR_WBP( _RD, _RN, _RM );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldr_wbup )
		_LDR_WBUP( _RD, _RN, _RM );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _ldr_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_u_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_U( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_p_lsl )
		_LDI( _RT, _SHIFT );
 		_LSL( _RT, _RM, _RT );
		_LDR_P( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsl #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_up_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_UP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_wp_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_WP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsl #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_wup_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_WUP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_b_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_B( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_bu_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_BU( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_bp_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_BP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsl #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_bup_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_BUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_wbp_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_LDR_WBP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsl #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_wbup_lsl )
		_LDI( _RT, _SHIFT);
		_LSL( _RT, _RM, _RT );
		_LDR_WBUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_u_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_U( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_p_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_P( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_up_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_UP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_wp_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_WP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_wup_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_WUP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_b_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_B( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_bu_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_BU( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_bp_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_BP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_bup_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_BUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_wbp_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_WBP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_wbup_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_LDR_WBUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_u_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_U( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_p_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_P( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", asr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_up_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_UP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_wp_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_WP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", asr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_wup_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_WUP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_b_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_B( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_bu_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_BU( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_bp_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_BP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", asr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_bup_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_BUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_wbp_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_LDR_WBP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", asr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_wbup_asr )
		_LDI( _RT, _SHIFT);
		_ASR( _RT, _RM, _RT );
		_LDR_WBUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_u_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_U( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_p_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_P( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", ror #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_up_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_UP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_wp_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_WP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", ror #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_wup_ror )
		_LDI( _RT, _SHIFT);
		_ROR( _RT, _RM, _RT );
		_LDR_WUP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_b_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_B( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_bu_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_BU( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _ldr_bp_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_BP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", ror #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_bup_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_BUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _ldr_wbp_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_WBP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", ror #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_wbup_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_LDR_WBUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _ldr_imm )
		_LDI( _RT, _OFFSET );
		_LDR( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _OFFSET );
	_END

	_INSTRUCTION( _ldr_u_imm )
		_LDI( _RT, _OFFSET );
		_LDR_U( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _OFFSET );
	_END

	_INSTRUCTION( _ldr_p_imm )
		_LDI( _RT, _OFFSET );
		_LDR_P( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _OFFSET << "]" );
	_END

	_INSTRUCTION( _ldr_up_imm )
		_LDI( _RT, _OFFSET );
		_LDR_UP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _OFFSET << "]" );
	_END

	_INSTRUCTION( _ldr_wp_imm )
		_LDI( _RT, _OFFSET );
		_LDR_WP( _RD, _RN, _RT );
		_LDI( _RT, _OFFSET );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _OFFSET << "]!" );
	_END

	_INSTRUCTION( _ldr_wup_imm )
		_LDI( _RT, _OFFSET );
		_LDR_WUP( _RD, _RN, _RT );
		_LOG( "ldr r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _OFFSET << "]!" );
	_END

	_INSTRUCTION( _ldr_b_imm )
		_LDI( _RT, _OFFSET );
		_LDR_B( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _OFFSET );
	_END

	_INSTRUCTION( _ldr_bu_imm )
		_LDI( _RT, _OFFSET );
		_LDR_BU( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _OFFSET );
	_END

	_INSTRUCTION( _ldr_bp_imm )
		_LDI( _RT, _OFFSET );
		_LDR_BP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _OFFSET << "]" );
	_END

	_INSTRUCTION( _ldr_bup_imm )
		_LDI( _RT, _OFFSET );
		_LDR_BUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _OFFSET << "]" );
	_END

	_INSTRUCTION( _ldr_wbp_imm )
		_LDI( _RT, _OFFSET );
		_LDR_WBP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _OFFSET << "]!" );
	_END

	_INSTRUCTION( _ldr_wbup_imm )
		_LDI( _RT, _OFFSET );
		_LDR_WBUP( _RD, _RN, _RT );
		_LOG( "ldrb r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _OFFSET << "]!" );
	_END

	_INSTRUCTION( _str )
		_STR( _RD, _RN, _RM );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _str_u )
		_STR_U( _RD, _RN, _RM );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _str_p )
		_STR_P( _RD, _RN, _RM );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _str_up )
		_STR_UP( _RD, _RN, _RM );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _str_wp )
		_STR_WP( _RD, _RN, _RM );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _str_wup )
		_STR_WUP( _RD, _RN, _RM );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _str_b )
		_STR_B( _RD, _RN, _RM );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX );
	_END

	_INSTRUCTION( _str_bu )
		_STR_BU( _RD, _RN, _RM );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX );
	_END

	_INSTRUCTION( _str_bp )
		_STR_BP( _RD, _RN, _RM );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _str_bup )
		_STR_BUP( _RD, _RN, _RM );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]" );
	_END

	_INSTRUCTION( _str_wbp )
		_STR_WBP( _RD, _RN, _RM );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _str_wbup )
		_STR_WBUP( _RD, _RN, _RM );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << "]!" );
	_END

	_INSTRUCTION( _str_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _str_u_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_U( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _str_p_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_P( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsl #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_up_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_UP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_wp_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_WP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsl #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_wup_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_WUP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_b_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_B( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _str_bu_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_BU( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _str_bp_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_BP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsl #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_bup_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_BUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_wbp_lsl )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_STR_WBP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsl #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_wbup_lsl )
		_LDI( _RT, _SHIFT);
		_LSL( _RT, _RM, _RT );
		_STR_WBUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _str_u_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_U( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _str_p_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_P( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_up_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_UP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_wp_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_WP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_wup_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_WUP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_b_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_B( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _str_bu_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_BU( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", lsr #" << _SHIFT );
	_END

	_INSTRUCTION( _str_bp_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_BP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_bup_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_BUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_wbp_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_WBP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", lsr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_wbup_lsr )
		_LDI( _RT, _SHIFT );
		_LSR( _RT, _RM, _RT );
		_STR_WBUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", lsr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _str_u_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_U( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _str_p_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_P( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", asr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_up_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_UP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_wp_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_WP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", asr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_wup_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_WUP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_b_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_B( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _str_bu_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_BU( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _str_bp_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_BP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", asr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_bup_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_BUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_wbp_asr )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_STR_WBP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", asr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_wbup_asr )
		_LDI( _RT, _SHIFT);
		_ASR( _RT, _RM, _RT );
		_STR_WBUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _str_u_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_U( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _str_p_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_P( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", ror #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_up_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_UP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_wp_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_WP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", ror #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_wup_ror )
		_LDI( _RT, _SHIFT);
		_ROR( _RT, _RM, _RT );
		_STR_WUP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_b_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_B( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], -r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _str_bu_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_BU( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _str_bp_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_BP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", ror #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_bup_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_BUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT << "]" );
	_END

	_INSTRUCTION( _str_wbp_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_WBP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", -r" << _RM_IDX << ", ror #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_wbup_ror )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_STR_WBUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT << "]!" );
	_END

	_INSTRUCTION( _str_imm )
		_LDI( _RT, _OFFSET );
		_STR( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _OFFSET );
	_END

	_INSTRUCTION( _str_u_imm )
		_LDI( _RT, _OFFSET );
		_STR_U( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _OFFSET );
	_END

	_INSTRUCTION( _str_p_imm )
		_LDI( _RT, _OFFSET );
		_STR_P( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _OFFSET << "]" );
	_END

	_INSTRUCTION( _str_up_imm )
		_LDI( _RT, _OFFSET );
		_STR_UP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _OFFSET << "]" );
	_END

	_INSTRUCTION( _str_wp_imm )
		_LDI( _RT, _OFFSET );
		_STR_WP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _OFFSET << "]!" );
	_END

	_INSTRUCTION( _str_wup_imm )
		_LDI( _RT, _OFFSET );
		_STR_WUP( _RD, _RN, _RT );
		_LOG( "str r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _OFFSET << "]!" );
	_END

	_INSTRUCTION( _str_b_imm )
		_LDI( _RT, _OFFSET );
		_STR_B( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], #-" << _OFFSET );
	_END

	_INSTRUCTION( _str_bu_imm )
		_LDI( _RT, _OFFSET );
		_STR_BU( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << "], #" << _OFFSET );
	_END

	_INSTRUCTION( _str_bp_imm )
		_LDI( _RT, _OFFSET );
		_STR_BP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _OFFSET << "]" );
	_END

	_INSTRUCTION( _str_bup_imm )
		_LDI( _RT, _OFFSET );
		_STR_BUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _OFFSET << "]" );
	_END

	_INSTRUCTION( _str_wbp_imm )
		_LDI( _RT, _OFFSET );
		_STR_WBP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", #-" << _OFFSET << "]!" );
	_END

	_INSTRUCTION( _str_wbup_imm )
		_LDI( _RT, _OFFSET );
		_STR_WBUP( _RD, _RN, _RT );
		_LOG( "strb r" << _RD_IDX << ", [r" << _RN_IDX << ", #" << _OFFSET << "]!" );
	_END
};

#endif
