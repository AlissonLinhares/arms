#ifndef DECODER_H
#define DECODER_H

#include <operations.h>
#include <instructions.h>

namespace arm2x {

#define IMM24_MASK 0b00000000111111111111111111111111
#define IMM16_MASK 0b00000000000000001111111111111111
#define IMM12_MASK 0b00000000000000000000111111111111
#define IMM2_MASK  0b00000000000000000000000000110000
#define SHIFT_MASK 0b00000000000000000000111110000000
#define IMM4L_MASK 0b00000000000011110000000000000000
#define IMM4H_MASK 0b00000000000000000000111100000000
#define RM_MASK    0b00000000000000000000000000001111
#define RS_MASK    0b00000000000000000000111100000000
#define RD_MASK    0b00000000000000001111000000000000
#define RN_MASK    0b00000000000011110000000000000000
#define COND_MASK  0b11110000000000000000000000000000

#define _EXTRACT_IMM4L( OP ) ((OP >> 16) & 0b000000000000000000001111)
#define _EXTRACT_IMM4H( OP ) ((OP >> 8 ) & 0b000000000000000000001111)
#define _EXTRACT_COND( OP )  ((OP >> 28)                             )
#define _EXTRACT_RM( OP )    ((OP      ) & 0b000000000000000000001111)
#define _EXTRACT_RS( OP )    ((OP >> 8 ) & 0b000000000000000000001111)
#define _EXTRACT_RD( OP )    ((OP >> 12) & 0b000000000000000000001111)
#define _EXTRACT_RN( OP )    ((OP >> 16) & 0b000000000000000000001111)
#define _EXTRACT_SHIFT( OP ) ((OP >> 7 ) & 0b000000000000000000011111)
#define _EXTRACT_IMM12( OP ) ((OP      ) & 0b000000000000111111111111)
#define _EXTRACT_IMM16( OP ) ((OP      ) & 0b000000001111111111111111)
#define _EXTRACT_IMM24( OP ) ((OP      ) & 0b111111111111111111111111)

	class Decoder {
	private:
		inline const uint32_t getID( const uint32_t instruction, const uint32_t a, const uint32_t b ) const {
			return (instruction & a) | ((~instruction) & b);
		}

		Decoder() {

		}

		inline const uint32_t rotate( const uint32_t value, const unsigned int n ) const {
			return (value >> n) | (value << (32 - n));
		}

	public:
		inline void decode( tOperation& op, const uint32_t opcode ) const {
			op.param.rd     = (GPRIndex) _EXTRACT_RD(opcode);
			op.param.rn     = (GPRIndex) _EXTRACT_RN(opcode);
			op.param.rm     = (GPRIndex) _EXTRACT_RM(opcode);
			op.param.rs     = (GPRIndex) _EXTRACT_RS(opcode);

			op.param.shift  = _EXTRACT_SHIFT(opcode);
			op.param.imm12  = _EXTRACT_IMM12(opcode);

			op.param.disp   = (_EXTRACT_IMM4H(opcode) << 4) | _EXTRACT_RM(opcode);
			op.param.rlist  = _EXTRACT_IMM16(opcode);
			op.param.imm24  = _EXTRACT_IMM24(opcode);
			op.param.imm16  = _EXTRACT_IMM4L(opcode) << 12 | _EXTRACT_IMM12(opcode);

			op.cond = condition[_EXTRACT_COND(opcode)];
			op.inst = instructions.find(opcode);
		}

		inline static Decoder& getInstance() {
			static Decoder decoder;
			return decoder;
		}
	private:
		Instructions instructions;
	};
};

#endif
