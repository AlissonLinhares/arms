#ifndef SMSUD_H
#define SMSUD_H

#include <arch.h>

namespace arm2x {

	_INSTRUCTION( _smlad )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_LOW(_RS))) +
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_HIGH(_RS))) + SINT64(_RD);

		_RN = RESULT;
		_QF = (_QF == 1) || (RESULT != ((int32_t)(RESULT)));

		_LOG("smlad r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smladx )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_HIGH(_RS))) +
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_LOW(_RS))) + SINT64(_RD);

		_RN = RESULT;
		_QF = (_QF == 1) || (RESULT != ((int32_t)(RESULT)));

		_LOG("smladx r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smuad )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_LOW(_RS))) +
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_HIGH(_RS)));

		_RN = RESULT;
		_QF = (_QF == 1) || (RESULT != ((int32_t)(RESULT)));

		_LOG("smuad r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _smuadx )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_HIGH(_RS))) +
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_LOW(_RS)));

		_RN = RESULT;
		_QF = (_QF == 1) || (RESULT != ((int32_t)(RESULT)));

		_LOG("smuadx r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _smlsd )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_LOW(_RS))) -
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_HIGH(_RS))) + SINT64(_RD);

		_RN = RESULT;
		_QF = (_QF == 1) || (RESULT != ((int32_t)(RESULT)));

		_LOG("smlsd r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smlsdx )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_HIGH(_RS))) -
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_LOW(_RS))) + SINT64(_RD);

		_RN = RESULT;
		_QF = (_QF == 1) || (RESULT != ((int32_t)(RESULT)));

		_LOG("smlsdx r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smusd )
		_RN = SINT16(_LOW(_RM)) * SINT16(_LOW(_RS)) -
			SINT16(_HIGH(_RM)) * SINT16(_HIGH(_RS));

		_LOG("smusd r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _smusdx )
		_RN = SINT16(_LOW(_RM)) * SINT16(_HIGH(_RS)) -
			SINT16(_HIGH(_RM)) * SINT16(_LOW(_RS));

		_LOG("smusdx r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _sdiv )
		_RN = SINT32(_RM) / SINT32(_RS);
		_LOG("sdiv r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _udiv )
		_RN = _RM / _RS;
		_LOG("udiv r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _smlald )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_LOW(_RS))) +
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_HIGH(_RS))) +
			((SINT64(_RN) << 32) | _RD);

		_RN = (RESULT >> 32);
		_RD = RESULT;

		_LOG("smlald r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _smlaldx )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_HIGH(_RS))) +
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_LOW(_RS))) + 
			((SINT64(_RN) << 32) | _RD);

		_RN = (RESULT >> 32);
		_RD = RESULT;

		_LOG("smlald r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _smlsld )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_LOW(_RS))) -
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_HIGH(_RS))) +
			((SINT64(_RN) << 32) | _RD);

		_RN = RESULT >> 32;
		_RD = RESULT;

		_LOG("smlsld r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _smlsldx )
		int64_t RESULT = SINT64(SINT16(_LOW(_RM)) * SINT16(_HIGH(_RS))) -
			SINT64(SINT16(_HIGH(_RM)) * SINT16(_LOW(_RS))) + 
			((SINT64(_RN) << 32) | _RD);

		_RN = RESULT >> 32;
		_RD = RESULT;

		_LOG("smlsldx r" << _RD_IDX << ", r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX);
	_END

	_INSTRUCTION( _smmla )
		_RN = ((SINT64(_RD) << 32) + SINT64(_RM) * SINT64(_RS)) >> 32;
		_LOG("smmla r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smmlar )
		_RN = 0x80000000 + (((SINT64(_RD) << 32) + SINT64(_RM) * SINT64(_RS)) >> 32);
		_LOG("smmlar r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smmul )
		_RN = (SINT64(_RM) * SINT64(_RS)) >> 32;
		_LOG("smmul r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smmulr )
		_RN = 0x80000000 + ((SINT64(_RM) * SINT64(_RS)) >> 32);
		_LOG("smmulr r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smmls )
		_RN = ((SINT64(_RD) << 32) - SINT64(_RM) * SINT64(_RS)) >> 32;
		_LOG("smmls r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END

	_INSTRUCTION( _smmlsr )
		_RN = 0x80000000 + (((SINT64(_RD) << 32) - SINT64(_RM) * SINT64(_RS)) >> 32);
		_LOG("smmlsr r" << _RN_IDX << ", r" << _RM_IDX << ", r" << _RS_IDX << ", r" << _RD_IDX);
	_END
};

#endif
