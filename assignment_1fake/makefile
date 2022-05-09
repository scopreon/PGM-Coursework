CC=gcc
CCFLAGS=-g -std=c99 -Wall -Werror
CFLAGS=-std=c99
MODULES=fileCheck.o pgmImage.o
MAINS=pgmEcho.o
TARGETS=pgmEcho

all:	${TARGETS}

clean:
	rm ${TARGETS} ${MAINS} ${MODULES}

pgmEcho:	pgmEcho.o ${MODULES}
	${CC}	${CCFLAGS}	-o pgmEcho	pgmEcho.o	${MODULES}
