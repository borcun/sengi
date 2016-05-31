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

#define SG_DEFAULT_VALUE 0.0
#define SG_INVALID_VALUE -1

//! boolean enumeration
typedef enum {
  SG_FALSE, /**< false type */
  SG_TRUE   /**< true type */
} sg_bool;

//! row or column vector enumeration
typedef enum {
  SG_INVVEC, /**< invalid vector type */
  SG_RVEC,   /**< row vector */
  SG_CVEC    /**< column vector */
} sg_vector_t;

//! vector data structure
struct sg_vector {
  size_t size;      /**< vector element size */
  sg_vector_t type; /**< vector type such as row or column */
  double *data;     /**< vector data array */
};

//! matrix data structure
struct sg_matrix {
  size_t row;     /**< matrix row size */
  size_t col;     /**< matrix column size */
  double **data;  /**< matrix data array */
};

typedef struct sg_vector sg_vector;
typedef struct sg_matrix sg_matrix;

#endif
