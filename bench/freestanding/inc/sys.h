#include <posix.h>

#define DEFAULT_BUFFER_SIZE 80
char NEW_LINE[] = "\n";

int strToInt( char *str ) {
	unsigned int result;
	char sign = (*str == '-') && str++;

	for( result = 0; *str >= '0' && *str <= '9'; str++ )
		result = (result << 3) + (result << 1) + *str - '0';

	if( sign )
		return -result;

	return result;
}

int read() {
	char buffer[DEFAULT_BUFFER_SIZE];

	for ( int i = 0; i < DEFAULT_BUFFER_SIZE; i++ ) {
		_read( 0, buffer + i, 1 );

		if ( buffer[i] == '\n' )
			break;
	}
	
	return strToInt( buffer );
}

void print( const char* str ) {
	int size = 0;
	const char* ptr = str;

	while ( *(ptr++) != 0 )
		size++;

	_write( 1, (char*) str, size );
}

void println( const char* str ) {
	print( str );
	_write( 1, NEW_LINE, 1 );
}

void print( int value ) {
	char buffer[DEFAULT_BUFFER_SIZE];
	int i = DEFAULT_BUFFER_SIZE;

	do {
		buffer[--i] = '0' + (value % 10);
		value = value / 10;
	} while ( i > 0 && value != 0 );

	_write( 1, buffer + i, DEFAULT_BUFFER_SIZE - i );
}

void println( int value ) {
	print( value );
	_write( 1, NEW_LINE, 1 );
}
