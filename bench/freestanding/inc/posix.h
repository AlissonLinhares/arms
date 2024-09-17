#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#undef errno

extern int errno;
char *__env[1] = { 0 };
char **environ = __env;

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

static int stack[80000];

// exit application
extern "C" void _exit( int status ) {
	volatile register int r0 asm("r0") = status;
	volatile register unsigned r7 asm("r7") = SYS_EXIT;
	asm volatile ( "svc #0" : : "r"(r0), "r"(r7) );
	__builtin_unreachable();
}

// Creates a new process by duplicating the calling process.
extern "C" int _fork() {
	_exit(1);
}

// Read from a file descriptor.
extern "C" int _read( int fd, char *buffer, int len ) {
	volatile register int r0 asm("r0") = fd;
	volatile register char* r1 asm("r1") = buffer;
	volatile register int r2 asm("r2") = len;
	volatile register unsigned r7 asm("r7") = SYS_READ;
	asm volatile ( "svc #0" : "=r" (r0) : "r"(r0), "r"(r1), "r"(r2), "r"(r7) : );
	return r0;
}

// Write to a file descriptor.
extern "C" int _write( int fd, char *buffer, int len ) {
	volatile register int r0 asm("r0") = fd;
	volatile register char* r1 asm("r1") = buffer;
	volatile register int r2 asm("r2") = len;
	volatile register unsigned r7 asm("r7") = SYS_WRITE;
	asm volatile ( "svc #0" : "=r" (r0) : "r"(r0), "r"(r1), "r"(r2), "r"(r7) );
	return r0;
}

// Open a file.
extern "C" int _open( const char *path, int flags, int mode ) {
	volatile register const char* r0 asm("r0") = path;
	volatile register int r1 asm("r1") = flags;
	volatile register int r2 asm("r2") = mode;
	volatile register unsigned r7 asm("r7") = SYS_OPEN;
	asm volatile ( "svc #0" : "=r" (r0) : "r"(r0), "r"(r1), "r"(r2), "r"(r7) );
	return *(int*) r0;
}

// Close a file descriptor.
extern "C" int _close( int fd ) {
	volatile register int r0 asm("r0") = fd;
	volatile register unsigned r7 asm("r7") = SYS_CLOSE;
	asm volatile ( "svc #0" : "=r" (r0) : "r"(r0), "r"(r7) );
	return r0;
}

// Wait for a child process.
extern "C" int _wait( int *status ) {
	_exit(1);
}

// Create a new link (directory entry) for the existing file, oldname.
extern "C" int _link( const char *oldPath, const char *newPath ){
	_exit(1);
}

// Delete a name and possibly the file it refers to.
extern "C" int _unlink( char *path ){
	_exit(1);
}

// Executes the program pointed to by filename.
extern "C" int _execve( char *path, char **argv, char **env ){
	_exit(1);
}

// Obtain information about the named file and _write it to the area pointed to by the buf argument.
extern "C" int _fstat( int fd, struct stat *st ) {
	// volatile register int r0 asm("r0") = fd;
	// volatile register struct stat* r1 asm("r1") = st;
	// volatile register unsigned r7 asm("r7") = SYS_FSTAT;
	// asm volatile ( "svc #0" : "=r" (r0) : "r"(r0), "r"(r1), "r"(r7) : "memory" );
	// return r0;
	st->st_mode = S_IFCHR;
	return 0;
}

// Repositions the offset of the open file associated with the file descriptor fd to the argument offset.
extern "C" int _lseek( int fd, int offset, int whence ) {
	volatile register int r0 asm("r0") = fd;
	volatile register int r1 asm("r1") = offset;
	volatile register int r2 asm("r2") = whence;
	volatile register unsigned r7 asm("r7") = SYS_LSEEK;
	asm volatile ( "svc #0" : "=r" (r0) : "r"(r0), "r"(r1), "r"(r2), "r"(r7) );
	return r0;
}

// Shall return the process ID of the calling process.
extern "C" int _getpid() {
	_exit(1);
}

// Generate a SIGALRM signal for the process after the number of realtime seconds specified.
extern "C" unsigned _alarm( unsigned seconds ) {
	_exit(1);
}

// Send signal to a process 
extern "C" int _kill( int pid, int sig ){
	_exit(1);
}

// Stores the current process times in the struct tms.
extern "C" clock_t _times( struct tms *buffer ){
	_exit(1);
}

extern "C" caddr_t _brk( void *addr ) {
	volatile register void* r0 asm("r0") = addr;
	volatile register unsigned r7 asm("r7") = SYS_BRK;
	asm volatile ( "svc #0" : "=r" (r0) : "r"(r0), "r"(r7) );
	return (caddr_t) addr;
}

extern "C" caddr_t _sbrk( int incr ) {
	static caddr_t heap = (caddr_t) stack;

	caddr_t addr = heap;
	heap += incr;

	return addr;
}

// extern "C" caddr_t _sbrk( int incr ) {
// 	static caddr_t heap = 0;
//
// 	if ( (heap == 0) && (( heap = _brk( 0 )) == (caddr_t) -1 ))
// 		_exit(1);
//
// 	caddr_t addr = heap;
// 	heap += incr;
//
// 	if ( _brk( heap ) == (caddr_t) -1 ) {
// 		errno = ENOMEM;
// 		return (caddr_t) -1;
// 	}
//
// 	return addr;
// }

// Returns the time of a day.
extern "C" int _gettimeofday( struct timeval *p, struct timezone *z ) {
	_exit(1);
}

// Suspends the execution of the calling thread until the time specified in seconds has elapsed.
extern "C" int _sleep( unsigned int seconds ) {
	_exit(1);
}

// Check user's permissions for a file.
extern "C" int _access( const char *pathname, int mode ) {
	_exit(1);
}

// The isatty() function tests whether fd is an open file descriptor referring to a terminal.
// obs.: isatty isn't a syscall!
extern "C" int _isatty( int file ) {
	if ( file < 3 )
		return 1;

	errno = EINVAL;
	return 0;
}

extern "C" int main();

extern "C" void _start() {
	volatile register int* sp asm("sp") = &(stack[79990]);
	_exit(main());
}
