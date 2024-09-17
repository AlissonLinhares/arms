#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>
#include <operations.h>

using namespace std;

namespace arm2x {
	class Cache {
	public:
		Cache( size_t size ) : size(size) {
			operations = new tOperation[size];
			reset();
		}

		inline void reset() {
			for ( int i = 0; i < size; i++ )
				operations[i].offset = -1;
		}

		inline tOperation& operator[]( const size_t offset ) {
			return operations[offset % size];
		}

		inline const tOperation& operator[]( const size_t offset ) const {
			return operations[offset % size];
		}

		virtual ~Cache() {
			delete[] operations;
		}

	private:
		tOperation* operations;
		size_t size;
	};
};

#endif
