#include "base.h"

int main() {
	vector_t vec1 = create_rv( 3 );
	vector_t vec2 = create_cv( 3 );
	matrix_t mat1 = create_m( 2, 3 );
	matrix_t mat2 = create_m( 3, 2 );

	fill_v( vec1, 5 );
	fill_v( vec2, 5 );
	fill_m( mat1, 4 );

	print_v( vec1 );
	printf("\n");
	print_v( vec2 );
	printf("\n");
	print_m( mat1 );
	
	transpose_m( mat1, mat2 );

	printf("\n");
	print_m( mat1 );
	printf("\n");
	print_m( mat2 );

	release_v( vec1 );
	release_v( vec2 );
	release_m( mat1 );
	release_m( mat2 );

	return 0;
}
