#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <dataprocessing.h>
#include <loadstore.h>
#include <eloadstore.h>
#include <multiply.h>
#include <blocktransfer.h>
#include <branch.h>
#include <misc.h>
#include <pusr.h>
#include <conditions.h>
#include <svc.h>
#include <smsud.h>
#include <hints.h>
#include <unordered_map>

#define TOTAL_ARM_INSTRUCTION_FORMATS 14

namespace arm2x {
	class Instructions {
	private:
		struct tGFormat {
			uint32_t mask;
			unordered_map<uint32_t, tInstruction> instructions;

			inline void add( const uint32_t opcode, const tInstruction inst ) {
				instructions[opcode] = inst;
			}
		};
		
	public:
		Instructions() {

			formats = new tGFormat[TOTAL_ARM_INSTRUCTION_FORMATS];
			formats[0].mask = 0b00001111111111111111111111111111;
			formats[0].add(0b00000011001000001111000000000001, _yield);         // cond 0011001000001111000000000001
			formats[0].add(0b00000011001000001111000000000010, _wfe);           // cond 0011001000001111000000000010
			formats[0].add(0b00000011001000001111000000000011, _wfi);           // cond 0011001000001111000000000011

			formats[1].mask = 0b00001111111111111111111111110000;
			formats[1].add(0b00000001001000001111000000000000, _undefined);     // cond 000100100000111100000000 rm
			formats[1].add(0b00000001001001001111000000000000, _msr_g);         // cond 000100100100111100000000 rm
			formats[1].add(0b00000001001010001111000000000000, _msr_w);         // cond 000100101000111100000000 rm
			formats[1].add(0b00000001001011001111000000000000, _msr_wg);        // cond 000100101100111100000000 rm
			formats[1].add(0b00000001001011111111111100010000, _bx);            // cond 000100101111111111110001 rm
			formats[1].add(0b00000001001011111111111100100000, _bxj);           // cond 000100101111111111110010 rm
			formats[1].add(0b00000001001011111111111100110000, _blx);           // cond 000100101111111111110011 rm

			// formats[x].mask = 0b00001111111000000000000001111111;
			// formats[x].add(0b00000111110000000000000000011111, _bfc);           // cond 0111110 imm5  rd   imm5  001 1111
			// formats[x].mask = 0b00001111111000000000000001110000;
			// formats[x].add(0b00000111110000000000000000010000, _bfi);           // cond 0111110 imm5  rd   imm5  001 rn

			formats[2].mask = 0b00001111111000000000000001110000;
			formats[2].add(0b00000110101000000000000001010000, _ssat_asr);      // cond 0110101 imm5  rd   imm5  101 rn
			formats[2].add(0b00000110101000000000000000010000, _ssat_lsl);      // cond 0110101 imm5  rd   imm5  001 rn
			formats[2].add(0b00000110111000000000000001010000, _usat_asr);      // cond 0110111 imm5  rd   imm5  101 rn
			formats[2].add(0b00000110111000000000000000010000, _usat_lsl);      // cond 0110111 imm5  rd   imm5  001 rn

			formats[3].mask = 0b00001111111111110000001111110000;
			formats[3].add(0b00000110100011110000000001110000, _sxtb16);        // cond 011010001111 rd   r2 000111 rm
			formats[3].add(0b00000110101011110000000001110000, _sxtb);          // cond 011010101111 rd   r2 000111 rm
			formats[3].add(0b00000110101111110000000001110000, _sxth);          // cond 011010111111 rd   r2 000111 rm
			formats[3].add(0b00000110110011110000000001110000, _uxtb16);        // cond 011011001111 rd   r2 000111 rm
			formats[3].add(0b00000110111011110000000001110000, _uxtb);          // cond 011011101111 rd   r2 000111 rm
			formats[3].add(0b00000110111111110000000001110000, _uxth);          // cond 011011111111 rd   r2 000111 rm

			formats[4].mask = 0b00001111111100001111000011110000;
			formats[4].add(0b00000111000000001111000000010000, _smuad);         // cond 01110000 rd   1111 rm   0001 rn
			formats[4].add(0b00000111000000001111000000110000, _smuadx);        // cond 01110000 rd   1111 rm   0011 rn
			formats[4].add(0b00000111000000001111000001010000, _smusd);         // cond 01110000 rd   1111 rm   0101 rn
			formats[4].add(0b00000111000000001111000001110000, _smusdx);        // cond 01110000 rd   1111 rm   0111 rn
			formats[4].add(0b00000111000100001111000000010000, _sdiv);          // cond 01110001 rd   1111 rm   0001 rn
			formats[4].add(0b00000111001100001111000000010000, _udiv);          // cond 01110011 rd   1111 rm   0001 rn
			formats[4].add(0b00000111010100001111000000010000, _smmul);         // cond 01110101 rd   1111 rm   0001 rn
			formats[4].add(0b00000111010100001111000000110000, _smmulr);        // cond 01110101 rd   1111 rm   0011 rn

			formats[5].mask = 0b00001111111111111111000000000000;
			formats[5].add(0b00000011001000001111000000000000, _undefined);     // cond 0011001000001111000000000000
			formats[5].add(0b00000011001001001111000000000000, _msr_g_imm);     // cond 0011001001001111000000000000
			formats[5].add(0b00000011001010001111000000000000, _msr_w_imm);     // cond 0011001010001111000000000000
			formats[5].add(0b00000011001011001111000000000000, _msr_wg_imm);    // cond 0011001011001111000000000000

			formats[6].mask = 0b00001111111111110000111111111111;
			formats[6].add(0b00000001000011110000000000000000, _mrs);           // cond 000100001111  rd   000000000000

			formats[7].mask = 0b00001111111111110000111111110000;
			formats[7].add(0b00000110101111110000111100110000, _rev);           // cond 011010111111  rd   11110011 rm
			formats[7].add(0b00000110101111110000111110110000, _rev16);         // cond 011010111111  rd   11111011 rm
			formats[7].add(0b00000110111111110000111100110000, _rbit);          // cond 011011111111  rd   11110011 rm
			formats[7].add(0b00000110111111110000111110110000, _revsh);         // cond 011011111111  rd   11111011 rm
			formats[7].add(0b00000001011011110000111100010000, _clz);           // cond 000101101111  rd   11110001 rm

			formats[8].mask = 0b00001111111100000000001111110000;
			formats[8].add(0b00000110100000000000000001110000, _sxtab16);       // cond 01101000 rn   rd   r2 000111 rm
			formats[8].add(0b00000110101000000000000001110000, _sxtab);         // cond 01101010 rn   rd   r2 000111 rm
			formats[8].add(0b00000110101100000000000001110000, _sxtah);         // cond 01101011 rn   rd   r2 000111 rm
			formats[8].add(0b00000110110000000000000001110000, _uxtab16);       // cond 01101100 rn   rd   r2 000111 rm
			formats[8].add(0b00000110111000000000000001110000, _uxtab);         // cond 01101110 rn   rd   r2 000111 rm
			formats[8].add(0b00000110111100000000000001110000, _uxtah);         // cond 01101111 rn   rd   r2 000111 rm

			formats[9].mask = 0b00001111111100000000000011110000;
			formats[9].add(0b00000000000100000000000010110000, _ldrh);          // cond 00000001 rn   rd   imm4 1011 rm
			formats[9].add(0b00000000000100000000000011010000, _ldrsb);         // cond 00000001 rn   rd   imm4 1101 rm
			formats[9].add(0b00000000000100000000000011110000, _ldrsh);         // cond 00000001 rn   rd   imm4 1111 rm
			formats[9].add(0b00000000000000000000000010110000, _strh);          // cond 00000000 rn   rd   imm4 1011 rm
			formats[9].add(0b00000000000000000000000011010000, _ldrd);          // cond 00000000 rn   rd   imm4 1101 rm
			formats[9].add(0b00000000000000000000000011110000, _strd);          // cond 00000000 rn   rd   imm4 1111 rm
			formats[9].add(0b00000000000000000000000010010000, _mul);           // cond 00000000 rn   rs   rs   1001 rm
			formats[9].add(0b00000000000000000000000000010000, _and_lsl);       // cond 00000000 rn   rd   rs   0001 rm
			formats[9].add(0b00000000000000000000000000110000, _and_lsr);       // cond 00000000 rn   rd   rs   0011 rm
			formats[9].add(0b00000000000000000000000001010000, _and_asr);       // cond 00000000 rn   rd   rs   0101 rm
			formats[9].add(0b00000000000000000000000001110000, _and_ror);       // cond 00000000 rn   rd   rs   0111 rm
			formats[9].add(0b00000000000100000000000000010000, _ands_lsl);      // cond 00000001 rn   rd   rs   0001 rm
			formats[9].add(0b00000000000100000000000000110000, _ands_lsr);      // cond 00000001 rn   rd   rs   0011 rm
			formats[9].add(0b00000000000100000000000001010000, _ands_asr);      // cond 00000001 rn   rd   rs   0101 rm
			formats[9].add(0b00000000000100000000000001110000, _ands_ror);      // cond 00000001 rn   rd   rs   0111 rm
			formats[9].add(0b00000000000100000000000010010000, _muls);          // cond 00000001 rn   rd   rs   1001 rm
			formats[9].add(0b00000000001000000000000000010000, _eor_lsl);       // cond 00000010 rn   rd   rs   0001 rm
			formats[9].add(0b00000000001000000000000000110000, _eor_lsr);       // cond 00000010 rn   rd   rs   0011 rm
			formats[9].add(0b00000000001000000000000001010000, _eor_asr);       // cond 00000010 rn   rd   rs   0101 rm
			formats[9].add(0b00000000001000000000000001110000, _eor_ror);       // cond 00000010 rn   rd   rs   0111 rm
			formats[9].add(0b00000000001000000000000010010000, _mla);           // cond 00000010 rn   rd   rs   1001 rm
			formats[9].add(0b00000000001100000000000000010000, _eors_lsl);      // cond 00000011 rn   rd   rs   0001 rm
			formats[9].add(0b00000000001100000000000000110000, _eors_lsr);      // cond 00000011 rn   rd   rs   0011 rm
			formats[9].add(0b00000000001100000000000001010000, _eors_asr);      // cond 00000011 rn   rd   rs   0101 rm
			formats[9].add(0b00000000001100000000000001110000, _eors_ror);      // cond 00000011 rn   rd   rs   0111 rm
			formats[9].add(0b00000000001100000000000010010000, _mlas);          // cond 00000011 rn   rd   rs   1001 rm
			formats[9].add(0b00000000010000000000000000010000, _sub_lsl);       // cond 00000100 rn   rd   rs   0001 rm
			formats[9].add(0b00000000010000000000000000110000, _sub_lsr);       // cond 00000100 rn   rd   rs   0011 rm
			formats[9].add(0b00000000010000000000000001010000, _sub_asr);       // cond 00000100 rn   rd   rs   0101 rm
			formats[9].add(0b00000000010000000000000001110000, _sub_ror);       // cond 00000100 rn   rd   rs   0111 rm
			formats[9].add(0b00000000010000000000000010010000, _umaal);         // cond 00000100 rn   rs   rs   1001 rm
			formats[9].add(0b00000000010000000000000010110000, _strh_i);        // cond 00000100 rn   rd   imm4 1011 rm
			formats[9].add(0b00000000010000000000000011010000, _ldrd_i);        // cond 00000100 rn   rd   imm4 1101 rm
			formats[9].add(0b00000000010000000000000011110000, _strd_i);        // cond 00000100 rn   rd   imm4 1111 rm
			formats[9].add(0b00000000010100000000000000010000, _subs_lsl);      // cond 00000101 rn   rd   rs   0001 rm
			formats[9].add(0b00000000010100000000000000110000, _subs_lsr);      // cond 00000101 rn   rd   rs   0011 rm
			formats[9].add(0b00000000010100000000000001010000, _subs_asr);      // cond 00000101 rn   rd   rs   0101 rm
			formats[9].add(0b00000000010100000000000001110000, _subs_ror);      // cond 00000101 rn   rd   rs   0111 rm
			formats[9].add(0b00000000010100000000000010110000, _ldrh_i);        // cond 00000101 rn   rd   imm4 1011 rm
			formats[9].add(0b00000000010100000000000011010000, _ldrsb_i);       // cond 00000101 rn   rd   imm4 1101 rm
			formats[9].add(0b00000000010100000000000011110000, _ldrsh_i);       // cond 00000101 rn   rd   imm4 1111 rm
			formats[9].add(0b00000000011000000000000000010000, _rsb_lsl);       // cond 00000110 rn   rd   rs   0001 rm
			formats[9].add(0b00000000011000000000000000110000, _rsb_lsr);       // cond 00000110 rn   rd   rs   0011 rm
			formats[9].add(0b00000000011000000000000001010000, _rsb_asr);       // cond 00000110 rn   rd   rs   0101 rm
			formats[9].add(0b00000000011000000000000001110000, _rsb_ror);       // cond 00000110 rn   rd   rs   0111 rm
			formats[9].add(0b00000000011000000000000010010000, _mls);           // cond 00000110 rn   rd   rs   1001 rm
			formats[9].add(0b00000000011100000000000000010000, _rsbs_lsl);      // cond 00000111 rn   rd   rs   0001 rm
			formats[9].add(0b00000000011100000000000000110000, _rsbs_lsr);      // cond 00000111 rn   rd   rs   0011 rm
			formats[9].add(0b00000000011100000000000001010000, _rsbs_asr);      // cond 00000111 rn   rd   rs   0101 rm
			formats[9].add(0b00000000011100000000000001110000, _rsbs_ror);      // cond 00000111 rn   rd   rs   0111 rm
			formats[9].add(0b00000000100000000000000000010000, _add_lsl);       // cond 00001000 rn   rd   rs   0001 rm
			formats[9].add(0b00000000100000000000000000110000, _add_lsr);       // cond 00001000 rn   rd   rs   0011 rm
			formats[9].add(0b00000000100000000000000001010000, _add_asr);       // cond 00001000 rn   rd   rs   0101 rm
			formats[9].add(0b00000000100000000000000001110000, _add_ror);       // cond 00001000 rn   rd   rs   0111 rm
			formats[9].add(0b00000000100000000000000010010000, _umull);         // cond 00001000 rn   rd   rs   1001 rm
			formats[9].add(0b00000000100000000000000010110000, _strh_u);        // cond 00001000 rn   rd   imm4 1011 rm
			formats[9].add(0b00000000100000000000000011010000, _ldrd_u);        // cond 00001000 rn   rd   imm4 1101 rm
			formats[9].add(0b00000000100000000000000011110000, _strd_u);        // cond 00001000 rn   rd   imm4 1111 rm
			formats[9].add(0b00000000100100000000000000010000, _adds_lsl);      // cond 00001001 rn   rd   rs   0001 rm
			formats[9].add(0b00000000100100000000000000110000, _adds_lsr);      // cond 00001001 rn   rd   rs   0011 rm
			formats[9].add(0b00000000100100000000000001010000, _adds_asr);      // cond 00001001 rn   rd   rs   0101 rm
			formats[9].add(0b00000000100100000000000001110000, _adds_ror);      // cond 00001001 rn   rd   rs   0111 rm
			formats[9].add(0b00000000100100000000000010010000, _umulls);        // cond 00001001 rn   rd   rs   1001 rm
			formats[9].add(0b00000000100100000000000010110000, _ldrh_u);        // cond 00001001 rn   rd   imm4 1011 rm
			formats[9].add(0b00000000100100000000000011010000, _ldrsb_u);       // cond 00001001 rn   rd   imm4 1101 rm
			formats[9].add(0b00000000100100000000000011110000, _ldrsh_u);       // cond 00001001 rn   rd   imm4 1111 rm
			formats[9].add(0b00000000101000000000000000010000, _adc_lsl);       // cond 00001010 rn   rd   rs   0001 rm
			formats[9].add(0b00000000101000000000000000110000, _adc_lsr);       // cond 00001010 rn   rd   rs   0011 rm
			formats[9].add(0b00000000101000000000000001010000, _adc_asr);       // cond 00001010 rn   rd   rs   0101 rm
			formats[9].add(0b00000000101000000000000001110000, _adc_ror);       // cond 00001010 rn   rd   rs   0111 rm
			formats[9].add(0b00000000101000000000000010010000, _umlal);         // cond 00001010 rn   rd   rs   1001 rm
			formats[9].add(0b00000000101100000000000000010000, _adcs_lsl);      // cond 00001011 rn   rd   rs   0001 rm
			formats[9].add(0b00000000101100000000000000110000, _adcs_lsr);      // cond 00001011 rn   rd   rs   0011 rm
			formats[9].add(0b00000000101100000000000001010000, _adcs_asr);      // cond 00001011 rn   rd   rs   0101 rm
			formats[9].add(0b00000000101100000000000001110000, _adcs_ror);      // cond 00001011 rn   rd   rs   0111 rm
			formats[9].add(0b00000000101100000000000010010000, _umlals);        // cond 00001011 rn   rs   rm   1001 rm
			formats[9].add(0b00000000110000000000000000010000, _sbc_lsl);       // cond 00001100 rn   rd   rs   0001 rm
			formats[9].add(0b00000000110000000000000000110000, _sbc_lsr);       // cond 00001100 rn   rd   rs   0011 rm
			formats[9].add(0b00000000110000000000000001010000, _sbc_asr);       // cond 00001100 rn   rd   rs   0101 rm
			formats[9].add(0b00000000110000000000000001110000, _sbc_ror);       // cond 00001100 rn   rd   rs   0111 rm
			formats[9].add(0b00000000110000000000000010010000, _smull);         // cond 00001100 rn   rd   rs   1001 rm
			formats[9].add(0b00000000110000000000000010110000, _strh_iu);       // cond 00001100 rn   rd   imm4 1011 rm
			formats[9].add(0b00000000110000000000000011010000, _ldrd_iu);       // cond 00001100 rn   rd   imm4 1101 rm
			formats[9].add(0b00000000110000000000000011110000, _strd_iu);       // cond 00001100 rn   rd   imm4 1111 rm
			formats[9].add(0b00000000110100000000000000010000, _sbcs_lsl);      // cond 00001101 rn   rd   rs   0001 rm
			formats[9].add(0b00000000110100000000000000110000, _sbcs_lsr);      // cond 00001101 rn   rd   rs   0011 rm
			formats[9].add(0b00000000110100000000000001010000, _sbcs_asr);      // cond 00001101 rn   rd   rs   0101 rm
			formats[9].add(0b00000000110100000000000001110000, _sbcs_ror);      // cond 00001101 rn   rd   rs   0111 rm
			formats[9].add(0b00000000110100000000000010010000, _smulls);        // cond 00001101 rn   rd   rs   1001 rm
			formats[9].add(0b00000000110100000000000010110000, _ldrh_iu);       // cond 00001101 rn   rd   imm4 1011 rm
			formats[9].add(0b00000000110100000000000011010000, _ldrsb_iu);      // cond 00001101 rn   rd   imm4 1101 rm
			formats[9].add(0b00000000110100000000000011110000, _ldrsh_iu);      // cond 00001101 rn   rd   imm4 1111 rm
			formats[9].add(0b00000000111000000000000000010000, _rsc_lsl);       // cond 00001110 rn   rd   rs   0001 rm
			formats[9].add(0b00000000111000000000000000110000, _rsc_lsr);       // cond 00001110 rn   rd   rs   0011 rm
			formats[9].add(0b00000000111000000000000001010000, _rsc_asr);       // cond 00001110 rn   rd   rs   0101 rm
			formats[9].add(0b00000000111000000000000001110000, _rsc_ror);       // cond 00001110 rn   rd   rs   0111 rm
			formats[9].add(0b00000000111000000000000010010000, _smlal);         // cond 00001110 rn   rd   rs   1001 rm
			formats[9].add(0b00000000111100000000000000010000, _rscs_lsl);      // cond 00001111 rn   rd   rs   0001 rm
			formats[9].add(0b00000000111100000000000000110000, _rscs_lsr);      // cond 00001111 rn   rd   rs   0011 rm
			formats[9].add(0b00000000111100000000000001010000, _rscs_asr);      // cond 00001111 rn   rd   rs   0101 rm
			formats[9].add(0b00000000111100000000000001110000, _rscs_ror);      // cond 00001111 rn   rd   rs   0111 rm
			formats[9].add(0b00000000111100000000000010010000, _smlals);        // cond 00001111 rn   rd   rm   1001 rm
			formats[9].add(0b00000001000000000000000010000000, _smlabb);        // cond 00010000 rn   rd   rs   1000 rm
			formats[9].add(0b00000001000000000000000011000000, _smlabt);        // cond 00010000 rn   rd   rs   1100 rm
			formats[9].add(0b00000001000000000000000010100000, _smlatb);        // cond 00010000 rn   rd   rs   1010 rm
			formats[9].add(0b00000001000000000000000011100000, _smlatt);        // cond 00010000 rn   rd   rs   1110 rm
			formats[9].add(0b00000001000000000000000000010000, _tst_lsl);       // cond 00010000 rn   rd   rs   0001 rm
			formats[9].add(0b00000001000000000000000000110000, _tst_lsr);       // cond 00010000 rn   rd   rs   0011 rm
			formats[9].add(0b00000001000000000000000001010000, _tst_asr);       // cond 00010000 rn   rd   rs   0101 rm
			formats[9].add(0b00000001000000000000000001110000, _tst_ror);       // cond 00010000 rn   rd   rs   0111 rm
			formats[9].add(0b00000001000000000000000010110000, _strh_p);        // cond 00010000 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001000000000000000011010000, _ldrd_p);        // cond 00010000 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001000000000000000011110000, _strd_p);        // cond 00010000 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001000100000000000000010000, _tst_lsl);       // cond 00010001 rn   rd   rs   0001 rm
			formats[9].add(0b00000001000100000000000000110000, _tst_lsr);       // cond 00010001 rn   rd   rs   0011 rm
			formats[9].add(0b00000001000100000000000001010000, _tst_asr);       // cond 00010001 rn   rd   rs   0101 rm
			formats[9].add(0b00000001000100000000000001110000, _tst_ror);       // cond 00010001 rn   rd   rs   0111 rm
			formats[9].add(0b00000001000100000000000010110000, _ldrh_p);        // cond 00010001 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001000100000000000011010000, _ldrsb_p);       // cond 00010001 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001000100000000000011110000, _ldrsh_p);       // cond 00010001 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001001000000000000000110000, _teq_lsr);       // cond 00010010 rn   rd   rs   0011 rm
			formats[9].add(0b00000001001000000000000000010000, _teq_lsl);       // cond 00010010 rn   rd   rs   0001 rm
			formats[9].add(0b00000001001000000000000001010000, _teq_asr);       // cond 00010010 rn   rd   rs   0101 rm
			formats[9].add(0b00000001001000000000000001110000, _teq_ror);       // cond 00010010 rn   rd   rs   0111 rm
			formats[9].add(0b00000001001000000000000010110000, _strh_wp);       // cond 00010010 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001001000000000000011010000, _ldrd_wp);       // cond 00010010 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001001000000000000011110000, _strd_wp);       // cond 00010010 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001001100000000000000010000, _teq_lsl);       // cond 00010011 rn   rd   rs   0001 rm
			formats[9].add(0b00000001001100000000000000110000, _teq_lsr);       // cond 00010011 rn   rd   rs   0011 rm
			formats[9].add(0b00000001001100000000000001010000, _teq_asr);       // cond 00010011 rn   rd   rs   0101 rm
			formats[9].add(0b00000001001100000000000001110000, _teq_ror);       // cond 00010011 rn   rd   rs   0111 rm
			formats[9].add(0b00000001001100000000000010110000, _ldrh_wp);       // cond 00010011 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001001100000000000011010000, _ldrsb_wp);      // cond 00010011 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001001100000000000011110000, _ldrsh_wp);      // cond 00010011 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001010000000000000000010000, _cmp_lsl);       // cond 00010100 rn   rd   rs   0001 rm
			formats[9].add(0b00000001010000000000000000110000, _cmp_lsr);       // cond 00010100 rn   rd   rs   0011 rm
			formats[9].add(0b00000001010000000000000001010000, _cmp_asr);       // cond 00010100 rn   rd   rs   0101 rm
			formats[9].add(0b00000001010000000000000001110000, _cmp_ror);       // cond 00010100 rn   rd   rs   0111 rm
			formats[9].add(0b00000001010000000000000010110000, _strh_ip);       // cond 00010100 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001010000000000000011010000, _ldrd_ip);       // cond 00010100 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001010000000000000011110000, _strd_ip);       // cond 00010100 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001010100000000000000010000, _cmp_lsl);       // cond 00010101 rn   rd   rs   0001 rm
			formats[9].add(0b00000001010100000000000000110000, _cmp_lsr);       // cond 00010101 rn   rd   rs   0011 rm
			formats[9].add(0b00000001010100000000000001010000, _cmp_asr);       // cond 00010101 rn   rd   rs   0101 rm
			formats[9].add(0b00000001010100000000000001110000, _cmp_ror);       // cond 00010101 rn   rd   rs   0111 rm
			formats[9].add(0b00000001010100000000000010110000, _ldrh_ip);       // cond 00010101 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001010100000000000011010000, _ldrsb_ip);      // cond 00010101 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001010100000000000011110000, _ldrsh_ip);      // cond 00010101 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001011000000000000000010000, _cmn_lsl);       // cond 00010110 rn   rd   rs   0001 rm
			formats[9].add(0b00000001011000000000000000110000, _cmn_lsr);       // cond 00010110 rn   rd   rs   0011 rm
			formats[9].add(0b00000001011000000000000001010000, _cmn_asr);       // cond 00010110 rn   rd   rs   0101 rm
			formats[9].add(0b00000001011000000000000001110000, _cmn_ror);       // cond 00010110 rn   rd   rs   0111 rm
			formats[9].add(0b00000001011000000000000010110000, _strh_wip);      // cond 00010110 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001011000000000000011010000, _ldrd_wip);      // cond 00010110 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001011000000000000011110000, _strd_wip);      // cond 00010110 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001011100000000000000010000, _cmn_lsl);       // cond 00010111 rn   rd   rs   0001 rm
			formats[9].add(0b00000001011100000000000000110000, _cmn_lsr);       // cond 00010111 rn   rd   rs   0011 rm
			formats[9].add(0b00000001011100000000000001010000, _cmn_asr);       // cond 00010111 rn   rd   rs   0101 rm
			formats[9].add(0b00000001011100000000000001110000, _cmn_ror);       // cond 00010111 rn   rd   rs   0111 rm
			formats[9].add(0b00000001011100000000000010110000, _ldrh_wip);      // cond 00010111 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001011100000000000011010000, _ldrsb_wip);     // cond 00010111 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001011100000000000011110000, _ldrsh_wip);     // cond 00010111 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001100000000000000000010000, _orr_lsl);       // cond 00011000 rn   rd   rs   0001 rm
			formats[9].add(0b00000001100000000000000000110000, _orr_lsr);       // cond 00011000 rn   rd   rs   0011 rm
			formats[9].add(0b00000001100000000000000001010000, _orr_asr);       // cond 00011000 rn   rd   rs   0101 rm
			formats[9].add(0b00000001100000000000000001110000, _orr_ror);       // cond 00011000 rn   rd   rs   0111 rm
			formats[9].add(0b00000001100000000000000010110000, _strh_up);       // cond 00011000 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001100000000000000011010000, _ldrd_up);       // cond 00011000 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001100000000000000011110000, _strd_up);       // cond 00011000 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001100100000000000000010000, _orrs_lsl);      // cond 00011001 rn   rd   rs   0001 rm
			formats[9].add(0b00000001100100000000000001110000, _orrs_ror);      // cond 00011001 rn   rd   rs   0111 rm
			formats[9].add(0b00000001100100000000000001010000, _orrs_asr);      // cond 00011001 rn   rd   rs   0101 rm
			formats[9].add(0b00000001100100000000000000110000, _orrs_lsr);      // cond 00011001 rn   rd   rs   0011 rm
			formats[9].add(0b00000001100100000000000010110000, _ldrh_up);       // cond 00011001 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001100100000000000011010000, _ldrsb_up);      // cond 00011001 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001100100000000000011110000, _ldrsh_up);      // cond 00011001 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001101000000000000000010000, _mov_lsl);       // cond 00011010 rn   rd   rs   0001 rm
			formats[9].add(0b00000001101000000000000000110000, _mov_lsr);       // cond 00011010 rn   rd   rs   0011 rm
			formats[9].add(0b00000001101000000000000001010000, _mov_asr);       // cond 00011010 rn   rd   rs   0101 rm
			formats[9].add(0b00000001101000000000000001110000, _mov_ror);       // cond 00011010 rn   rd   rs   0111 rm
			formats[9].add(0b00000001101000000000000010110000, _strh_wup);      // cond 00011010 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001101000000000000011010000, _ldrd_wup);      // cond 00011010 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001101000000000000011110000, _strd_wup);      // cond 00011010 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001101100000000000000010000, _movs_lsl);      // cond 00011011 rn   rd   rs   0001 rm
			formats[9].add(0b00000001101100000000000000110000, _movs_lsr);      // cond 00011011 rn   rd   rs   0011 rm
			formats[9].add(0b00000001101100000000000001010000, _movs_asr);      // cond 00011011 rn   rd   rs   0101 rm
			formats[9].add(0b00000001101100000000000001110000, _movs_ror);      // cond 00011011 rn   rd   rs   0111 rm
			formats[9].add(0b00000001101100000000000010110000, _ldrh_wup);      // cond 00011011 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001101100000000000011010000, _ldrsb_wup);     // cond 00011011 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001101100000000000011110000, _ldrsh_wup);     // cond 00011011 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001110000000000000000010000, _bic_lsl);       // cond 00011100 rn   rd   rs   0001 rm
			formats[9].add(0b00000001110000000000000000110000, _bic_lsr);       // cond 00011100 rn   rd   rs   0011 rm
			formats[9].add(0b00000001110100000000000000010000, _bics_lsl);      // cond 00011101 rn   rd   rs   0001 rm
			formats[9].add(0b00000001110000000000000001010000, _bic_asr);       // cond 00011100 rn   rd   rs   0101 rm
			formats[9].add(0b00000001110000000000000001110000, _bic_ror);       // cond 00011100 rn   rd   rs   0111 rm
			formats[9].add(0b00000001110000000000000010110000, _strh_iup);      // cond 00011100 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001110000000000000011010000, _ldrd_iup);      // cond 00011100 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001110000000000000011110000, _strd_iup);      // cond 00011100 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001110100000000000000110000, _bics_lsr);      // cond 00011101 rn   rd   rs   0011 rm
			formats[9].add(0b00000001110100000000000001010000, _bics_asr);      // cond 00011101 rn   rd   rs   0101 rm
			formats[9].add(0b00000001110100000000000001110000, _bics_ror);      // cond 00011101 rn   rd   rs   0111 rm
			formats[9].add(0b00000001110100000000000010110000, _ldrh_iup);      // cond 00011101 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001110100000000000011010000, _ldrsb_iup);     // cond 00011101 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001110100000000000011110000, _ldrsh_iup);     // cond 00011101 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001111000000000000000010000, _mvn_lsl);       // cond 00011110 rn   rd   rs   0001 rm
			formats[9].add(0b00000001111000000000000000110000, _mvn_lsr);       // cond 00011110 rn   rd   rs   0011 rm
			formats[9].add(0b00000001111000000000000001010000, _mvn_asr);       // cond 00011110 rn   rd   rs   0101 rm
			formats[9].add(0b00000001111000000000000001110000, _mvn_ror);       // cond 00011110 rn   rd   rs   0111 rm
			formats[9].add(0b00000001111000000000000010110000, _strh_wiup);     // cond 00011110 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001111000000000000011010000, _ldrd_wiup);     // cond 00011110 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001111000000000000011110000, _strd_wiup);     // cond 00011110 rn   rd   imm4 1111 rm
			formats[9].add(0b00000001111100000000000000010000, _mvns_lsl);      // cond 00011111 rn   rd   rs   0001 rm
			formats[9].add(0b00000001111100000000000000110000, _mvns_lsr);      // cond 00011111 rn   rd   rs   0011 rm
			formats[9].add(0b00000001111100000000000001010000, _mvns_asr);      // cond 00011111 rn   rd   rs   0101 rm
			formats[9].add(0b00000001111100000000000001110000, _mvns_ror);      // cond 00011111 rn   rd   rs   0111 rm
			formats[9].add(0b00000001111100000000000010110000, _ldrh_wiup);     // cond 00011111 rn   rd   imm4 1011 rm
			formats[9].add(0b00000001111100000000000011010000, _ldrsb_wiup);    // cond 00011111 rn   rd   imm4 1101 rm
			formats[9].add(0b00000001111100000000000011110000, _ldrsh_wiup);    // cond 00011111 rn   rd   imm4 1111 rm
			formats[9].add(0b00000111000000000000000000010000, _smlad);         // cond 01110000 rn   rd   rs   0001 rm
			formats[9].add(0b00000111000000000000000000110000, _smladx);        // cond 01110000 rn   rd   rs   0011 rm
			formats[9].add(0b00000111000000000000000001010000, _smlsd);         // cond 01110000 rn   rd   rs   0101 rm
			formats[9].add(0b00000111000000000000000001110000, _smlsdx);        // cond 01110000 rn   rd   rs   0111 rm
			formats[9].add(0b00000111010000000000000000010000, _smlald);        // cond 01110100 rn   rd   rs   0001 rm
			formats[9].add(0b00000111010000000000000000110000, _smlaldx);       // cond 01110100 rn   rd   rs   0011 rm
			formats[9].add(0b00000111010000000000000001010000, _smlsld);        // cond 01110100 rn   rd   rs   0101 rm
			formats[9].add(0b00000111010000000000000001110000, _smlsldx);       // cond 01110100 rn   rd   rs   0111 rm
			formats[9].add(0b00000111010100000000000000010000, _smmla);         // cond 01110101 rn   rd   rs   0001 rm
			formats[9].add(0b00000111010100000000000000110000, _smmlar);        // cond 01110101 rn   rd   rs   0011 rm
			formats[9].add(0b00000111010100000000000011010000, _smmls);         // cond 01110101 rn   rd   rs   1101 rm
			formats[9].add(0b00000111010100000000000011110000, _smmlsr);        // cond 01110101 rn   rd   rs   1111 rm

			formats[10].mask = 0b00001111111100000000111111110000;
			formats[10].add(0b00000110111000000000111100110000, _usat16);        // cond 01101110 imm4 rd   11110011 rm
			formats[10].add(0b00000000000000000000000000000000, _and);           // cond 00000000 rn   rd   00000000 rm
			formats[10].add(0b00000000000000000000000000100000, _and);           // cond 00000000 rn   rd   00000010 rm
			formats[10].add(0b00000000000000000000000001000000, _and);           // cond 00000000 rn   rd   00000100 rm
			formats[10].add(0b00000000000000000000000001100000, _and_rrx);       // cond 00000000 rn   rd   00000110 rm
			formats[10].add(0b00000000000100000000000000000000, _ands);          // cond 00000001 rn   rd   00000000 rm
			formats[10].add(0b00000000000100000000000000100000, _ands);          // cond 00000001 rn   rd   00000010 rm
			formats[10].add(0b00000000000100000000000001000000, _ands);          // cond 00000001 rn   rd   00000100 rm
			formats[10].add(0b00000000000100000000000001100000, _ands_rrx);      // cond 00000001 rn   rd   00000110 rm
			formats[10].add(0b00000000001000000000000000000000, _eor);           // cond 00000010 rn   rd   00000000 rm
			formats[10].add(0b00000000001000000000000000100000, _eor);           // cond 00000010 rn   rd   00000010 rm
			formats[10].add(0b00000000001000000000000001000000, _eor);           // cond 00000010 rn   rd   00000100 rm
			formats[10].add(0b00000000001000000000000001100000, _eor_rrx);       // cond 00000010 rn   rd   00000110 rm
			formats[10].add(0b00000000001100000000000000000000, _eors);          // cond 00000011 rn   rd   00000000 rm
			formats[10].add(0b00000000001100000000000000100000, _eors);          // cond 00000011 rn   rd   00000010 rm
			formats[10].add(0b00000000001100000000000001000000, _eors);          // cond 00000011 rn   rd   00000100 rm
			formats[10].add(0b00000000001100000000000001100000, _eors_rrx);      // cond 00000011 rn   rd   00000110 rm
			formats[10].add(0b00000000010000000000000000000000, _sub);           // cond 00000100 rn   rd   00000000 rm
			formats[10].add(0b00000000010000000000000000100000, _sub);           // cond 00000100 rn   rd   00000010 rm
			formats[10].add(0b00000000010000000000000001000000, _sub);           // cond 00000100 rn   rd   00000100 rm
			formats[10].add(0b00000000010000000000000001100000, _sub_rrx);       // cond 00000100 rn   rd   00000110 rm
			formats[10].add(0b00000000010100000000000000000000, _subs);          // cond 00000101 rn   rd   00000000 rm
			formats[10].add(0b00000000010100000000000000100000, _subs);          // cond 00000101 rn   rd   00000010 rm
			formats[10].add(0b00000000010100000000000001000000, _subs);          // cond 00000101 rn   rd   00000100 rm
			formats[10].add(0b00000000010100000000000001100000, _subs_rrx);      // cond 00000101 rn   rd   00000110 rm
			formats[10].add(0b00000000011000000000000000000000, _rsb);           // cond 00000110 rn   rd   00000000 rm
			formats[10].add(0b00000000011000000000000000100000, _rsb);           // cond 00000110 rn   rd   00000010 rm
			formats[10].add(0b00000000011000000000000001000000, _rsb);           // cond 00000110 rn   rd   00000100 rm
			formats[10].add(0b00000000011000000000000001100000, _rsb_rrx);       // cond 00000110 rn   rd   00000110 rm
			formats[10].add(0b00000000011100000000000000000000, _rsbs);          // cond 00000111 rn   rd   00000000 rm
			formats[10].add(0b00000000011100000000000000100000, _rsbs);          // cond 00000111 rn   rd   00000010 rm
			formats[10].add(0b00000000011100000000000001000000, _rsbs);          // cond 00000111 rn   rd   00000100 rm
			formats[10].add(0b00000000011100000000000001100000, _rsbs_rrx);      // cond 00000111 rn   rd   00000110 rm
			formats[10].add(0b00000000100000000000000000000000, _add);           // cond 00001000 rn   rd   00000000 rm
			formats[10].add(0b00000000100000000000000000100000, _add);           // cond 00001000 rn   rd   00000010 rm
			formats[10].add(0b00000000100000000000000001000000, _add);           // cond 00001000 rn   rd   00000100 rm
			formats[10].add(0b00000000100000000000000001100000, _add_rrx);       // cond 00001000 rn   rd   00000110 rm
			formats[10].add(0b00000000100100000000000000000000, _adds);          // cond 00001001 rn   rd   00000000 rm
			formats[10].add(0b00000000100100000000000000100000, _adds);          // cond 00001001 rn   rd   00000010 rm
			formats[10].add(0b00000000100100000000000001000000, _adds);          // cond 00001001 rn   rd   00000100 rm
			formats[10].add(0b00000000100100000000000001100000, _adds_rrx);      // cond 00001001 rn   rd   00000110 rm
			formats[10].add(0b00000000101000000000000000000000, _adc);           // cond 00001010 rn   rd   00000000 rm
			formats[10].add(0b00000000101000000000000000100000, _adc);           // cond 00001010 rn   rd   00000010 rm
			formats[10].add(0b00000000101000000000000001000000, _adc);           // cond 00001010 rn   rd   00000100 rm
			formats[10].add(0b00000000101000000000000001100000, _adc_rrx);       // cond 00001010 rn   rd   00000110 rm
			formats[10].add(0b00000000101100000000000000000000, _adcs);          // cond 00001011 rn   rd   00000000 rm
			formats[10].add(0b00000000101100000000000000100000, _adcs);          // cond 00001011 rn   rd   00000010 rm
			formats[10].add(0b00000000101100000000000001000000, _adcs);          // cond 00001011 rn   rd   00000100 rm
			formats[10].add(0b00000000101100000000000001100000, _adcs_rrx);      // cond 00001011 rn   rd   00000110 rm
			formats[10].add(0b00000000110000000000000000000000, _sbc);           // cond 00001100 rn   rd   00000000 rm
			formats[10].add(0b00000000110000000000000000100000, _sbc);           // cond 00001100 rn   rd   00000010 rm
			formats[10].add(0b00000000110000000000000001000000, _sbc);           // cond 00001100 rn   rd   00000100 rm
			formats[10].add(0b00000000110000000000000001100000, _sbc_rrx);       // cond 00001100 rn   rd   00000110 rm
			formats[10].add(0b00000000110100000000000000000000, _sbcs);          // cond 00001101 rn   rd   00000000 rm
			formats[10].add(0b00000000110100000000000000100000, _sbcs);          // cond 00001101 rn   rd   00000010 rm
			formats[10].add(0b00000000110100000000000001000000, _sbcs);          // cond 00001101 rn   rd   00000100 rm
			formats[10].add(0b00000000110100000000000001100000, _sbcs_rrx);      // cond 00001101 rn   rd   00000110 rm
			formats[10].add(0b00000000111000000000000000000000, _rsc);           // cond 00001110 rn   rd   00000000 rm
			formats[10].add(0b00000000111000000000000000100000, _rsc);           // cond 00001110 rn   rd   00000010 rm
			formats[10].add(0b00000000111000000000000001000000, _rsc);           // cond 00001110 rn   rd   00000100 rm
			formats[10].add(0b00000000111000000000000001100000, _rsc_rrx);       // cond 00001110 rn   rd   00000110 rm
			formats[10].add(0b00000000111100000000000000000000, _rscs);          // cond 00001111 rn   rd   00000000 rm
			formats[10].add(0b00000000111100000000000000100000, _rscs);          // cond 00001111 rn   rd   00000010 rm
			formats[10].add(0b00000000111100000000000001000000, _rscs);          // cond 00001111 rn   rd   00000100 rm
			formats[10].add(0b00000000111100000000000001100000, _rscs_rrx);      // cond 00001111 rn   rd   00000110 rm
			formats[10].add(0b00000001000000000000000000000000, _tst);           // cond 00010000 rn   rd   00000000 rm
			formats[10].add(0b00000001000000000000000000100000, _tst);           // cond 00010000 rn   rd   00000010 rm
			formats[10].add(0b00000001000000000000000001000000, _tst);           // cond 00010000 rn   rd   00000100 rm
			formats[10].add(0b00000001000000000000000001100000, _tst_rrx);       // cond 00010000 rn   rd   00000110 rm
			formats[10].add(0b00000001000100000000000000000000, _tst);           // cond 00010001 rn   rd   00000000 rm
			formats[10].add(0b00000001000100000000000000100000, _tst);           // cond 00010001 rn   rd   00000010 rm
			formats[10].add(0b00000001000100000000000001000000, _tst);           // cond 00010001 rn   rd   00000100 rm
			formats[10].add(0b00000001000100000000000001100000, _tst_rrx);       // cond 00010001 rn   rd   00000110 rm
			formats[10].add(0b00000001001000000000000000000000, _teq);           // cond 00010010 rn   rd   00000000 rm
			formats[10].add(0b00000001001000000000000000100000, _teq);           // cond 00010010 rn   rd   00000010 rm
			formats[10].add(0b00000001001000000000000001000000, _teq);           // cond 00010010 rn   rd   00000100 rm
			formats[10].add(0b00000001001000000000000001100000, _teq_rrx);       // cond 00010010 rn   rd   00000110 rm
			formats[10].add(0b00000001001100000000000000000000, _teq);           // cond 00010011 rn   rd   00000000 rm
			formats[10].add(0b00000001001100000000000000100000, _teq);           // cond 00010011 rn   rd   00000010 rm
			formats[10].add(0b00000001001100000000000001000000, _teq);           // cond 00010011 rn   rd   00000100 rm
			formats[10].add(0b00000001001100000000000001100000, _teq_rrx);       // cond 00010011 rn   rd   00000110 rm
			formats[10].add(0b00000001010000000000000000000000, _cmp);           // cond 00010100 rn   rd   00000000 rm
			formats[10].add(0b00000001010000000000000000100000, _cmp);           // cond 00010100 rn   rd   00000010 rm
			formats[10].add(0b00000001010000000000000001000000, _cmp);           // cond 00010100 rn   rd   00000100 rm
			formats[10].add(0b00000001010000000000000001100000, _cmp_rrx);       // cond 00010100 rn   rd   00000110 rm
			formats[10].add(0b00000001010100000000000000000000, _cmp);           // cond 00010101 rn   rd   00000000 rm
			formats[10].add(0b00000001010100000000000000100000, _cmp);           // cond 00010101 rn   rd   00000010 rm
			formats[10].add(0b00000001010100000000000001000000, _cmp);           // cond 00010101 rn   rd   00000100 rm
			formats[10].add(0b00000001010100000000000001100000, _cmp_rrx);       // cond 00010101 rn   rd   00000110 rm
			formats[10].add(0b00000001011000000000000000000000, _cmn);           // cond 00010110 rn   rd   00000000 rm
			formats[10].add(0b00000001011000000000000000100000, _cmn);           // cond 00010110 rn   rd   00000010 rm
			formats[10].add(0b00000001011000000000000001000000, _cmn);           // cond 00010110 rn   rd   00000100 rm
			formats[10].add(0b00000001011000000000000001100000, _cmn_rrx);       // cond 00010110 rn   rd   00000110 rm
			formats[10].add(0b00000001011100000000000000000000, _cmn);           // cond 00010111 rn   rd   00000000 rm
			formats[10].add(0b00000001011100000000000000100000, _cmn);           // cond 00010111 rn   rd   00000010 rm
			formats[10].add(0b00000001011100000000000001000000, _cmn);           // cond 00010111 rn   rd   00000100 rm
			formats[10].add(0b00000001011100000000000001100000, _cmn_rrx);       // cond 00010111 rn   rd   00000110 rm
			formats[10].add(0b00000001100000000000000000000000, _orr);           // cond 00011000 rn   rd   00000000 rm
			formats[10].add(0b00000001100000000000000000100000, _orr);           // cond 00011000 rn   rd   00000010 rm
			formats[10].add(0b00000001100000000000000001000000, _orr);           // cond 00011000 rn   rd   00000100 rm
			formats[10].add(0b00000001100000000000000001100000, _orr_rrx);       // cond 00011000 rn   rd   00000110 rm
			formats[10].add(0b00000001100100000000000000000000, _orrs);          // cond 00011001 rn   rd   00000000 rm
			formats[10].add(0b00000001100100000000000000100000, _orrs);          // cond 00011001 rn   rd   00000010 rm
			formats[10].add(0b00000001100100000000000001000000, _orrs);          // cond 00011001 rn   rd   00000100 rm
			formats[10].add(0b00000001100100000000000001100000, _orrs_rrx);      // cond 00011001 rn   rd   00000110 rm
			formats[10].add(0b00000001101000000000000000000000, _mov);           // cond 00011010 rn   rd   00000000 rm
			formats[10].add(0b00000001101000000000000000100000, _mov);           // cond 00011010 rn   rd   00000010 rm
			formats[10].add(0b00000001101000000000000001000000, _mov);           // cond 00011010 rn   rd   00000100 rm
			formats[10].add(0b00000001101000000000000001100000, _mov_rrx);       // cond 00011010 rn   rd   00000110 rm
			formats[10].add(0b00000001101100000000000000000000, _movs);          // cond 00011011 rn   rd   00000000 rm
			formats[10].add(0b00000001101100000000000000100000, _movs);          // cond 00011011 rn   rd   00000010 rm
			formats[10].add(0b00000001101100000000000001000000, _movs);          // cond 00011011 rn   rd   00000100 rm
			formats[10].add(0b00000001101100000000000001100000, _movs_rrx);      // cond 00011011 rn   rd   00000110 rm
			formats[10].add(0b00000001110000000000000000000000, _bic);           // cond 00011100 rn   rd   00000000 rm
			formats[10].add(0b00000001110000000000000000100000, _bic);           // cond 00011100 rn   rd   00000010 rm
			formats[10].add(0b00000001110000000000000001000000, _bic);           // cond 00011100 rn   rd   00000100 rm
			formats[10].add(0b00000001110000000000000001100000, _bic_rrx);       // cond 00011100 rn   rd   00000110 rm
			formats[10].add(0b00000001110100000000000000000000, _bics);          // cond 00011101 rn   rd   00000000 rm
			formats[10].add(0b00000001110100000000000000100000, _bics);          // cond 00011101 rn   rd   00000010 rm
			formats[10].add(0b00000001110100000000000001000000, _bics);          // cond 00011101 rn   rd   00000100 rm
			formats[10].add(0b00000001110100000000000001100000, _bics_rrx);      // cond 00011101 rn   rd   00000110 rm
			formats[10].add(0b00000001111000000000000000000000, _mvn);           // cond 00011110 rn   rd   00000000 rm
			formats[10].add(0b00000001111000000000000000100000, _mvn);           // cond 00011110 rn   rd   00000010 rm
			formats[10].add(0b00000001111000000000000001000000, _mvn);           // cond 00011110 rn   rd   00000100 rm
			formats[10].add(0b00000001111000000000000001100000, _mvn_rrx);       // cond 00011110 rn   rd   00000110 rm
			formats[10].add(0b00000001111100000000000000000000, _mvns);          // cond 00011111 rn   rd   00000000 rm
			formats[10].add(0b00000001111100000000000000100000, _mvns);          // cond 00011111 rn   rd   00000010 rm
			formats[10].add(0b00000001111100000000000001000000, _mvns);          // cond 00011111 rn   rd   00000100 rm
			formats[10].add(0b00000001111100000000000001100000, _mvns_rrx);      // cond 00011111 rn   rd   00000110 rm
			formats[10].add(0b00000110000000000000000000000000, _str);           // cond 01100000 rn   rd   00000000 rm
			formats[10].add(0b00000110000000000000000000100000, _str);           // cond 01100000 rn   rd   00000010 rm
			formats[10].add(0b00000110000000000000000001000000, _str);           // cond 01100000 rn   rd   00000100 rm
			formats[10].add(0b00000110000000000000000001100000, _str);           // cond 01100000 rn   rd   00000110 rm
			formats[10].add(0b00000110000100000000000000000000, _ldr);           // cond 01100001 rn   rd   00000000 rm
			formats[10].add(0b00000110000100000000000000100000, _ldr);           // cond 01100001 rn   rd   00000010 rm
			formats[10].add(0b00000110000100000000000001000000, _ldr);           // cond 01100001 rn   rd   00000100 rm
			formats[10].add(0b00000110000100000000000001100000, _ldr);           // cond 01100001 rn   rd   00000110 rm
			formats[10].add(0b00000110010000000000000000000000, _str_b);         // cond 01100100 rn   rd   00000000 rm
			formats[10].add(0b00000110010000000000000000100000, _str_b);         // cond 01100100 rn   rd   00000010 rm
			formats[10].add(0b00000110010000000000000001000000, _str_b);         // cond 01100100 rn   rd   00000100 rm
			formats[10].add(0b00000110010000000000000001100000, _str_b);         // cond 01100100 rn   rd   00000110 rm
			formats[10].add(0b00000110010100000000000000000000, _ldr_b);         // cond 01100101 rn   rd   00000000 rm
			formats[10].add(0b00000110010100000000000000100000, _ldr_b);         // cond 01100101 rn   rd   00000010 rm
			formats[10].add(0b00000110010100000000000001000000, _ldr_b);         // cond 01100101 rn   rd   00000100 rm
			formats[10].add(0b00000110010100000000000001100000, _ldr_b);         // cond 01100101 rn   rd   00000110 rm
			formats[10].add(0b00000110100000000000000000000000, _str_u);         // cond 01101000 rn   rd   00000000 rm
			formats[10].add(0b00000110100000000000000000100000, _str_u);         // cond 01101000 rn   rd   00000010 rm
			formats[10].add(0b00000110100000000000000001000000, _str_u);         // cond 01101000 rn   rd   00000100 rm
			formats[10].add(0b00000110100000000000000001100000, _str_u);         // cond 01101000 rn   rd   00000110 rm
			formats[10].add(0b00000110100100000000000000000000, _ldr_u);         // cond 01101001 rn   rd   00000000 rm
			formats[10].add(0b00000110100100000000000000100000, _ldr_u);         // cond 01101001 rn   rd   00000010 rm
			formats[10].add(0b00000110100100000000000001000000, _ldr_u);         // cond 01101001 rn   rd   00000100 rm
			formats[10].add(0b00000110100100000000000001100000, _ldr_u);         // cond 01101001 rn   rd   00000110 rm
			formats[10].add(0b00000110110000000000000000000000, _str_bu);        // cond 01101100 rn   rd   00000000 rm
			formats[10].add(0b00000110110000000000000000100000, _str_bu);        // cond 01101100 rn   rd   00000010 rm
			formats[10].add(0b00000110110000000000000001000000, _str_bu);        // cond 01101100 rn   rd   00000100 rm
			formats[10].add(0b00000110110000000000000001100000, _str_bu);        // cond 01101100 rn   rd   00000110 rm
			formats[10].add(0b00000110110100000000000000000000, _ldr_bu);        // cond 01101101 rn   rd   00000000 rm
			formats[10].add(0b00000110110100000000000000100000, _ldr_bu);        // cond 01101101 rn   rd   00000010 rm
			formats[10].add(0b00000110110100000000000001000000, _ldr_bu);        // cond 01101101 rn   rd   00000100 rm
			formats[10].add(0b00000110110100000000000001100000, _ldr_bu);        // cond 01101101 rn   rd   00000110 rm
			formats[10].add(0b00000111000000000000000000000000, _str_p);         // cond 01110000 rn   rd   00000000 rm
			formats[10].add(0b00000111000000000000000000100000, _str_p);         // cond 01110000 rn   rd   00000010 rm
			formats[10].add(0b00000111000000000000000001000000, _str_p);         // cond 01110000 rn   rd   00000100 rm
			formats[10].add(0b00000111000000000000000001100000, _str_p);         // cond 01110000 rn   rd   00000110 rm
			formats[10].add(0b00000111000100000000000000000000, _ldr_p);         // cond 01110001 rn   rd   00000000 rm
			formats[10].add(0b00000111000100000000000000100000, _ldr_p);         // cond 01110001 rn   rd   00000010 rm
			formats[10].add(0b00000111000100000000000001000000, _ldr_p);         // cond 01110001 rn   rd   00000100 rm
			formats[10].add(0b00000111000100000000000001100000, _ldr_p);         // cond 01110001 rn   rd   00000110 rm
			formats[10].add(0b00000111001000000000000000000000, _str_wp);        // cond 01110010 rn   rd   00000000 rm
			formats[10].add(0b00000111001000000000000000100000, _str_wp);        // cond 01110010 rn   rd   00000010 rm
			formats[10].add(0b00000111001000000000000001000000, _str_wp);        // cond 01110010 rn   rd   00000100 rm
			formats[10].add(0b00000111001000000000000001100000, _str_wp);        // cond 01110010 rn   rd   00000110 rm
			formats[10].add(0b00000111001100000000000000000000, _ldr_wp);        // cond 01110011 rn   rd   00000000 rm
			formats[10].add(0b00000111001100000000000000100000, _ldr_wp);        // cond 01110011 rn   rd   00000010 rm
			formats[10].add(0b00000111001100000000000001000000, _ldr_wp);        // cond 01110011 rn   rd   00000100 rm
			formats[10].add(0b00000111001100000000000001100000, _ldr_wp);        // cond 01110011 rn   rd   00000110 rm
			formats[10].add(0b00000111010000000000000000000000, _str_bp);        // cond 01110100 rn   rd   00000000 rm
			formats[10].add(0b00000111010000000000000000100000, _str_bp);        // cond 01110100 rn   rd   00000010 rm
			formats[10].add(0b00000111010000000000000001000000, _str_bp);        // cond 01110100 rn   rd   00000100 rm
			formats[10].add(0b00000111010000000000000001100000, _str_bp);        // cond 01110100 rn   rd   00000110 rm
			formats[10].add(0b00000111010100000000000000000000, _ldr_bp);        // cond 01110101 rn   rd   00000000 rm
			formats[10].add(0b00000111010100000000000000100000, _ldr_bp);        // cond 01110101 rn   rd   00000010 rm
			formats[10].add(0b00000111010100000000000001000000, _ldr_bp);        // cond 01110101 rn   rd   00000100 rm
			formats[10].add(0b00000111010100000000000001100000, _ldr_bp);        // cond 01110101 rn   rd   00000110 rm
			formats[10].add(0b00000111011000000000000000000000, _str_wbp);       // cond 01110110 rn   rd   00000000 rm
			formats[10].add(0b00000111011000000000000000100000, _str_wbp);       // cond 01110110 rn   rd   00000010 rm
			formats[10].add(0b00000111011000000000000001000000, _str_wbp);       // cond 01110110 rn   rd   00000100 rm
			formats[10].add(0b00000111011000000000000001100000, _str_wbp);       // cond 01110110 rn   rd   00000110 rm
			formats[10].add(0b00000111011100000000000000000000, _ldr_wbp);       // cond 01110111 rn   rd   00000000 rm
			formats[10].add(0b00000111011100000000000000100000, _ldr_wbp);       // cond 01110111 rn   rd   00000010 rm
			formats[10].add(0b00000111011100000000000001000000, _ldr_wbp);       // cond 01110111 rn   rd   00000100 rm
			formats[10].add(0b00000111011100000000000001100000, _ldr_wbp);       // cond 01110111 rn   rd   00000110 rm
			formats[10].add(0b00000111100000000000000000000000, _str_up);        // cond 01111000 rn   rd   00000000 rm
			formats[10].add(0b00000111100000000000000000100000, _str_up);        // cond 01111000 rn   rd   00000010 rm
			formats[10].add(0b00000111100000000000000001000000, _str_up);        // cond 01111000 rn   rd   00000100 rm
			formats[10].add(0b00000111100000000000000001100000, _str_up);        // cond 01111000 rn   rd   00000110 rm
			formats[10].add(0b00000111100100000000000000000000, _ldr_up);        // cond 01111001 rn   rd   00000000 rm
			formats[10].add(0b00000111100100000000000000100000, _ldr_up);        // cond 01111001 rn   rd   00000010 rm
			formats[10].add(0b00000111100100000000000001000000, _ldr_up);        // cond 01111001 rn   rd   00000100 rm
			formats[10].add(0b00000111100100000000000001100000, _ldr_up);        // cond 01111001 rn   rd   00000110 rm
			formats[10].add(0b00000111101000000000000000000000, _str_wup);       // cond 01111010 rn   rd   00000000 rm
			formats[10].add(0b00000111101000000000000000100000, _str_wup);       // cond 01111010 rn   rd   00000010 rm
			formats[10].add(0b00000111101000000000000001000000, _str_wup);       // cond 01111010 rn   rd   00000100 rm
			formats[10].add(0b00000111101000000000000001100000, _str_wup);       // cond 01111010 rn   rd   00000110 rm
			formats[10].add(0b00000111101100000000000000000000, _ldr_wup);       // cond 01111011 rn   rd   00000000 rm
			formats[10].add(0b00000111101100000000000000100000, _ldr_wup);       // cond 01111011 rn   rd   00000010 rm
			formats[10].add(0b00000111101100000000000001000000, _ldr_wup);       // cond 01111011 rn   rd   00000100 rm
			formats[10].add(0b00000111101100000000000001100000, _ldr_wup);       // cond 01111011 rn   rd   00000110 rm
			formats[10].add(0b00000111110000000000000000000000, _str_bup);       // cond 01111100 rn   rd   00000000 rm
			formats[10].add(0b00000111110000000000000000100000, _str_bup);       // cond 01111100 rn   rd   00000010 rm
			formats[10].add(0b00000111110000000000000001000000, _str_bup);       // cond 01111100 rn   rd   00000100 rm
			formats[10].add(0b00000111110000000000000001100000, _str_bup);       // cond 01111100 rn   rd   00000110 rm
			formats[10].add(0b00000111110100000000000000000000, _ldr_bup);       // cond 01111101 rn   rd   00000000 rm
			formats[10].add(0b00000111110100000000000000100000, _ldr_bup);       // cond 01111101 rn   rd   00000010 rm
			formats[10].add(0b00000111110100000000000001000000, _ldr_bup);       // cond 01111101 rn   rd   00000100 rm
			formats[10].add(0b00000111110100000000000001100000, _ldr_bup);       // cond 01111101 rn   rd   00000110 rm
			formats[10].add(0b00000111111000000000000000000000, _str_wbup);      // cond 01111110 rn   rd   00000000 rm
			formats[10].add(0b00000111111000000000000000100000, _str_wbup);      // cond 01111110 rn   rd   00000010 rm
			formats[10].add(0b00000111111000000000000001000000, _str_wbup);      // cond 01111110 rn   rd   00000100 rm
			formats[10].add(0b00000111111000000000000001100000, _str_wbup);      // cond 01111110 rn   rd   00000110 rm
			formats[10].add(0b00000111111100000000000000000000, _ldr_wbup);      // cond 01111111 rn   rd   00000000 rm
			formats[10].add(0b00000111111100000000000000100000, _ldr_wbup);      // cond 01111111 rn   rd   00000010 rm
			formats[10].add(0b00000111111100000000000001000000, _ldr_wbup);      // cond 01111111 rn   rd   00000100 rm
			formats[10].add(0b00000111111100000000000001100000, _ldr_wbup);      // cond 01111111 rn   rd   00000110 rm
			formats[10].add(0b00000110100000000000111110110000, _sel);           // cond 01101000 rn   rd   11111011 rm
			formats[10].add(0b00000110101000000000111100110000, _ssat16);        // cond 01101010 imm4 rd   11110011 rm

			formats[11].mask = 0b00001111111100000000000001110000;
			formats[11].add(0b00000000000000000000000000000000, _and_lsl_imm);  // cond 00000000 rn   rd   imm5  000 rm
			formats[11].add(0b00000000000000000000000000100000, _and_lsr_imm);  // cond 00000000 rn   rd   imm5  010 rm
			formats[11].add(0b00000000000000000000000001000000, _and_asr_imm);  // cond 00000000 rn   rd   imm5  100 rm
			formats[11].add(0b00000000000000000000000001100000, _and_ror_imm);  // cond 00000000 rn   rd   imm5  110 rm
			formats[11].add(0b00000000000100000000000000000000, _ands_lsl_imm); // cond 00000001 rn   rd   imm5  000 rm
			formats[11].add(0b00000000000100000000000000100000, _ands_lsr_imm); // cond 00000001 rn   rd   imm5  010 rm
			formats[11].add(0b00000000000100000000000001000000, _ands_asr_imm); // cond 00000001 rn   rd   imm5  100 rm
			formats[11].add(0b00000000000100000000000001100000, _ands_ror_imm); // cond 00000001 rn   rd   imm5  110 rm
			formats[11].add(0b00000000001000000000000000000000, _eor_lsl_imm);  // cond 00000010 rn   rd   imm5  000 rm
			formats[11].add(0b00000000001000000000000000100000, _eor_lsr_imm);  // cond 00000010 rn   rd   imm5  010 rm
			formats[11].add(0b00000000001000000000000001000000, _eor_asr_imm);  // cond 00000010 rn   rd   imm5  100 rm
			formats[11].add(0b00000000001000000000000001100000, _eor_ror_imm);  // cond 00000010 rn   rd   imm5  110 rm
			formats[11].add(0b00000000001100000000000000000000, _eors_lsl_imm); // cond 00000011 rn   rd   imm5  000 rm
			formats[11].add(0b00000000001100000000000000100000, _eors_lsr_imm); // cond 00000011 rn   rd   imm5  010 rm
			formats[11].add(0b00000000001100000000000001000000, _eors_asr_imm); // cond 00000011 rn   rd   imm5  100 rm
			formats[11].add(0b00000000001100000000000001100000, _eors_ror_imm); // cond 00000011 rn   rd   imm5  110 rm
			formats[11].add(0b00000000010000000000000000000000, _sub_lsl_imm);  // cond 00000100 rn   rd   imm5  000 rm
			formats[11].add(0b00000000010000000000000000100000, _sub_lsr_imm);  // cond 00000100 rn   rd   imm5  010 rm
			formats[11].add(0b00000000010000000000000001000000, _sub_asr_imm);  // cond 00000100 rn   rd   imm5  100 rm
			formats[11].add(0b00000000010000000000000001100000, _sub_ror_imm);  // cond 00000100 rn   rd   imm5  110 rm
			formats[11].add(0b00000000010100000000000000000000, _subs_lsl_imm); // cond 00000101 rn   rd   imm5  000 rm
			formats[11].add(0b00000000010100000000000000100000, _subs_lsr_imm); // cond 00000101 rn   rd   imm5  010 rm
			formats[11].add(0b00000000010100000000000001000000, _subs_asr_imm); // cond 00000101 rn   rd   imm5  100 rm
			formats[11].add(0b00000000010100000000000001100000, _subs_ror_imm); // cond 00000101 rn   rd   imm5  110 rm
			formats[11].add(0b00000000011000000000000000000000, _rsb_lsl_imm);  // cond 00000110 rn   rd   imm5  000 rm
			formats[11].add(0b00000000011000000000000000100000, _rsb_lsr_imm);  // cond 00000110 rn   rd   imm5  010 rm
			formats[11].add(0b00000000011000000000000001000000, _rsb_asr_imm);  // cond 00000110 rn   rd   imm5  100 rm
			formats[11].add(0b00000000011000000000000001100000, _rsb_ror_imm);  // cond 00000110 rn   rd   imm5  110 rm
			formats[11].add(0b00000000011100000000000000000000, _rsbs_lsl_imm); // cond 00000111 rn   rd   imm5  000 rm
			formats[11].add(0b00000000011100000000000000100000, _rsbs_lsr_imm); // cond 00000111 rn   rd   imm5  010 rm
			formats[11].add(0b00000000011100000000000001000000, _rsbs_asr_imm); // cond 00000111 rn   rd   imm5  100 rm
			formats[11].add(0b00000000011100000000000001100000, _rsbs_ror_imm); // cond 00000111 rn   rd   imm5  110 rm
			formats[11].add(0b00000000100000000000000000000000, _add_lsl_imm);  // cond 00001000 rn   rd   imm5  000 rm
			formats[11].add(0b00000000100000000000000000100000, _add_lsr_imm);  // cond 00001000 rn   rd   imm5  010 rm
			formats[11].add(0b00000000100000000000000001000000, _add_asr_imm);  // cond 00001000 rn   rd   imm5  100 rm
			formats[11].add(0b00000000100000000000000001100000, _add_ror_imm);  // cond 00001000 rn   rd   imm5  110 rm
			formats[11].add(0b00000000100100000000000000000000, _adds_lsl_imm); // cond 00001001 rn   rd   imm5  000 rm
			formats[11].add(0b00000000100100000000000000100000, _adds_lsr_imm); // cond 00001001 rn   rd   imm5  010 rm
			formats[11].add(0b00000000100100000000000001000000, _adds_asr_imm); // cond 00001001 rn   rd   imm5  100 rm
			formats[11].add(0b00000000100100000000000001100000, _adds_ror_imm); // cond 00001001 rn   rd   imm5  110 rm
			formats[11].add(0b00000000101000000000000000000000, _adc_lsl_imm);  // cond 00001010 rn   rd   imm5  000 rm
			formats[11].add(0b00000000101000000000000000100000, _adc_lsr_imm);  // cond 00001010 rn   rd   imm5  010 rm
			formats[11].add(0b00000000101000000000000001000000, _adc_asr_imm);  // cond 00001010 rn   rd   imm5  100 rm
			formats[11].add(0b00000000101000000000000001100000, _adc_ror_imm);  // cond 00001010 rn   rd   imm5  110 rm
			formats[11].add(0b00000000101100000000000000000000, _adcs_lsl_imm); // cond 00001011 rn   rd   imm5  000 rm
			formats[11].add(0b00000000101100000000000000100000, _adcs_lsr_imm); // cond 00001011 rn   rd   imm5  010 rm
			formats[11].add(0b00000000101100000000000001000000, _adcs_asr_imm); // cond 00001011 rn   rd   imm5  100 rm
			formats[11].add(0b00000000101100000000000001100000, _adcs_ror_imm); // cond 00001011 rn   rd   imm5  110 rm
			formats[11].add(0b00000000110000000000000000000000, _sbc_lsl_imm);  // cond 00001100 rn   rd   imm5  000 rm
			formats[11].add(0b00000000110000000000000000100000, _sbc_lsr_imm);  // cond 00001100 rn   rd   imm5  010 rm
			formats[11].add(0b00000000110000000000000001000000, _sbc_asr_imm);  // cond 00001100 rn   rd   imm5  100 rm
			formats[11].add(0b00000000110000000000000001100000, _sbc_ror_imm);  // cond 00001100 rn   rd   imm5  110 rm
			formats[11].add(0b00000000110100000000000000000000, _sbcs_lsl_imm); // cond 00001101 rn   rd   imm5  000 rm
			formats[11].add(0b00000000110100000000000000100000, _sbcs_lsr_imm); // cond 00001101 rn   rd   imm5  010 rm
			formats[11].add(0b00000000110100000000000001000000, _sbcs_asr_imm); // cond 00001101 rn   rd   imm5  100 rm
			formats[11].add(0b00000000110100000000000001100000, _sbcs_ror_imm); // cond 00001101 rn   rd   imm5  110 rm
			formats[11].add(0b00000000111000000000000000000000, _rsc_lsl_imm);  // cond 00001110 rn   rd   imm5  000 rm
			formats[11].add(0b00000000111000000000000000100000, _rsc_lsr_imm);  // cond 00001110 rn   rd   imm5  010 rm
			formats[11].add(0b00000000111000000000000001000000, _rsc_asr_imm);  // cond 00001110 rn   rd   imm5  100 rm
			formats[11].add(0b00000000111000000000000001100000, _rsc_ror_imm);  // cond 00001110 rn   rd   imm5  110 rm
			formats[11].add(0b00000000111100000000000000000000, _rscs_lsl_imm); // cond 00001111 rn   rd   imm5  000 rm
			formats[11].add(0b00000000111100000000000000100000, _rscs_lsr_imm); // cond 00001111 rn   rd   imm5  010 rm
			formats[11].add(0b00000000111100000000000001000000, _rscs_asr_imm); // cond 00001111 rn   rd   imm5  100 rm
			formats[11].add(0b00000000111100000000000001100000, _rscs_ror_imm); // cond 00001111 rn   rd   imm5  110 rm
			formats[11].add(0b00000001000000000000000000000000, _tst_lsl_imm);  // cond 00010000 rn   rd   imm5  000 rm
			formats[11].add(0b00000001000000000000000000100000, _tst_lsr_imm);  // cond 00010000 rn   rd   imm5  010 rm
			formats[11].add(0b00000001000000000000000001000000, _tst_asr_imm);  // cond 00010000 rn   rd   imm5  100 rm
			formats[11].add(0b00000001000000000000000001100000, _tst_ror_imm);  // cond 00010000 rn   rd   imm5  110 rm
			formats[11].add(0b00000001000100000000000000000000, _tst_lsl_imm);  // cond 00010001 rn   rd   imm5  000 rm
			formats[11].add(0b00000001000100000000000000100000, _tst_lsr_imm);  // cond 00010001 rn   rd   imm5  010 rm
			formats[11].add(0b00000001000100000000000001000000, _tst_asr_imm);  // cond 00010001 rn   rd   imm5  100 rm
			formats[11].add(0b00000001000100000000000001100000, _tst_ror_imm);  // cond 00010001 rn   rd   imm5  110 rm
			formats[11].add(0b00000001001000000000000000000000, _teq_lsl_imm);  // cond 00010010 rn   rd   imm5  000 rm
			formats[11].add(0b00000001001000000000000000100000, _teq_lsr_imm);  // cond 00010010 rn   rd   imm5  010 rm
			formats[11].add(0b00000001001000000000000001000000, _teq_asr_imm);  // cond 00010010 rn   rd   imm5  100 rm
			formats[11].add(0b00000001001000000000000001100000, _teq_ror_imm);  // cond 00010010 rn   rd   imm5  110 rm
			formats[11].add(0b00000001001100000000000000000000, _teq_lsl_imm);  // cond 00010011 rn   rd   imm5  000 rm
			formats[11].add(0b00000001001100000000000000100000, _teq_lsr_imm);  // cond 00010011 rn   rd   imm5  010 rm
			formats[11].add(0b00000001001100000000000001000000, _teq_asr_imm);  // cond 00010011 rn   rd   imm5  100 rm
			formats[11].add(0b00000001001100000000000001100000, _teq_ror_imm);  // cond 00010011 rn   rd   imm5  110 rm
			formats[11].add(0b00000001010000000000000000000000, _cmp_lsl_imm);  // cond 00010100 rn   rd   imm5  000 rm
			formats[11].add(0b00000001010000000000000000100000, _cmp_lsr_imm);  // cond 00010100 rn   rd   imm5  010 rm
			formats[11].add(0b00000001010000000000000001000000, _cmp_asr_imm);  // cond 00010100 rn   rd   imm5  100 rm
			formats[11].add(0b00000001010000000000000001100000, _cmp_ror_imm);  // cond 00010100 rn   rd   imm5  110 rm
			formats[11].add(0b00000001010100000000000000000000, _cmp_lsl_imm);  // cond 00010101 rn   rd   imm5  000 rm
			formats[11].add(0b00000001010100000000000000100000, _cmp_lsr_imm);  // cond 00010101 rn   rd   imm5  010 rm
			formats[11].add(0b00000001010100000000000001000000, _cmp_asr_imm);  // cond 00010101 rn   rd   imm5  100 rm
			formats[11].add(0b00000001010100000000000001100000, _cmp_ror_imm);  // cond 00010101 rn   rd   imm5  110 rm
			formats[11].add(0b00000001011000000000000000000000, _cmn_lsl_imm);  // cond 00010110 rn   rd   imm5  000 rm
			formats[11].add(0b00000001011000000000000000100000, _cmn_lsr_imm);  // cond 00010110 rn   rd   imm5  010 rm
			formats[11].add(0b00000001011000000000000001000000, _cmn_asr_imm);  // cond 00010110 rn   rd   imm5  100 rm
			formats[11].add(0b00000001011000000000000001100000, _cmn_ror_imm);  // cond 00010110 rn   rd   imm5  110 rm
			formats[11].add(0b00000001011100000000000000000000, _cmn_lsl_imm);  // cond 00010111 rn   rd   imm5  000 rm
			formats[11].add(0b00000001011100000000000000100000, _cmn_lsr_imm);  // cond 00010111 rn   rd   imm5  010 rm
			formats[11].add(0b00000001011100000000000001000000, _cmn_asr_imm);  // cond 00010111 rn   rd   imm5  100 rm
			formats[11].add(0b00000001011100000000000001100000, _cmn_ror_imm);  // cond 00010111 rn   rd   imm5  110 rm
			formats[11].add(0b00000001100000000000000000000000, _orr_lsl_imm);  // cond 00011000 rn   rd   imm5  000 rm
			formats[11].add(0b00000001100000000000000000100000, _orr_lsr_imm);  // cond 00011000 rn   rd   imm5  010 rm
			formats[11].add(0b00000001100000000000000001000000, _orr_asr_imm);  // cond 00011000 rn   rd   imm5  100 rm
			formats[11].add(0b00000001100000000000000001100000, _orr_ror_imm);  // cond 00011000 rn   rd   imm5  110 rm
			formats[11].add(0b00000001100100000000000000000000, _orrs_lsl_imm); // cond 00011001 rn   rd   imm5  000 rm
			formats[11].add(0b00000001100100000000000000100000, _orrs_lsr_imm); // cond 00011001 rn   rd   imm5  010 rm
			formats[11].add(0b00000001100100000000000001000000, _orrs_asr_imm); // cond 00011001 rn   rd   imm5  100 rm
			formats[11].add(0b00000001100100000000000001100000, _orrs_ror_imm); // cond 00011001 rn   rd   imm5  110 rm
			formats[11].add(0b00000001101000000000000000000000, _mov_lsl_imm);  // cond 00011010 rn   rd   imm5  000 rm
			formats[11].add(0b00000001101000000000000000100000, _mov_lsr_imm);  // cond 00011010 rn   rd   imm5  010 rm
			formats[11].add(0b00000001101000000000000001000000, _mov_asr_imm);  // cond 00011010 rn   rd   imm5  100 rm
			formats[11].add(0b00000001101000000000000001100000, _mov_ror_imm);  // cond 00011010 rn   rd   imm5  110 rm
			formats[11].add(0b00000001101100000000000000000000, _movs_lsl_imm); // cond 00011011 rn   rd   imm5  000 rm
			formats[11].add(0b00000001101100000000000000100000, _movs_lsr_imm); // cond 00011011 rn   rd   imm5  010 rm
			formats[11].add(0b00000001101100000000000001000000, _movs_asr_imm); // cond 00011011 rn   rd   imm5  100 rm
			formats[11].add(0b00000001101100000000000001100000, _movs_ror_imm); // cond 00011011 rn   rd   imm5  110 rm
			formats[11].add(0b00000001110000000000000000000000, _bic_lsl_imm);  // cond 00011100 rn   rd   imm5  000 rm
			formats[11].add(0b00000001110000000000000000100000, _bic_lsr_imm);  // cond 00011100 rn   rd   imm5  010 rm
			formats[11].add(0b00000001110000000000000001000000, _bic_asr_imm);  // cond 00011100 rn   rd   imm5  100 rm
			formats[11].add(0b00000001110000000000000001100000, _bic_ror_imm);  // cond 00011100 rn   rd   imm5  110 rm
			formats[11].add(0b00000001110100000000000000000000, _bics_lsl_imm); // cond 00011101 rn   rd   imm5  000 rm
			formats[11].add(0b00000001110100000000000000100000, _bics_lsr_imm); // cond 00011101 rn   rd   imm5  010 rm
			formats[11].add(0b00000001110100000000000001000000, _bics_asr_imm); // cond 00011101 rn   rd   imm5  100 rm
			formats[11].add(0b00000001110100000000000001100000, _bics_ror_imm); // cond 00011101 rn   rd   imm5  110 rm
			formats[11].add(0b00000001111000000000000000000000, _mvn_lsl_imm);  // cond 00011110 rn   rd   imm5  000 rm
			formats[11].add(0b00000001111000000000000000100000, _mvn_lsr_imm);  // cond 00011110 rn   rd   imm5  010 rm
			formats[11].add(0b00000001111000000000000001000000, _mvn_asr_imm);  // cond 00011110 rn   rd   imm5  100 rm
			formats[11].add(0b00000001111000000000000001100000, _mvn_ror_imm);  // cond 00011110 rn   rd   imm5  110 rm
			formats[11].add(0b00000001111100000000000000000000, _mvns_lsl_imm); // cond 00011111 rn   rd   imm5  000 rm
			formats[11].add(0b00000001111100000000000000100000, _mvns_lsr_imm); // cond 00011111 rn   rd   imm5  010 rm
			formats[11].add(0b00000001111100000000000001000000, _mvns_asr_imm); // cond 00011111 rn   rd   imm5  100 rm
			formats[11].add(0b00000001111100000000000001100000, _mvns_ror_imm); // cond 00011111 rn   rd   imm5  110 rm
			formats[11].add(0b00000110000000000000000000000000, _str_lsl);      // cond 01100000 rn   rd   imm5  000 rm
			formats[11].add(0b00000110000000000000000000100000, _str_lsr);      // cond 01100000 rn   rd   imm5  010 rm
			formats[11].add(0b00000110000000000000000001000000, _str_asr);      // cond 01100000 rn   rd   imm5  100 rm
			formats[11].add(0b00000110000000000000000001100000, _str_ror);      // cond 01100000 rn   rd   imm5  110 rm
			formats[11].add(0b00000110000100000000000000000000, _ldr_lsl);      // cond 01100001 rn   rd   imm5  000 rm
			formats[11].add(0b00000110000100000000000000100000, _ldr_lsr);      // cond 01100001 rn   rd   imm5  010 rm
			formats[11].add(0b00000110000100000000000001000000, _ldr_asr);      // cond 01100001 rn   rd   imm5  100 rm
			formats[11].add(0b00000110000100000000000001100000, _ldr_ror);      // cond 01100001 rn   rd   imm5  110 rm
			formats[11].add(0b00000110010000000000000000000000, _str_b_lsl);    // cond 01100100 rn   rd   imm5  000 rm
			formats[11].add(0b00000110010000000000000000100000, _str_b_lsr);    // cond 01100100 rn   rd   imm5  010 rm
			formats[11].add(0b00000110010000000000000001000000, _str_b_asr);    // cond 01100100 rn   rd   imm5  100 rm
			formats[11].add(0b00000110010000000000000001100000, _str_b_ror);    // cond 01100100 rn   rd   imm5  110 rm
			formats[11].add(0b00000110010100000000000000000000, _ldr_b_lsl);    // cond 01100101 rn   rd   imm5  000 rm
			formats[11].add(0b00000110010100000000000000100000, _ldr_b_lsr);    // cond 01100101 rn   rd   imm5  010 rm
			formats[11].add(0b00000110010100000000000001000000, _ldr_b_asr);    // cond 01100101 rn   rd   imm5  100 rm
			formats[11].add(0b00000110010100000000000001100000, _ldr_b_ror);    // cond 01100101 rn   rd   imm5  110 rm
			formats[11].add(0b00000110100000000000000000000000, _str_u_lsl);    // cond 01101000 rn   rd   imm5  000 rm
			formats[11].add(0b00000110100000000000000000010000, _pkhbt);        // cond 01101000 rn   rd   imm5  001 rm
			formats[11].add(0b00000110100000000000000000100000, _str_u_lsr);    // cond 01101000 rn   rd   imm5  010 rm
			formats[11].add(0b00000110100000000000000001000000, _str_u_asr);    // cond 01101000 rn   rd   imm5  100 rm
			formats[11].add(0b00000110100000000000000001010000, _pkhtb);        // cond 01101000 rn   rd   imm5  101 rm
			formats[11].add(0b00000110100000000000000001100000, _str_u_ror);    // cond 01101000 rn   rd   imm5  110 rm
			formats[11].add(0b00000110100100000000000000000000, _ldr_u_lsl);    // cond 01101001 rn   rd   imm5  000 rm
			formats[11].add(0b00000110100100000000000000100000, _ldr_u_lsr);    // cond 01101001 rn   rd   imm5  010 rm
			formats[11].add(0b00000110100100000000000001000000, _ldr_u_asr);    // cond 01101001 rn   rd   imm5  100 rm
			formats[11].add(0b00000110100100000000000001100000, _ldr_u_ror);    // cond 01101001 rn   rd   imm5  110 rm
			formats[11].add(0b00000110110000000000000000000000, _str_bu_lsl);   // cond 01101100 rn   rd   imm5  000 rm
			formats[11].add(0b00000110110000000000000000100000, _str_bu_lsr);   // cond 01101100 rn   rd   imm5  010 rm
			formats[11].add(0b00000110110000000000000001000000, _str_bu_asr);   // cond 01101100 rn   rd   imm5  100 rm
			formats[11].add(0b00000110110000000000000001100000, _str_bu_ror);   // cond 01101100 rn   rd   imm5  110 rm
			formats[11].add(0b00000110110100000000000000000000, _ldr_bu_lsl);   // cond 01101101 rn   rd   imm5  000 rm
			formats[11].add(0b00000110110100000000000000100000, _ldr_bu_lsr);   // cond 01101101 rn   rd   imm5  010 rm
			formats[11].add(0b00000110110100000000000001000000, _ldr_bu_asr);   // cond 01101101 rn   rd   imm5  100 rm
			formats[11].add(0b00000110110100000000000001100000, _ldr_bu_ror);   // cond 01101101 rn   rd   imm5  110 rm
			formats[11].add(0b00000111000000000000000000000000, _str_p_lsl);    // cond 01110000 rn   rd   imm5  000 rm
			formats[11].add(0b00000111000000000000000000100000, _str_p_lsr);    // cond 01110000 rn   rd   imm5  010 rm
			formats[11].add(0b00000111000000000000000001000000, _str_p_asr);    // cond 01110000 rn   rd   imm5  100 rm
			formats[11].add(0b00000111000000000000000001100000, _str_p_ror);    // cond 01110000 rn   rd   imm5  110 rm
			formats[11].add(0b00000111000100000000000000000000, _ldr_p_lsl);    // cond 01110001 rn   rd   imm5  000 rm
			formats[11].add(0b00000111000100000000000000100000, _ldr_p_lsr);    // cond 01110001 rn   rd   imm5  010 rm
			formats[11].add(0b00000111000100000000000001000000, _ldr_p_asr);    // cond 01110001 rn   rd   imm5  100 rm
			formats[11].add(0b00000111000100000000000001100000, _ldr_p_ror);    // cond 01110001 rn   rd   imm5  110 rm
			formats[11].add(0b00000111001000000000000000000000, _str_wp_lsl);   // cond 01110010 rn   rd   imm5  000 rm
			formats[11].add(0b00000111001000000000000000100000, _str_wp_lsr);   // cond 01110010 rn   rd   imm5  010 rm
			formats[11].add(0b00000111001000000000000001000000, _str_wp_asr);   // cond 01110010 rn   rd   imm5  100 rm
			formats[11].add(0b00000111001000000000000001100000, _str_wp_ror);   // cond 01110010 rn   rd   imm5  110 rm
			formats[11].add(0b00000111001100000000000000000000, _ldr_wp_lsl);   // cond 01110011 rn   rd   imm5  000 rm
			formats[11].add(0b00000111001100000000000000100000, _ldr_wp_lsr);   // cond 01110011 rn   rd   imm5  010 rm
			formats[11].add(0b00000111001100000000000001000000, _ldr_wp_asr);   // cond 01110011 rn   rd   imm5  100 rm
			formats[11].add(0b00000111001100000000000001100000, _ldr_wp_ror);   // cond 01110011 rn   rd   imm5  110 rm
			formats[11].add(0b00000111010000000000000000000000, _str_bp_lsl);   // cond 01110100 rn   rd   imm5  000 rm
			formats[11].add(0b00000111010000000000000000100000, _str_bp_lsr);   // cond 01110100 rn   rd   imm5  010 rm
			formats[11].add(0b00000111010000000000000001000000, _str_bp_asr);   // cond 01110100 rn   rd   imm5  100 rm
			formats[11].add(0b00000111010000000000000001100000, _str_bp_ror);   // cond 01110100 rn   rd   imm5  110 rm
			formats[11].add(0b00000111010100000000000000000000, _ldr_bp_lsl);   // cond 01110101 rn   rd   imm5  000 rm
			formats[11].add(0b00000111010100000000000000100000, _ldr_bp_lsr);   // cond 01110101 rn   rd   imm5  010 rm
			formats[11].add(0b00000111010100000000000001000000, _ldr_bp_asr);   // cond 01110101 rn   rd   imm5  100 rm
			formats[11].add(0b00000111010100000000000001100000, _ldr_bp_ror);   // cond 01110101 rn   rd   imm5  110 rm
			formats[11].add(0b00000111011000000000000000000000, _str_wbp_lsl);  // cond 01110110 rn   rd   imm5  000 rm
			formats[11].add(0b00000111011000000000000000100000, _str_wbp_lsr);  // cond 01110110 rn   rd   imm5  010 rm
			formats[11].add(0b00000111011000000000000001000000, _str_wbp_asr);  // cond 01110110 rn   rd   imm5  100 rm
			formats[11].add(0b00000111011000000000000001100000, _str_wbp_ror);  // cond 01110110 rn   rd   imm5  110 rm
			formats[11].add(0b00000111011100000000000000000000, _ldr_wbp_lsl);  // cond 01110111 rn   rd   imm5  000 rm
			formats[11].add(0b00000111011100000000000000100000, _ldr_wbp_lsr);  // cond 01110111 rn   rd   imm5  010 rm
			formats[11].add(0b00000111011100000000000001000000, _ldr_wbp_asr);  // cond 01110111 rn   rd   imm5  100 rm
			formats[11].add(0b00000111011100000000000001100000, _ldr_wbp_ror);  // cond 01110111 rn   rd   imm5  110 rm
			formats[11].add(0b00000111100000000000000000000000, _str_up_lsl);   // cond 01111000 rn   rd   imm5  000 rm
			formats[11].add(0b00000111100000000000000000100000, _str_up_lsr);   // cond 01111000 rn   rd   imm5  010 rm
			formats[11].add(0b00000111100000000000000001000000, _str_up_asr);   // cond 01111000 rn   rd   imm5  100 rm
			formats[11].add(0b00000111100000000000000001100000, _str_up_ror);   // cond 01111000 rn   rd   imm5  110 rm
			formats[11].add(0b00000111100100000000000000000000, _ldr_up_lsl);   // cond 01111001 rn   rd   imm5  000 rm
			formats[11].add(0b00000111100100000000000000100000, _ldr_up_lsr);   // cond 01111001 rn   rd   imm5  010 rm
			formats[11].add(0b00000111100100000000000001000000, _ldr_up_asr);   // cond 01111001 rn   rd   imm5  100 rm
			formats[11].add(0b00000111100100000000000001100000, _ldr_up_ror);   // cond 01111001 rn   rd   imm5  110 rm
			formats[11].add(0b00000111101000000000000000000000, _str_wup_lsl);  // cond 01111010 rn   rd   imm5  000 rm
			formats[11].add(0b00000111101000000000000000100000, _str_wup_lsr);  // cond 01111010 rn   rd   imm5  010 rm
			formats[11].add(0b00000111101000000000000001000000, _str_wup_asr);  // cond 01111010 rn   rd   imm5  100 rm
			formats[11].add(0b00000111101000000000000001100000, _str_wup_ror);  // cond 01111010 rn   rd   imm5  110 rm
			formats[11].add(0b00000111101100000000000000000000, _ldr_wup_lsl);  // cond 01111011 rn   rd   imm5  000 rm
			formats[11].add(0b00000111101100000000000000100000, _ldr_wup_lsr);  // cond 01111011 rn   rd   imm5  010 rm
			formats[11].add(0b00000111101100000000000001000000, _ldr_wup_asr);  // cond 01111011 rn   rd   imm5  100 rm
			formats[11].add(0b00000111101100000000000001100000, _ldr_wup_ror);  // cond 01111011 rn   rd   imm5  110 rm
			formats[11].add(0b00000111110000000000000000000000, _str_bup_lsl);  // cond 01111100 rn   rd   imm5  000 rm
			formats[11].add(0b00000111110000000000000000100000, _str_bup_lsr);  // cond 01111100 rn   rd   imm5  010 rm
			formats[11].add(0b00000111110000000000000001000000, _str_bup_asr);  // cond 01111100 rn   rd   imm5  100 rm
			formats[11].add(0b00000111110000000000000001100000, _str_bup_ror);  // cond 01111100 rn   rd   imm5  110 rm
			formats[11].add(0b00000111110100000000000000000000, _ldr_bup_lsl);  // cond 01111101 rn   rd   imm5  000 rm
			formats[11].add(0b00000111110100000000000000100000, _ldr_bup_lsr);  // cond 01111101 rn   rd   imm5  010 rm
			formats[11].add(0b00000111110100000000000001000000, _ldr_bup_asr);  // cond 01111101 rn   rd   imm5  100 rm
			formats[11].add(0b00000111110100000000000001100000, _ldr_bup_ror);  // cond 01111101 rn   rd   imm5  110 rm
			formats[11].add(0b00000111111000000000000000000000, _str_wbup_lsl); // cond 01111110 rn   rd   imm5  000 rm
			formats[11].add(0b00000111111000000000000000100000, _str_wbup_lsr); // cond 01111110 rn   rd   imm5  010 rm
			formats[11].add(0b00000111111000000000000001000000, _str_wbup_asr); // cond 01111110 rn   rd   imm5  100 rm
			formats[11].add(0b00000111111000000000000001100000, _str_wbup_ror); // cond 01111110 rn   rd   imm5  110 rm
			formats[11].add(0b00000111111100000000000000000000, _ldr_wbup_lsl); // cond 01111111 rn   rd   imm5  000 rm
			formats[11].add(0b00000111111100000000000000100000, _ldr_wbup_lsr); // cond 01111111 rn   rd   imm5  010 rm
			formats[11].add(0b00000111111100000000000001000000, _ldr_wbup_asr); // cond 01111111 rn   rd   imm5  100 rm
			formats[11].add(0b00000111111100000000000001100000, _ldr_wbup_ror); // cond 01111111 rn   rd   imm5  110 rm

			formats[12].mask = 0b00001111111100000000000000000000;
			formats[12].add(0b00001000000000000000000000000000, _stmda);        // cond 10000000 rn   imm16
			formats[12].add(0b00001000000100000000000000000000, _ldmda);        // cond 10000001 rn   imm16
			formats[12].add(0b00001000001000000000000000000000, _stmda_w);      // cond 10000010 rn   imm16
			formats[12].add(0b00001000001100000000000000000000, _ldmda_w);      // cond 10000011 rn   imm16
			formats[12].add(0b00001000100000000000000000000000, _stm);          // cond 10001000 rn   imm16
			formats[12].add(0b00001000100100000000000000000000, _ldm);          // cond 10001001 rn   imm16
			formats[12].add(0b00001000101000000000000000000000, _stm_w);        // cond 10001010 rn   imm16
			formats[12].add(0b00001000101100000000000000000000, _ldm_w);        // cond 10001011 rn   imm16
			formats[12].add(0b00001001000000000000000000000000, _stmdb);        // cond 10010000 rn   imm16
			formats[12].add(0b00001001000100000000000000000000, _ldmdb);        // cond 10010001 rn   imm16
			formats[12].add(0b00001001001000000000000000000000, _stmdb_w);      // cond 10010010 rn   imm16
			formats[12].add(0b00001001001100000000000000000000, _ldmdb_w);      // cond 10010011 rn   imm16
			formats[12].add(0b00001001100000000000000000000000, _stmib);        // cond 10011000 rn   imm16
			formats[12].add(0b00001001100100000000000000000000, _ldmib);        // cond 10011001 rn   imm16
			formats[12].add(0b00001001101000000000000000000000, _stmib_w);      // cond 10011010 rn   imm16
			formats[12].add(0b00001001101100000000000000000000, _ldmib_w);      // cond 10011011 rn   imm16
			formats[12].add(0b00000010000000000000000000000000, _and_imm);      // cond 00100000 rn   rd   imm12
			formats[12].add(0b00000010000100000000000000000000, _ands_imm);     // cond 00100001 rn   rd   imm12
			formats[12].add(0b00000010001000000000000000000000, _eor_imm);      // cond 00100010 rn   rd   imm12
			formats[12].add(0b00000010001100000000000000000000, _eors_imm);     // cond 00100011 rn   rd   imm12
			formats[12].add(0b00000010010000000000000000000000, _sub_imm);      // cond 00100100 rn   rd   imm12
			formats[12].add(0b00000010010100000000000000000000, _subs_imm);     // cond 00100101 rn   rd   imm12
			formats[12].add(0b00000010011000000000000000000000, _rsb_imm);      // cond 00100110 rn   rd   imm12
			formats[12].add(0b00000010011100000000000000000000, _rsbs_imm);     // cond 00100111 rn   rd   imm12
			formats[12].add(0b00000010100000000000000000000000, _add_imm);      // cond 00101000 rn   rd   imm12
			formats[12].add(0b00000010100100000000000000000000, _adds_imm);     // cond 00101001 rn   rd   imm12
			formats[12].add(0b00000010101000000000000000000000, _adc_imm);      // cond 00101010 rn   rd   imm12
			formats[12].add(0b00000010101100000000000000000000, _adcs_imm);     // cond 00101011 rn   rd   imm12
			formats[12].add(0b00000010110000000000000000000000, _sbc_imm);      // cond 00101100 rn   rd   imm12
			formats[12].add(0b00000010110100000000000000000000, _sbcs_imm);     // cond 00101101 rn   rd   imm12
			formats[12].add(0b00000010111000000000000000000000, _rsc_imm);      // cond 00101110 rn   rd   imm12
			formats[12].add(0b00000010111100000000000000000000, _rscs_imm);     // cond 00101111 rn   rd   imm12
			formats[12].add(0b00000011000000000000000000000000, _movw);         // cond 00110000 imm4 rd   imm12
			formats[12].add(0b00000011000100000000000000000000, _tst_imm);      // cond 00110001 rn   rd   imm12
			formats[12].add(0b00000011001000000000000000000000, _teq_imm);      // cond 00110010 rn   rd   imm12
			formats[12].add(0b00000011001100000000000000000000, _teq_imm);      // cond 00110011 rn   rd   imm12
			formats[12].add(0b00000011010000000000000000000000, _movt);         // cond 00110100 imm4 rd   imm12
			formats[12].add(0b00000011010100000000000000000000, _cmp_imm);      // cond 00110101 rn   rd   imm12
			formats[12].add(0b00000011011000000000000000000000, _cmn_imm);      // cond 00110110 rn   rd   imm12
			formats[12].add(0b00000011011100000000000000000000, _cmn_imm);      // cond 00110111 rn   rd   imm12
			formats[12].add(0b00000011100000000000000000000000, _orr_imm);      // cond 00111000 rn   rd   imm12
			formats[12].add(0b00000011100100000000000000000000, _orrs_imm);     // cond 00111001 rn   rd   imm12
			formats[12].add(0b00000011101000000000000000000000, _mov_imm);      // cond 00111010 rn   rd   imm12
			formats[12].add(0b00000011101100000000000000000000, _movs_imm);     // cond 00111011 rn   rd   imm12
			formats[12].add(0b00000011110000000000000000000000, _bic_imm);      // cond 00111100 rn   rd   imm12
			formats[12].add(0b00000011110100000000000000000000, _bics_imm);     // cond 00111101 rn   rd   imm12
			formats[12].add(0b00000011111000000000000000000000, _mvn_imm);      // cond 00111110 rn   rd   imm12
			formats[12].add(0b00000011111100000000000000000000, _mvns_imm);     // cond 00111111 rn   rd   imm12
			formats[12].add(0b00000100000000000000000000000000, _str_imm);      // cond 01000000 rn   rd   imm12
			formats[12].add(0b00000100000100000000000000000000, _ldr_imm);      // cond 01000001 rn   rd   imm12
			formats[12].add(0b00000100010000000000000000000000, _str_b_imm);    // cond 01000100 rn   rd   imm12
			formats[12].add(0b00000100010100000000000000000000, _ldr_b_imm);    // cond 01000101 rn   rd   imm12
			formats[12].add(0b00000100100000000000000000000000, _str_u_imm);    // cond 01001000 rn   rd   imm12
			formats[12].add(0b00000100100100000000000000000000, _ldr_u_imm);    // cond 01001001 rn   rd   imm12
			formats[12].add(0b00000100110000000000000000000000, _str_bu_imm);   // cond 01001100 rn   rd   imm12
			formats[12].add(0b00000100110100000000000000000000, _ldr_bu_imm);   // cond 01001101 rn   rd   imm12
			formats[12].add(0b00000101000000000000000000000000, _str_p_imm);    // cond 01010000 rn   rd   imm12
			formats[12].add(0b00000101000100000000000000000000, _ldr_p_imm);    // cond 01010001 rn   rd   imm12
			formats[12].add(0b00000101001000000000000000000000, _str_wp_imm);   // cond 01010010 rn   rd   imm12
			formats[12].add(0b00000101001100000000000000000000, _ldr_wp_imm);   // cond 01010011 rn   rd   imm12
			formats[12].add(0b00000101010000000000000000000000, _str_bp_imm);   // cond 01010100 rn   rd   imm12
			formats[12].add(0b00000101010100000000000000000000, _ldr_bp_imm);   // cond 01010101 rn   rd   imm12
			formats[12].add(0b00000101011000000000000000000000, _str_wbp_imm);  // cond 01010110 rn   rd   imm12
			formats[12].add(0b00000101011100000000000000000000, _ldr_wbp_imm);  // cond 01010111 rn   rd   imm12
			formats[12].add(0b00000101100000000000000000000000, _str_up_imm);   // cond 01011000 rn   rd   imm12
			formats[12].add(0b00000101100100000000000000000000, _ldr_up_imm);   // cond 01011001 rn   rd   imm12
			formats[12].add(0b00000101101000000000000000000000, _str_wup_imm);  // cond 01011010 rn   rd   imm12
			formats[12].add(0b00000101101100000000000000000000, _ldr_wup_imm);  // cond 01011011 rn   rd   imm12
			formats[12].add(0b00000101110000000000000000000000, _str_bup_imm);  // cond 01011100 rn   rd   imm12
			formats[12].add(0b00000101110100000000000000000000, _ldr_bup_imm);  // cond 01011101 rn   rd   imm12
			formats[12].add(0b00000101111000000000000000000000, _str_wbup_imm); // cond 01011110 rn   rd   imm12
			formats[12].add(0b00000101111100000000000000000000, _ldr_wbup_imm); // cond 01011111 rn   rd   imm12

			formats[13].mask = 0b00001111000000000000000000000000;
			formats[13].add(0b00001010000000000000000000000000, _b);            // cond 1010 imm24
			formats[13].add(0b00001011000000000000000000000000, _bl);           // cond 1011 imm24
			formats[13].add(0b00001111000000000000000000000000, _svc);          // cond 1111 imm24
		}

		inline const tInstruction find( const uint32_t opcode ) const {
			for ( int i = 0; i < TOTAL_ARM_INSTRUCTION_FORMATS; i++ ) {
				auto instructions = formats[i].instructions;
				auto inst = instructions.find(opcode & formats[i].mask);

				if (inst != instructions.end())
					return inst->second;
			}

			return _undefined;
		}

		~Instructions() {
			delete[] formats;
		}

	private:
		tGFormat* formats;
	};

	tCondition condition[] = {
		_condition_eq,
		_condition_ne,
		_condition_cshs,
		_condition_cclo,
		_condition_mi,
		_condition_pl,
		_condition_vs,
		_condition_vc,
		_condition_hi,
		_condition_ls,
		_condition_ge,
		_condition_lt,
		_condition_gt,
		_condition_le,
		_condition_al,
		_condition_nv
	};
};

#endif
