#include "base.h"

int main() {
	vector_t vec1 = create_rv( 3 );
	vector_t vec2 = create_cv( 3 );
	matrix_t mat = create_m( 2, 3 );

	fill_v( vec1, 5 );
	fill_v( vec2, 5 );
	fill_m( mat, 4 );

	print_v( vec1 );
	printf("\n");
	print_v( vec2 );
	printf("\n");
	print_m( mat );
	
	transpose_m( mat );

	printf("\n");
	print_m( mat );

	release_v( vec1 );
	release_v( vec2 );
	release_m( mat );

	return 0;
}
