CC = gcc
INC = src/inc/
SRC = src/base/*.c src/util/*.c src/main.c
OBJ = src/base/*.o src/util/*.o
LIB = *.so
RM = rm

all: ${SRC}
	${CC} -c -Wall ${SRC} -I ${INC}

clean: ${OBJ}
	${RM} -rf ${OBJ}
