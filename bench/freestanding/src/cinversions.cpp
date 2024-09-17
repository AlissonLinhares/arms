#include <sys.h>

using namespace std;

long long nInversions = 0;

void merge( int* array, int size, int center, int* result ) {
	const int* left  = array;
	const int lsize  = center;
	const int* right = array + center;
	const int rsize  = size  - center;

	int i = 0;
	int j = 0;
	int k = 0;

	while ( i < lsize && j < rsize ) {
		if ( left[i] <= right[j] ) {
			result[k++] = left[i++];
		} else {
			nInversions += lsize - i;
			result[k++] = right[j++];
		}
	}

	while ( i < lsize )
		result[k++] = left[i++];

	while ( j < rsize )
		result[k++] = right[j++];

	for ( int z = 0; z < size; z++ )
		array[z] = result[z];
}

void mergeSort( int* array, int size, int* result ) {
	int center = size / 2;

	if ( center == 0 )
		return;

	mergeSort( array         , center, result );
	mergeSort( array + center, size - center, result );

	merge( array, size, center, result );
}

int main(){
	int t = read();

	for(int a0 = 0; a0 < t; a0++){
		int n = read();

		int *array  = new int[n];
		int *buffer = new int[n];

		for(int arr_i = 0;arr_i < n;arr_i++)
			array[arr_i] = read();

		nInversions = 0;
		mergeSort(array, n, buffer);
		println(nInversions);

		delete[] array;
		delete[] buffer;
	}

	return 0;
}
