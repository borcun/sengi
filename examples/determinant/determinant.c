#include "base.h"
#include <stdlib.h>

int main() {
  matrix_t mat = create_m( 3, 3 );
  	
  put_m( mat, 0, 0, 1 );
  put_m( mat, 0, 1, 4 );
  put_m( mat, 0, 2, 7 );
  put_m( mat, 1, 0, 3 );
  put_m( mat, 1, 1, 0 );
  put_m( mat, 1, 2, 5 );
  put_m( mat, 2, 0, -1 );
  put_m( mat, 2, 1, 9 );
  put_m( mat, 2, 2, 11 );
  
  print_m( mat );
  printf( "det of mat : %f\n", det( mat ) );

  release_m( mat );
  
  return 0;
}
