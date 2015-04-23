#include "base.h"

int main( int argc, char **argv ) {
  vector_t vec1 = createV( 3 );

  releaseV( vec1 );

  return 0;
}
