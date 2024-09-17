#include <arch.h>

#ifndef MULTIPLY_H
#define MULTIPLY_H

namespace arm2x {
	_INSTRUCTION( _mul )
		_RN = _RM * _RS;
		_LOG( "mul r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _muls )
		_RN = _RM * _RS;
		_UPDATE_FLAGS( _RN );
		_LOG( "muls r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _mla )
		_RN = _RM * _RS + _RD;
		_LOG( "mla r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX );
	_END

	_INSTRUCTION( _mlas )
		_RN = _RM * _RS + _RD;
		_UPDATE_FLAGS( _RN );
		_LOG( "mlas r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX );
	_END

	_INSTRUCTION( _mls )
		_RN = _RD - (_RM * _RS);
		_LOG( "mls r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX );
	_END

	_INSTRUCTION( _umaal )
		uint64_t RESULT = UINT64(_RM) * UINT64(_RS) + UINT64(_RD) + UINT64(_RN);
		_RD = RESULT;
		_RN = RESULT >> 32;
		_LOG( "umaal r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _umull )
		uint64_t RESULT = UINT64(_RM) * UINT64(_RS);
		_RD = RESULT;
		_RN = RESULT >> 32;
		_LOG( "umull r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _umulls )
		uint64_t RESULT = UINT64(_RM) * UINT64(_RS);
		_RD = RESULT;
		_RN = RESULT >> 32;
		_UPDATE_FLAGS64( RESULT );

		_LOG( "umull r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _umlal )
		uint64_t RESULT = UINT64(_RM) * UINT64(_RS) + (UINT64(_RD) | UINT64(_RN) << 32);
		_RD = RESULT;
		_RN = RESULT >> 32;

		_LOG( "umlal r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _umlals )
		uint64_t RESULT = UINT64(_RM) * UINT64(_RS) + (UINT64(_RD) | UINT64(_RN) << 32);
		_RD = RESULT;
		_RN = RESULT >> 32;

		_UPDATE_FLAGS64( RESULT );
		_LOG( "umlals r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _smull )
		int64_t RESULT = SINT64(_RM) * SINT64(_RS);
		_RD = RESULT;
		_RN = RESULT >> 32;

		_LOG( "smull r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _smulls )
		int64_t RESULT = SINT64(_RM) * SINT64(_RS);
		_RD = RESULT;
		_RN = RESULT >> 32;

		_UPDATE_FLAGS64( RESULT );
		_LOG( "smulls r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _smlabb )
		_RT = SINT16(_RM) * SINT16(_RS);
		_RN = _RT + _RD;

		if ( _QF == 0 ) {
			bool a = _RT & 0x80000000;
			bool b = _RD & 0x80000000;
			bool c = _RN & 0x80000000;

			_QF = (a == b) & (c != a);
		}

		_LOG( "smlabb r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX );
	_END

	_INSTRUCTION( _smlabt )
		_RT = SINT16(_RM) * SINT16(_HIGH(_RS));
		_RN = _RT + _RD;

		if ( _QF == 0 ) {
			bool a = _RT & 0x80000000;
			bool b = _RD & 0x80000000;
			bool c = _RN & 0x80000000;

			_QF = (a == b) & (c != a);
		}

		_LOG( "smlabt r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX );
	_END

	_INSTRUCTION( _smlatb )
		_RT = (SINT16(_HIGH(_RM)) * SINT16(_RS));
		_RN = _RT + _RD;

		if ( _QF == 0 ) {
			bool a = _RT & 0x80000000;
			bool b = _RD & 0x80000000;
			bool c = _RN & 0x80000000;

			_QF = (a == b) & (c != a);
		}

		_LOG( "smlatb r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX );
	_END

	_INSTRUCTION( _smlatt )
		_RT = SINT16(_HIGH(_RM)) * SINT16(_HIGH(_RS));
		_RN = _RT + _RD;

		if ( _QF == 0 ) {
			bool a = _RT & 0x80000000;
			bool b = _RD & 0x80000000;
			bool c = _RN & 0x80000000;

			_QF = (a == b) & (c != a);
		}

		_LOG( "smlatt r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX );
	_END

	_INSTRUCTION( _smlal )
		uint64_t RESULT = SINT64(_RM) * SINT64(_RS) + (UINT64(_RD) | UINT64(_RN) << 32);
		_RD = RESULT;
		_RN = RESULT >> 32;

		_LOG( "smlal r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END

	_INSTRUCTION( _smlals )
		uint64_t RESULT = SINT64(_RM) * SINT64(_RS) + (UINT64(_RD) | UINT64(_RN) << 32);
		_RD = RESULT;
		_RN = RESULT >> 32;

		_UPDATE_FLAGS64( RESULT );
		_LOG( "smlals r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX );
	_END
}

#endif
