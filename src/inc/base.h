/**
 * @file base.h
 * @brief libalg basic functions
 * @data April 23, 2015
 * @author boo
 * @copyright free software
 */

#include "types.h"

#ifndef TYPES_H
#define TYPES_H

#define LIBALG_ERR( msg ) fprintf( stderr, "%s\n", msg ) 

/// \brief function that creates a vector
/// @param len - vector element size
/// @return if vector is created, return the vector. Otherwise, return NULL.
vector_t *createV( size_t size );

/// \brief funtion that creates a matrix
/// @param row - matrix row size
/// @param col - matrix column size
/// @return if matrix is created, return the matrix. Otherwise, return NULL.
matrix_t *createM( size_t row, size_t col );

/// \brief function that releases vector
/// @param vec - vector
/// @return -
void releaseV( vector_t *vec );

/// \brief function that releases matrix
/// @param mat - matrix
/// @return -
void releaseM( matrix_t *mat );

#endif
