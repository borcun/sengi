all:
	gcc -c -Wall base_test.c -I ../../src/inc
	gcc base_test.o -o base_test -lsgbase -L ../../lib -lm

clean:
	rm -rf base_test.o base_test
