#include <config.h>
#include <stdint.h>
#include <iostream>

using namespace std;

#ifndef FLAGS_H
#define FLAGS_H

namespace arm2x {

	/**
	 * The ARM architecture supports seven processor modes.
	 * @see ARM Architecture Reference Manual (2nd Edition), Chapter A2, Processor modes
	 */
	enum ProcessorMode {
		USER = 16,       /**< Normal program execution mode. */
		FIQ = 17,        /**< Supports a high-speed data transfer or channel process. */
		IRQ = 18,        /**< Used for general-purpose interrupt handling. */
		SUPERVISOR = 19, /**< A protected mode for the operating system. */
		ABORT = 23,      /**< Implements virtual memory and/or memory protection. */
		UNDEFINED = 27,  /**< Supports software emulation of hardware coprocessors. */
		SYSTEM = 31      /**< Privileged operating system tasks (ARM architecture version 4 and above). */
	};

	/**
	 * The current program status register (CPSR) is accessible in all processor modes. It contains condition code
	 * flags, interrupt disable bits, the current processor mode, and other status and control information.
	 * ---------------------------------------------------------------------------------------------
	 * - 31 - 30 - 29 - 28 - 27 - 26 - 23            8 - 7 - 6 - 5 - 4  - 3  - 2  - 1  - 0  - Bits
	 * ---------------------------------------------------------------------------------------------
	 * - N  - Z  - C  - V  - Q  - GE    DNM(RAZ)       - I - F - T - M4 - M3 - M2 - M1 - M0 - Flags
	 * ---------------------------------------------------------------------------------------------
	 */
	union tCPSRFormat {
		uint32_t value;
		struct {
			/** M0, M1, M2, M3, and M4 (M[4:0]) are the mode bits, and these determine the mode in which the processor operates. */
			unsigned MODE : 5;
			/**
			 * The T bit should be zero (SBZ) on ARM architecture version 3 and below, and on non-T variants of ARM architecture version 4. No instructions
			 * exist in these architectures that can switch between ARM and Thumb states.
			 *
			 * On T variants of ARM architecture 4 and above, the T bit has the following meanings:
			 * T=0 Indicates ARM execution; T=1 Indicates Thumb execution.
			 *
			 * Instructions that switch between ARM and Thumb states can be used freely on implementations of these architectures.
			 * On non-T variants of ARM architecture version 5 and above, the T bit has the following meanings:
			 * T=0 Indicates ARM execution; T=1 Forces the next instruction executed to cause an undefined instruction exception
			 */
			unsigned T : 1;
			unsigned F : 1; /**< Disables FIQ interrupts when it is set. */
			unsigned I : 1; /**< Disables IRQ interrupts when it is set. */
			unsigned DNM : 16;
			unsigned GE : 3;
			/**
			 * Q flag and is used to indicate whether overflow and/or saturation has occurred in some of the enhanced DSP instructions.
			 * Similarly, bit[27] of each SPSR is a Q flag, and is used to preserve and restore the CPSR Q flag if an exception occurs. For more details of the Q flag, see Chapter A10 Enhanced DSP Extension.
			 */
			unsigned Q : 1;
			/**
			 * For an addition or subtraction, V is set to 1 if signed overflow occurred, regarding the operands and result as two's complement signed integers.
			 * For non-addition/subtractions, V is normally left unchanged (but see the individual instruction descriptions for any special cases).
			 */
			unsigned V : 1;
			/**
			 * For an addition, including the comparison instruction CMN, C is set to 1 if the addition produced a carry (that is, an unsigned overflow), and to 0 otherwise.
			 * For a subtraction, including the comparison instruction CMP, C is set to 0 if the subtraction produced a borrow (that is, an unsigned underflow), and to 1 otherwise.
			 * For non-addition/subtractions that incorporate a shift operation, C is set to the last bit shifted out of the value by the shifter.
			 * For other non-addition/subtractions, C is normally left unchanged (but see the individual instruction descriptions for any special cases).
			 */
			unsigned C : 1;
			/** Is set to 1 if the result of the instruction is zero (which often indicates an equal result from a comparison), and to 0 otherwise. */
			unsigned Z : 1;
			/** Is set to 1 if the result of the instruction is negative, and to 0 otherwise. */
			unsigned N : 1;
		} format;
	} __attribute__((packed));

	enum FlagIndex {
		NF,
		ZF,
		CF,
		VF,
		QF,
		GE,
		DNM,
		IF,
		FF,
		TF,
		MODE,
		FLAG_INDEX_LEN
	};

	class Flags {
	private:
		Flags() {
			reset();
		}

		Flags( Flags& copy ) {
			/** The copy constructor is not allowed. */
		}

	public:
		void print() {
			cout << "------ CPSR ------"   <<  endl;
			cout << "N:   " << flags[NF]   <<  endl;
			cout << "Z:   " << flags[ZF]   <<  endl;
			cout << "C:   " << flags[CF]   <<  endl;
			cout << "V:   " << flags[VF]   <<  endl;
			cout << "Q:   " << flags[QF]   <<  endl;
			cout << "GE:  " << flags[GE]   <<  endl;
			cout << "DNM: " << flags[DNM]  <<  endl;
			cout << "I:   " << flags[IF]   <<  endl;
			cout << "F:   " << flags[FF]   <<  endl;
			cout << "T:   " << flags[TF]   <<  endl;
			cout << "MODE:" << flags[MODE] <<  endl;
			cout << "------------------"   <<  endl;
		}

		inline static Flags& getInstance() {
			static Flags flags;
			return flags;
		}

		inline unsigned& operator[] ( const FlagIndex id ) {
			return flags[id];
		}

		inline const unsigned getValue ( const FlagIndex id ) const {
			return flags[id];
		}

		inline void setValue ( const FlagIndex id, const unsigned value ) {
			flags[id] = value;
		}

		inline void reset() {
			for ( int i = 0; i < FLAG_INDEX_LEN; i++ )
				flags[i] = 0;

			flags[MODE] = USER;
		}

		inline const tCPSRFormat toCPSR() const {
			tCPSRFormat status;
			status.format.N    = flags[NF];
			status.format.Z    = flags[ZF];
			status.format.C    = flags[CF];
			status.format.V    = flags[VF];
			status.format.Q    = flags[QF];
			status.format.GE   = flags[GE];
			status.format.DNM  = flags[DNM];
			status.format.I    = flags[IF];
			status.format.F    = flags[FF];
			status.format.T    = flags[TF];
			status.format.MODE = flags[MODE];
			return status;
		}

	private:
		unsigned flags[FLAG_INDEX_LEN];
	};
}

#endif
