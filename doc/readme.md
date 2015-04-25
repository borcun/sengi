this file is dummy file for library design now.

types.h - file contains vector, matrix and some types of library
					this types will be structure and union.
					
base.h - this header contains base operations of types as arithmetic operations.
base.c - this source file contains function implementation of base header.

libalg.h - the header file contains complex function prototypes such as decomposition, eliminations.
libalg.c - the source file contains function implementation of libalg.h

util.h - the file contains utility functions prototypes. ?
util.c - it contains prototype implementations of util.h

types.h -> base.h -> libalg.h : header inclusive sequence

doxygen file will be created.
static and dynamic library files will be created.
each function will be test, so the several test functions will be implemented.
each function will be sampled, the example directory will be filled :)

types.h
=======
struct vector ( zeros, ones )
struct matrix ( zeros, ones, hessian matrix, computer vision special matrices etc. )

base.h
======
arithmetic operations, inverse, transpose, diagonal, reverse vector
fill and to_array functions
file operations ( read from file, write to file ... )

libalg.h
=========
decompositions, eliminations, solver functions
