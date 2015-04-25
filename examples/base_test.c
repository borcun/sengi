#include "base.h"

int main() {
	vector_t vec = create_v( 3 );
	matrix_t mat = create_m( 2, 3 );

	fill_v( vec, 5 );
	fill_m( mat, 4 );

	print_v( vec );
	printf("\n");
	print_m( mat );

	release_v( vec );
	release_m( mat );

	return 0;
}
