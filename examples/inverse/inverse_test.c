#include "base.h"
#include <stdlib.h>

int main() {
	matrix_t mat = create_m( 3, 3 );
	matrix_t inv = create_m( 3, 3 );
	
	put_m( mat, 0, 0, 1 );
	put_m( mat, 0, 1, 2 );
	put_m( mat, 0, 2, 3 );
	put_m( mat, 1, 0, 0 );
	put_m( mat, 1, 1, 4 );
	put_m( mat, 1, 2, 5 );
	put_m( mat, 2, 0, 1 );
	put_m( mat, 2, 1, 0 );
	put_m( mat, 2, 2, 6 );

	inverse_m( mat, inv );
	print_m( inv );

	release_m( mat );
	release_m( inv );

	return 0;
}
