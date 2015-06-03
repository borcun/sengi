all:
	gcc -c -Wall inverse_test.c -I ../../src/inc
	gcc inverse_test.o -o inverse_test -lbase -L ../../lib -lm

clean:
	rm -rf inverse_test.o inverse_test
