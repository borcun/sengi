#include "util.h"

int main() {
  vector_t vec;
  matrix_t mat;

  mat = read_m( "mat.dat" );
  vec = read_v( "vec.dat" );

  if( NULL != vec )
    print_v( vec );

  printf( "\n" );
  
  if( NULL != mat )
    print_m( mat );
  
  return 0;
}
