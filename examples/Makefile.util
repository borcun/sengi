all:
	gcc -c -Wall util_test.c -I ../src/inc
	gcc util_test.o -o util_test -lbase -lutil -L ../lib -lm

clean:
	rm -rf util_test.o util_test
