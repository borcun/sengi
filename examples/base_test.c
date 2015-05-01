#include "base.h"

int main() {
  vector_t vec1 = create_rv( 3 );
  vector_t vec2 = create_cv( 3 );
  vector_t vec3 = create_rv( 3 );
  vector_t vec4 = create_rv( 3 );
  vector_t vec5 = create_cv( 3 );
  matrix_t mat1 = create_m( 2, 3 );
  matrix_t mat2 = create_m( 3, 2 );

  fill_v( vec1, 5 );
  fill_v( vec2, 5 );
  fill_m( mat1, 4 );

  to_v( vec3, mat1->data[0] );
  get_row_m( mat1, 1, vec4 );
  
  printf( "vec1\n" );
  print_v( vec1 );
  printf("\nvec2\n");
  print_v( vec2 );
  printf("\nvec3\n");
  print_v( vec3 );
  printf("\nvec4\n");
  print_v( vec4 );
  printf("\nmatrix1\n");
  print_m( mat1 );
	
  transpose_m( mat1, mat2 );
  get_col_m( mat2, 1, vec5 );
  
  printf("matrix2\n");
  print_m( mat2 );
  printf("vec5\n");
  print_v( vec5 );

  release_v( vec1 );
  release_v( vec2 );
  release_v( vec3 );
  release_v( vec4 ); 
  release_v( vec5 );
  release_m( mat1 );
  release_m( mat2 );

  return 0;
}
