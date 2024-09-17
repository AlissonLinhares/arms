#include <arch.h>

#ifndef CONDITIONS_H
#define CONDITIONS_H

namespace arm2x {
	bool _condition_eq() {
		return _ZF;
	}

	bool _condition_ne() {
		return !_ZF;
	}

	bool _condition_cshs() {
		return _CF;
	}

	bool _condition_cclo() {
		return !_CF;
	}

	bool _condition_mi() {
		return _NF;
	}

	bool _condition_pl() {
		return !_NF;
	}

	bool _condition_vs() {
		return _VF;
	}

	bool _condition_vc() {
		return !_VF;
	}

	bool _condition_hi() {
		return ( _CF && !_ZF );
	}

	bool _condition_ls() {
		return ( !_CF || _ZF );
	}

	bool _condition_ge() {
		return ( _NF == _VF );
	}

	bool _condition_lt() {
		return ( _NF != _VF );
	}

	bool _condition_gt() {
		return ( !_ZF && (_NF == _VF) );
	}

	bool _condition_le() {
		return (  _ZF || (_NF != _VF) );
	}

	bool _condition_al() {
		return true;
	}

	bool _condition_nv() {
		_ASSERT( true, "Unsupported condition" );
	}
};

#endif
