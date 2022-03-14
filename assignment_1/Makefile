COMPILER = gcc
CCFLAGS = -std=c99 -ggdb -o

a: pgmEcho.c fileCheck.c pgmImage.c
	${COMPILER} ${CCFLAGS} pgmEcho pgmEcho.c fileCheck.c pgmImage.c -I.
b: pgmComp.c fileCheck.c pgmImage.c
	${COMPILER} ${CCFLAGS} pgmComp pgmComp.c fileCheck.c pgmImage.c -I.
a: pgma2b.c fileCheck.c pgmImage.c
	${COMPILER} ${CCFLAGS} pgma2b pgma2b.c fileCheck.c pgmImage.c -I.
a: pgmb2a.c fileCheck.c pgmImage.c
	${COMPILER} ${CCFLAGS} pgmb2a pgmb2a.c fileCheck.c pgmImage.c -I.