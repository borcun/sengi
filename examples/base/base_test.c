#include "sg_base.h"

int main() {
  sg_vector vec1 = create_rv( 3 );
  sg_vector vec2 = create_cv( 3 );
  sg_vector vec3 = create_rv( 3 );
  sg_vector vec4 = create_rv( 3 );
  sg_vector vec5 = create_cv( 3 );
  sg_vector vec6 = create_rv( 3 );
  sg_vector vec7 = create_rv( 3 );
  sg_vector vec8 = create_cv( 2 );
  sg_vector vec9 = create_cv( 3 );
  sg_vector vec10 = create_rv( 2 );
  sg_vector vec11 = create_rv( 3 );
  sg_matrix mat1 = create_m( 2, 3 );
  sg_matrix mat2 = create_m( 3, 2 );
  sg_matrix mat3 = create_m( 3, 2 );
  sg_matrix mat4 = create_m( 3, 2 );
  sg_matrix mat5 = create_m( 3, 2 );
  sg_matrix mat6 = create_m( 2, 2 );
  double res;

  // fill row vector vec1 with 5
  fill_v( vec1, 5.0 );
  // fill column vector vec2 with 6
  fill_v( vec2, 6.0 );
  // fill column vector vec8 with 10
  fill_v( vec8, 10.0 );
  // fill column vector vec10 with 10
  fill_v( vec10, 10.0 );
  // fill matrix mat1 with 4
  fill_m( mat1, 4 );
  // fill column vector vec3 with any array
  to_v( vec3, mat1.data[0] );
  // get matrix mat1 second row into vector vec4
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

  // get transpose of matrix mat1 into matrix mat2
  transpose_m( mat1, mat2 );
  // get transpose of matrix mat1 into matrix mat3
  transpose_m( mat1, mat3 );

  // add two matrices
  add_mm( mat2, mat3, mat4 );
  // subtract two matrices
  sub_mm( mat2, mat3, mat5 );
  // multiply two matrices
  mult_mm( mat1, mat2, mat6 );

  // add two vectors
  add_vv( vec1, vec3, vec6 );
  // subtract two vectors
  sub_vv( vec1, vec3, vec7 );
  // find dot product of two vectors
  dot_product_vv( vec1, vec2, &res );
  // get second column of matrix mat2 into vector vec5
  get_col_m( mat2, 1, vec5 );
  
  printf("matrix2\n");
  print_m( mat2 );
  printf("matrix4\n");
  print_m( mat4 );
  printf("matrix5\n");
  print_m( mat5 );
  printf("matrix6\n");
  print_m( mat6 );
  printf("vec5\n");
  print_v( vec5 );
  printf( "\nvec1 + vec3 = vec6\n" );
  print_v( vec6 );
  printf( "\nvec1 - vec3 = vec7\n" );
  print_v( vec7 );
  printf("\ndot product vec1 and vec2 = res\n");
  printf( "%.2f\n", res );

  // multiply matrix with a vector
  mult_mv( mat2, vec8, vec9 );
  printf( "\nmat2 * vec8 = vec9\n" );
  print_v( vec9 );

  // multiply vector with a matrix
  mult_vm( vec10, mat1, vec11 );
  printf( "\nvec10 * mat1 = vec11\n" );
  print_v( vec11 );

  release_v( vec1 );
  release_v( vec2 );
  release_v( vec3 );
  release_v( vec4 ); 
  release_v( vec5 );
  release_v( vec6 ); 
  release_v( vec7 );
  release_v( vec8 ); 
  release_v( vec9 );
  release_v( vec10 ); 
  release_v( vec11 );
  release_m( mat1 );
  release_m( mat2 );
  release_m( mat3 );
  release_m( mat4 );
  release_m( mat5 );
  release_m( mat6 );

  return 0;
}
