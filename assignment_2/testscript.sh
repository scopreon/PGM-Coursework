#!/usr/bin/env bash

GREEN='\033[0;1;32m'
RED='\033[0;31m'
BLUE='\033[0;1;34m'
NC='\033[0m' # No Color
echo -e "UNIT TESTING FOR Programming Project Assignment 2\n"
make clean > /dev/null 2>&1
make > /dev/null 2>&1
comparison(){
    if [ "$1" == "$2" ]
    then
        echo -e "${GREEN}PASSED${NC}"
    else
        echo -e "${RED}FAILED${NC}"
        echo -e "\tExpected\t${1}"
        echo -e "\tRecieved\t${2}"
    fi
}

#-----------------Testing for no arguments-----------------#
echo -n "Testing no arguments for gtopoEcho: "
WHATWEWANT="Usage: ./gtopoEcho inputFile width height outputFile"
WHATWEGET=$(./gtopoEcho)
./gtopoEcho > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for gtopoComp: "
WHATWEWANT="Usage: ./gtopoComp firstFile width height secondFile"
WHATWEGET=$(./gtopoComp)
./gtopoComp > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for gtopoReduce: "
WHATWEWANT="Usage: ./gtopoReduce input width height reduction_factor output"
WHATWEGET=$(./gtopoReduce)
./gtopoReduce > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for gtopoTile: "
WHATWEWANT="Usage: ./gtopoTile inputFile width height tiling_factor outputFile_<row>_<column>"
WHATWEGET=$(./gtopoTile)
./gtopoReduce > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for gtopoAssemble: "
WHATWEWANT="Usage: ./gtopoAssemble outputFile width height (row column inputFile width height)+"
WHATWEGET=$(./gtopoAssemble)
./gtopoReduce > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo
#-----------------Testing for incorrect number of arguments > 0-----------------#
echo -n "Testing incorrect numbers of arguments for gtopoEcho: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./gtopoEcho test.dem)
./gtopoEcho pepper.ascii.gtopo > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing incorrect numbers of arguments for gtopoComp: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./gtopoComp test.dem)
./gtopoComp pepper.ascii.gtopo > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing incorrect numbers of arguments for gtopoReduce: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./gtopoReduce test.dem)
./gtopoReduce pepper.ascii.gtopo > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing incorrect numbers of arguments for gtopoTile: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./gtopoTile test.dem)
./gtopoReduce pepper.ascii.gtopo > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing incorrect numbers of arguments for gtopoAssemble: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./gtopoAssemble test.dem)
./gtopoReduce pepper.ascii.gtopo > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo
#endtesting