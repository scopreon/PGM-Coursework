#!/usr/bin/env bash
./gtopoReduce GTOPO30/gt30w020n90_dem/gt30w020n90.dem 4800 6000 25 test.dem
./gtopoPrintLand test.dem 192 240 test.txt 65 123 800