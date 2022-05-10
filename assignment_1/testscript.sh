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

#-----------------Testing for no arguments-----------------#
echo -n "Testing no arguments for pgmEcho: "
WHATWEWANT="Usage: ./pgmEcho inputImage.pgm outputImage.pgm"
WHATWEGET=$(./pgmEcho)
./pgmEcho > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing no arguments for pgmComp: "
WHATWEWANT="Usage: ./pgmComp inputImage.pgm inputImage.pgm"
WHATWEGET=$(./pgmComp)
./pgmComp > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing no arguments for pgma2b: "
WHATWEWANT="Usage: ./pgma2b inputImage.pgm outputImage.pgm"
WHATWEGET=$(./pgma2b)
./pgma2b > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing no arguments for pgmb2a: "
WHATWEWANT="Usage: ./pgmb2a inputImage.pgm outputImage.pgm"
WHATWEGET=$(./pgmb2a)
./pgmb2a > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing no arguments for pgmReduce: "
WHATWEWANT="Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm"
WHATWEGET=$(./pgmReduce)
./pgmReduce > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi
#-----------------Testing for incorrect number of arguments > 0-----------------#
echo -n "Testing incorrect numbers of arguments for pgmEcho: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmEcho pepper.ascii.pgm)
./pgmEcho pepper.ascii.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing incorrect numbers of arguments for pgmComp: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmComp pepper.ascii.pgm)
./pgmComp pepper.ascii.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing incorrect numbers of arguments for pgma2b: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgma2b pepper.ascii.pgm)
./pgma2b pepper.ascii.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing incorrect numbers of arguments for pgmb2a: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmb2a pepper.ascii.pgm)
./pgmb2a pepper.binary.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing incorrect numbers of arguments for pgmReduce: "
WHATWEWANT="ERROR: Bad Argument Count"
WHATWEGET=$(./pgmReduce pepper.ascii.pgm)
./pgmReduce pepper.ascii.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi
#-----------------Testing formating, gray, width, height etc...-----------------#
echo -n "Testing comment line too big: "
WHATWEWANT="ERROR: Bad Comment Line (pepper_CommentBig.pgm)"
WHATWEGET=$(./pgmEcho pepper_CommentBig.pgm temp.pgm)
./pgmEcho pepper_CommentBig.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing width value too big: "
WHATWEWANT="ERROR: Bad Dimensions (pepper_WidthBig.pgm)"
WHATWEGET=$(./pgmEcho pepper_WidthBig.pgm temp.pgm)
./pgmEcho pepper_WidthBig.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing width value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (pepper_WidthSmall.pgm)"
WHATWEGET=$(./pgmEcho pepper_WidthSmall.pgm temp.pgm)
./pgmEcho pepper_WidthSmall.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing height value too big: "
WHATWEWANT="ERROR: Bad Dimensions (pepper_HeightBig.pgm)"
WHATWEGET=$(./pgmEcho pepper_HeightBig.pgm temp.pgm)
./pgmEcho pepper_HeightBig.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing height value less than 1: "
WHATWEWANT="ERROR: Bad Dimensions (pepper_HeightSmall.pgm)"
WHATWEGET=$(./pgmEcho pepper_HeightSmall.pgm temp.pgm)
./pgmEcho pepper_HeightSmall.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing max gray value greater than 255: "
WHATWEWANT="ERROR: Bad Max Gray Value (pepper_MaxgrayBig.pgm)"
WHATWEGET=$(./pgmEcho pepper_MaxgrayBig.pgm temp.pgm)
./pgmEcho pepper_MaxgrayBig.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing max gray value less than 1: "
WHATWEWANT="ERROR: Bad Max Gray Value (pepper_MaxgraySmall.pgm)"
WHATWEGET=$(./pgmEcho pepper_MaxgraySmall.pgm temp.pgm)
./pgmEcho pepper_MaxgraySmall.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi
#-----------------Reading in data error-----------------#
echo -n "Testing data bigger than max gray: "
WHATWEWANT="ERROR: Bad Data (pepper_ValueBig.pgm)"
WHATWEGET=$(./pgmEcho pepper_ValueBig.pgm temp.pgm)
./pgmEcho pepper_ValueBig.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing data smaller than 0: "
WHATWEWANT="ERROR: Bad Data (pepper_ValueSmall.pgm)"
WHATWEGET=$(./pgmEcho pepper_ValueSmall.pgm temp.pgm)
./pgmEcho pepper_ValueSmall.pgm temp.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi
#-----------------Testing pgmComp with same and different files-----------------#
echo -n "Testing different ascii images: "
WHATWEWANT="DIFFERENT"
WHATWEGET=$(./pgmComp pepper_ascii.pgm pepper_Different_ascii.pgm)
./pgmComp pepper.ascii.pgm pepper_Different.ascii.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing different binary images: "
WHATWEWANT="DIFFERENT"
WHATWEGET=$(./pgmComp pepper_binary.pgm pepper_Different_binary.pgm)
./pgmComp pepper.ascii.pgm pepper_Different.ascii.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing identical ascii images: "
WHATWEWANT="IDENTICAL"
WHATWEGET=$(./pgmComp pepper_ascii.pgm pepper_ascii.pgm)
./pgmComp pepper.ascii.pgm pepper.ascii.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi

echo -n "Testing identical binary images: "
WHATWEWANT="IDENTICAL"
WHATWEGET=$(./pgmComp pepper_binary.pgm pepper_binary.pgm)
./pgmComp pepper.binary.pgm pepper.binary.pgm > /dev/null 2>&1
VALUE=$?
if [ "$WHATWEWANT" == "$WHATWEGET" ]
then
    echo -e "${GREEN}PASSED${NC} with code ${VALUE}"
else
    echo -e "${RED}FAILED${NC} with code ${VALUE}"
    echo -e "\tExpected\t${WHATWEWANT}"
    echo -e "\tRecieved\t${WHATWEGET}"
fi
#endtesting