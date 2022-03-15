all : pgmEcho pgmComp pgma2b pgmb2a pgmReduce
# pgmComp.c pgma2b.c pgmb2a.c pgmReduce.c
pgmEcho: fileCheck.c pgmImage.c
	gcc -std=c99 -ggdb -o pgmEcho pgmEcho.c fileCheck.c pgmImage.c -I.
pgmComp: fileCheck.c pgmImage.c
	gcc -std=c99 -ggdb -o pgmComp pgmComp.c fileCheck.c pgmImage.c -I.
pgma2b: fileCheck.c pgmImage.c
	gcc -std=c99 -ggdb -o pgma2b pgma2b.c fileCheck.c pgmImage.c -I.
pgmb2a: fileCheck.c pgmImage.c
	gcc -std=c99 -ggdb -o pgmb2a pgmb2a.c fileCheck.c pgmImage.c -I.
pgmReduce: fileCheck.c pgmImage.c
	gcc -std=c99 -ggdb -o pgmReduce pgmReduce.c fileCheck.c pgmImage.c -I.