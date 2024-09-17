#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <memory.h>
#include <registers.h>
#include <flags.h>

namespace arm2x {
	struct tParam {
		signed imm24 : 24;
		unsigned shift  :  5;
		unsigned imm12  : 12;
		unsigned imm16  : 16;
		unsigned disp   : 8;
		unsigned rlist  : 16;
		GPRIndex rs, rd, rn, rm;
	};

	typedef bool (*tCondition)();
	typedef void (*tInstruction)(const tParam &param);

	struct tOperation {
		tCondition cond;
		tInstruction inst;
		tParam param;
		uint32_t offset;
	};
};

#endif
