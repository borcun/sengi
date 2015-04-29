
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

#define SENGI_ERR( msg ) fprintf( stderr, "%s\n", msg ) 

/// \brief function that creates a row vector
/// @param len - vector element size
/// @return if vector is created, return the vector. Otherwise, return NULL.
vector_t create_rv( const size_t size );

/// \brief function that creates a column vector
/// @param len - vector element size
/// @return if vector is created, return the vector. Otherwise, return NULL.
vector_t create_cv( const size_t size );

/// \brief funtion that creates a matrix
/// @param row - matrix row size
/// @param col - matrix column size
/// @return if matrix is created, return the matrix. Otherwise, return NULL.
matrix_t create_m( const size_t row, const size_t col );

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
void fill_v( vector_t vec, const double val );

/// \brief function that fills matrix with value
/// @param mat - matrix
/// @param param - parameter
/// @return -
void fill_m( matrix_t mat, const double val );

/// \brief function that transposes the source matrix and copies it to destination matrix
/// @param src - source matrix
/// @param des - destination matrix
/// @return -
void transpose_m( matrix_t src, matrix_t des );

/// \brief function that finds inverse of matrix
/// the inverse method is Gauss-Jordan elimination
/// @param mat - matrix
/// @return -
void inverse_m( matrix_t mat ); 

/// \brief function that prints vector
/// @param vec - vector
/// @return -
void print_v( const vector_t vec );

/// \brief function that prints matrix
/// @param mat - matrix
/// @return -
void print_m( const matrix_t m );

#endif
