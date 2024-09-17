#include <arch.h>

#ifndef BRANCH_H
#define BRANCH_H

namespace arm2x {
	_INSTRUCTION( _b )
		_LDI( _RT, _ADDR );
		_RT = _PC + (_RT << 2);
		_B(_RT);
		_LOG( "b #" << _ADDR );
	_END

	_INSTRUCTION( _bl )
		_LDI( _RT, _ADDR );
		_RT = _PC + (_RT << 2);
		_BL(_RT);
		_LOG( "bl #" << _ADDR );
	_END

	_INSTRUCTION( _bx )
		_B(_RM);
		_LOG( "bx r" << _RM_IDX );
	_END

	_INSTRUCTION( _blx )
		_BL(_RM);
		_LOG( "blx r" << _RM_IDX );
	_END

	_INSTRUCTION( _bxj )
		_B(_RM);
		_LOG( "bxj r" << _RM_IDX );
		_ASSERT( true, "bxj is not support" )
	_END
};

#endif
