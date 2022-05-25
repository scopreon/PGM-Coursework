#!/usr/bin/env bash
# ./pgmEcho pepper.ascii.pgm temp0.pgm
# ./pgma2b temp0.pgm temp1.pgm
# ./pgmb2a temp1.pgm temp1.pgm

# ./pgmComp pepper.ascii.pgm temp1.pgm
# ./pgmReduce temp0.pgm 2 temp2.pgm

#test for no arguments each program
#test for not correct args each program >0
#height too big
#height too small
#width too big
#width too small
#magic number 

GREEN='\033[0;1;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color
echo -e "UNIT TESTING FOR Programming Project\n"

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
echo -n "Testing no arguments for pgmEcho: "
WHATWEWANT="Usage: ./pgmEcho inputImage.pgm outputImage.pgm"
WHATWEGET=$(./pgmEcho)
./pgmEcho > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for pgmComp: "
WHATWEWANT="Usage: ./pgmComp inputImage.pgm inputImage.pgm"
WHATWEGET=$(./pgmComp)
./pgmComp > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for pgma2b: "
WHATWEWANT="Usage: ./pgma2b inputImage.pgm outputImage.pgm"
WHATWEGET=$(./pgma2b)
./pgma2b > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo -n "Testing no arguments for pgmb2a: "
WHATWEWANT="Usage: ./pgmb2a inputImage.pgm outputImage.pgm"
WHATWEGET=$(./pgmb2a)
./pgmb2a > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for pgmReduce: "
WHATWEWANT="Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm"
WHATWEGET=$(./pgmReduce)
./pgmReduce > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for pgmTile: "
WHATWEWANT="Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm"
WHATWEGET=$(./pgmTile)
./pgmReduce > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing no arguments for pgmAssemble: "
WHATWEWANT="Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+"
WHATWEGET=$(./pgmAssemble)
./pgmReduce > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo
#-----------------Testing for incorrect number of arguments > 0-----------------#
echo -n "Testing incorrect numbers of arguments for pgmEcho: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmEcho images/pepper.ascii.pgm)
./pgmEcho pepper.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing incorrect numbers of arguments for pgmComp: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmComp images/pepper.ascii.pgm)
./pgmComp pepper.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing incorrect numbers of arguments for pgma2b: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgma2b images/pepper.ascii.pgm)
./pgma2b pepper.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing incorrect numbers of arguments for pgmb2a: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmb2a images/pepper.ascii.pgm)
./pgmb2a pepper.binary.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing incorrect numbers of arguments for pgmReduce: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmReduce images/pepper.ascii.pgm)
./pgmReduce pepper.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo -n "Testing incorrect numbers of arguments for pgmTile: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmTile images/pepper.ascii.pgm)
./pgmReduce pepper.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo -n "Testing incorrect numbers of arguments for pgmAssemble: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmAssemble images/pepper.ascii.pgm)
./pgmReduce pepper.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo
#-----------------Testing formating, gray, width, height etc...-----------------#
#-------------------------------Testing for echo--------------------------------#
echo "Testing for pgmEcho"
echo -n "Testing comment line too big: "
WHATWEWANT="ERROR: Bad Comment Line (images/pepper_CommentBig.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_CommentBig.pgm images/temp.pgm)
./pgmEcho pepper_CommentBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthBig.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_WidthBig.pgm images/temp.pgm)
./pgmEcho pepper_WidthBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthSmall.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_WidthSmall.pgm images/temp.pgm)
./pgmEcho pepper_WidthSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightBig.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_HeightBig.pgm images/temp.pgm)
./pgmEcho pepper_HeightBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightSmall.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_HeightSmall.pgm images/temp.pgm)
./pgmEcho pepper_HeightSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value greater than 255: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgrayBig.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_MaxgrayBig.pgm images/temp.pgm)
./pgmEcho pepper_MaxgrayBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value less than 1: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgraySmall.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_MaxgraySmall.pgm images/temp.pgm)
./pgmEcho pepper_MaxgraySmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data bigger than max gray: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueBig.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_ValueBig.pgm images/temp.pgm)
./pgmEcho pepper_ValueBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data smaller than 0: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueSmall.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_ValueSmall.pgm images/temp.pgm)
./pgmEcho pepper_ValueSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo

#-------------------------------Testing for comp--------------------------------#
echo "Testing for pgmComp"
echo -n "Testing comment line too big: "
WHATWEWANT="ERROR: Bad Comment Line (images/pepper_CommentBig.pgm)"
WHATWEGET=$(./pgmComp images/pepper_CommentBig.pgm images/temp.pgm)
./pgmComp pepper_CommentBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthBig.pgm)"
WHATWEGET=$(./pgmComp images/pepper_WidthBig.pgm images/temp.pgm)
./pgmComp pepper_WidthBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthSmall.pgm)"
WHATWEGET=$(./pgmComp images/pepper_WidthSmall.pgm images/temp.pgm)
./pgmComp pepper_WidthSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightBig.pgm)"
WHATWEGET=$(./pgmComp images/pepper_HeightBig.pgm images/temp.pgm)
./pgmComp pepper_HeightBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightSmall.pgm)"
WHATWEGET=$(./pgmComp images/pepper_HeightSmall.pgm images/temp.pgm)
./pgmComp pepper_HeightSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value greater than 255: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgrayBig.pgm)"
WHATWEGET=$(./pgmComp images/pepper_MaxgrayBig.pgm images/temp.pgm)
./pgmComp pepper_MaxgrayBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value less than 1: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgraySmall.pgm)"
WHATWEGET=$(./pgmComp images/pepper_MaxgraySmall.pgm images/temp.pgm)
./pgmComp pepper_MaxgraySmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data bigger than max gray: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueBig.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_ValueBig.pgm images/temp.pgm)
./pgmEcho pepper_ValueBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data smaller than 0: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueSmall.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_ValueSmall.pgm images/temp.pgm)
./pgmEcho pepper_ValueSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo

#-------------------------------Testing for a2b--------------------------------#
echo "Testing for pgma2b"
echo -n "Testing comment line too big: "
WHATWEWANT="ERROR: Bad Comment Line (images/pepper_CommentBig.pgm)"
WHATWEGET=$(./pgma2b images/pepper_CommentBig.pgm images/temp.pgm)
./pgma2b pepper_CommentBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthBig.pgm)"
WHATWEGET=$(./pgma2b images/pepper_WidthBig.pgm images/temp.pgm)
./pgma2b pepper_WidthBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthSmall.pgm)"
WHATWEGET=$(./pgma2b images/pepper_WidthSmall.pgm images/temp.pgm)
./pgma2b pepper_WidthSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightBig.pgm)"
WHATWEGET=$(./pgma2b images/pepper_HeightBig.pgm images/temp.pgm)
./pgma2b pepper_HeightBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightSmall.pgm)"
WHATWEGET=$(./pgma2b images/pepper_HeightSmall.pgm images/temp.pgm)
./pgma2b pepper_HeightSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value greater than 255: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgrayBig.pgm)"
WHATWEGET=$(./pgma2b images/pepper_MaxgrayBig.pgm images/temp.pgm)
./pgma2b pepper_MaxgrayBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value less than 1: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgraySmall.pgm)"
WHATWEGET=$(./pgma2b images/pepper_MaxgraySmall.pgm images/temp.pgm)
./pgma2b pepper_MaxgraySmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo

#-------------------------------Testing for b2a--------------------------------#
echo "Testing for pgmb2a"
echo -n "Testing comment line too big: "
WHATWEWANT="ERROR: Bad Comment Line (images/pepper_CommentBig.pgm)"
WHATWEGET=$(./pgmb2a images/pepper_CommentBig.pgm images/temp.pgm)
./pgmb2a pepper_CommentBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthBig.pgm)"
WHATWEGET=$(./pgmb2a images/pepper_WidthBig.pgm images/temp.pgm)
./pgmb2a pepper_WidthBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthSmall.pgm)"
WHATWEGET=$(./pgmb2a images/pepper_WidthSmall.pgm images/temp.pgm)
./pgmb2a pepper_WidthSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightBig.pgm)"
WHATWEGET=$(./pgmb2a images/pepper_HeightBig.pgm images/temp.pgm)
./pgmb2a pepper_HeightBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightSmall.pgm)"
WHATWEGET=$(./pgmb2a images/pepper_HeightSmall.pgm images/temp.pgm)
./pgmb2a pepper_HeightSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value greater than 255: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgrayBig.pgm)"
WHATWEGET=$(./pgmb2a images/pepper_MaxgrayBig.pgm images/temp.pgm)
./pgmb2a pepper_MaxgrayBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value less than 1: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgraySmall.pgm)"
WHATWEGET=$(./pgmb2a images/pepper_MaxgraySmall.pgm images/temp.pgm)
./pgmb2a pepper_MaxgraySmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo

#-------------------------------Testing for reduce--------------------------------#
echo "Testing for pgmReduce"
echo -n "Testing comment line too big: "
WHATWEWANT="ERROR: Bad Comment Line (images/pepper_CommentBig.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_CommentBig.pgm 2 images/temp.pgm)
./pgmReduce pepper_CommentBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthBig.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_WidthBig.pgm 2 images/temp.pgm)
./pgmReduce pepper_WidthBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthSmall.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_WidthSmall.pgm 2 images/temp.pgm)
./pgmReduce pepper_WidthSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightBig.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_HeightBig.pgm 2 images/temp.pgm)
./pgmReduce pepper_HeightBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightSmall.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_HeightSmall.pgm 2 images/temp.pgm)
./pgmReduce pepper_HeightSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value greater than 255: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgrayBig.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_MaxgrayBig.pgm 2 images/temp.pgm)
./pgmReduce pepper_MaxgrayBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value less than 1: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgraySmall.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_MaxgraySmall.pgm 2 images/temp.pgm)
./pgmReduce pepper_MaxgraySmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data bigger than max gray: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueBig.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_ValueBig.pgm 2 images/temp.pgm)
./pgmEcho pepper_ValueBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data smaller than 0: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueSmall.pgm)"
WHATWEGET=$(./pgmReduce images/pepper_ValueSmall.pgm 2 images/temp.pgm)
./pgmEcho pepper_ValueSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo

#-------------------------------Testing for tile--------------------------------#
echo "Testing for pgmTile"
echo -n "Testing comment line too big: "
WHATWEWANT="ERROR: Bad Comment Line (images/pepper_CommentBig.pgm)"
WHATWEGET=$(./pgmTile images/pepper_CommentBig.pgm 2 "a_<row>_<column>.pgm")
./pgmTile pepper_CommentBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthBig.pgm)"
WHATWEGET=$(./pgmTile images/pepper_WidthBig.pgm 2 "a_<row>_<column>.pgm")
./pgmTile pepper_WidthBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthSmall.pgm)"
WHATWEGET=$(./pgmTile images/pepper_WidthSmall.pgm 2 "a_<row>_<column>.pgm")
./pgmTile pepper_WidthSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightBig.pgm)"
WHATWEGET=$(./pgmTile images/pepper_HeightBig.pgm 2 "a_<row>_<column>.pgm")
./pgmTile pepper_HeightBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightSmall.pgm)"
WHATWEGET=$(./pgmTile images/pepper_HeightSmall.pgm 2 "a_<row>_<column>.pgm")
./pgmTile pepper_HeightSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value greater than 255: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgrayBig.pgm)"
WHATWEGET=$(./pgmTile images/pepper_MaxgrayBig.pgm 2 "a_<row>_<column>.pgm")
./pgmTile pepper_MaxgrayBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value less than 1: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgraySmall.pgm)"
WHATWEGET=$(./pgmTile images/pepper_MaxgraySmall.pgm 2 "a_<row>_<column>.pgm")
./pgmTile pepper_MaxgraySmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data bigger than max gray: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueBig.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_ValueBig.pgm images/temp.pgm)
./pgmEcho pepper_ValueBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data smaller than 0: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueSmall.pgm)"
WHATWEGET=$(./pgmTile images/pepper_ValueSmall.pgm 2 "a_<row>_<column>.pgm")
./pgmEcho pepper_ValueSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo

#-------------------------------Testing for assemble--------------------------------#
echo "Testing for pgmAssemble"
echo -n "Testing comment line too big: "
WHATWEWANT="ERROR: Bad Comment Line (images/pepper_CommentBig.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_CommentBig.pgm)
./pgmAssemble pepper_CommentBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthBig.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_WidthBig.pgm)
./pgmAssemble pepper_WidthBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing width value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_WidthSmall.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_WidthSmall.pgm)
./pgmAssemble pepper_WidthSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value too big: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightBig.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_HeightBig.pgm)
./pgmAssemble pepper_HeightBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing height value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (images/pepper_HeightSmall.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_HeightSmall.pgm)
./pgmAssemble pepper_HeightSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value greater than 255: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgrayBig.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_MaxgrayBig.pgm)
./pgmAssemble pepper_MaxgrayBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing max gray value less than 1: "
WHATWEWANT="ERROR: Bad Max Gray Value (images/pepper_MaxgraySmall.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_MaxgraySmall.pgm)
./pgmAssemble pepper_MaxgraySmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data bigger than max gray: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueBig.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_ValueBig.pgm)
./pgmEcho pepper_ValueBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data smaller than 0: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueSmall.pgm)"
WHATWEGET=$(./pgmAssemble test.pgm 2 2 0 0 images/pepper_ValueSmall.pgm)
./pgmEcho pepper_ValueSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
echo

#-----------------Reading in data error-----------------#
echo -n "Testing data bigger than max gray: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueBig.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_ValueBig.pgm images/temp.pgm)
./pgmEcho pepper_ValueBig.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing data smaller than 0: "
WHATWEWANT="ERROR: Bad Data (images/pepper_ValueSmall.pgm)"
WHATWEGET=$(./pgmEcho images/pepper_ValueSmall.pgm images/temp.pgm)
./pgmEcho pepper_ValueSmall.pgm temp.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

#-----------------Testing pgmComp with same and different files-----------------#
echo -n "Testing different ascii images: "
WHATWEWANT="DIFFERENT"
WHATWEGET=$(./pgmComp images/pepper_ascii.pgm images/pepper_Different_ascii.pgm)
./pgmComp pepper.ascii.pgm pepper_Different.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing different binary images: "
WHATWEWANT="DIFFERENT"
WHATWEGET=$(./pgmComp images/pepper_binary.pgm images/pepper_Different_binary.pgm)
./pgmComp pepper.ascii.pgm pepper_Different.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing identical ascii images: "
WHATWEWANT="IDENTICAL"
WHATWEGET=$(./pgmComp images/pepper_ascii.pgm images/pepper_ascii.pgm)
./pgmComp pepper.ascii.pgm pepper.ascii.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"

echo -n "Testing identical binary images: "
WHATWEWANT="IDENTICAL"
WHATWEGET=$(./pgmComp images/pepper_binary.pgm images/pepper_binary.pgm)
./pgmComp pepper.binary.pgm pepper.binary.pgm > /dev/null 2>&1
comparison "$WHATWEWANT" "$WHATWEGET"
#endtesting