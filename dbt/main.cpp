#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "microcode.h"

using namespace std;

#define SYS_exit 93
#define SYS_exit_group 94
#define SYS_getpid 172
#define SYS_kill 129
#define SYS_read 63
#define SYS_write 64
#define SYS_openat 56
#define SYS_close 57
#define SYS_lseek 62
#define SYS_brk 214
#define SYS_linkat 37
#define SYS_unlinkat 35
#define SYS_mkdirat 34
#define SYS_renameat 38
#define SYS_chdir 49
#define SYS_getcwd 17
#define SYS_fstat 80
#define SYS_fstatat 79
#define SYS_faccessat 48
#define SYS_pread 67
#define SYS_pwrite 68
#define SYS_uname 160
#define SYS_getuid 174
#define SYS_geteuid 175
#define SYS_getgid 176
#define SYS_getegid 177
#define SYS_mmap 222
#define SYS_munmap 215
#define SYS_mremap 216
#define SYS_mprotect 226
#define SYS_prlimit64 261
#define SYS_getmainvars 2011
#define SYS_rt_sigaction 134
#define SYS_writev 66
#define SYS_gettimeofday 169
#define SYS_times 153
#define SYS_fcntl 25
#define SYS_ftruncate 46
#define SYS_getdents 61
#define SYS_dup 23
#define SYS_readlinkat 78
#define SYS_rt_sigprocmask 135
#define SYS_ioctl 29
#define SYS_getrlimit 163
#define SYS_setrlimit 164
#define SYS_getrusage 165
#define SYS_clock_gettime 113
#define SYS_set_tid_address 96
#define SYS_set_robust_list 99

int main(int argc, const char *argv[]) {
	uint32_t instruction;

	if (argc < 2)
		cout << "Microcode not found" << endl;
	else if (argc < 3)
		cout << "Index table not found" << endl;
	else if (argc < 4)
		cout << "No ARM raw binary found" << endl;

	Microcode mc(argv[1], argv[2]);

	ifstream file(argv[3]);
	if (!(mc.init() && file.is_open()))
		return 1;

	while( true ) {
		file.read( (char*) &instruction, 4 );

		if ( file.eof() )
			break;

		const vector<uint32_t> *code = mc.decode(instruction);

		for ( uint32_t inst : (*code) ) {
			char* binary = ((char*) &inst);
			cout << binary[0] << binary[1] << binary[2] << binary[3];
		}
	}

	file.close();
	return 0;
}
