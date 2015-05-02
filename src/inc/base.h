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
/// @param data - double data array
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
/// @return if filling is success, return true. Otherwise, return false.
bool_t fill_v( vector_t vec, const double val );
		   
/// \brief function that fills matrix with value
/// @param mat - matrix
/// @param param - parameter
/// @return if filling is success, return true. Otherwise, return false.
bool_t fill_m( matrix_t mat, const double val );

/// \brief function that copies source vector to destination vector
/// @param src - source vector
/// @param des - destination vector
/// @return -
void copy_vv( vector_t src, vector_t des );

/// \brief function that copies source matrix to destination matrix
/// @param src - source matrix
/// @param des - destination matrix
/// @return -
void copy_mm( matrix_t src, matrix_t des );

/// \brief function that converts data array to vector
/// @param vec - vector
/// @param data - data array
/// @return if the convertion is success, return true. Otherwise, return false.
bool_t to_v( vector_t vec, const double *data );

/// \brief function that gets row of matrix which is indicated by row index
/// @param mat - matrix
/// @param row - matrix row index
/// @param vec - vector
/// @return if operation is success, return true. Otherwise, return false.
bool_t get_row_m( const matrix_t mat, const size_t row, vector_t vec );

/// \brief function that gets column of matrix which is indicated by col index
/// @param mat - matrix
/// @param col - matrix column index
/// @param vec - vector
/// @return if operation is success, return true. Otherwise, return false.
bool_t get_col_m( const matrix_t mat, const size_t col, vector_t vec );

/// \brief function that adds two matrices
/// @param mat1 - first matrix
/// @param mat2 - second matrix
/// @param res - result matrix
/// @return -
void add_mm( matrix_t mat1, matrix_t mat2, matrix_t res );

/// \brief function that subtracts two matrices
/// @param mat1 - first matrix
/// @param mat2 - second matrix
/// @param res - result matrix
/// @return -
void sub_mm( matrix_t mat1, matrix_t mat2, matrix_t res );

/// \brief function that multiplies two matrices
/// @param mat1 - first matrix
/// @param mat2 - second matrix
/// @param res - result matrix
/// @return -
void mult_mm( matrix_t mat1, matrix_t mat2, matrix_t res );

/// \brief function that adds two vectors
/// @param vec1 - first vector
/// @param vec2 - second vector
/// @param res - result vector
/// @return -
void add_vv( vector_t vec1, vector_t vec2, vector_t res );

/// \brief function that subtracts two vectors
/// @param vec1 - first vector
/// @param vec2 - second vector
/// @param res - result vector
/// @return -
void sub_vv( vector_t vec1, vector_t vec2, vector_t res );

/// \brief function that performs dot product of two vectors
/// @param vec1 - first vector
/// @param vec2 - second vector
/// @param res - result
/// @return -
void dot_product_vv( vector_t vec1, vector_t vec2, double *res );

/// \brief function that performs cross product of two vectors
/// @param vec1 - first vector
/// @param vec2 - second vector
/// @param res - result vector
/// @return -
void cross_product_vv( vector_t vec1, vector_t vec2, vector_t res );

/// \brief function that transposes the source matrix and copies it to destination matrix
/// @param src - source matrix
/// @param des - destination matrix
/// @return if transpose operation is success, return true. Otherwise, return false.
bool_t transpose_m( const matrix_t src, matrix_t des );

/// \brief function that finds inverse of matrix
/// the inverse method is Gauss-Jordan elimination
/// @param mat - matrix
/// @return if inverse operation is success, return true. Otherwise, return false.
bool_t inverse_m( const matrix_t src, matrix_t des ); 

/// \brief function that eliminate matrix via Gauss method
/// @param src - source matrix
/// @param des - destination matrix
/// @return if elimination is success, return true. Otherwise, return false.
bool_t eliminate_m( const matrix_t src, matrix_t des );

/// \brief function that scales vector with a number
/// @param vec - vector
/// @param num - number
/// @return -
void scale_v( vector_t vec, const double num ); 

/// \brief function that scales matrix with a number
/// @param mat - matrix
/// @param num - number
/// @return -
void scale_m( matrix_t matrix, const double num );

/// \brief function that prints vector
/// @param vec - vector
/// @return -
void print_v( const vector_t vec );

/// \brief function that prints matrix
/// @param mat - matrix
/// @return -
void print_m( const matrix_t m );

/// \brief function that checks whether the vector is valid
/// @param vec - vector
/// @return if the vector is valid, return true. Otherwise, return false. 
bool_t is_valid_v( vector_t vec );

/// \brief function that checks whether the matrix is valid
/// @param mat - matrix
/// @return if the matrix is valid, return true. Otherwise, return false. 
bool_t is_valid_m( matrix_t mat );

#endif
