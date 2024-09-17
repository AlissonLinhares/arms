#ifndef MISC_H
#define MISC_H

#include <arch.h>

namespace arm2x {
	_INSTRUCTION( _clz )
		_RD = __builtin_clz(_RM);
		_LOG( "clz r" << _RD_IDX << ", r" << _RM_IDX )
		_ASSERT( _RM == 0, "Invalid operation." );
	_END

	_INSTRUCTION( _undefined )
		_NOP;
		_ASSERT( true, "Unsupported Instruction at " << std::hex << _PC << std::dec );
	_END

	_INSTRUCTION( _movw )
		_LDI( _RD, _IMM16 );
		_LOG( "movw r" << _RD_IDX << ", #" << _IMM16 );
	_END

	_INSTRUCTION( _movt )
		_LDI( _RT, _IMM16 );
		_RD = (_RD & 0x0000FFFF) | (_RT << 16);
		_LOG( "movt r" << _RD_IDX << ", #" << _IMM16 );
	_END

	_INSTRUCTION( _msr_w_imm )
		_LEI( _RT, _IMM12 );
		_NF = (_RT >> 31) & 1;
		_ZF = (_RT >> 30) & 1;
		_CF = (_RT >> 29) & 1;
		_VF = (_RT >> 28) & 1;
		_QF = (_RT >> 27) & 1;
		_LOG( "msr cpsr_f, #" << _IMM12 );
	_END

	_INSTRUCTION( _msr_g_imm )
		_LEI( _RT, _IMM12 );
		_GE = (_RT >> 19) & 7;
		_LOG( "msr cpsr_s, #" << _IMM12 );
	_END

	_INSTRUCTION( _msr_wg_imm )
		_LEI( _RT, _IMM12 );
		_NF = (_RT >> 31) & 1;
		_ZF = (_RT >> 30) & 1;
		_CF = (_RT >> 29) & 1;
		_VF = (_RT >> 28) & 1;
		_QF = (_RT >> 27) & 1;
		_GE = (_RT >> 19) & 7;
		_LOG( "msr cpsr_fs, #" << _IMM12 );
	_END

	_INSTRUCTION( _msr_w )
		_NF = (_RM >> 31) & 1;
		_ZF = (_RM >> 30) & 1;
		_CF = (_RM >> 29) & 1;
		_VF = (_RM >> 28) & 1;
		_QF = (_RM >> 27) & 1;
		_LOG( "msr cpsr_f, r" << _RM_IDX );
	_END

	_INSTRUCTION( _msr_g )
		_GE = (_RM >> 19) & 7;
		_LOG( "msr cpsr_s, r" << _RM_IDX );
	_END

	_INSTRUCTION( _msr_wg )
		_NF = (_RM >> 31) & 1;
		_ZF = (_RM >> 30) & 1;
		_CF = (_RM >> 29) & 1;
		_VF = (_RM >> 28) & 1;
		_QF = (_RM >> 27) & 1;
		_GE = (_RM >> 19) & 7;
		_LOG( "msr cpsr_fs, r" << _RM_IDX );
	_END

	_INSTRUCTION( _mrs )
		_RD = Flags::getInstance().toCPSR().value;
		_LOG( "msr r" << _RD_IDX << ", cpsr" );
	_END

	_INSTRUCTION( _msrs )
		_NOP;
		_ASSERT( true, "System Level Instruction - MSR IMMEDIATE" );
	_END
};

#endif
