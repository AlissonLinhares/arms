#include <sys.h>

int fib( int n ) {
	if ( n <= 1 )
		return 1;

	return fib( n - 1) + fib( n - 2 );
}

int main() {
	int n = read();

	println("Fibonacci sequence:");
	for ( int i = 0; i < n; i++ ) {
		print("fib(");
		print(i);
		print(") = ");
		println(fib(i));
	}

	return 0;
}
