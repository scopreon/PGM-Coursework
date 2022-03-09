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

	image img1 = {.width=0,.height=0, .maxGray=255, .imageData=NULL, .commentLine=NULL};
	image *ptr_img1;
	ptr_img1=&img1;
	
	unsigned char magic_number[2] = {'0','0'};
	ptr_img1->magic_Number=(unsigned short *) magic_number;
	unsigned short *magic_Number = (unsigned short *) magic_number;
	ptr_img1->inputFile =  fopen(argv[1], "r");
	ptr_img1->fileName=argv[1];

	if (ptr_img1->inputFile == NULL)
		return EXIT_BAD_INPUT_FILE;

	magic_number[0] = getc(ptr_img1->inputFile);
	magic_number[1] = getc(ptr_img1->inputFile);

	if(magicNumberCheck(ptr_img1, MAGIC_NUMBER_ASCII_PGM)){
		return EXIT_BAD_INPUT_FILE;
		}

	int scanCount = fscanf(ptr_img1->inputFile, " ");

	if(getCommentLine(ptr_img1,MAX_COMMENT_LINE_LENGTH)){
		return EXIT_BAD_INPUT_FILE;
	}

	scanCount = fscanf(ptr_img1->inputFile, " %u %u %u", &(ptr_img1->width), &(ptr_img1->height), &(ptr_img1->maxGray));

	if(sizeCheck(ptr_img1,scanCount,MIN_IMAGE_DIMENSION,MAX_IMAGE_DIMENSION)){
		return EXIT_BAD_INPUT_FILE;
	}

	long nImageBytes = ptr_img1->width * ptr_img1->height * sizeof(unsigned char);
	ptr_img1->imageData = (unsigned char *) malloc(nImageBytes);
	if(readData(ptr_img1,nImageBytes)){
		return EXIT_BAD_INPUT_FILE;
	}

	fclose(ptr_img1->inputFile);
	image img2 = {.width=ptr_img1->width,.height=ptr_img1->height, .maxGray=ptr_img1->maxGray, .imageData=ptr_img1->imageData, .commentLine=ptr_img1->commentLine};
	ptr_img1->fileName=argv[2];
	image *ptr_img2;
	ptr_img2=&img2;
	ptr_img2->outputFile = fopen(argv[2], "w");

	if(writeData(ptr_img2,nImageBytes)){
		return EXIT_BAD_OUTPUT_FILE;
	}

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */
