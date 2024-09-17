#include <debug.h>
#include <registers.h>
#include <elf.h>

#ifndef MEMORY_H
#define MEMORY_H

namespace arm2x {

	class Memory {
	private:
		Memory( size_t size ) : size(size) {
			memory = new uint8_t[size];
		}

	public:
		inline static Memory& getInstance() {
			static Memory memory( DEFAULT_MEMORY_SIZE );
			return memory;
		}

		inline const uint32_t load( const uint32_t offset ) const {
			return *(uint32_t*) (memory + offset);
		}

		inline const uint16_t loadShort( const uint32_t offset ) const {
			return *(uint16_t*) (memory + offset);
		}

		inline const uint8_t loadByte( const uint32_t offset ) const {
			return memory[offset];
		}

		inline void store( const uint32_t offset, const uint32_t value ) {
			*(uint32_t*) (memory + offset) = value;
		}

		inline void storeShort( const uint32_t offset, const uint16_t value ) {
			*(uint16_t*) (memory + offset) = value;
		}

		inline void storeByte( const uint32_t offset, const uint8_t value ) {
			memory[offset] = value;
		}

		inline const uint32_t fetch() const {
			Registers& reg = Registers::getInstance();

			_ASSERT( reg[IP] > DEFAULT_MEMORY_SIZE, "Invalid Fetch Address" )
			_ASSERT( reg[SP] < heap, "Invalid Stack Address" )

			return load( reg[IP] );
		}

		inline void init( ELF &elf ) {
			heap = elf.loadSections( (char*) memory, DEFAULT_MEMORY_SIZE );
			_ASSERT( heap == 0, "Not Enough Memory" );
		}

		inline char* getMemoryOffset() const {
			return (char*) memory;
		}

		inline const uint32_t brk( const uint32_t offset ) {
			if ( offset == 0 ) {
				return heap;
			} else if ( (offset <= DEFAULT_MEMORY_SIZE) && (offset >= heap) ) {
				heap = offset;
				return 0;
			}

			return -1;
		}

		~Memory() {
			delete[] memory;
		}
	private:
		uint8_t *memory;
		uint32_t heap;
		size_t size;
	};
}

#endif
