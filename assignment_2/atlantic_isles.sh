#!/usr/bin/env bash
rm *.txt
./gtopoReduce /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020n90_dem/gt30w020n90.dem 4800 6000 25 test.dem
./gtopoAssemble test2.dem 288 288 12 96 test.dem 192 240
./gtopoTile test2.dem 288 288 4 "a<row><column>.dem"
./gtopoPrintLand a22.dem 72 72 atlantic_isles_target.txt 64 121 800
diff /vol/scratch/SoC/COMP1921/COMP1921A2_handout/atlantic_isles_target.txt atlantic_isles_target.txt
rm *.dem