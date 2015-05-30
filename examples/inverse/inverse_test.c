#include "base.h"
#include <stdlib.h>

int main() {
	matrix_t mat = create_m( 2, 2 );
	matrix_t inv = create_m( 2, 2 );

	int i, j;

	for( i=0 ; i < 2 ; ++i )
		for( j=0 ; j < 2 ; ++j )
			put_m( mat, i, j, rand() % 10 );

	print_m( mat );
	inverse_m( mat, inv );
	print_m( inv );

	release_m( mat );
	release_m( inv );

	return 0;
}
