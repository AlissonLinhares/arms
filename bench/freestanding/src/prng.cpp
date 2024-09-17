#include <sys.h>

unsigned int prng() {
	static unsigned int seed = 5323;
	seed = (8253729 * seed + 2396403);
	return seed  % 32767;
}

int main() {
	int n = read();
	for (int i=0; i < n; ++i) {
		println(prng());
	}
}
