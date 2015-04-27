/**
 * @file base.h
 * @brief libalg basic functions
 * @data April 23, 2015
 * @author boo
 * @copyright free software
 */

#include "types.h"

#ifndef BASE_H
#define BASE_H

#define LIBALG_ERR( msg ) fprintf( stderr, "%s\n", msg ) 

/// \brief function that creates a row vector
/// @param len - vector element size
/// @return if vector is created, return the vector. Otherwise, return NULL.
vector_t create_rv( size_t size );

/// \brief function that creates a column vector
/// @param len - vector element size
/// @return if vector is created, return the vector. Otherwise, return NULL.
vector_t create_cv( size_t size );

/// \brief funtion that creates a matrix
/// @param row - matrix row size
/// @param col - matrix column size
/// @return if matrix is created, return the matrix. Otherwise, return NULL.
matrix_t create_m( size_t row, size_t col );

/// \brief function that releases vector
/// @param vec - vector
/// @return -
void release_v( vector_t vec );

/// \brief function that releases matrix
/// @param mat - matrix
/// @return -
void release_m( matrix_t mat );

/// \brief function that fills vector with value
/// @param vec - vector
/// @param val - value
/// @return -
void fill_v( vector_t vec, double val );

/// \brief function that fills matrix with value
/// @param mat - matrix
/// @param param - parameter
/// @return -
void fill_m( matrix_t mat, double val );

/// \brief function that prints vector
/// @param vec - vector
/// @return -
void print_v( vector_t vec );

/// \brief function that prints matrix
/// @param mat - matrix
/// @return -
void print_m( matrix_t m );

#endif
