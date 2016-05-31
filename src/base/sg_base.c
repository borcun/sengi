#include "sg_base.h"

// function that create a row vector
sg_vector create_rv( const size_t size ) {
  sg_vector vec = { 0, SG_INVVEC, NULL };
  
  if( 1 > size ) {
    SENGI_ERR( INVALID_SIZE );
    return vec;
  }
   
  vec.data = ( double * ) calloc( SG_DEFAULT_VALUE, size * sizeof( double ) );

  if( NULL == vec.data ) {
    SENGI_ERR( MEM_ALLOC );
    return vec;
  }

  vec.type = SG_RVEC;
  vec.size = size;
 
  return vec;
}

// function that creates a column vector
sg_vector create_cv( const size_t size ) {
  sg_vector vec = { 0, SG_INVVEC, NULL };
  
  if( 1 > size ) {
    SENGI_ERR( INVALID_SIZE );
    return vec;
  }
  
  vec.data = ( double * ) calloc( SG_DEFAULT_VALUE, size * sizeof( double ) );

  if( NULL == vec.data ) {
    SENGI_ERR( MEM_ALLOC );
    return vec;
  }

  vec.type = SG_CVEC;
  vec.size = size;

  return vec;
}

// function that creates a matrix
sg_matrix create_m( const size_t row, const size_t col ) {
  int i, j;
  sg_matrix mat = { 0, 0, NULL };

  if( row < 2 ) {
    SENGI_ERR( INVALID_ROW );
    return mat;
  }

  if( col < 2 ) {
    SENGI_ERR( INVALID_COL );
    return mat;
  }

  mat.data = ( double ** ) malloc( row * sizeof( double * ) );

  if( NULL == mat.data ) {
    SENGI_ERR( MEM_ALLOC );
    return mat;
  }

  for( i=0 ; i < row ; ++i ) {
    mat.data[ i ] = ( double * ) calloc( SG_DEFAULT_VALUE, col * sizeof( double ) );

    if( NULL == mat.data[ i ] ) {
      SENGI_ERR( MEM_ALLOC );

      for( j=0 ; j < i ; ++j ) {
	free( mat.data[ j ] );
      }

      return mat;
    }
  }

  mat.row = row;
  mat.col = col;

  return mat;
}

// function that create identity matrix
sg_matrix create_im( const size_t size ) {
  int i;
  sg_matrix identity = create_m( size, size ); 
  
  if( is_valid_m( identity ) ) {    
    for( i = 0 ; i < size ; ++i ) {
      identity.data[ i ][ i ] = 1.0;
    }
  }
  else {
    SENGI_ERR( INVALID_MAT );
  }
  
  return identity;
} 

// function that releases the vector
void release_v( sg_vector vec ) {
  if( is_valid_v( vec ) ) {
    free( vec.data );
  }
  else {
    SENGI_ERR( INVALID_VEC );
  }
  
  return;
}

// function that releases the matrix
void release_m( sg_matrix mat ) {
  int i;

  if( is_valid_m( mat ) ) {
    for( i=0 ; i < mat.row ; ++i )
      free( mat.data[ i ] );
  }
  else {
    SENGI_ERR( INVALID_MAT );
  }
  
  return;
}

// function that puts the value into the vector
void put_v( sg_vector vec, const size_t index, const double val ) {
  if( !is_valid_v( vec ) ) {
    SENGI_ERR( INVALID_VEC );
  }
  else if( index >= vec.size ) {
    SENGI_ERR( INVALID_INDEX );
  }
  else {
    vec.data[ index ] = val;
  }
      
  return;
}

// function that puts the value into matrix
void put_m( sg_matrix mat, const size_t row, const size_t col, const double val ) {
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
  }
  else if( row >= mat.row ) {
    SENGI_ERR( INVALID_ROW );
  }
  else if( col >= mat.col ) {
    SENGI_ERR( INVALID_COL );
  }
  else {
    mat.data[ row ][ col ] = val;
  }
	  
  return;
}

// function that fills the vector with val
void fill_v( sg_vector vec, const double val ) {
  int i;

  if( is_valid_v( vec ) ) {
    for( i=0 ; i < vec.size ; ++i ) {
      vec.data[ i ] = val;
    }
  }
  else {
    SENGI_ERR( INVALID_VEC );
  }
  
  return;
}

// function that fills the matrix with val
void fill_m( sg_matrix mat, const double val ) {
  int i, j;

  if( is_valid_m( mat ) ) {  
    for( i=0 ; i < mat.row ; ++i ) {
      for( j=0 ; j < mat.col ; ++j ) {
	mat.data[ i ][ j ] = val;
      }
    }  
  }
  else {
    SENGI_ERR( INVALID_MAT );
  }
  
  return;
}

// function that copies the source vector to the destination vector
void copy_v( const sg_vector src, sg_vector des ) {
  int i;
  
  if( is_valid_v( src ) && is_valid_v( des ) ) {
    if( src.size == des.size ) {
      for( i=0 ; i < src.size ; ++i ) {
	src.data[ i ] = des.data[ i ];
      }
    }
    else {
      SENGI_ERR( MATCH_SIZE );
    }
  }
  else {
    SENGI_ERR( INVALID_VEC );
  }
  
  return;
}

// function that copies the source matrix to the destination matrix
void copy_m( const sg_matrix src, sg_matrix des ) {
  int i, j;

  if( is_valid_m( src ) && is_valid_m( des ) ) {
    if( src.row == des.row ) {
      if( src.col == des.col ) {
	for( i=0 ; i < src.row ; ++i ) {
	  for( j=0 ; j < src.col ; ++j ) {
	    des.data[ i ][ j ] = src.data[ i ][ j ];
	  }
	}
      }
      else {
	SENGI_ERR( MATCH_COL );
      }
    }
    else {
      SENGI_ERR( MATCH_ROW );
    }
  }
  else {
    SENGI_ERR( INVALID_MAT );
  }

  return;
}

// function that returns norm of the vector
size_t norm_v( const sg_vector vec ) {
  double total = SG_DEFAULT_VALUE;
  int i;
  
  if( is_valid_v( vec ) ) {
    for( i=0 ; i < vec.size ; ++i ) {
      total += pow( vec.data[ i ], 2 );
    }

    return sqrt( total );
  }
  else {
    SENGI_ERR( INVALID_VEC );
  }
  
  return SG_INVALID_VALUE;
}

// function that returns norm of the matrix
size_t norm_m( const sg_matrix mat ) {
  double total = SG_DEFAULT_VALUE;
  int i, j;

  if( is_valid_m( mat ) ) {
    for( i=0 ; i < mat.row ; ++i ) {
      for( j=0 ; j < mat.col ; ++j ) {
	total += pow( mat.data[ i ][ j ], 2 );
      }
    }

    return sqrt( total );
  }
  else {
    SENGI_ERR( INVALID_MAT );
  }
  
  return SG_INVALID_VALUE;
}

// function that finds diagonal vector of the matrix
sg_bool diagonal_m( sg_matrix mat, sg_vector vec ) {
  int i;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( "the matrix is invalid" );
    return SG_FALSE;
  }
  else if( !is_valid_v( vec ) ) {
    SENGI_ERR( "the vector is invalid" );
    return SG_FALSE;
  }
  else if( mat.col != vec.size ) {
    SENGI_ERR( "the matrix and vector sizes do not match" );
    return SG_FALSE;
  }
  else if( mat.col > mat.row ) {
    SENGI_ERR( "the row must be bigger than the column" );
    return SG_FALSE;
  }
  else {
    for( i=0 ; i < mat.row ; ++i ) {
      vec.data[ i ] = mat.data[ i ][ i ];
    }
    
    return SG_TRUE;
  }
}

// function that extends the matrix with vector
void extend_mv( sg_matrix mat, const sg_vector vec ) {
  int i, j;
  size_t row, col;
  double **data;

  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
  }
  else if( !is_valid_v( vec ) ) {
    SENGI_ERR( INVALID_VEC );
  }
  else {
    switch( vec.type ) {
    case SG_RVEC: {
      if( mat.col != vec.size ) {
	SENGI_ERR( MATCH_COL_SIZE );
      }
      else {
	data = ( double ** ) malloc( sizeof( double * ) * ( mat.row + 1 ) );

	if( NULL == data ) {
	  SENGI_ERR( MEM_ALLOC );
	  return;
	}

	for( i=0 ; i < mat.row ; ++i ) {
	  data[ i ] = ( double * ) malloc( sizeof( double ) * mat.col );

	  if( NULL == data[ i ] ) {
	    SENGI_ERR( MEM_ALLOC );

	    for( j=0 ; j < i ; ++j ) {
	      free( data[ j ] );
	    }

	    free( data );
	    return;
	  }
	
	  memcpy( data[ i ], mat.data[ i ], mat.col );
	}

	memcpy( data[ mat.row ], vec.data, vec.size );
	row = mat.row + 1;
	col = mat.col;
	
	release_m( mat );
	mat = create_m( row, col );
	to_m( mat, data );

	for( i=0 ; i < row ; ++i ) {
	  free( data[ i ] );
	}
	
	free( data );
      } // end of else
      break;
    }
    case SG_CVEC: {
      if( mat.row != vec.size ) {
	SENGI_ERR( MATCH_ROW_SIZE );
      }
      else {
	data = ( double ** ) malloc( sizeof( double * ) * mat.row );

	if( NULL == data ) {
	  SENGI_ERR( MEM_ALLOC );
	  return;
	}

	for( i=0 ; i < mat.row ; ++i ) {
	  data[ i ] = ( double * ) malloc( sizeof( double ) * ( mat.col + 1 ) );

	  if( NULL == data[ i ] ) {
	    SENGI_ERR( MEM_ALLOC );

	    for( j=0 ; j < i ; ++j ) {
	      free( data[ j ] );
	    }
	    
	    free( data );
	    return;
	  }

	  // copy whole row data to row of new data array
	  memcpy( data[ i ], mat.data[ i ], mat.col );
	  // add the data of column vector to end of row
	  data[ i ][ mat.col ] = vec.data[ i ];
	}

	row = mat.row;
	col = mat.col + 1;
	
	release_m( mat );
	mat = create_m( row, col );
	to_m( mat, data );

	for( i=0 ; i < row ; ++i ) {
	  free( data[ i ] );
	}
	
	free( data );
      } // end of else
      break;
    }
    default: {
      SENGI_ERR( INVALID_VEC );
      break;
    }
    }
  }
  
  return;
}

// function that extends the matrix with another matrix
void extend_mm( sg_matrix aug, const sg_matrix mat ) {
  return;
}

// function that converts the array to the vector
sg_bool to_v( sg_vector vec, double *data ) {
  int i;
  
  if( !is_valid_v( vec ) ) {
    SENGI_ERR( INVALID_VEC );
    return SG_FALSE;
  }
  else if( NULL == data ) {
    SENGI_ERR( INVALID_DATA );
    return SG_FALSE;
  }

  for( i=0 ; i < vec.size ; ++i ) {
    vec.data[ i ] = data[ i ];
  }
  
  return SG_TRUE;
}

// function that converts the array to the matrix
sg_bool to_m( sg_matrix mat, double **data ) {
  int i, j;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
    return SG_FALSE;
  }
  else if( NULL == data ) {
    SENGI_ERR( INVALID_DATA );
    return SG_FALSE;
  }

  for( i=0 ; i < mat.row ; ++i ) {
    for( j=0 ; j < mat.col ; ++j ) {
      mat.data[ i ][ j ] = data[ i ][ j ];
    }
  }
  
  return SG_TRUE;
}

// function that gets a row of the matrix
sg_bool get_row_m( const sg_matrix mat, const size_t row, sg_vector vec ) {
  if( is_valid_m( mat ) && is_valid_v( vec ) ) {
    if( mat.col != vec.size ) {
      SENGI_ERR( MATCH_COL_SIZE );
      return SG_FALSE;
    }

    return to_v( vec, mat.data[ row ] );
  }

  return SG_FALSE;
}

// function that gets a column of the matrix
sg_bool get_col_m( const sg_matrix mat, const size_t col, sg_vector vec ) {
  int i;
  
  if( is_valid_m( mat ) && is_valid_v( vec ) ) {
    if( mat.row != vec.size ) {
      SENGI_ERR( MATCH_ROW_SIZE );
      return SG_FALSE;
    }

    for( i=0 ; i < mat.row ; ++i ) {
      vec.data[ i ] = mat.data[ i ][ col ];
    }
    
    return SG_TRUE;
  }

  return SG_FALSE;
}

// function that replace rows of the matrix
void replace_rows_m( sg_matrix mat, int row1, int row2 ) {
  int j;
  double temp;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
  }
  else if( ( row1 < 0 || row1 >= mat.row ) && ( row2 < 0 || row2 >= mat.row ) ) {
    SENGI_ERR( INVALID_ROW );
  }
  else {
    for( j=0 ; j < mat.col ; ++j ) {
      temp = mat.data[ row1 ][ j ];
      mat.data[ row1 ][ j ] = mat.data[ row2 ][ j ];
      mat.data[ row2 ][ j ] = temp;
    }
  }
  
  return;
}

// function that adds two matrices
void add_mm( const sg_matrix mat1, const sg_matrix mat2, sg_matrix res ) {
  int i, j;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1.row != mat2.row || mat1.row != res.row ) {
      SENGI_ERR( MATCH_ROW );
    }
    else if( mat1.col != mat2.col || mat1.col != res.col ) {
      SENGI_ERR( MATCH_COL );
    }
    else {
      for( i=0 ; i < mat1.row ; ++i ) {
	for( j=0 ; j < mat1.col ; ++j ) {
	  res.data[ i ][ j ] = mat1.data[ i ][ j ] + mat2.data[ i ][ j ];
	}
      }
    }
  }
  else {
    SENGI_ERR( INVALID_MAT );
  }
  
  return;
}

// function that substracts two matrices
void sub_mm( const sg_matrix mat1, const sg_matrix mat2, sg_matrix res ) {
  int i, j;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1.row != mat2.row || mat1.row != res.row ) {
      SENGI_ERR( MATCH_ROW );
    }
    else if( mat1.col != mat2.col || mat1.col != res.col ) {
      SENGI_ERR( MATCH_COL );
    }
    else {
      for( i=0 ; i < mat1.row ; ++i ) {
	for( j=0 ; j < mat1.col ; ++j ) {
	  res.data[ i ][ j ] = mat1.data[ i ][ j ] - mat2.data[ i ][ j ];
	}
      }
    }
  }
  else {
    SENGI_ERR( INVALID_MAT );
  }
  
  return;
}

// function that multiplies two matrices
void mult_mm( const sg_matrix mat1, const sg_matrix mat2, sg_matrix res ) {
  int i, j, k;
  double temp = SG_DEFAULT_VALUE;
  
  if( is_valid_m( mat1 ) && is_valid_m( mat2 ) && is_valid_m( res ) ) {
    if( mat1.col != mat2.row ) {
      SENGI_ERR( MATCH_ROW_COL );
    }
    else if( mat1.row != res.row ) {
      SENGI_ERR( MATCH_ROW );
    }
    else if( mat2.col != res.col ) {
      SENGI_ERR( MATCH_COL );
    }
    else {
      for( i=0 ; i < mat1.row ; ++i ) {
	for( k=0 ; k < mat2.col ; ++k ) {
	  for( j=0 ; j < mat2.row ; ++j ) {
	    temp += mat1.data[ i ][ j ] * mat2.data[ j ][ k ];
	  }

	  res.data[ i ][ k ] = temp;
	  temp = SG_DEFAULT_VALUE;
	}
      }
    }
  }
  else {
    SENGI_ERR( INVALID_MAT );
  }
  
  return;
}

// function that multiplies the matrix and the vector
void mult_mv( const sg_matrix mat, const sg_vector vec, sg_vector res ) {
  int i, j;
  double total = SG_DEFAULT_VALUE;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
  }
  else if( !is_valid_v( vec ) || !is_valid_v( res ) ) {
    SENGI_ERR( INVALID_VEC );
  }
  else {
    if( mat.col != vec.size ) {
      SENGI_ERR( MATCH_COL_SIZE );
    }
    else if( mat.row != res.size ) {
      SENGI_ERR( MATCH_ROW_SIZE );
    }
    else if( vec.type != SG_CVEC || res.type != SG_CVEC ) {
      SENGI_ERR( MUST_COL_VEC );
    }
    else {
      for( i=0 ; i < mat.row ; ++i ) {
	for( j=0 ; j < mat.col ; ++j ) {
	  total += mat.data[ i ][ j ] * vec.data[ j ];
	}

	res.data[ i ] = total;
	total = SG_DEFAULT_VALUE;
      }
    }
  }

  return;
}

// function that multiplies the vector and the matrix
void mult_vm( const sg_vector vec, const sg_matrix mat, sg_vector res ) {
  int i, j;
  double total = SG_DEFAULT_VALUE;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
  }
  else if( !is_valid_v( vec ) || !is_valid_v( res ) ) {
    SENGI_ERR( INVALID_VEC );
  }
  else {
    if( mat.row != vec.size ) {
      SENGI_ERR( MATCH_ROW_SIZE );
    }
    else if( mat.col != res.size ) {
      SENGI_ERR( MATCH_COL_SIZE );
    }
    else if( vec.type != SG_RVEC || res.type != SG_RVEC ) {
      SENGI_ERR( MUST_ROW_VEC );
    }
    else {
      for( i=0 ; i < mat.col ; ++i ) {
	for( j=0 ; j < mat.row ; ++j ) {
	  total += vec.data[ j ] * mat.data[ j ][ i ];
	}

	res.data[ i ] = total;
	total = SG_DEFAULT_VALUE;
      }
    }
  }

  return;
}

// function that adds two vectors
void add_vv( const sg_vector vec1, const sg_vector vec2, sg_vector res ) {
  int i;
  
  if( is_valid_v( vec1 ) && is_valid_v( vec2 ) && is_valid_v( res ) ) {
    if( vec1.size == vec2.size && vec1.size == res.size ) {
      for( i=0 ; i < vec1.size ; ++i ) {
	res.data[ i ] = vec1.data[ i ] + vec2.data[ i ];
      }
    }
    else {
      SENGI_ERR( MATCH_SIZE );
    }
  }
  else {
    SENGI_ERR( INVALID_VEC );
  }

  return;
}

// function that substracts two vectors
void sub_vv( const sg_vector vec1, const sg_vector vec2, sg_vector res ) {
  int i;
  
  if( is_valid_v( vec1 ) && is_valid_v( vec2 ) && is_valid_v( res ) ) {
    if( vec1.size == vec2.size && vec1.size == res.size ) {
      for( i=0 ; i < vec1.size ; ++i ) {
	res.data[ i ] = vec1.data[ i ] - vec2.data[ i ];
      }
    }
    else {
      SENGI_ERR( MATCH_SIZE );
    }
  }
  else {
    SENGI_ERR( INVALID_VEC );
  }
  
  return;
}

// function that finds dot product of two vectors
void dot_product_vv( const sg_vector vec1, const sg_vector vec2, double *res ) {
  int i;
  
  if( is_valid_v( vec1 ) && is_valid_v( vec2 ) ) {
    if( ( vec1.size == vec2.size ) &&
	( ( vec1.type == SG_RVEC && vec2.type == SG_CVEC ) ||
	  ( vec1.type == SG_CVEC && vec2.type == SG_RVEC ) ) )
      {
	if( NULL == res ) {
	  res = ( double *) calloc( SG_DEFAULT_VALUE, sizeof( double ) );
	}

	if( NULL != res ) {
	  /* if user pass pointer which has one more element,
	     function fill its first index only */
	  for( i=0 ; i < vec1.size ; ++i ) {
	    res[ 0 ] += vec1.data[ i ] * vec2.data[ i ];
	  }
	}
	else {
	  SENGI_ERR( MEM_ALLOC );
	}
      }
    else {
      SENGI_ERR( MATCH_SIZE );
    }
  }
  else {
    SENGI_ERR( INVALID_VEC );
  }
  
  return;
}

// function that finds cross product of the vectors
void cross_product_vv( const sg_vector vec1, const sg_vector vec2, sg_vector res ) {
  if( !is_valid_v( vec1 ) || !is_valid_v( vec2 ) || !is_valid_v( res ) ) {
    SENGI_ERR( INVALID_VEC );
  }
  else if( vec1.size != 3 || vec2.size != 3 || res.size != 3 ) {
    SENGI_ERR( CROSS_PRODUCT );
  }
  else {
    res.data[ 0 ] = vec1.data[ 1 ] * vec2.data[ 2 ] - vec1.data[ 2 ] * vec2.data[ 1 ];
    res.data[ 1 ] = vec1.data[ 2 ] * vec2.data[ 0 ] - vec1.data[ 0 ] * vec2.data[ 2 ];
    res.data[ 2 ] = vec1.data[ 0 ] * vec2.data[ 1 ] - vec1.data[ 1 ] * vec2.data[ 0 ];    
  }
      
  return;
}

// function that finds transpose of the matrix
void transpose_m( const sg_matrix src, sg_matrix des ) {
  int i, j;

  if( !is_valid_m( src ) || !is_valid_m( des ) ) {
    SENGI_ERR( INVALID_MAT );
  }
  else if( src.row != des.col || src.col != des.row ) {
    SENGI_ERR( MATCH_ROW_COL );
  }
  else {
    for( i=0 ; i < src.col ; ++i ) {
      for( j=0 ; j < src.row ; ++j ) {
	des.data[ i ][ j ] = src.data[ j ][ i ];
      }
    }
  }

  return;
}

// function that finds inverse matrix of the matrix
// Gauss - Jordan Elimination : [ A | I ] -> [ I | A^-1 ] 
void inverse_m( const sg_matrix src, sg_matrix des ) {
  sg_matrix mat;
  int i, j, k, n = src.row;
  double ratio;
     
  if( !is_valid_m( src ) || !is_valid_m( des ) ) {
    SENGI_ERR( INVALID_MAT );
    return;
  }
  
  if( src.row != src.col || des.row != des.col ) {
    SENGI_ERR( SQUARE_MATRIX );
    return;
  }

  if( src.row != des.row ) {
    SENGI_ERR( MATCH_ROW_COL );
    return;
  }
	
  mat = create_m( src.row, src.row );
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
    return;
  }

  copy_m( src, mat );
  fill_m( des, SG_DEFAULT_VALUE );

  for( i=0 ; i < n ; ++i ) {
    put_m( des, i, i, 1.0 );
  }

  // forward elimination
  for( i=0 ; i < (n-1) ; ++i ) {
    for( j=i+1 ; j < n ; ++j ) {
      // if divider is 0, jump over the row
      if ( mat.data[ i ][ i ] != SG_DEFAULT_VALUE ) {
	ratio = mat.data[ j ][ i ] / mat.data[ i ][ i ] ;
	
	for( k=0 ; k < n ; ++k ) {
	  mat.data[ j ][ k ] -= mat.data[ i ][ k ] * ratio;
	  des.data[ j ][ k ] -= des.data[ i ][ k ] * ratio;
	}
      }
    }
  }
  
  // backward elimination
  for( i=n-1 ; i > 0 ; --i ) {
    for( j=i-1 ; j >= 0 ; --j ) {
      if ( mat.data[ i ][ i ] != SG_DEFAULT_VALUE ) {
	ratio = mat.data[ j ][ i ] / mat.data[ i ][ i ] ;

	for( k=0 ; k < n ; ++k ) {			
	  mat.data[ j ][ k ] -= mat.data[ i ][ k ] * ratio;
	  des.data[ j ][ k ] -= des.data[ i ][ k ] * ratio;
	}
      }
    }
  }

  //dividing elements
  for( i=0 ; i < n ; ++i ) {
    ratio = mat.data[ i ][ i ];
    mat.data[ i ][ i ] /= ratio;

    for( j=0 ; j < n ; ++j ) {
      des.data[ i ][ j ] /= ratio;
    }
  }

  return;
}

// function that eliminates the source matrix
// Gauss Elimination
void eliminate_m( const sg_matrix src, sg_matrix des ) {
  int i, j, k, n = src.row;
  double ratio;
     
  if( !is_valid_m( src ) || !is_valid_m( des ) ) {
    SENGI_ERR( INVALID_MAT );
    return;
  }
  
  if( src.row != src.col || des.row != des.col ) {
    SENGI_ERR( SQUARE_MATRIX );
    return;
  }

  if( src.row != des.row ) {
    SENGI_ERR( MATCH_ROW_COL );
    return;
  }

  copy_m( src, des );
	
  // forward elimination
  for( i=0 ; i < n-1 ; ++i ) {
    for( j=i+1 ; j < n ; ++j ) {
      // if divider is 0, jump over the row
      if ( src.data[ i ][ i ] != SG_DEFAULT_VALUE ) {
	ratio = src.data[ j ][ i ] / src.data[ i ][ i ] ;
	
	for( k=i ; k < n ; ++k ) {
	  des.data[ j ][ k ] -= src.data[ i ][ k ] * ratio;
	}
      }
    }
  }

  // division
  for( i=0 ; i < n ; ++i ) {		
    for( j=0 ; j < n ; ++j ) {
      // if divider is 0, jump over the row
      if ( des.data[ i ][ j ] != SG_DEFAULT_VALUE ) {
	ratio = des.data[ i ][ j ];
	
	for( k=0 ; k < n ; ++k ) {
	  des.data[ i ][ k ] /= ratio;
	}
	
	break;
      }
    }
  }
  
  // todo
  
  return;
}

// function that find the minor of a matrix
sg_matrix minors( sg_matrix src , size_t row , size_t col ) {
  int i, j, a = 0, b = 0;
  sg_matrix n_mat = { 0, 0, NULL };

  if( !is_valid_m( src ) ) {
    SENGI_ERR( INVALID_MAT );
    return n_mat;
  }
  
  n_mat = create_m( src.row - 1 , src.col - 1 );

  for( i = 0 ; i < src.row ; ++i ) {
    if( i != row ) {
      for( j = 0 ; j < src.col ; ++j ) {
	if (j != col) {
	  n_mat.data[ a ][ b ] = src.data[ i ][ j ];
	  ++b;	
	}
      }
      
      ++a;
    }
  }

  return n_mat;
}

// function that calculate the determinant
double det( sg_matrix src ) {
  int i, j;
  double retval = SG_DEFAULT_VALUE;
    
  if( src.row != src.col ) {
    SENGI_ERR( SQUARE_MATRIX );
    return SG_INVALID_VALUE;
  }

  if( 1 == src.row ) {
    retval = src.data[ 0 ][ 0 ];
  }
  else if( 2 == src.row ) {
    retval = ( src.data[ 0 ][ 0 ] * src.data[ 1 ][ 1 ] ) - ( src.data[ 0 ][ 1 ] * src.data[ 1 ][ 0 ] );
  }
  else if( 3 == src.row ) {
    retval = (
	      ( src.data[ 0 ][ 0 ] * src.data[ 1 ][ 1 ] * src.data[ 2 ][ 2 ] )
	      +( src.data[ 1 ][ 0 ] * src.data[ 2 ][ 1 ] * src.data[ 0 ][ 2 ] )
	      +( src.data[ 2 ][ 0 ] * src.data[ 0 ][ 1 ] * src.data[ 1 ][ 2 ] )
	      -( src.data[ 0 ][ 2 ] * src.data[ 1 ][ 1 ] * src.data[ 2 ][ 0 ] )
	      -( src.data[ 1 ][ 2 ] * src.data[ 2 ][ 1 ] * src.data[ 0 ][ 0 ] )
	      -( src.data[ 2 ][ 2 ] * src.data[ 0 ][ 1 ] * src.data[ 1 ][ 0 ] )
	      );
  }
  else {
    retval = SG_DEFAULT_VALUE;

    for ( i=0 ;  ;  ) {
      for( j=0 ; j < src.col ; ++j ) {
	retval += pow( -1, ( i + j + 2 ) ) * src.data[ i ][ j ] * det( minors( src , i , j ) );	
      } 

      break;
    }
  }

  return retval;
}

// function that scales the vector with val
void scale_v( sg_vector vec, const double val ) {
  int i;
  
  if( !is_valid_v( vec ) ) {
    SENGI_ERR( INVALID_VEC );
  }
  else {
    for( i=0 ; i < vec.size ; ++i ) {
      vec.data[ i ] = val * vec.data[ i ];
    }
  }

  return;
}

// function that scales the matrix with val
void scale_m( sg_matrix mat, const double val ) {
  int i, j;
  
  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
  }
  else {
    for( i=0 ; i < mat.row ; ++i ) {
      for( j=0 ; j < mat.col ; ++j ) {
	mat.data[ i ][ j ] = val * mat.data[ i ][ j ];
      }
    }
  }

  return;
}

// function that prints the vector
void print_v( const sg_vector vec ) {
  int i;

  if( !is_valid_v( vec ) ) {
    SENGI_ERR( INVALID_VEC );
  }
  else if( SG_RVEC == vec.type ) {
    for( i=0 ; i < vec.size ; ++i ) {
      fprintf( stdout, "%f ", vec.data[ i ] );
    }
    
    fprintf( stdout, "%s", "\n" );
  }
  else {
    for( i=0 ; i < vec.size ; ++i ) {
      fprintf( stdout, "%f\n", vec.data[ i ] );
    }
  }

  return;
}

// function that prints the matrix
void print_m( const sg_matrix mat ) {
  int i, j;

  if( !is_valid_m( mat ) ) {
    SENGI_ERR( INVALID_MAT );
  }
  else {
    for( i=0 ; i < mat.row ; ++i ) {
      for( j=0 ; j < mat.col ; ++j ) {
	fprintf( stdout, "%f ", mat.data[ i ][ j ] );
      }
      
      fprintf( stdout, "%s", "\n" );
    }

    fprintf( stdout, "%s", "\n" );
  }

  return;
}

// function that checks whether the vector is valid
sg_bool is_valid_v( const sg_vector vec ) {
  if( vec.size < 1 ) {
    return SG_FALSE;
  }

  if( NULL == vec.data ) {
    return SG_FALSE;
  }

  if( !( SG_RVEC == vec.type || SG_CVEC == vec.type ) ) {
    return SG_FALSE;
  }
  
  return SG_TRUE;
}

// function that checks whether the matrix is valid
sg_bool is_valid_m( const sg_matrix mat ) {
  if( mat.row < 2 || mat.col < 2 ) {
    return SG_FALSE;
  }

  if( NULL == mat.data ) {
    return SG_FALSE;
  }

  return SG_TRUE;
}
