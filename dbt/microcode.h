// https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
// http://learning.gem5.org/book/part2/memoryobject.html

#ifndef MICROCODE_H
#define MICROCODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

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

#define _IMM_MASK      0b11111111111111111111000001111111
#define _SHIFT_MASK    0b10000000000000000001000000010111
#define _DISP_MASK     0b10000000000000000010000000010111
#define _IMM12_MASK    0b10000000000000000011000000010111
#define _IMM16_MASK    0b10000000000000000100000000010111
#define _REG_LIST_MASK 0b10000000000000000101000000010111
#define _ADDR_MASK     0b10000000000000000110000000010111

using namespace std;

class Microcode {
private:
	struct tBlock {
		size_t begin;
		size_t end;
		tBlock(size_t begin, size_t end) : begin(begin), end(end) {}
	};

	struct tRV32IM {
		unsigned op   : 7;
		unsigned rd   : 5;
		unsigned func : 3;
		unsigned rs1  : 5;
		unsigned rs2  : 5;
		unsigned imm7 : 7;
	} __attribute__((packed));

	struct tADDI {
		unsigned op   : 7;
		unsigned rd   : 5;
		unsigned func : 3;
		unsigned rs1  : 5;
		unsigned imm  : 12;
		tADDI( unsigned rd, unsigned imm ) : op(0b0010011), rd(rd), func(0), rs1(0), imm(imm) {
			
		}
	} __attribute__((packed));

	struct tLUI {
		unsigned op    : 7;
		unsigned rd    : 5;
		unsigned imm20 : 20;
		tLUI( unsigned rd, unsigned imm ) : op(0b0110111), rd(rd), imm20(imm) {
			
		}
	} __attribute__((packed));

	struct tSRLI {
		unsigned op    : 7;
		unsigned rd    : 5;
		unsigned func  : 3;
		unsigned rs1   : 5;
		unsigned shamt : 5;
		unsigned imm7  : 7;

		tSRLI( unsigned rd, unsigned shamt ) : op(0b0010011), rd(rd), func(5), rs1(rd), shamt(shamt), imm7(0) {
			
		}
	} __attribute__((packed));

	static bool comparator(tBlock *a,tBlock *b) { return a->begin < b->begin; }

public:
	Microcode( const char* cPath, const char* iPath) : iPath(iPath), cPath(cPath) {

	}

	inline bool init() {
		return loadCode(cPath) && loadIndex(iPath);
	}

	inline const vector<uint32_t>* decode(const uint32_t opcode) {
		cache.clear();

		for(auto mask : masks) {
			unordered_map<uint32_t,tBlock*> m = mapping[mask];
			auto inst = m.find(opcode & mask);

			if(inst != m.end())
				return translate(inst->second, opcode);
		}

		return &cache;
	}

	~Microcode() {
		for(auto group : mapping) {
			for(auto block : group.second)
				delete block.second;
			group.second.clear();
		}

		cache.clear();
		mapping.clear();
		delete[] binary;
	}

protected:
	void getFixedImm24( vector<uint32_t>&cache, unsigned dst, uint32_t imm ) {
		tLUI lui(dst, imm >> 4);
		tSRLI srli(dst, 8);
		tADDI addi(dst, imm & 0x1111);
		cache.push_back(*((uint32_t*) &lui));
		cache.push_back(*((uint32_t*) &srli));
		cache.push_back(*((uint32_t*) &addi));
	}

	void getFixedImm20( vector<uint32_t>&cache, unsigned dst, uint32_t imm ) {
		tLUI lui(dst, imm);
		tSRLI srli(dst, 12);
		cache.push_back(*((uint32_t*) &lui));
		cache.push_back(*((uint32_t*) &srli));
	}

	void getFixedImm8( vector<uint32_t>&cache, unsigned dst, uint8_t imm ) {
		tADDI addi(dst, imm);
		cache.push_back(*((uint32_t*) &addi));
	}

	const vector<uint32_t>* translate(const tBlock *block, uint32_t opcode) {
		unsigned rd = _EXTRACT_RD(opcode);
		unsigned rn = _EXTRACT_RN(opcode);
		unsigned rm = _EXTRACT_RM(opcode);
		unsigned rs = _EXTRACT_RS(opcode);

		uint8_t disp   = (_EXTRACT_IMM4H(opcode) << 4) | _EXTRACT_RM(opcode);
		uint8_t shift  = _EXTRACT_SHIFT(opcode);
		uint16_t imm12 = _EXTRACT_IMM12(opcode);
		uint16_t rlist = _EXTRACT_IMM16(opcode);
		uint16_t imm16 = _EXTRACT_IMM4L(opcode) << 12 | _EXTRACT_IMM12(opcode);
		uint32_t imm24 = _EXTRACT_IMM24(opcode);

		for ( unsigned i = block->begin; i < block->end; i++ ) {
			tRV32IM* tmp = (tRV32IM*) &binary[i];

			switch (binary[i] & _IMM_MASK) {
				case _SHIFT_MASK:
					getFixedImm8(cache, getFixedRegister(tmp->rd, rd, rn, rm, rs), shift);
					continue;
				case _DISP_MASK:
					getFixedImm8(cache, getFixedRegister(tmp->rd, rd, rn, rm, rs), disp);
					continue;
				case _IMM12_MASK:
					getFixedImm20(cache, getFixedRegister(tmp->rd, rd, rn, rm, rs), imm12);
					continue;
				case _IMM16_MASK:
					getFixedImm20(cache, getFixedRegister(tmp->rd, rd, rn, rm, rs), imm16);
					continue;
				case _REG_LIST_MASK:
					getFixedImm20(cache, getFixedRegister(tmp->rd, rd, rn, rm, rs), rlist);
					continue;
				case _ADDR_MASK:
					getFixedImm24(cache, getFixedRegister(tmp->rd, rd, rn, rm, rs), imm24);
					continue;
			}
			
			cache.push_back(binary[i]);
			tRV32IM* inst = (tRV32IM*) &cache.back();
			if ( inst->op == 0b0110011 || inst->op == 0b0111011 ) {
				inst->rd  = getFixedRegister(inst->rd, rd, rn, rm, rs);
				inst->rs1 = getFixedRegister(inst->rs1, rd, rn, rm, rs);
				inst->rs2 = getFixedRegister(inst->rs2, rd, rn, rm, rs);
			} else if ( inst->op == 0b1100111 || inst->op == 0b0011011 || inst->op == 0b0000011 || inst->op == 0b0010011 ) {
				inst->rd  = getFixedRegister(inst->rd, rd, rn, rm, rs);
				inst->rs1 = getFixedRegister(inst->rs1, rd, rn, rm, rs);
			} else if ( inst->op == 0b1100011 || inst->op == 0b0100011 ) {
				inst->rs1 = getFixedRegister(inst->rs1, rd, rn, rm, rs);
				inst->rs2 = getFixedRegister(inst->rs2, rd, rn, rm, rs);
			} else if (inst->op == 0b0010111 || inst->op == 0b0110111 || inst->op == 0b1101111) {
				inst->rd  = getFixedRegister(inst->rd, rd, rn, rm, rs);
			}
		}

		return &cache;
	}

	inline unsigned getARMToRISCV( const unsigned id ) {
		switch (id) {
			case 0:  return 10; // x3
			case 1:  return 11; // x4
			case 2:  return 12; // x5
			case 3:  return 13; // x8
			case 4:  return 14; // x9
			case 5:  return 15; // x10
			case 6:  return 16; // x11
			case 7:  return 17; // x12
			case 8:  return 3 ; // x13
			case 9:  return 4 ; // x14
			case 10: return 5 ; // x15
			case 11: return 8 ; // x16
			case 12: return 9 ; // x17
			case 13: return 2 ; // x2
			case 14: return 1 ; // x1
			default: return 18; // x18
		}
	}

	inline unsigned getFixedRegister( const unsigned id, const unsigned rd, const unsigned rn, const unsigned rm, const unsigned rs ) {
		if ( id == 24 )
			return getARMToRISCV(rn);
		else if ( id == 25 )
			return getARMToRISCV(rm);
		else if ( id == 26 )
			return getARMToRISCV(rs);
		else if ( id == 27 )
			return getARMToRISCV(rd);
		
		return id;
	}

private:
	inline bool loadIndex(const char* path) {
		uint64_t baseAddr = -1;
		uint64_t i, j, addr;
		vector<tBlock*> index;
		ifstream file(path);

		if (!file.is_open())
			return false;
		
		while (true) {
			file.read( (char*) &i, 8 );
			file.read( (char*) &j, 8 );
			file.read( (char*) &addr, 8 );

			if (file.eof())
				break;

			if (masks.size() == 0 || masks.back() != i)
				masks.push_back(i);

			tBlock* block = new tBlock(addr, 0);
			mapping[i][j] = block;
			index.push_back(block);
			if (addr < baseAddr)
				baseAddr = addr;
		}

		sort(index.begin(), index.end(), comparator);

		index[index.size() - 1]->end = binSize;

		for ( int i = index.size() - 1; i > 0; i-- ) {
			if ( index[i-1]->begin == index[i]->begin ) {
				index[i]->begin = (index[i]->begin - baseAddr)/4;
				index[i-1]->end = index[i]->end;
			} else {
				index[i]->begin = (index[i]->begin - baseAddr)/4;
				index[i-1]->end = index[i]->begin;
			}
		}

		index[0]->begin = (index[0]->begin - baseAddr) / 4;

		index.clear();
		file.close();
		return true;
	}

	inline bool loadCode(const char* path) {
		ifstream file(path);

		if (!file.is_open())
			return false;

		file.seekg (0, ios::end);
		this->binSize = file.tellg() / 4;
		binary = new uint32_t[binSize];

		file.seekg (0, ios::beg);
		for ( unsigned i = 0; i < binSize; i++ )
			file.read( (char*) &(binary[i]), 4 );

		file.close();
		return true;
	}

private:
	size_t binSize;
	uint32_t* binary;
	vector<uint32_t> cache;
	vector<uint32_t> masks;
	unordered_map<uint32_t,unordered_map<uint32_t,tBlock*>> mapping;
	const char* iPath;
	const char* cPath;
};

#endif
