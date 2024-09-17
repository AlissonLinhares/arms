#include <sys.h>

int fat_it( int n ) {
	int result = 1;

	for ( int i = n; i > 1; i-- )
		result = result * i;

	return result;
}

int fat_rec( int n ) {
	if ( n <= 1 )
		return 1;

	return fat_rec( n - 1 ) * n;
}

int main() {
	int n = read();

	println("\nFactorial sequence:");
	for ( int i = 0; i < n; i++ ) {
		print(i);
		print("! = ");

		int r = fat_it(i);
		if ( r != fat_rec(i) ) {
			println("Execution error");
			return 1;
		}

		println(r);
	}

	return 0;
}
