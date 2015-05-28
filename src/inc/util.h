/**
 * @file util.h
 * @brief sengi library utility header
 * @author boo
 * @date May 28, 2015
 * @copyright free software
 */

#ifndef UTIL_H
#define UTIL_H

#include "base.h"

/// \brief function that reads a vector from file
/// @param path - file path
/// @return if a vector can be created, return it. Otherwise, return NULL.
vector_t read_v( const char *path );

/// \brief function that reads a matrix from file
/// @param path - file path
/// @return if a matrix can be created, return it. Otherwise, return NULL.
matrix_t read_m( const char *path );

/// \brief function that writes a vector into file
/// @param path - file path
/// @param vec - vector
/// @return -
void write_v( const char *path, const vector_t vec );

/// \brief function that writes a matrix into file
/// @param path - file path
/// @param mat - matrix
/// @return -
void write_m( const char *path, const matrix_t mat );

#endif
