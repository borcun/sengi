#include "../../inc/base.h"

vector_t *create( size_t size ) {
  vector_t *vec;

  if( 0 > size ) {
    LIBALG_ERR( "vector size is invalid" );
    return NULL;
  }
  
  vec = ( vector_t * ) malloc( sizeof( vector_t ) );

  if( NULL == vec ) {
    LIBALG_ERR( "creating vector is failed" );
    return NULL;
  }
  
  vec->data = ( double * ) malloc( size * sizeof( double ) );

  if( NULL == vec->data ) {
    LIBALG_ERR( "creating vector is failed" );
    free( vec );
    return NULL;
  }

  vec->size = size;
    
  return vec;
}

matrix_t *create( size_t row, size_t col ) {
  size_t i, j;
  matrix_t *mat;

  if( 0 > row || 0 > col ) {
    LIBALG_ERR( "matrix row or column is invalid" );
    return NULL;
  }

  mat = ( matrix_t * ) malloc( sizeof( matrix_t ) );

  if( NULL == mat ) {
    LIBALG_ERR( "creating matrix is failed" );
    return NULL;
  }

  mat->data = ( double ** ) malloc( row * sizeof( double * ) );

  if( NULL == mat->data ) {
    LIBALG_ERR( "creating matrix is failed" );
    free( mat );
    return NULL;
  }

  for( i=0 ; i < row ; ++i ) {
    mat->data[ i ] = ( double * ) malloc( col * sizeof( double ) );

    if( NULL == mat->data[ i ] ) {
      LIBALG_ERR( "creating matrix is failed" );

      for( j=0 ; j < i ; ++j )
	free( mat->data[ j ] );

      free( mat );
      return NULL;
    }
  }

  mat->row = row;
  mat->col = col;

  return mat;
}

void release( vector_t *vec ) {
  free( vec->data );
  free( vec );
  return;
}

void release( matrix_t *mat ) {
  size_t i;

  for( i=0 ; i < mat->row ; ++i )
    free( mat->data[ i ] );

  free( mat );
  return;
}