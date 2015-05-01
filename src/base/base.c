#include "../inc/base.h"

vector_t create_rv( const size_t size ) {
  vector_t vec;
  
  if( 0 > size ) {
    SENGI_ERR( "vector size is invalid" );
    return NULL;
  }
  
  vec = ( vector_t ) malloc( sizeof( struct vector_t ) );

  if( NULL == vec ) {
    SENGI_ERR( "creating vector is failed" );
    return NULL;
  }
  
  vec->data = ( double * ) malloc( size * sizeof( double ) );

  if( NULL == vec->data ) {
    SENGI_ERR( "creating vector is failed" );
    free( vec );
    return NULL;
  }

  vec->vt = RVEC;
  vec->size = size;
 
  return vec;
}

vector_t create_cv( const size_t size ) {
  vector_t vec;
  
  if( 0 > size ) {
    SENGI_ERR( "vector size is invalid" );
    return NULL;
  }
  
  vec = ( vector_t ) malloc( sizeof( struct vector_t ) );

  if( NULL == vec ) {
    SENGI_ERR( "creating vector is failed" );
    return NULL;
  }
  
  vec->data = ( double * ) malloc( size * sizeof( double ) );

  if( NULL == vec->data ) {
    SENGI_ERR( "creating vector is failed" );
    free( vec );
    return NULL;
  }

  vec->vt = CVEC;
  vec->size = size;

  return vec;
}

matrix_t create_m( const size_t row, const size_t col ) {
  size_t i, j;
  matrix_t mat;

  if( 0 > row || 0 > col ) {
    SENGI_ERR( "matrix row or column is invalid" );
    return NULL;
  }

  mat = ( matrix_t ) malloc( sizeof( struct matrix_t ) );

  if( NULL == mat ) {
    SENGI_ERR( "creating matrix is failed" );
    return NULL;
  }

  mat->data = ( double ** ) malloc( row * sizeof( double * ) );

  if( NULL == mat->data ) {
    SENGI_ERR( "creating matrix is failed" );
    free( mat );
    return NULL;
  }

  for( i=0 ; i < row ; ++i ) {
    mat->data[ i ] = ( double * ) malloc( col * sizeof( double ) );

    if( NULL == mat->data[ i ] ) {
      SENGI_ERR( "creating matrix is failed" );

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

void release_v( vector_t vec ) {
  free( vec->data );
  free( vec );
  return;
}

void release_m( matrix_t mat ) {
  size_t i;

  for( i=0 ; i < mat->row ; ++i )
    free( mat->data[ i ] );

  free( mat );
  return;
}

bool_t fill_v( vector_t vec, const double val ) {
  size_t i;

  if( vec->size < 1 ) {
    SENGI_ERR( "invalid vector size" );
    return FALSE;
  }
  
  for( i=0 ; i < vec->size ; ++i )
    vec->data[ i ] = val;

  return TRUE;
}

bool_t fill_m( matrix_t mat, const double val ) {
  size_t i, j;

  if( mat->row < 1 || mat->col < 1 ) {
    SENGI_ERR( "invalid matrix row or column size" );
    return FALSE;
  }
  
  for( i=0 ; i < mat->row ; ++i ) {
    for( j=0 ; j < mat->col ; ++j )
      mat->data[ i ][ j ] = val;
  }

  return TRUE;
}

bool_t to_v( vector_t vec, const double *data ) {
  size_t i;
  
  if( NULL == data ) {
    SENGI_ERR( "invalid data array" );
    return FALSE;
  }

  if( vec->size < 1 ) {
    SENGI_ERR( "invalid vector size" );
    return FALSE;
  }

  for( i=0 ; i < vec->size ; ++i )
    vec->data[ i ] = data[ i ];

  return TRUE;
}

bool_t get_row_m( matrix_t mat, size_t row, vector_t vec ) {
  if( row < 1 || row >= mat->row ) {
    SENGI_ERR( "row value is out of bounds" );
    return FALSE;
  }

  if( mat->col < 1 || mat->row < 1 ) {
    SENGI_ERR( "matrix row or column size is invalid" );
    return FALSE;
  }

  if( mat->col != vec->size ) {
    SENGI_ERR( "matrix column does not match vector size" );
    return FALSE;
  }

  return to_v( vec, mat->data[ row ] );
}

bool_t get_col_m( matrix_t mat, size_t col, vector_t vec ) {
  size_t i;
  
  if( col < 1 || col >= mat->row ) {
    SENGI_ERR( "column value is out of bounds" );
    return FALSE;
  }

  if( mat->col < 1 || mat->row < 1 ) {
    SENGI_ERR( "matrix row or column size is invalid" );
    return FALSE;
  }

  if( mat->row != vec->size ) {
    SENGI_ERR( "matrix row does not match vector size" );
    return FALSE;
  }

  for( i=0 ; i < mat->row ; ++i )
    vec->data[ i ] = mat->data[ i ][ col ];
    
  return TRUE;
}

bool_t transpose_m( matrix_t src, matrix_t des ) {
  size_t i, j;

  if( src->row != des->col || src->col != des->row ) {
    SENGI_ERR( "destination matrix does not match transpose of source matrix" );
    return FALSE;
  }

  if( src->row < 1 || src->col < 1 ) {
    SENGI_ERR( "invalid source matrix row or column size" );
    return FALSE;
  }

  if( des->row < 1 || des->col < 1 ) {
    SENGI_ERR( "invalid destination matrix row or column size" );
    return FALSE;
  }

  for( i=0 ; i < src->col ; ++i ) {
    for( j=0 ; j < src->row ; ++j )
      des->data[ i ][ j ] = src->data[ j ][ i ];
  }

  return TRUE;
}

bool_t inverse_m( matrix_t src, matrix_t des ) {
  return TRUE;
}

bool_t eliminate_m( matrix_t src, matrix_t des ) {
  double pivot;
  size_t i, j;
  
  if( src->row != des->col || src->col != des->row ) {
    SENGI_ERR( "destination matrix does not match transpose of source matrix" );
    return FALSE;
  }

  if( src->row < 1 || src->col < 1 ) {
    SENGI_ERR( "invalid source matrix row or column size" );
    return FALSE;
  }

  if( des->row < 1 || des->col < 1 ) {
    SENGI_ERR( "invalid destination matrix row or column size" );
    return FALSE;
  }

  // perform elimination
  
  return TRUE;
}

void print_v( const vector_t vec ) {
  size_t i;

  if( RVEC == vec->vt ) {
    for( i=0 ; i < vec->size ; ++i )
      fprintf( stdout, "%f ", vec->data[ i ] ); 
    fprintf( stdout, "%s", "\n" );
  }
  else {
    for( i=0 ; i < vec->size ; ++i )
      fprintf( stdout, "%f\n", vec->data[ i ] );
  }

  return;
}

void print_m( const matrix_t mat ) {
  size_t i, j;

  for( i=0 ; i < mat->row ; ++i ) {
    for( j=0 ; j < mat->col ; ++j )
      fprintf( stdout, "%f ", mat->data[ i ][ j ] );
    fprintf( stdout, "%s", "\n" );
  }

  fprintf( stdout, "%s", "\n" );
  return;
}
