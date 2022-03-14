/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Hamish Carr                     */
/***********************************/

/***********************************/
/* A first iteration to take a pgm */
/* file in binary and convert to   */
/* ASCII or vice versa             */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "fileCheck.h"
#include "pgmImage.h"
#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
	{ /* main() */
	/* check for correct number of arguments */
	if (argc != 3)	
		{ /* wrong arg count */
		/* print an error message        */
		printf("Usage: %s input_file output_file\n", argv[0]);
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
		} /* wrong arg count */
	
	/* variables for storing the image       */
    	/* this is NOT good modularisation       */
    	/* and you will eventually replace it    */
    	/* for now, leave it here                */

	/* the magic number		         */
	/* stored as two bytes to avoid	         */
	/* problems with endianness	         */
	/* Raw:    0x5035 or P5		         */
	/* ASCII:  0x5032 or P2		         */

	/* at this point, we are done and can exit with a success code */
	image img1 = {.width=0,.height=0, .maxGray=255, .imageData=NULL, .commentLine=NULL};
	image *ptr_img1=&img1;

	image img2 = {.width=0,.height=0, .maxGray=255, .imageData=NULL, .commentLine=NULL};
	image *ptr_img2=&img2;

	int returnVal = readInFile(ptr_img1, argv[1]);
	if(returnVal!=0){
		return returnVal;
	}
	returnVal = readInFile(ptr_img2, argv[2]);
	if(returnVal!=0){
		return returnVal;
	}
	if(ptr_img1->width != ptr_img2->width || ptr_img1->height != ptr_img2->height){
		printf("DIFFERENT\n");
		return EXIT_NO_ERRORS;
	}
	long nImageBytes = ptr_img1->width * ptr_img1->height * sizeof(unsigned char);

	unsigned char *nextGrayValue1 = ptr_img1->imageData;
	unsigned char *nextGrayValue2 = ptr_img2->imageData;
	while (nextGrayValue1 < ptr_img1->imageData + nImageBytes){
		int nextCol = (nextGrayValue1 - ptr_img1->imageData + 1) % ptr_img1->width;
		if(((float) *nextGrayValue2)/ptr_img2->maxGray!=((float) *nextGrayValue1)/ptr_img1->maxGray){
			printf("DIFFERENT\n");
			return EXIT_NO_ERRORS;
		}
		nextGrayValue1++;
		nextGrayValue2++;
	}
	printf("IDENTICAL\n");
	return EXIT_NO_ERRORS;
	} /* main() */
