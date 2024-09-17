#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/cdefs.h>
#include <unistd.h>
#include <time.h>
#include <registers.h>
#include <memory.h>

#ifndef SDISPATCH_H
#define SDISPATCH_H

// https://w3challs.com/syscalls/?arch=arm_strong
#define SYS_RESTART      0x0
#define SYS_EXIT         0x1
#define SYS_FORK         0x2
#define SYS_READ         0x3
#define SYS_WRITE        0x4
#define SYS_OPEN         0x5
#define SYS_CLOSE        0x6
#define SYS_WAIT         0x7
#define SYS_CREAT        0x8
#define SYS_LINK         0x9
#define SYS_UNLINK       0xA
#define SYS_EXECVE       0xB
#define SYS_CHDIR        0xC
#define SYS_MKNOD        0xE
#define SYS_CHMOD        0xF
#define SYS_LCHOW        0x10
#define SYS_STAT         0x12
#define SYS_LSEEK        0x13
#define SYS_GETPID       0x14
#define SYS_ALARM        0x1B
#define SYS_FSTAT        0x6C
#define SYS_KILL         0x25
#define SYS_TIMES        0x2B
#define SYS_BRK          0x2D
#define SYS_GETTIMEOFDAY 0x4E
#define SYS_SLEEP        0xA2
#define SYS_ACCESS       0x21
#define SYS_UNAME        0x7a

namespace arm2x {
	using namespace std;

	struct ARMStat {
		uint32_t dev;
		uint32_t ino;
		uint32_t mode;
		uint32_t nlink;
		uint32_t uid;
		uint32_t gid;
		uint32_t rdev;
		uint32_t size;
		uint32_t blksize;
		uint32_t blocks;
		uint32_t atime;
		uint32_t mtime;
		uint32_t ctime;
	} __attribute__((packed));

	inline const uint32_t _uname( char* output ) {
		const char* data = "Linuxbender4.9.0-3-amd64#1 SMP Debian 4.9.30-2+deb9u5 (2017-09-19)armv7l(none)\0";

		while( data != 0 )
			*(output++) = *(data++);
	}

	inline const uint32_t _fstat( const uint32_t fd, char *offset ) {
		struct stat src;
		uint32_t result = fstat( fd, &src );

		ARMStat* tgt = (ARMStat*)(offset);
		tgt->dev      = src.st_dev;
		tgt->ino      = src.st_ino;
		tgt->mode     = src.st_mode;
		tgt->nlink    = src.st_nlink;
		tgt->uid      = src.st_uid;
		tgt->gid      = src.st_gid;
		tgt->rdev     = src.st_rdev;
		tgt->size     = src.st_size;
		tgt->blksize  = src.st_blksize;
		tgt->blocks   = src.st_blocks;
		tgt->atime    = src.st_atime;
		tgt->mtime    = src.st_mtime;
		tgt->ctime    = src.st_ctime;
		return result;
	}

	_INSTRUCTION( _svc )
		Registers& registers = Registers::getInstance();
		char* offset = Memory::getInstance().getMemoryOffset();

		switch ( registers[R7] ) {
			case SYS_EXIT:
				_LOG( "swi #0x0" );
				_PRINT_STATISTICS;
				exit( registers[R0] );
				break;
			case SYS_READ:
				registers[R0] = read( registers[R0], offset + registers[R1], registers[R2] );
				break;
			case SYS_WRITE:
				registers[R0] = write( registers[R0], offset + registers[R1], registers[R2] );
				break;
			case SYS_OPEN:
				registers[R0] = open( offset + registers[R0], registers[R1], registers[R2] );
				break;
			case SYS_CLOSE:
				registers[R0] = close( registers[R0] );
				break;
			case SYS_FSTAT:
				registers[R0] = _fstat( registers[R0], offset + registers[R1] );
				break;
			case SYS_BRK:
				registers[R0] = Memory::getInstance().brk( registers[R0] );
				break;
			case SYS_UNAME:
				_uname( offset + registers[R0] );
				break;
			default:
				_ASSERT( true, "Unsupported syscall: #" << registers[R7] );
		}
	_END
}

#endif
