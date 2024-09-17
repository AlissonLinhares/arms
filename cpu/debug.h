#ifndef DEBUG_H
#define DEBUG_H

#include <config.h>

#if DEBUG_ENABLE || ASSERT_ENABLE || SHOW_STATISTICS
	#include <iostream>
	#include <iomanip>
	#include <registers.h>
	#include <flags.h>
	using namespace std;
#endif

#if SINGLE_STEP
	#define STEP cin.get();
#else
	#define STEP
#endif

#if SHOW_REGISTERS
	#define REGISTERS cout \
		<< std::hex << " > r0:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R0]  \
		<< "\t"     <<   " r1:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R1]  \
		<< "\t"     <<   " r2:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R2]  \
		<< "\t"     <<   " r3:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R3]  \
		<< "\n"     << " > r4:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R4]  \
		<< "\t"     <<   " r5:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R5]  \
		<< "\t"     <<   " r6:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R6]  \
		<< "\t"     <<   " r7:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R7]  \
		<< "\n"     << " > r8:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R8]  \
		<< "\t"     <<   " r9:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R9]  \
		<< "\t"     <<   " r10: " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R10] \
		<< "\t"     <<   " r11: " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R11] \
		<< "\n"     << " > r12: " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[R12] \
		<< "\t"     <<   " sp:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[SP]  \
		<< "\t"     <<   " lr:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[LR]  \
		<< "\t"     <<   " pc:  " << "0x" << setfill('0') << setw(8) << Registers::getInstance()[PC]  \
		<< "\n"     << " > cpsr: " << "0x" << setfill('0') << setw(8) << Flags::getInstance().toCPSR().value \
		<< std::dec << endl;
#else
	#define REGISTERS
#endif

#if DEBUG_ENABLE
	#define _LOG( str ) cout << str << endl; REGISTERS STEP
#else
	#define _LOG( str )
#endif

#if ASSERT_ENABLE
	#define _ASSERT( cond, str ) \
	if ( cond ) { \
		cout << __FILE__ << ", " << __LINE__ << ", error: " << str << endl; \
		REGISTERS \
		STEP \
		exit(0); \
	}
#else
	#define _ASSERT( cond, str )
#endif

#if SHOW_STATISTICS
	unsigned long long hits = 0;
	unsigned long long misses = 0;

	#define _PRINT_STATISTICS cout \
		<< "\nCache hits: " << hits \
		<< "\nCache misses: " << misses \
		<< endl;
#else
	#define _PRINT_STATISTICS
#endif

#endif
