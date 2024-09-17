#include <operations.h>

#ifndef DISPATCH_H
#define DISPATCH_H

namespace arm2x {
	class Dispatch {
	private:
		Dispatch() {

		}

	public:
		inline static Dispatch& getInstance() {
			static Dispatch decoder;
			return decoder;
		}

		inline void exec( const tOperation &operation ) const {
			if ( operation.cond == _condition_al || operation.cond() )
				operation.inst( operation.param );
		}
	};
};

#endif
