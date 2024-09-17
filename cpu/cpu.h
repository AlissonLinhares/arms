#include <debug.h>
#include <memory.h>
#include <registers.h>
#include <flags.h>
#include <decoder.h>
#include <dispatch.h>
#include <cache.h>

#ifndef CPU_H
#define CPU_H

namespace arm2x {
	class CPU {
	public:
		CPU() {

		}

		inline void setPC( const uint32_t value ) {
			Registers::getInstance().setValue( IP, value );
		}

		inline void setSP( const uint32_t value ) {
			Registers::getInstance().setValue( SP, value );
		}

		inline void setMode( const ProcessorMode mode ) {
			Flags::getInstance().setValue( MODE, mode );
		}

		inline void start() {
			Memory& memory = Memory::getInstance();
			Decoder& decoder = Decoder::getInstance();
			Dispatch& dispatch = Dispatch::getInstance();
			Registers& registers = Registers::getInstance();

			Cache cache( DEFAULT_CACHE_SIZE );

			while ( true ) {
				tOperation& operation = cache[registers[IP]];

#if SHOW_STATISTICS
				if ( operation.offset != registers[IP] ) {
					operation.offset = registers[IP];
					decoder.decode( operation, memory.fetch() );
					misses++;
				} else {
					hits++;
				}
#else
				if ( operation.offset != registers[IP] ) {
					operation.offset = registers[IP];
					decoder.decode( operation, memory.fetch() );
				}
#endif

				registers[IP] = registers[IP] + 4;
				registers[PC] = registers[IP] + 4;

				dispatch.exec( operation );
			}
		}
	};
};

#endif
