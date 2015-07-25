all:
	gcc -c -Wall determinant.c -I ../../src/inc
	gcc determinant.o -o determinant -lbase -L ../../lib -lm

clean:
	rm -rf determinant.o determinant
