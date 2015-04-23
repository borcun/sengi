/**
 * @file types.h
 * @brief types header file
 * @date April 23, 2015
 * @author boo
 * @copyright free software
 */

#include <stdio.h>
#include <stdlib.h>

//! boolean enumeration
typedef enum {
  FALSE, /**< false type */
  TRUE   /**< true type */
} bool_t;

//! vector data structure
typedef struct {
  size_t size;  /**< vector element size */
  double *data; /**< vector data array */
} vector_t;

//! matrix data structure
typedef struct {
  size_t row;    /**< matrix row size */
  size_t col;    /**< matrix column size */
  double **data;  /**< matrix data array */
} matrix_t;
