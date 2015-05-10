/**
 * @file types.h
 * @brief types header file
 * @date April 23, 2015
 * @author boo
 * @copyright free software
 */

#ifndef TYPES_H
#define TYPES_H 

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_VAL 0.0

//! boolean enumeration
typedef enum {
  FALSE, /**< false type */
  TRUE   /**< true type */
} bool_t;

//! row or column vector enumeration
typedef enum {
  RVEC, /**< row vector */
  CVEC  /**< column vector */
} vt_t;

//! vector data structure
struct vector_t {
  size_t size;  /**< vector element size */
  vt_t type;    /**< vector type such as row or column */
  double *data; /**< vector data array */
};

//! matrix data structure
struct matrix_t {
  size_t row;     /**< matrix row size */
  size_t col;     /**< matrix column size */
  double **data;  /**< matrix data array */
};

typedef struct vector_t * vector_t;
typedef struct matrix_t * matrix_t;

#endif
