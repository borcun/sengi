all:
	gcc -c -Wall trace_test.c -I ../../src/inc
	gcc trace_test.o -o trace_test -lsgbase -L ../../lib -lm

clean:
	rm -rf trace_test.o trace_test
