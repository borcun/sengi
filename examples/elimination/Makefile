all:
	gcc -c -Wall elimination_test.c -I ../../src/inc
	gcc elimination_test.o -o elimination_test -lbase -L ../../lib -lm

clean:
	rm -rf elimination_test.o elimination_test
