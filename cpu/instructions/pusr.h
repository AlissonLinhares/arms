#include <arch.h>

#ifndef PUSR_H
#define PUSR_H

namespace arm2x {
	_INSTRUCTION( _pkhbt )
		_LDI( _RT, _SHIFT );
		_LSL( _RT, _RM, _RT );
		_RD = ( _RT & W1_MASK ) | ( _RN & W0_MASK );
		_LOG( "pkhbt r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", lsl #" << _SHIFT );
	_END

	_INSTRUCTION( _pkhtb )
		_LDI( _RT, _SHIFT );
		_ASR( _RT, _RM, _RT );
		_RD = (( _RT & W0_MASK ) | ( _RN & W1_MASK ));
		_LOG( "pkhtb r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", asr #" << _SHIFT );
	_END

	_INSTRUCTION( _sxtab16 )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = ( _RN + EXTEND( _RT, 8, 16 ) ) & W0_MASK;
		_RD = _RD | (( _RN & W1_MASK ) + ( EXTEND( _RT >> 16, 8, 16) << 16 ) );
		_LOG( "sxtab16 r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", #" << _SHIFT );
	_END

	_INSTRUCTION( _sxtb16 )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = (EXTEND(_RT >> 16, 8, 16) << 16) | EXTEND(_RT, 8, 16);
		_LOG( "sxtb16 r" << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _sel )
		_NOP;
		_ASSERT( true, "Unimplemented Instruction" );
	_END

	_INSTRUCTION( _ssat_lsl )
		_NOP;
		_ASSERT( true, "Unimplemented Instruction" );
	_END

	_INSTRUCTION( _ssat_asr )
		_NOP;
		_ASSERT( true, "Unimplemented Instruction" );
	_END

	_INSTRUCTION( _ssat16 )
		_NOP;
		_ASSERT( true, "Unimplemented Instruction" );
	_END

	_INSTRUCTION( _sxtab )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = _RN + EXTEND( _RT, 8, 32 );
		_LOG( "sxtab r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _sxtb )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = EXTEND( _RT, 8, 32 );
		_LOG( "uxtb r" << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _rev )
		_RD = (_RM << 24) | ((_RM & B1_MASK) << 8) | ((_RM & B2_MASK) >> 8) | (_RM >> 24);
		_LOG( "rev r" << _RD_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _sxtah )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = _RN + EXTEND( _RT, 16, 32 );
		_LOG( "uxtah r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _sxth )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = EXTEND( _RT, 16, 32 );
		_LOG( "uxtah r" << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _rev16 )
		_RD = ((_RM & B3_MASK) >> 8) | ((_RM & B2_MASK) << 8) | ((_RM & B1_MASK) >> 8) | ((_RM & B0_MASK) << 8);
		_LOG( "rev16 r" << _RD_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _uxtab16 )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = _LOW(_RN + _B0(_RT)) | ((( _RN & W1_MASK ) + (_RT & B2_MASK)) & W1_MASK);
		_LOG( "uxtab16 r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _uxtb16 )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = (_RT & B2_MASK) | (_RT & B0_MASK);
		_LOG( "uxtb16 r" << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _usat_lsl )
		_NOP;
		_ASSERT( true, "Unimplemented Instruction" );
	_END

	_INSTRUCTION( _usat_asr )
		_NOP;
		_ASSERT( true, "Unimplemented Instruction" );
	_END

	_INSTRUCTION( _usat16 )
		_NOP;
		_ASSERT( true, "Unimplemented Instruction" );
	_END

	_INSTRUCTION( _uxtab )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = _RN + _B0( _RT );
		_LOG( "uxtab r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _uxtb )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = _B0( _RT );
		_LOG( "uxtb r" << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _rbit )
		_RT = _RM;
		_RT = ((_RT & 0xAAAAAAAA) >> 1) | ((_RT & 0x55555555) << 1);
		_RT = ((_RT & 0xCCCCCCCC) >> 2) | ((_RT & 0x33333333) << 2);
		_RT = ((_RT & 0xF0F0F0F0) >> 4) | ((_RT & 0x0F0F0F0F) << 4);
		_RT = ((_RT & 0xFF00FF00) >> 8) | ((_RT & 0x00FF00FF) << 8);
    	_RD = (_RT >> 16) | (_RT << 16);
		_LOG( "rbit r" << _RD_IDX << ", r" << _RM_IDX );
	_END

	_INSTRUCTION( _uxtah )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = _RN + _LOW( _RT );
		_LOG( "uxtah r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _uxth )
		_LDI( _RT, _SHIFT );
		_ROR( _RT, _RM, _RT );
		_RD = _LOW( _RT );
		_LOG( "uxtah r" << _RD_IDX << ", r" << _RM_IDX << ", ror #" << _SHIFT );
	_END

	_INSTRUCTION( _revsh )
		_RD = (EXTEND( _RM, 8, 32 ) << 8) | ((_RM >> 8) & B0_MASK);
		_LOG( "revsh r" << _RD_IDX << ", r" << _RM_IDX );
	_END
};

#endif
