CC = gcc
INC = src/inc/
SRC = src/base/*.c src/util/*.c
OBJ = src/*.o
LIB = lib/*.a
RM = rm
AR = ar
MV = mv

all: ${SRC}
	${CC} -c -Wall ${SRC} -I ${INC}
	${MV} *.o src
	${AR} -cvq lib/libbase.a src/base.o
	${AR} -cvq lib/libutil.a src/util.o

clean: ${OBJ}
	${RM} -rf ${OBJ} ${LIB}
