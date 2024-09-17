#include <arch.h>

#ifndef HINTS_H
#define HINTS_H

namespace arm2x {
	_INSTRUCTION( _yield )
		_NOP;
		_LOG( "yield" );
	_END

	_INSTRUCTION( _wfe )
		_NOP;
		_LOG( "wfe" );
	_END

	_INSTRUCTION( _wfi )
		_NOP;
		_LOG( "wfi" );
	_END
};

#endif
