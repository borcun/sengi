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
	${AR} -cvq lib/libsgbase.a src/sg_base.o
	${AR} -cvq lib/libsgutil.a src/sg_util.o

clean: ${OBJ}
	${RM} -rf ${OBJ} ${LIB}
