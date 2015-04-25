#include "base.h"

int main() {
	vector_t vec = createV( 3 );
	matrix_t mat = createM( 2, 3 );

	fillV( vec, 5 );
	printV( vec );

	releaseV( vec );
	releaseM( mat );

	return 0;
}
