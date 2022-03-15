#!/usr/bin/env bash
./pgmEcho balloons.pgm temp0.pgm
./pgma2b temp0.pgm temp1.pgm
./pgmb2a temp1.pgm temp1.pgm
./pgmb2a temp1.pgm temp1.pgm

./pgmComp balloons.pgm temp1.pgm
./pgmReduce temp0.pgm temp2.pgm 2
