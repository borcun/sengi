/**
 * @file sg_error.h
 * @brief error header
 * @details
 * @ingroup SG_ERROR
 * @author boo
 * @date May 10, 2015
 * @copyright free software
 * @bug
 */

#ifndef SG_ERROR_H
#define SG_ERROR_H

//! sengi error function
#define SENGI_ERR( msg ) fprintf( stderr, "%s\n", msg )

//! memory allocation error
#define MEM_ALLOC      "memory allocation error occurs"

//! invalid matrix error
#define INVALID_MAT    "the matrix is invalid"

//! invalid vector error
#define INVALID_VEC    "the vector is invalid"

//! invalid row value
#define INVALID_ROW    "the row value is invalid"

//! invalid column value
#define INVALID_COL    "the column value is invalid"

//! invalid size
#define INVALID_SIZE   "the size value is invalid"

//! invalid index
#define INVALID_INDEX  "the index value is invalid"

//! invalid data
#define INVALID_DATA   "the data is invalid"

//! invalid path
#define INVALID_PATH   "the file path is invalid"

//! file not opened error
#define NOT_OPENED     "the file can not be opened"

//! column vector error
#define MUST_COL_VEC   "the vector must be column vector"

//! row vector error
#define MUST_ROW_VEC   "the vector must be row vector"

//! unmatched row error
#define MATCH_ROW      "the matrix rows do not match"

//! unmatched column error
#define MATCH_COL      "the matrix columns do not match"

//! row-column unmatched error
#define MATCH_ROW_COL  "the row and column of the matrices do not match"

//! unmatched vector size
#define MATCH_SIZE     "the vector sizes do not match"

//! unmatched vector-matrix row size
#define MATCH_ROW_SIZE "the matrix row and the vector size do not match" 

//! unmatched vector-matrix column size
#define MATCH_COL_SIZE "the matrix column and the vector size do not match" 

//! cross product vector
// @todo fix error message
#define CROSS_PRODUCT  "the vector sizes have to be 3D"

//! square matrix error
#define SQUARE_MATRIX  "the matrix must be square"

#endif
