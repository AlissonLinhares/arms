#include <sys.h>

int ack( int i, int j ) {
	if ( i == 0 )
		return j + 1;

	if ( j == 0 )
		return ack(i - 1, 1);

	return ack(i - 1, ack(i, (j - 1)));
}

int main() {
	int n = read();
	int m = read();

	for ( int i = 0; i <= n; i++ ) {
		for ( int j = 0; j <= m; j++ ) {
			print( "ack( " );
			print( i );
			print( ", " );
			print( j );
			print( " ) = " );
			println( ack(i, j) );
		}
	}

	return 0;
}
