// https://stackoverflow.com/questions/2114163/reading-a-register-value-into-a-c-variable
#include <config.h>
#include <stdint.h>
#include <iostream>

using namespace std;

#ifndef REGISTERS_H
#define REGISTERS_H

#define REGISTER_INDEX_LEN 17

#define IP (PC + 1)

namespace arm2x {

	enum GPRIndex {
		/**
		 * Registers R0 to R7 are unbanked registers. This means that each of
		 * them refers to the same 32-bit physical register in all processor
		 * modes. They are completely general-purpose registers, with no
		 * special uses implied by the architecture, and can be used wherever
		 * an instruction allows a general-purpose register to be specified.
		 */
		R0,
		R1,
		R2,
		R3,
		R4,
		R5,
		R6,
		R7,
		/**
		 * Registers R8 to R14 are banked registers. The physical register
		 * referred to by each of them depends on the current processor mode.
		 */
		R8,
		R9,
		R10,
		R11,
		R12,
		/**
		 * Register R15 holds the Program Counter (PC). It can often be used in
		 * place of one of the general-purpose registers R0 to R14, and is
		 * therefore considered one of the general-purpose registers. However,
		 * there are also many instruction-specific restrictions or special
		 * cases about its use. These are noted in the individual instruction
		 * descriptions. Usually, the instruction is UNPREDICTABLE if R15 is
		 * used in a manner that breaks these restrictions.
		 */
		SP,
		LR,
		PC
	};

	GPRIndex rd, rs, rn, rm;

	class Registers {
	private:
		Registers() {
			reset();
		}

		Registers( Registers& copy ) {
			/** The copy constructor is not allowed. */
		}

	public:
		inline static Registers& getInstance() {
			static Registers localInstance;
			return localInstance;
		}

		inline uint32_t& operator[] ( const unsigned id ) {
			return registers[id];
		}

		inline const uint32_t getValue ( const unsigned id ) const {
			return registers[id];
		}

		inline void setValue ( const unsigned id, const uint32_t value ) {
			registers[id] = value;
		}

		void reset() {
			for ( int i = 0; i < REGISTER_INDEX_LEN; i++ )
				registers[i] = 0;

			registers[SP] = DEFAULT_STACK_ADDRESS;
		}

	private:
		uint32_t registers[REGISTER_INDEX_LEN];
	};
}

#endif
