#include <sys.h>

double pi( int n ) {
	double sum = 0.0;
	int sign = 1;

	for ( int i = 0; i < n; ++i ) {
		sum += sign / ( 2.0 * i + 1.0 );
		sign *= -1;
	}

	return 4.0 * sum;
}

int main() {
	int n = read();

	for ( int i = 0; i < n; i++ ) {
		print( "n == " );
		print( i );
		print( ": " );
		println( (int)(pi(i) * 10000000) );
	}

	return 0;
}
