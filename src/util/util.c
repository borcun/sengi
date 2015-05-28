#include "../inc/util.h"

// function that reads a vector from file
vector_t read_v( const char *path ) {
	FILE *fptr;
	vector_t vec = NULL;
	size_t i;
	size_t size;
	double data;

	if( NULL == path ) {
		SENGI_ERR( INVALID_PATH );
		return NULL;
	}

	if( NULL == ( fptr = fopen( path, "r" ) ) ) {
		SENGI_ERR( NOT_OPENED );
		return NULL;
	}

	fscanf( fptr, "%zu", &size );

	if( size < 1 ) {
		SENGI_ERR( INVALID_SIZE );
		return NULL;
	}

	vec = create_rv( size );

	if( !is_valid_v( vec ) )
		SENGI_ERR( INVALID_VEC );
	else {
		for( i=0 ; i < size ; ++i ) {
			fscanf( fptr, "%lf", &data );
			put_v( vec, i, data );
		}
	}

	fclose( fptr );
	return vec;
}

// function that reads a matrix from file
matrix_t read_m( const char *path ) {
	FILE *fptr;
	matrix_t mat = NULL;
	
	if( NULL == path ) {
		SENGI_ERR( INVALID_PATH );
		return NULL;
	}

	if( NULL == ( fptr = fopen( path, "r" ) ) ) {
		SENGI_ERR( NOT_OPENED );
		return NULL;
	}

	fclose( fptr );

	return mat;
}

// function that writes a vector into file
void write_v( const char *path, const vector_t vec ) {
	return;
}

// function that writes a matrix into file
void write_m( const char *path, const matrix_t mat ) {
	return;
}
