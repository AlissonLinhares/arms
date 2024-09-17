#include <sys.h>

void bubbleSort( int array[], int size ) {
	for ( int i = size - 1; i > 0; --i ) {
		for ( int j = 0; j < i; ++j ) {
			if ( array[j] > array[j + 1] ) {
				int aux = array[j];
				array[j] = array[j + 1];
				array[j + 1] = aux;
			}
		}
	}
}

int main() {
	int size = read();

	if ( size <= 0 )
		return 1;

	int array[size];

	for ( int i = 0; i < size; i++ )
		array[i] = read();

	bubbleSort( array, size );

	for ( int i = 0; i < size; i++ )
		println( array[i] );

	return 0;
}
