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

  vec->type = RVEC;
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

  vec->type = CVEC;
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
  if( is_valid_v( vec ) ) {
    free( vec->data );
    free( vec );
  }
  
  return;
}

void release_m( matrix_t mat ) {
  size_t i;

  if( is_valid_m( mat ) ) {
    for( i=0 ; i < mat->row ; ++i )
      free( mat->data[ i ] );

    free( mat );
  }

  return;
}

bool_t fill_v( vector_t vec, const double val ) {
  size_t i;

  if( is_valid_v( vec ) ) {  
    for( i=0 ; i < vec->size ; ++i )
      vec->data[ i ] = val;

    return TRUE;
  }
  
  return FALSE;
}

bool_t fill_m( matrix_t mat, const double val ) {
  size_t i, j;

  if( is_valid_m( mat ) ) {  
    for( i=0 ; i < mat->row ; ++i ) {
      for( j=0 ; j < mat->col ; ++j )
	mat->data[ i ][ j ] = val;
    }
  
    return TRUE;
  }

  return FALSE;
}

void copy_v( const vector_t src, vector_t des ) {
  size_t i;
  
  if( is_valid_v( src ) && is_valid_v( des ) ) {
    if( src->size == des->size ) {
      for( i=0 ; i < src->size ; ++i )
	src->data[ i ] = des->data[ i ];
    }
  }

  return;
}

void copy_m( const matrix_t src, matrix_t des ) {
  size_t i, j;

  if( is_valid_m( src ) && is_valid_m( des ) ) {
    if( src->row == des->row && src->col == des->col ) {
      for( i=0 ; i < src->row ; ++i ) {
	for( j=0 ; j < src->col ; ++j )
	  des->data[ i ][ j ] = src->data[ i ][ j ];
      }
    }
  }

  return;
}

size_t norm_v( const vector_t vec ) {
  double total = 0.0;
  size_t i;
  
  if( is_valid_v( vec ) ) {
    for( i=0 ; i < vec->size ; ++i )
      total += pow( vec->data[ i ], 2 );

    return sqrt( total );
  }

  return -1;
}

size_t norm_m( const matrix_t mat ) {
  double total = 0.0;
  size_t i, j;

  if( is_valid_m( mat ) ) {
    for( i=0 ; i < mat->row ; ++i ) {
      for( j=0 ; j < mat->col ; ++j )
	total += pow( mat->data[ i ][ j ], 2 );
    }

    return sqrt( total );
  }

  return -1;
}

void extend_mv( matrix_t mat, const vector_t vec ) {
  size_t i, j;
  size_t row, col;
  double **data;

  if( is_valid_m( mat ) && is_valid_v( vec ) ) {  
    switch( vec->type ) {
    case RVEC:
      if( mat->col != vec->size )
	SENGI_ERR( "the matrix column and the vector size does not match" );
      else {
	data = ( double ** ) malloc( sizeof( double * ) * ( mat->row + 1 ) );

	if( NULL == data ) {
	  SENGI_ERR( "a memory allocation error occurs" );
	  return;
	}

	for( i=0 ; i < mat->row ; ++i ) {
	  data[ i ] = ( double * ) malloc( sizeof( double ) * mat->col );

	  if( NULL == data[ i ] ) {
	    SENGI_ERR( "" );

	    for( j=0 ; j < i ; ++j )
	      free( data[ j ] );
	    free( data );

	    return;
	  }
	
	  memcpy( data[ i ], mat->data[ i ], mat->col );
	}

	memcpy( data[ mat->row ], vec->data, vec->size );
	row = mat->row + 1;
	col = mat->col;
	
	release_m( mat );
	mat = create_m( row, col );
	to_m( mat, data );

	for( i=0 ; i < row ; ++i )
	  free( data[ i ] );
	free( data );
      } // end of else
      break;
    case CVEC:
      if( mat->row != vec->size )
	SENGI_ERR( "the matrix row and the vector size does not match" );
      else {
	data = ( double ** ) malloc( sizeof( double * ) * mat->row );

	if( NULL == data ) {
	  SENGI_ERR( "a memory allocation error occurs" );
	  return;
	}

	for( i=0 ; i < mat->row ; ++i ) {
	  data[ i ] = ( double * ) malloc( sizeof( double ) * ( mat->col + 1 ) );

	  if( NULL == data[ i ] ) {
	    SENGI_ERR( "" );

	    for( j=0 ; j < i ; ++j )
	      free( data[ j ] );
	    free( data );

	    return;
	  }

	  // copy whole row data to row of new data array
	  memcpy( data[ i ], mat->data[ i ], mat->col );
	  // add the data of column vector to end of row
	  data[ i ][ mat->col ] = vec->data[ i ];
	}

	row = mat->row;
	col = mat->col + 1;
	
	release_m( mat );
	mat = create_m( row, col );
	to_m( mat, data );

	for( i=0 ; i < row ; ++i )
	  free( data[ i ] );
	free( data );
      } // end of else
      break;
    default:
      SENGI_ERR( "the vector type is invalid" );
      break;
    }
  }
  else
    SENGI_ERR( "the matrix or the vector is invalid" );
  
  return;
}

void extend_mm( matrix_t aug, const matrix_t mat ) {
  return;
}

bool_t to_v( vector_t vec, double *data ) {
  size_t i;
  
  if( !is_valid_v( vec ) ) {
    SENGI_ERR( "the vector is invalid" );
    return FALSE;
  }
  else if( NULL == data ) {
    SENGI_ERR( "the data is invalid" );
    return FALSE;
  }
  else {
    for( i=0 ; i < vec->size ; ++i )
      vec->data[ i ] = data[ i ];

    return TRUE;
  }
}

bool_t to_m( matrix_t mat, double **data ) {
  size_t i, j;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( "the matrix is invalid" );
    return FALSE;
  }
  else if( NULL == data ) {
    SENGI_ERR( "the data is invalid" );
    return FALSE;
  }
  else {
    for( i=0 ; i < mat->row ; ++i ) {
      for( j=0 ; j < mat->col ; ++j )
	mat->data[ i ][ j ] = data[ i ][ j ];
    }
    
    return TRUE;
  }
}

bool_t get_row_m( const matrix_t mat, const size_t row, vector_t vec ) {
  if( is_valid_m( mat ) && is_valid_v( vec ) ) {
    if( mat->col != vec->size ) {
      SENGI_ERR( "matrix column does not match vector size" );
      return FALSE;
    }

    return to_v( vec, mat->data[ row ] );
  }

  return FALSE;
}

bool_t get_col_m( const matrix_t mat, const size_t col, vector_t vec ) {
  size_t i;
  
  if( is_valid_m( mat ) && is_valid_v( vec ) ) {
    if( mat->row != vec->size ) {
      SENGI_ERR( "matrix row does not match vector size" );
      return FALSE;
    }

    for( i=0 ; i < mat->row ; ++i )
      vec->data[ i ] = mat->data[ i ][ col ];
    
    return TRUE;
  }

  return FALSE;
}

void add_mm( const matrix_t mat1, const matrix_t mat2, matrix_t res ) {
  size_t i, j;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1->row != mat2->row || mat1->col != mat2->col )
      SENGI_ERR( "matrices row or column size does not match" );
    else if( mat1->row != res->row || mat1->col != res->col ) {
      SENGI_ERR( "result matrix row or column size is not correct" );
    }
    else {
      for( i=0 ; i < mat1->row ; ++i ) {
	for( j=0 ; j < mat1->col ; ++j )
	  res->data[ i ][ j ] = mat1->data[ i ][ j ] + mat2->data[ i ][ j ];
      }
    }
  }
  
  return;
}

void sub_mm( const matrix_t mat1, const matrix_t mat2, matrix_t res ) {
  size_t i, j;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1->row != mat2->row || mat1->col != mat2->col )
      SENGI_ERR( "matrices row or column size does not match" );
    else if( mat1->row != res->row || mat1->col != res->col ) {
      SENGI_ERR( "result matrix row or column size is not correct" );
    }
    else {
      for( i=0 ; i < mat1->row ; ++i ) {
	for( j=0 ; j < mat1->col ; ++j )
	  res->data[ i ][ j ] = mat1->data[ i ][ j ] - mat2->data[ i ][ j ];
      }
    }
  }
  
  return;
}

void mult_mm( const matrix_t mat1, const matrix_t mat2, matrix_t res ) {
  size_t i, j, k;
  double temp = 0.0;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1->col != mat2->row )
      SENGI_ERR( "matrices row or column size does not match" );
    else if( mat1->row != res->row || mat2->col != res->col ) {
      SENGI_ERR( "result matrix row or column size is not correct" );
    }
    else {
      for( i=0 ; i < mat1->row ; ++i ) {
	for( k=0 ; k < mat2->col ; ++k ) {
	  for( j=0 ; j < mat2->row ; ++j )
	    temp += mat1->data[ i ][ j ] * mat2->data[ j ][ k ];

	  res->data[ i ][ k ] = temp;
	  temp = 0.0;
	}
      }
    }
  }
  
  return;
}

void mult_mv( const matrix_t mat, const vector_t vec, vector_t res ) {
  size_t i, j;
  double total = 0.0;
  
  if( is_valid_m( mat ) && is_valid_v( vec ) && is_valid_v( res ) ) {
    if( mat->col != vec->size )
      SENGI_ERR( "the matrix column and the vector size does not match" );
    else if( mat->row != res->size )
      SENGI_ERR( "the matrix row and the result vector size does not match" );
    else if( vec->type != CVEC || res->type != CVEC )
      SENGI_ERR( "the vector and result vector must be column vectors" );
    else {
      for( i=0 ; i < mat->row ; ++i ) {
	for( j=0 ; j < mat->col ; ++j )
	  total += mat->data[ i ][ j ] * vec->data[ j ];

	res->data[ i ] = total;
	total = 0.0;
      }
    }
  }
  else
    SENGI_ERR( "the matrix or the vectors is invalid" );

  return;
}

void mult_vm( const vector_t vec, const matrix_t mat, vector_t res ) {
  size_t i, j;
  double total = 0.0;
  
  if( is_valid_m( mat ) && is_valid_v( vec ) && is_valid_v( res ) ) {
    if( mat->row != vec->size )
      SENGI_ERR( "the matrix row and vector size does not match" );
    else if( mat->col != res->size )
      SENGI_ERR( "the matrix column and the result vector size does not match" );
    else if( vec->type != RVEC || res->type != RVEC )
      SENGI_ERR( "the vector and result vector must be row vectors" );
    else {
      for( i=0 ; i < mat->col ; ++i ) {
	for( j=0 ; j < mat->row ; ++j )
	  total += vec->data[ j ] * mat->data[ j ][ i ];

	res->data[ i ] = total;
	total = 0.0;
      }
    }
  }
  else
    SENGI_ERR( "the matrix or the vectors is invalid" );

  return;
}

void add_vv( const vector_t vec1, const vector_t vec2, vector_t res ) {
  size_t i;
  
  if( is_valid_v( vec1 ) && is_valid_v( vec2 ) && is_valid_v( res ) ) {
    if( vec1->size == vec2->size && vec1->size == res->size ) {
      for( i=0 ; i < vec1->size ; ++i )
	res->data[ i ] = vec1->data[ i ] + vec2->data[ i ];
    }
  }

  return;
}

void sub_vv( const vector_t vec1, const vector_t vec2, vector_t res ) {
  size_t i;
  
  if( is_valid_v( vec1 ) && is_valid_v( vec2 ) && is_valid_v( res ) ) {
    if( vec1->size == vec2->size && vec1->size == res->size ) {
      for( i=0 ; i < vec1->size ; ++i )
	res->data[ i ] = vec1->data[ i ] - vec2->data[ i ];
    }
  }

  return;
}

void dot_product_vv( const vector_t vec1, const vector_t vec2, double *res ) {
  size_t i;
  
  if( is_valid_v( vec1 ) && is_valid_v( vec2 ) ) {
    if( ( vec1->size == vec2->size ) &&
	( ( vec1->type == RVEC && vec2->type == CVEC ) ||
	 ( vec1->type == CVEC && vec2->type == RVEC ) ) )
      {
	if( NULL == res )
	  res = ( double *) calloc( 0.0, sizeof( double ) );
	if( NULL != res ) {
	  for( i=0 ; i < vec1->size ; ++i )
	    /* if user pass pointer which has one more element,
	       function fill its first index only */
	    res[ 0 ] += vec1->data[ i ] * vec2->data[ i ];
	}
	else
	  SENGI_ERR( "a memory allocation error occurs" );
    }
    else
      SENGI_ERR( "the vectors rows or columns do not match" );
  }

  return;
}

void cross_product_vv( const vector_t vec1, const vector_t vec2, vector_t res ) {
  return;
}

bool_t transpose_m( const matrix_t src, matrix_t des ) {
  size_t i, j;

  if( src->row != des->col || src->col != des->row ) {
    SENGI_ERR( "destination matrix does not match transpose of source matrix" );
    return FALSE;
  }

  if( src->row < 1 || src->col < 1 ) {
    SENGI_ERR( "source matrix row or column size is invalid" );
    return FALSE;
  }

  if( des->row < 1 || des->col < 1 ) {
    SENGI_ERR( "destination matrix row or column size is invalid" );
    return FALSE;
  }

  for( i=0 ; i < src->col ; ++i ) {
    for( j=0 ; j < src->row ; ++j )
      des->data[ i ][ j ] = src->data[ j ][ i ];
  }

  return TRUE;
}

bool_t inverse_m( const matrix_t src, matrix_t des ) {
  return TRUE;
}

bool_t eliminate_m( const matrix_t src, matrix_t des ) {
  /*  double pivot;
  size_t i, j;
  */
  if( src->row != des->col || src->col != des->row ) {
    SENGI_ERR( "destination matrix does not match transpose of source matrix" );
    return FALSE;
  }

  if( src->row < 1 || src->col < 1 ) {
    SENGI_ERR( "source matrix row or column size is invalid" );
    return FALSE;
  }

  if( des->row < 1 || des->col < 1 ) {
    SENGI_ERR( "destination matrix row or column size is invalid" );
    return FALSE;
  }

  // perform elimination
  
  return TRUE;
}

void scale_v( vector_t vec, const double num ) {
  size_t i;
  
  if( NULL == vec )
    SENGI_ERR( "vector instance is invalid" );
  else if( vec->size < 1 )
    SENGI_ERR( "vector size is invalid" );
  else {
    for( i=0 ; i < vec->size ; ++i )
      vec->data[ i ] = num * vec->data[ i ];
  }

  return;
}

void scale_m( matrix_t mat, const double num ) {
  size_t i, j;
  
  if( NULL == mat )
    SENGI_ERR( "matrix instance is invalid" );
  else if( mat->row < 1 || mat->col < 1 )
    SENGI_ERR( "matrix row or column size is invalid" );
  else {
    for( i=0 ; i < mat->row ; ++i ) {
      for( j=0 ; j < mat->col ; ++j )
	mat->data[ i ][ j ] = num * mat->data[ i ][ j ];
    }
  }

  return;
}

void print_v( const vector_t vec ) {
  size_t i;

  if( RVEC == vec->type ) {
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

bool_t is_valid_v( const vector_t vec ) {
  if( NULL == vec ) {
    SENGI_ERR( "the vector is null" );
    return FALSE;
  }
  else if( vec->size < 1 ) {
    SENGI_ERR( "the vector size is invalid" );
    return FALSE;
  }
  else if( NULL == vec->data ) {
    SENGI_ERR( "the vector data is null" );
    return FALSE;
  }
  else if( !(RVEC == vec->type || CVEC == vec->type) ) {
    SENGI_ERR( "the vector type is invalid" );
    return FALSE;
  }
  else
    return TRUE;
}

bool_t is_valid_m( const matrix_t mat ) {
  if( NULL == mat ) {
    SENGI_ERR( "the matrix is null" );
    return FALSE;
  }
  else if( mat->row < 1 || mat->col < 1 ) {
    SENGI_ERR( "the matrix row or column is invalid" );
    return FALSE;
  }
  else if( NULL == mat->data ) {
    SENGI_ERR( "the matrix data is null" );
    return FALSE;
  }
  else if( NULL == mat->data[ 0 ] ) {
    SENGI_ERR( "the matrix data is null" );
    return FALSE;
  }
  else
    return TRUE;
}
