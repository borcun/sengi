#include "base.h"

// function that create a row vector
vector_t create_rv( const size_t size ) {
  vector_t vec;
  
  if( 1 > size ) {
    SENGI_ERR( INVALID_SIZE );
    return NULL;
  }
  
  vec = ( vector_t ) malloc( sizeof( struct vector_t ) );

  if( NULL == vec ) {
    SENGI_ERR( MEM_ALLOC );
    return NULL;
  }
  
  vec->data = ( double * ) calloc( DEFAULT_VAL, size * sizeof( double ) );

  if( NULL == vec->data ) {
    SENGI_ERR( MEM_ALLOC );
    free( vec );
    return NULL;
  }

  vec->type = RVEC;
  vec->size = size;
 
  return vec;
}

// function that creates a column vector
vector_t create_cv( const size_t size ) {
  vector_t vec;
  
  if( 1 > size ) {
    SENGI_ERR( INVALID_SIZE );
    return NULL;
  }
  
  vec = ( vector_t ) malloc( sizeof( struct vector_t ) );

  if( NULL == vec ) {
    SENGI_ERR( MEM_ALLOC );
    return NULL;
  }
  
  vec->data = ( double * ) calloc( DEFAULT_VAL, size * sizeof( double ) );

  if( NULL == vec->data ) {
    SENGI_ERR( MEM_ALLOC );
    free( vec );
    return NULL;
  }

  vec->type = CVEC;
  vec->size = size;

  return vec;
}

// function that creates a matrix
matrix_t create_m( const size_t row, const size_t col ) {
  size_t i, j;
  matrix_t mat;

  if( row < 1 ) {
    SENGI_ERR( INVALID_ROW );
    return NULL;
  }

  if( col < 1 ) {
    SENGI_ERR( INVALID_COL );
    return NULL;
  }

  mat = ( matrix_t ) malloc( sizeof( struct matrix_t ) );

  if( NULL == mat ) {
    SENGI_ERR( MEM_ALLOC );
    return NULL;
  }

  mat->data = ( double ** ) malloc( row * sizeof( double * ) );

  if( NULL == mat->data ) {
    SENGI_ERR( MEM_ALLOC );
    free( mat );
    return NULL;
  }

  for( i=0 ; i < row ; ++i ) {
    mat->data[ i ] = ( double * ) calloc( DEFAULT_VAL, col * sizeof( double ) );

    if( NULL == mat->data[ i ] ) {
      SENGI_ERR( MEM_ALLOC );

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

// function that create identity matrix
matrix_t create_im( const size_t size ) {
  size_t i;
  matrix_t identity = create_m( size, size ); 
  
  if( is_valid_m( identity ) ) {
    fill_m( identity, 0.0 );
    
    for( i = 0 ; i < size ; ++i )
      identity->data[ i ][ i ] = 1.0;
    
    return identity;
  }
  
  return NULL;
} 

// function that releases the vector
void release_v( vector_t vec ) {
  if( is_valid_v( vec ) ) {
    free( vec->data );
    free( vec );
  }
  else
    SENGI_ERR( INVALID_VEC );
  
  return;
}

// function that releases the matrix
void release_m( matrix_t mat ) {
  size_t i;

  if( is_valid_m( mat ) ) {
    for( i=0 ; i < mat->row ; ++i )
      free( mat->data[ i ] );
    free( mat );
  }
  else
    SENGI_ERR( INVALID_MAT );
  
  return;
}

// function that puts the value into the vector
void put_v( vector_t vec, const size_t index, const double val ) {
  if( !is_valid_v( vec ) )
    SENGI_ERR( INVALID_VEC );
  else if( index >= vec->size )
    SENGI_ERR( INVALID_INDEX );
  else
    vec->data[ index ] = val;
      
  return;
}

// function that puts the value into matrix
void put_m( matrix_t mat, const size_t row, const size_t col, const double val ) {
  if( !is_valid_m( mat ) )
    SENGI_ERR( INVALID_MAT );
  else if( row >= mat->row )
    SENGI_ERR( INVALID_ROW );
  else if( col >= mat->col )
    SENGI_ERR( INVALID_COL );
  else
    mat->data[ row ][ col ] = val;
	  
  return;
}

// function that fills the vector with val
void fill_v( vector_t vec, const double val ) {
  size_t i;

  if( is_valid_v( vec ) ) {  
    for( i=0 ; i < vec->size ; ++i )
      vec->data[ i ] = val;  
  }
  else
    SENGI_ERR( INVALID_VEC );
  
  return;
}

// function that fills the matrix with val
void fill_m( matrix_t mat, const double val ) {
  size_t i, j;

  if( is_valid_m( mat ) ) {  
    for( i=0 ; i < mat->row ; ++i ) {
      for( j=0 ; j < mat->col ; ++j )
				mat->data[ i ][ j ] = val;
    }  
  }
  else
    SENGI_ERR( INVALID_MAT );
  
  return;
}

// function that copies the source vector to the destination vector
void copy_v( const vector_t src, vector_t des ) {
  size_t i;
  
  if( is_valid_v( src ) && is_valid_v( des ) ) {
    if( src->size == des->size ) {
      for( i=0 ; i < src->size ; ++i )
	src->data[ i ] = des->data[ i ];
    }
    else
      SENGI_ERR( MATCH_SIZE );
  }
  else
    SENGI_ERR( INVALID_VEC );
  
  return;
}

// function that copies the source matrix to the destination matrix
void copy_m( const matrix_t src, matrix_t des ) {
  size_t i, j;

  if( is_valid_m( src ) && is_valid_m( des ) ) {
    if( src->row == des->row ) {
      if( src->col == des->col ) {
	for( i=0 ; i < src->row ; ++i ) {
	  for( j=0 ; j < src->col ; ++j )
	    des->data[ i ][ j ] = src->data[ i ][ j ];
	}
      }
      else
	SENGI_ERR( MATCH_COL );
    }
    else
      SENGI_ERR( MATCH_ROW );
  }
  else
    SENGI_ERR( INVALID_MAT );

  return;
}

// function that returns norm of the vector
size_t norm_v( const vector_t vec ) {
  double total = 0.0;
  size_t i;
  
  if( is_valid_v( vec ) ) {
    for( i=0 ; i < vec->size ; ++i )
      total += pow( vec->data[ i ], 2 );

    return sqrt( total );
  }
  else
    SENGI_ERR( INVALID_VEC );
  
  return -1;
}

// function that returns norm of the matrix
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
  else
    SENGI_ERR( INVALID_MAT );
  
  return -1;
}

// function that finds diagonal vector of the matrix
bool_t diagonal_m( matrix_t mat, vector_t vec ) {
  size_t i;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( "the matrix is invalid" );
    return FALSE;
  }
  else if( !is_valid_v( vec ) ) {
    SENGI_ERR( "the vector is invalid" );
    return FALSE;
  }
  else if( mat->col != vec->size ) {
    SENGI_ERR( "the matrix and vector sizes do not match" );
    return FALSE;
  }
  else if( mat->col > mat->row ) {
    SENGI_ERR( "the row must be bigger than the column" );
    return FALSE;
  }
  else {
    for( i=0 ; i < mat->row ; ++i )
      vec->data[ i ] = mat->data[ i ][ i ];
    
    return TRUE;
  }
}

// function that extends the matrix with vector
void extend_mv( matrix_t mat, const vector_t vec ) {
  size_t i, j;
  size_t row, col;
  double **data;

  if( !is_valid_m( mat ) )
    SENGI_ERR( INVALID_MAT );
  else if( !is_valid_v( vec ) )
    SENGI_ERR( INVALID_VEC );
  else {
    switch( vec->type ) {
    case RVEC:
      if( mat->col != vec->size )
	SENGI_ERR( MATCH_COL_SIZE );
      else {
	data = ( double ** ) malloc( sizeof( double * ) * ( mat->row + 1 ) );

	if( NULL == data ) {
	  SENGI_ERR( MEM_ALLOC );
	  return;
	}

	for( i=0 ; i < mat->row ; ++i ) {
	  data[ i ] = ( double * ) malloc( sizeof( double ) * mat->col );

	  if( NULL == data[ i ] ) {
	    SENGI_ERR( MEM_ALLOC );

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
	SENGI_ERR( MATCH_ROW_SIZE );
      else {
	data = ( double ** ) malloc( sizeof( double * ) * mat->row );

	if( NULL == data ) {
	  SENGI_ERR( MEM_ALLOC );
	  return;
	}

	for( i=0 ; i < mat->row ; ++i ) {
	  data[ i ] = ( double * ) malloc( sizeof( double ) * ( mat->col + 1 ) );

	  if( NULL == data[ i ] ) {
	    SENGI_ERR( MEM_ALLOC );

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
      SENGI_ERR( INVALID_VEC );
      break;
    }
  }
  
  return;
}

// function that extends the matrix with another matrix
void extend_mm( matrix_t aug, const matrix_t mat ) {
  return;
}

// function that converts the array to the vector
bool_t to_v( vector_t vec, double *data ) {
  size_t i;
  
  if( !is_valid_v( vec ) ) {
    SENGI_ERR( INVALID_VEC );
    return FALSE;
  }
  else if( NULL == data ) {
    SENGI_ERR( INVALID_DATA );
    return FALSE;
  }
  else {
    for( i=0 ; i < vec->size ; ++i )
      vec->data[ i ] = data[ i ];

    return TRUE;
  }
}

// function that converts the array to the matrix
bool_t to_m( matrix_t mat, double **data ) {
  size_t i, j;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
    return FALSE;
  }
  else if( NULL == data ) {
    SENGI_ERR( INVALID_DATA );
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

// function that gets a row of the matrix
bool_t get_row_m( const matrix_t mat, const size_t row, vector_t vec ) {
  if( is_valid_m( mat ) && is_valid_v( vec ) ) {
    if( mat->col != vec->size ) {
      SENGI_ERR( MATCH_COL_SIZE );
      return FALSE;
    }

    return to_v( vec, mat->data[ row ] );
  }

  return FALSE;
}

// function that gets a column of the matrix
bool_t get_col_m( const matrix_t mat, const size_t col, vector_t vec ) {
  size_t i;
  
  if( is_valid_m( mat ) && is_valid_v( vec ) ) {
    if( mat->row != vec->size ) {
      SENGI_ERR( MATCH_ROW_SIZE );
      return FALSE;
    }

    for( i=0 ; i < mat->row ; ++i )
      vec->data[ i ] = mat->data[ i ][ col ];
    
    return TRUE;
  }

  return FALSE;
}

// function that replace rows of the matrix
void replace_rows_m( matrix_t mat, int row1, int row2 ) {
  size_t j;
  double temp;
  
  if( !is_valid_m( mat ) )
    SENGI_ERR( INVALID_MAT );
  else if( ( row1 < 0 || row1 >= mat->row ) && ( row2 < 0 || row2 >= mat->row ) )
    SENGI_ERR( INVALID_ROW );
  else {
    for( j=0 ; j < mat->col ; ++j ) {
      temp = mat->data[ row1 ][ j ];
      mat->data[ row1 ][ j ] = mat->data[ row2 ][ j ];
      mat->data[ row2 ][ j ] = temp;
    }
  }
  
  return;
}

// function that adds two matrices
void add_mm( const matrix_t mat1, const matrix_t mat2, matrix_t res ) {
  size_t i, j;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1->row != mat2->row || mat1->row != res->row )
      SENGI_ERR( MATCH_ROW );
    else if( mat1->col != mat2->col || mat1->col != res->col )
      SENGI_ERR( MATCH_COL );
    else {
      for( i=0 ; i < mat1->row ; ++i ) {
	for( j=0 ; j < mat1->col ; ++j )
	  res->data[ i ][ j ] = mat1->data[ i ][ j ] + mat2->data[ i ][ j ];
      }
    }
  }
  
  return;
}

// function that substracts two matrices
void sub_mm( const matrix_t mat1, const matrix_t mat2, matrix_t res ) {
  size_t i, j;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1->row != mat2->row || mat1->row != res->row )
      SENGI_ERR( MATCH_ROW );
    else if( mat1->col != mat2->col || mat1->col != res->col ) {
      SENGI_ERR( MATCH_COL );
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

// function that multiplies two matrices
void mult_mm( const matrix_t mat1, const matrix_t mat2, matrix_t res ) {
  size_t i, j, k;
  double temp = 0.0;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1->col != mat2->row )
      SENGI_ERR( MATCH_ROW_COL );
    else if( mat1->row != res->row )
      SENGI_ERR( MATCH_ROW );
    else if( mat2->col != res->col )
      SENGI_ERR( MATCH_COL );
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
  else
    SENGI_ERR( INVALID_MAT );
  
  return;
}

// function that multiplies the matrix and the vector
void mult_mv( const matrix_t mat, const vector_t vec, vector_t res ) {
  size_t i, j;
  double total = 0.0;
  
  if( !is_valid_m( mat ) )
    SENGI_ERR( INVALID_MAT );
  else if( !is_valid_v( vec ) || !is_valid_v( res ) )
    SENGI_ERR( INVALID_VEC );
  else {
    if( mat->col != vec->size )
      SENGI_ERR( MATCH_COL_SIZE );
    else if( mat->row != res->size )
      SENGI_ERR( MATCH_ROW_SIZE );
    else if( vec->type != CVEC || res->type != CVEC )
      SENGI_ERR( MUST_COL_VEC );
    else {
      for( i=0 ; i < mat->row ; ++i ) {
	for( j=0 ; j < mat->col ; ++j )
	  total += mat->data[ i ][ j ] * vec->data[ j ];

	res->data[ i ] = total;
	total = 0.0;
      }
    }
  }

  return;
}

// function that multiplies the vector and the matrix
void mult_vm( const vector_t vec, const matrix_t mat, vector_t res ) {
  size_t i, j;
  double total = 0.0;
  
  if( !is_valid_m( mat ) )
    SENGI_ERR( INVALID_MAT );
  else if( is_valid_v( vec ) && is_valid_v( res ) )
    SENGI_ERR( INVALID_VEC );
  else {
    if( mat->row != vec->size )
      SENGI_ERR( MATCH_ROW_SIZE );
    else if( mat->col != res->size )
      SENGI_ERR( MATCH_COL_SIZE );
    else if( vec->type != RVEC || res->type != RVEC )
      SENGI_ERR( MUST_ROW_VEC );
    else {
      for( i=0 ; i < mat->col ; ++i ) {
	for( j=0 ; j < mat->row ; ++j )
	  total += vec->data[ j ] * mat->data[ j ][ i ];

	res->data[ i ] = total;
	total = 0.0;
      }
    }
  }

  return;
}

// function that adds two vectors
void add_vv( const vector_t vec1, const vector_t vec2, vector_t res ) {
  size_t i;
  
  if( is_valid_v( vec1 ) && is_valid_v( vec2 ) && is_valid_v( res ) ) {
    if( vec1->size == vec2->size && vec1->size == res->size ) {
      for( i=0 ; i < vec1->size ; ++i )
	res->data[ i ] = vec1->data[ i ] + vec2->data[ i ];
    }
    else
      SENGI_ERR( MATCH_SIZE );
  }
  else
    SENGI_ERR( INVALID_VEC );

  return;
}

// function that substracts two vectors
void sub_vv( const vector_t vec1, const vector_t vec2, vector_t res ) {
  size_t i;
  
  if( is_valid_v( vec1 ) && is_valid_v( vec2 ) && is_valid_v( res ) ) {
    if( vec1->size == vec2->size && vec1->size == res->size ) {
      for( i=0 ; i < vec1->size ; ++i )
	res->data[ i ] = vec1->data[ i ] - vec2->data[ i ];
    }
    else
      SENGI_ERR( MATCH_SIZE );
  }
  else
    SENGI_ERR( INVALID_VEC );
  
  return;
}

// function that finds dot product of two vectors
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
	  SENGI_ERR( MEM_ALLOC );
    }
    else
      SENGI_ERR( MATCH_SIZE );
  }
  else
    SENGI_ERR( INVALID_VEC );
  
  return;
}

// function that finds cross product of the vectors
void cross_product_vv( const vector_t vec1, const vector_t vec2, vector_t res ) {
  if( !is_valid_v( vec1 ) || !is_valid_v( vec2 ) || !is_valid_v( res ) )
    SENGI_ERR( INVALID_VEC );
  else if( vec1->size != 3 || vec2->size != 3 || res->size != 3 )
    SENGI_ERR( CROSS_PRODUCT );
  else {
    res->data[ 0 ] = vec1->data[ 1 ] * vec2->data[ 2 ] - vec1->data[ 2 ] * vec2->data[ 1 ];
    res->data[ 1 ] = vec1->data[ 2 ] * vec2->data[ 0 ] - vec1->data[ 0 ] * vec2->data[ 2 ];
    res->data[ 2 ] = vec1->data[ 0 ] * vec2->data[ 1 ] - vec1->data[ 1 ] * vec2->data[ 0 ];    
  }
      
  return;
}

// function that finds transpose of the matrix
void transpose_m( const matrix_t src, matrix_t des ) {
  size_t i, j;

  if( !is_valid_m( src ) || !is_valid_m( des ) )
    SENGI_ERR( INVALID_MAT );
  else if( src->row != des->col || src->col != des->row )
    SENGI_ERR( MATCH_ROW_COL );
  else {
    for( i=0 ; i < src->col ; ++i ) {
      for( j=0 ; j < src->row ; ++j )
				des->data[ i ][ j ] = src->data[ j ][ i ];
    }
  }

  return;
}

// function that finds inverse matrix of the matrix
void inverse_m( const matrix_t src, matrix_t des ) {
  matrix_t mat = create_m (src->row,src->row);
  size_t i,j,k,n = src->row;
  double ratio;
  
  des = create_im( src->row );
  copy_m (src,mat);
  /*Gauss Elimination
   [ A | I] -> [I | A^-1] 
  */
   
  if( src->row != src->col ){
    SENGI_ERR( SQUARE_MATRIX );
    return ;
  }
	if( !is_valid_m( des ) || !is_valid_m( mat )) {
		SENGI_ERR( INVALID_MAT );
		return;
	}

  // forward elimination
  for( i=0 ; i < (n-1) ; ++i ){
    for( j=i+1 ; j < n ; ++j ){
      if ( mat->data[ i ][ i ] == 0)
        continue;

      ratio = mat->data[ j ][ i ] / mat->data[ i ][ i ] ;
      for( k=0 ; k < n ; ++k ){
        mat->data[ j ][ k ] = mat->data[ j ][ k ] - mat->data[ i ][ k ]*ratio;
        des->data[ j ][ k ] = des->data[ j ][ k ] - des->data[ i ][ k ]*ratio;
      }
    }
  }

  //backward elimination
	for( i=n-1 ; i > 0 ; --i ){
    for( j=i-1 ; j >= 0 ; --j ){
      if ( mat->data[ i ][ i ] == 0)
        continue;

      ratio = mat->data[ j ][ i ] / mat->data[ i ][ i ] ;
      for( k=0 ; k < n ; ++k ){
        mat->data[ j ][ k ] = mat->data[ j ][ k ] - mat->data[ i ][ k ]*ratio;
        des->data[ j ][ k ] = des->data[ j ][ k ] - des->data[ i ][ k ]*ratio;
      }
    }
  }

  //dividing elements
  for( i=0 ; i < n ; ++i ){
    ratio = mat->data[ i ][ i ];
    mat->data[ i ][ i ] = mat->data[ i ][ i ] / mat->data[ i ][ i ]; 
    for( j=0 ; j < n ; ++j ){
      des->data[ i ][ i ] = des->data[ i ][ i ] / ratio ;
    }
  }


 return;
}

// function that eliminates the source matrix
void eliminate_m( const matrix_t src, matrix_t des ) {
  if( !is_valid_m( src ) || !is_valid_m( des ) )
    SENGI_ERR( INVALID_MAT );
  else if( src->row != des->col || src->col != des->row )
    SENGI_ERR( MATCH_ROW_COL );
  else {
    // perform elimination
  }
  
  return;
}

// function that scales the vector with val
void scale_v( vector_t vec, const double val ) {
  size_t i;
  
  if( !is_valid_v( vec ) )
    SENGI_ERR( INVALID_VEC );
  else {
    for( i=0 ; i < vec->size ; ++i )
      vec->data[ i ] = val * vec->data[ i ];
  }

  return;
}

// function that scales the matrix with val
void scale_m( matrix_t mat, const double val ) {
  size_t i, j;
  
  if( !is_valid_m( mat ) )
    SENGI_ERR( INVALID_MAT );
  else {
    for( i=0 ; i < mat->row ; ++i ) {
      for( j=0 ; j < mat->col ; ++j )
	mat->data[ i ][ j ] = val * mat->data[ i ][ j ];
    }
  }

  return;
}

// function that prints the vector
void print_v( const vector_t vec ) {
  size_t i;

  if( !is_valid_v( vec ) )
    SENGI_ERR( INVALID_VEC );
  else if( RVEC == vec->type ) {
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

// function that prints the matrix
void print_m( const matrix_t mat ) {
  size_t i, j;

  if( !is_valid_m( mat ) )
    SENGI_ERR( INVALID_MAT );
  else {
    for( i=0 ; i < mat->row ; ++i ) {
      for( j=0 ; j < mat->col ; ++j )
	fprintf( stdout, "%f ", mat->data[ i ][ j ] );
      fprintf( stdout, "%s", "\n" );
    }

    fprintf( stdout, "%s", "\n" );
  }

  return;
}

// function that checks whether the vector is valid
bool_t is_valid_v( const vector_t vec ) {
  if( NULL == vec )
    return FALSE;
  else if( vec->size < 1 )
    return FALSE;
  else if( NULL == vec->data )
    return FALSE;
  else if( !(RVEC == vec->type || CVEC == vec->type) )
    return FALSE;
  else
    return TRUE;
}

// function that checks whether the matrix is valid
bool_t is_valid_m( const matrix_t mat ) {
  if( NULL == mat )
    return FALSE;
  else if( mat->row < 1 || mat->col < 1 )
    return FALSE;
  else if( NULL == mat->data )
    return FALSE;
  else if( NULL == mat->data[ 0 ] )
    return FALSE;
  else
    return TRUE;
}
