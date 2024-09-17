#include <arch.h>

#ifndef BLOCKTRANSFER_H
#define BLOCKTRANSFER_H

#define _LDM_AFTER( cond, reg, addr, op ) if ( cond ) { _LD( reg, addr ); op; }
#define _STM_AFTER( cond, addr, reg, op ) if ( cond ) { _ST( addr, reg ); op; }
#define _LDM_BEFORE( cond, reg, addr, op ) if ( cond ) { op; _LD( reg, addr ); }
#define _STM_BEFORE( cond, addr, reg, op ) if ( cond ) { op; _ST( addr, reg ); }

#define _STORE_ALL_DECREMENT_AFTER( imm, addr ) \
		_STM_AFTER( imm & 0x8000, addr, _PC , addr -= 4 ) \
		_STM_AFTER( imm & 0x4000, addr, _LR , addr -= 4 ) \
		_STM_AFTER( imm & 0x2000, addr, _SP , addr -= 4 ) \
		_STM_AFTER( imm & 0x1000, addr, _R12, addr -= 4 ) \
		_STM_AFTER( imm & 0x800 , addr, _R11, addr -= 4 ) \
		_STM_AFTER( imm & 0x400 , addr, _R10, addr -= 4 ) \
		_STM_AFTER( imm & 0x200 , addr, _R9 , addr -= 4 ) \
		_STM_AFTER( imm & 0x100 , addr, _R8 , addr -= 4 ) \
		_STM_AFTER( imm & 0x80  , addr, _R7 , addr -= 4 ) \
		_STM_AFTER( imm & 0x40  , addr, _R6 , addr -= 4 ) \
		_STM_AFTER( imm & 0x20  , addr, _R5 , addr -= 4 ) \
		_STM_AFTER( imm & 0x10  , addr, _R4 , addr -= 4 ) \
		_STM_AFTER( imm & 0x8   , addr, _R3 , addr -= 4 ) \
		_STM_AFTER( imm & 0x4   , addr, _R2 , addr -= 4 ) \
		_STM_AFTER( imm & 0x2   , addr, _R1 , addr -= 4 ) \
		_STM_AFTER( imm & 0x1   , addr, _R0 , addr -= 4 )

#define _STORE_ALL_INCREMENT_AFTER( imm, addr ) \
		_STM_AFTER( imm & 0x1   , addr, _R0 , addr += 4 ) \
		_STM_AFTER( imm & 0x2   , addr, _R1 , addr += 4 ) \
		_STM_AFTER( imm & 0x4   , addr, _R2 , addr += 4 ) \
		_STM_AFTER( imm & 0x8   , addr, _R3 , addr += 4 ) \
		_STM_AFTER( imm & 0x10  , addr, _R4 , addr += 4 ) \
		_STM_AFTER( imm & 0x20  , addr, _R5 , addr += 4 ) \
		_STM_AFTER( imm & 0x40  , addr, _R6 , addr += 4 ) \
		_STM_AFTER( imm & 0x80  , addr, _R7 , addr += 4 ) \
		_STM_AFTER( imm & 0x100 , addr, _R8 , addr += 4 ) \
		_STM_AFTER( imm & 0x200 , addr, _R9 , addr += 4 ) \
		_STM_AFTER( imm & 0x400 , addr, _R10, addr += 4 ) \
		_STM_AFTER( imm & 0x800 , addr, _R11, addr += 4 ) \
		_STM_AFTER( imm & 0x1000, addr, _R12, addr += 4 ) \
		_STM_AFTER( imm & 0x2000, addr, _SP , addr += 4 ) \
		_STM_AFTER( imm & 0x4000, addr, _LR , addr += 4 ) \
		_STM_AFTER( imm & 0x8000, addr, _PC , addr += 4 )

#define _LOAD_ALL_DECREMENT_AFTER( imm, addr ) \
		_LDM_AFTER( imm & 0x8000,  _IP , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x4000,  _LR , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x2000,  _SP , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x1000,  _R12, addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x800 ,  _R11, addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x400 ,  _R10, addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x200 ,  _R9 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x100 ,  _R8 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x80  ,  _R7 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x40  ,  _R6 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x20  ,  _R5 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x10  ,  _R4 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x8   ,  _R3 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x4   ,  _R2 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x2   ,  _R1 , addr, addr -= 4 ) \
		_LDM_AFTER( imm & 0x1   ,  _R0 , addr, addr -= 4 )

#define _LOAD_ALL_INCREMENT_AFTER( imm, addr ) \
		_LDM_AFTER( imm & 0x1   ,  _R0 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x2   ,  _R1 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x4   ,  _R2 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x8   ,  _R3 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x10  ,  _R4 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x20  ,  _R5 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x40  ,  _R6 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x80  ,  _R7 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x100 ,  _R8 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x200 ,  _R9 , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x400 ,  _R10, addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x800 ,  _R11, addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x1000,  _R12, addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x2000,  _SP , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x4000,  _LR , addr, addr += 4 ) \
		_LDM_AFTER( imm & 0x8000,  _IP , addr, addr += 4 )

#define _STORE_ALL_DECREMENT_BEFORE( imm, addr ) \
		_STM_BEFORE( imm & 0x8000, addr, _PC , addr -= 4 ) \
		_STM_BEFORE( imm & 0x4000, addr, _LR , addr -= 4 ) \
		_STM_BEFORE( imm & 0x2000, addr, _SP , addr -= 4 ) \
		_STM_BEFORE( imm & 0x1000, addr, _R12, addr -= 4 ) \
		_STM_BEFORE( imm & 0x800 , addr, _R11, addr -= 4 ) \
		_STM_BEFORE( imm & 0x400 , addr, _R10, addr -= 4 ) \
		_STM_BEFORE( imm & 0x200 , addr, _R9 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x100 , addr, _R8 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x80  , addr, _R7 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x40  , addr, _R6 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x20  , addr, _R5 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x10  , addr, _R4 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x8   , addr, _R3 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x4   , addr, _R2 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x2   , addr, _R1 , addr -= 4 ) \
		_STM_BEFORE( imm & 0x1   , addr, _R0 , addr -= 4 )

#define _STORE_ALL_INCREMENT_BEFORE( imm, addr ) \
		_STM_BEFORE( imm & 0x1   , addr, _R0 , addr += 4 ) \
		_STM_BEFORE( imm & 0x2   , addr, _R1 , addr += 4 ) \
		_STM_BEFORE( imm & 0x4   , addr, _R2 , addr += 4 ) \
		_STM_BEFORE( imm & 0x8   , addr, _R3 , addr += 4 ) \
		_STM_BEFORE( imm & 0x10  , addr, _R4 , addr += 4 ) \
		_STM_BEFORE( imm & 0x20  , addr, _R5 , addr += 4 ) \
		_STM_BEFORE( imm & 0x40  , addr, _R6 , addr += 4 ) \
		_STM_BEFORE( imm & 0x80  , addr, _R7 , addr += 4 ) \
		_STM_BEFORE( imm & 0x100 , addr, _R8 , addr += 4 ) \
		_STM_BEFORE( imm & 0x200 , addr, _R9 , addr += 4 ) \
		_STM_BEFORE( imm & 0x400 , addr, _R10, addr += 4 ) \
		_STM_BEFORE( imm & 0x800 , addr, _R11, addr += 4 ) \
		_STM_BEFORE( imm & 0x1000, addr, _R12, addr += 4 ) \
		_STM_BEFORE( imm & 0x2000, addr, _SP , addr += 4 ) \
		_STM_BEFORE( imm & 0x4000, addr, _LR , addr += 4 ) \
		_STM_BEFORE( imm & 0x8000, addr, _PC , addr += 4 )

#define _LOAD_ALL_DECREMENT_BEFORE( imm, addr ) \
		_LDM_BEFORE( imm & 0x8000,  _IP , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x4000,  _LR , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x2000,  _SP , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x1000,  _R12, addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x800 ,  _R11, addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x400 ,  _R10, addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x200 ,  _R9 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x100 ,  _R8 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x80  ,  _R7 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x40  ,  _R6 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x20  ,  _R5 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x10  ,  _R4 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x8   ,  _R3 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x4   ,  _R2 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x2   ,  _R1 , addr, addr -= 4 ) \
		_LDM_BEFORE( imm & 0x1   ,  _R0 , addr, addr -= 4 )

#define _LOAD_ALL_INCREMENT_BEFORE( imm, addr ) \
		_LDM_BEFORE( imm & 0x1   ,  _R0 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x2   ,  _R1 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x4   ,  _R2 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x8   ,  _R3 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x10  ,  _R4 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x20  ,  _R5 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x40  ,  _R6 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x80  ,  _R7 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x100 ,  _R8 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x200 ,  _R9 , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x400 ,  _R10, addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x800 ,  _R11, addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x1000,  _R12, addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x2000,  _SP , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x4000,  _LR , addr, addr += 4 ) \
		_LDM_BEFORE( imm & 0x8000,  _IP , addr, addr += 4 )

namespace arm2x {
	struct tRegisterList {
		unsigned value : 16;
		tRegisterList( unsigned data ) : value(data) {}
	} __attribute__((packed));

#if DEBUG_ENABLE
	std::ostream& operator<<( std::ostream& so, tRegisterList list ) {
		bool comma = false;
		so << "{ ";

		for ( int i = 0; i < 16; i++ ) {
			if ( list.value & 1 ) {
				if ( comma )
					so << ", " << "r" << i;
				else
					so << "r" << i;

				comma = true;
			}

			list.value = list.value >> 1;
		}

		so << " }";
		return so;
	}
#endif

	_INSTRUCTION( _stmda )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_STORE_ALL_DECREMENT_AFTER( _RT, _RX );
		_LOG( "stmda r" << _RN_IDX << ", " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _stmda_w )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_STORE_ALL_DECREMENT_AFTER( _RT, _RX );
		_RN = _RX;
		_LOG( "stmda r" << _RN_IDX << "!, " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _ldmda )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_LOAD_ALL_DECREMENT_AFTER( _RT, _RX );
		_LOG( "ldmda r" << _RN_IDX << ", " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _ldmda_w )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_LOAD_ALL_DECREMENT_AFTER( _RT, _RX );
		_RN = _RX;
		_LOG( "ldmda r" << _RN_IDX << "!, " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _stm )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_STORE_ALL_INCREMENT_AFTER( _RT, _RX );
		_LOG( "stm r" << _RN_IDX << ", " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _stm_w )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_STORE_ALL_INCREMENT_AFTER( _RT, _RX );
		_RN = _RX;
		_LOG( "stm r" << _RN_IDX << "!, " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _ldm )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_LOAD_ALL_INCREMENT_AFTER( _RT, _RX );
		_LOG( "ldm r" << _RN_IDX << ", " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _ldm_w )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_LOAD_ALL_INCREMENT_AFTER( _RT, _RX );
		_RN = _RX;
		_LOG( "ldm r" << _RN_IDX << "!, " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _stmdb )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_STORE_ALL_DECREMENT_BEFORE( _RT, _RX );
		_LOG( "stmdb r" << _RN_IDX << ", " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _stmdb_w )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_STORE_ALL_DECREMENT_BEFORE( _RT, _RX );
		_RN = _RX;
		_LOG( "stmdb r" << _RN_IDX << "!, " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _ldmdb )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_LOAD_ALL_DECREMENT_BEFORE( _RT, _RX );
		_LOG( "ldmdb r" << _RN_IDX << ", " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _ldmdb_w )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_LOAD_ALL_DECREMENT_BEFORE( _RT, _RX );
		_RN = _RX;
		_LOG( "ldmdb r" << _RN_IDX << "!, " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _stmib )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_STORE_ALL_INCREMENT_BEFORE( _RT, _RX );
		_LOG( "stmib r" << _RN_IDX << ", " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _stmib_w )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_STORE_ALL_INCREMENT_BEFORE( _RT, _RX );
		_RN = _RX;
		_LOG( "stmib r" << _RN_IDX << "!, " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _ldmib )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_LOAD_ALL_INCREMENT_BEFORE( _RT, _RX );
		_LOG( "ldmib r" << _RN_IDX << ", " << ((tRegisterList) _REG_LIST) );
	_END

	_INSTRUCTION( _ldmib_w )
		_RX = _RN;
		_LDI( _RT, _REG_LIST );
		_LOAD_ALL_INCREMENT_BEFORE( _RT, _RX );
		_RN = _RX;
		_LOG( "ldmib r" << _RN_IDX << "!, " << ((tRegisterList) _REG_LIST) );
	_END
};

#endif
