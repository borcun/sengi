/**
 * @file sg_base.h
 * @brief sengi library basic functions
 * @details
 * @ingroup SG_BASE
 * @date April 23, 2015
 * @author boo
 * @copyright free software
 * @todo compherensive test functions for whole SENGI library 
 * @bug
 */

#include <math.h>
#include <string.h>
#include "sg_types.h"
#include "sg_error.h"

#ifndef SG_BASE_H
#define SG_BASE_H

/// \brief function that creates a row vector
/// @param size - row vector size
/// @return if vector is created, return the vector. Otherwise, return NULL.
sg_vector create_rv( const size_t size );

/// \brief function that creates a column vector
/// @param size - column vector size
/// @return if vector is created, return the vector. Otherwise, return NULL.
sg_vector create_cv( const size_t size );

/// \brief funtion that creates a matrix
/// @param row - matrix row size
/// @param col - matrix column size
/// @return if matrix is created, return the matrix. Otherwise, return NULL.
sg_matrix create_m( const size_t row, const size_t col );

/// \brief function that creates identity matrix
/// @param size - matrix size
/// @return if matrix is created, return the matrix. Otherwise, return NULL.
sg_matrix create_im( const size_t size );

/// \brief function that releases vector
/// @param vec - vector
/// @return -
void release_v( sg_vector vec );

/// \brief function that releases matrix
/// @param mat - matrix
/// @return -
void release_m( sg_matrix mat );

/// \brief function that puts the value into the vector
/// @param vec - vector
/// @param index - index
/// @param val - value
/// @return -
void put_v( sg_vector vec, const size_t index, const double val );

/// \brief function that puts the value into the matrix
/// @param mat - matrix
/// @param row - row index
/// @param col - column index
/// @param val - value
/// @return -
void put_m( sg_matrix mat, const size_t row, const size_t col, const double val );

/// \brief function that fills vector with value
/// @param vec - vector
/// @param val - value
/// @return -
void fill_v( sg_vector vec, const double val );
		   
/// \brief function that fills matrix with value
/// @param mat - matrix
/// @param val - value
/// @return -
void fill_m( sg_matrix mat, const double val );

/// \brief function that copies source vector to destination vector
/// @param src - source vector
/// @param des - destination vector
/// @return -
void copy_v( const sg_vector src, sg_vector des );

/// \brief function that copies source matrix to destination matrix
/// @param src - source matrix
/// @param des - destination matrix
/// @return -
void copy_m( const sg_matrix src, sg_matrix des );

/// \brief function that finds norm of vector
/// @param vec - vector
/// @return if the vector is valid, return norm of vector. Otherwise, return -1.
size_t norm_v( const sg_vector vec );

/// \brief function that finds norm of matrix
/// @param mat - matrix
/// @return if the matrix is valid, return norm of matrix. Otherwise, return -1.
size_t norm_m( const sg_matrix mat );

/// \brief function that gets diagonal of matrix
/// @param mat - matrix
/// @param diag - diagonal vector
/// @return if the matrix is suitable for finding diagonal, return SG_TRUE. Otherwise, return SG_FALSE.
sg_bool diagonal_m( sg_matrix mat, sg_vector diag );

/// \brief function that gets sum of diagonal elements of square matrix
/// @note if the matrix is valid, t is set to trace. Otherwise, set to NULL.
/// @warning the matrix must be square.
/// @param mat - matrix
/// @param t - trace value
/// @return if the operation is successfully, return SG_TRUE. Otherwise, return SG_FALSE.
sg_bool trace_m( sg_matrix mat, double *t );

/// \brief function that extends matrix with the vector according to vector type
/// @param mat - matrix
/// @param vec - vector
/// @return -
void extend_mv( sg_matrix mat, const sg_vector vec );

/// \brief function that extends matrix with the matrix
/// @param aug - augmented matrix
/// @param mat - matrix
/// @return -
void extend_mm( sg_matrix aug, const sg_matrix mat );

/// \brief function that converts data array to vector
/// @param vec - vector
/// @param data - data array
/// @return if the convertion is success, return SG_TRUE. Otherwise, return SG_FALSE.
sg_bool to_v( sg_vector vec, double *data );

/// \brief function that converts data array to matrix
/// @param mat - matrix
/// @param data - data array
/// @return if the convertion is success, return SG_TRUE. Otherwise, return SG_FALSE.
sg_bool to_m( sg_matrix mat, double **data );

/// \brief function that gets row of matrix which is indicated by row index
/// @param mat - matrix
/// @param row - matrix row index
/// @param vec - vector
/// @return if operation is success, return SG_TRUE. Otherwise, return SG_FALSE.
sg_bool get_row_m( const sg_matrix mat, const size_t row, sg_vector vec );

/// \brief function that gets column of matrix which is indicated by col index
/// @param mat - matrix
/// @param col - matrix column index
/// @param vec - vector
/// @return if operation is success, return SG_TRUE. Otherwise, return SG_FALSE.
sg_bool get_col_m( const sg_matrix mat, const size_t col, sg_vector vec );

/// \brief function that replaces rows of matrix
/// @param mat - matrix
/// @param row1 - first row index
/// @param row2 - second row index
/// @return -
void replace_rows_m( sg_matrix mat, int row1, int row2 );

/// \brief function that adds two matrices
/// @param mat1 - first matrix
/// @param mat2 - second matrix
/// @param res - result matrix
/// @return -
void add_mm( const sg_matrix mat1, const sg_matrix mat2, sg_matrix res );

/// \brief function that subtracts two matrices
/// @param mat1 - first matrix
/// @param mat2 - second matrix
/// @param res - result matrix
/// @return -
void sub_mm( const sg_matrix mat1, const sg_matrix mat2, sg_matrix res );

/// \brief function that multiplies two matrices
/// @param mat1 - first matrix
/// @param mat2 - second matrix
/// @param res - result matrix
/// @return -
void mult_mm( const sg_matrix mat1, const sg_matrix mat2, sg_matrix res );

/// \brief function that multiplies matrix and vector
/// @param mat - matrix
/// @param vec - vector
/// @param res - result vector
/// @return -
void mult_mv( const sg_matrix mat, const sg_vector vec, sg_vector res );

/// \brief function that multiplies vector and matrix
/// @param vec - vector
/// @param mat - matrix
/// @param res - result matrix
/// @return -
void mult_vm( const sg_vector vec, const sg_matrix mat, sg_vector res );

/// \brief function that adds two vectors
/// @param vec1 - first vector
/// @param vec2 - second vector
/// @param res - result vector
/// @return -
void add_vv( const sg_vector vec1, const sg_vector vec2, sg_vector res );

/// \brief function that subtracts two vectors
/// @param vec1 - first vector
/// @param vec2 - second vector
/// @param res - result vector
/// @return -
void sub_vv( const sg_vector vec1, const sg_vector vec2, sg_vector res );

/// \brief function that performs dot product of two vectors
/// @param vec1 - first vector
/// @param vec2 - second vector
/// @param res - result
/// @return -
void dot_product_vv( const sg_vector vec1, const sg_vector vec2, double *res );

/// \brief function that performs cross product of two vectors
/// @param vec1 - first vector
/// @param vec2 - second vector
/// @param res - result vector
/// @return -
void cross_product_vv( const sg_vector vec1, const sg_vector vec2, sg_vector res );

/// \brief function that transposes the source matrix and copies it to destination matrix
/// @param src - source matrix
/// @param des - destination matrix
/// @return -
void transpose_m( const sg_matrix src, sg_matrix des );

/// \brief function that finds inverse of matrix
/// @note the inverse method is Gauss-Jordan elimination
/// @param src - source matrix
/// @param des - destination matrix
/// @return -
void inverse_m( const sg_matrix src, sg_matrix des ); 

/// \brief function that eliminate matrix via Gauss method
/// @param src - source matrix
/// @param des - destination matrix
/// @return -
void eliminate_m( const sg_matrix src, sg_matrix des );

/// \brief function that scales vector with a number
/// @param vec - vector
/// @param val - value
/// @return -
void scale_v( sg_vector vec, const double val ); 

/// \brief function that scales matrix with a number
/// @param mat - matrix
/// @param val - value
/// @return -
void scale_m( sg_matrix mat, const double val );

/// \brief function that prints vector
/// @param vec - vector
/// @return -
void print_v( const sg_vector vec );

/// \brief function that prints matrix
/// @param mat - matrix
/// @return -
void print_m( const sg_matrix mat );

/// \brief function that find minors
/// @param src - matrix
/// @param row - row index
/// @param col - column index
/// @return - minors of that matrix
sg_matrix minors( sg_matrix src , size_t row , size_t col );

/// \brief fucntion that find the detarminant
///@param src - matrix
///@return deteminant of matrix
double det( sg_matrix src );

/// \brief function that checks whether the vector is valid
/// @param vec - vector
/// @return if the vector is valid, return SG_TRUE. Otherwise, return SG_FALSE. 
sg_bool is_valid_v( const sg_vector vec );

/// \brief function that checks whether the matrix is valid
/// @param mat - matrix
/// @return if the matrix is valid, return SG_TRUE. Otherwise, return SG_FALSE.
sg_bool is_valid_m( const sg_matrix mat );

#endif
