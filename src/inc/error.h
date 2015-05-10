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

#define INVALID_MAT    "the matrix is invalid"
#define INVALID_VEC    "the vector is invalid"
#define INVALID_ROW    "the row value is invalid"
#define INVALID_COL    "the column value is invalid"
#define INVALID_SIZE   "the size value is invalid"
#define INVALID_INDEX  "the index value is invalid"
#define FAILED_MAT     "the matrix can not be created"
#define FAILED_VEC     "the vector can not be created"
#define NOT_MATCH_ROW  "the matrix rows do not match"
#define NOT_MATCH_COL  "the matrix columns do not match"
#define NOT_MATCH_SIZE "the vector sizes do not match"

#endif
