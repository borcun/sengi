#include "sg_base.h"
#include <stdlib.h>

int main() {
  sg_matrix mat = create_m( 3, 3 );
  double t1 = 0.0f;
  double *t2 = NULL;
	
  put_m( mat, 0, 0, 1 );
  put_m( mat, 0, 1, 2 );
  put_m( mat, 0, 2, 3 );
  put_m( mat, 1, 0, 0 );
  put_m( mat, 1, 1, 4 );
  put_m( mat, 1, 2, 5 );
  put_m( mat, 2, 0, 1 );
  put_m( mat, 2, 1, 0 );
  put_m( mat, 2, 2, 6 );

  print_m( mat );

  if( trace_m( mat, &t1 ) ) {
    printf( "trace 1 : %lf\n", t1 );
  }
  else {
    printf( "The first trace try failed.\n" );
  }
  
  if( trace_m( mat, t2 ) ) {
    printf( "trace 2 : %lf\n", *t2 );
  }
  else {
    printf( "The second trace try failed.\n" );
  }

  release_m( mat );

  return 0;
}
