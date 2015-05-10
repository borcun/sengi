/**
 * @file error.h
 * @brief error header
 * @author boo
 * @date May 10, 2015
 * @copyright free software
 */

#ifndef ERROR_H
#define ERROR_H

//! sengi error function
#define SENGI_ERR( msg ) fprintf( stderr, "%s\n", msg )

#define MEM_ALLOC      "memory allocation error occurs"
#define INVALID_MAT    "the matrix is invalid"
#define INVALID_VEC    "the vector is invalid"
#define INVALID_ROW    "the row value is invalid"
#define INVALID_COL    "the column value is invalid"
#define INVALID_SIZE   "the size value is invalid"
#define INVALID_INDEX  "the index value is invalid"
#define INVALID_DATA   "the data is invalid"
#define MUST_COL_VEC   "the vector must be column vector"
#define MUST_ROW_VEC   "the vector must be row vector"
#define MATCH_ROW      "the matrix rows do not match"
#define MATCH_COL      "the matrix columns do not match"
#define MATCH_ROW_COL  "the row and column of the matrices do not match"
#define MATCH_SIZE     "the vector sizes do not match"
#define MATCH_ROW_SIZE "the matrix row and the vector size do not match" 
#define MATCH_COL_SIZE "the matrix column and the vector size do not match" 
#define CROSS_PRODUCT  "the vector sizes have to be 3D"
#endif
