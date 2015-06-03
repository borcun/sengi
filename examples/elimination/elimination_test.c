#include "base.h"

int main() {
	matrix_t mat = create_m( 3, 3 );
	matrix_t elim = create_m( 3, 3 );
	
	put_m( mat, 0, 0, 9 );
	put_m( mat, 0, 1, 3 );
	put_m( mat, 0, 2, 4 );
	put_m( mat, 1, 0, 4 );
	put_m( mat, 1, 1, 3 );
	put_m( mat, 1, 2, 4 );
	put_m( mat, 2, 0, 1 );
	put_m( mat, 2, 1, 1 );
	put_m( mat, 2, 2, 1 );

	eliminate_m( mat, elim );
	print_m( elim );

	release_m( mat );
	release_m( elim );

	return 0;
}
