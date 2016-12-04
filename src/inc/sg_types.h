/**
 * @file sg_types.h
 * @brief types header file
 * @date April 23, 2015
 * @author boo
 * @copyright free software
 */

#ifndef SG_TYPES_H
#define SG_TYPES_H 

#include <stdio.h>
#include <stdlib.h>

//! sengi default value
#define SG_DEFAULT_VALUE ( 0.0f )

//! sengi invalid value
#define SG_INVALID_VALUE ( -1 )

/// \brief enum sg_bool, boolean enumeration
typedef enum {
  //! sengi false type
  SG_FALSE,

  //! sengi true type
  SG_TRUE
  
} sg_bool;

/// \brief enum sg_vector_t, row or column vector enumeration
typedef enum {
  //! invalid vector type
  SG_INVVEC, 

  //! row vector
  SG_RVEC,

  //! column vector
  SG_CVEC
  
} sg_vector_t;

/// \brief struct sg_vector, vector data structure
struct sg_vector {
  size_t size;      /**< vector element size */
  sg_vector_t type; /**< vector type such as row or column */
  double *data;     /**< vector data array */
};

/// \brief struct sg_matrix, matrix data structure
struct sg_matrix {
  size_t row;     /**< matrix row size */
  size_t col;     /**< matrix column size */
  double **data;  /**< matrix data array */
};

//! typedef for struct sg_vector 
typedef struct sg_vector sg_vector;

//! typedef for struct sg_matrix
typedef struct sg_matrix sg_matrix;

#endif
