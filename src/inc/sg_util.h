/**
 * @file sg_util.h
 * @brief sengi library utility header
 * @author boo
 * @date May 28, 2015
 * @copyright free software
 */

#ifndef SG_UTIL_H
#define SG_UTIL_H

#include "sg_base.h"

/// \brief function that reads a vector from file
/// @param path - file path
/// @return vector or NULL
sg_vector read_v( const char *path );

/// \brief function that reads a matrix from file
/// @param path - file path
/// @return matrix or NULL
sg_matrix read_m( const char *path );

/// \brief function that writes a vector into file
/// @param path - file path
/// @param vec - vector
/// @return -
void write_v( const char *path, const sg_vector vec );

/// \brief function that writes a matrix into file
/// @param path - file path
/// @param mat - matrix
/// @return -
void write_m( const char *path, const sg_matrix mat );

#endif
