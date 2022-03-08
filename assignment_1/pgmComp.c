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

#include <image.h>

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


	// unsigned char magic_number[2] = {'0','0'};
	// unsigned short *magic_Number = (unsigned short *) magic_number;
	
	// /* we will store ONE comment	         */
	// char *commentLine = NULL;

	// /* the logical width & height	         */
	// /* note: cannot be negative	         */
	// unsigned int width = 0, height = 0;

	// /* maximum gray value (assumed)	         */
	// /* make it an integer for ease	         */
	// unsigned int maxGray = 255;

	// /* pointer to raw image data	         */
	// unsigned char *imageData = NULL;
	
	// /* now start reading in the data         */
	// /* try to open the file for text I/O     */
	// /* in ASCII mode b/c the header is text  */

    struct Images img1={.commentLine=NULL,.width=0,.height=0,.maxGray=255,.imageData=NULL};

    img1.magic_number[0] = '0';
    img1.magic_Number[1] = '0';

    img1.magic_Number = (unsigned short *) img1.magic_number;

	FILE *inputFile = fopen(argv[1], "r");

	/* if it fails, return error code        */
	if (inputFile == NULL)
		return EXIT_BAD_INPUT_FILE;

	/* read in the magic number              */
	img1.magic_number[0] = getc(inputFile);
	img1.magic_number[1] = getc(inputFile);

    

	/* sanity check on the magic number      */
	if (img1.magic_Number != MAGIC_NUMBER_ASCII_PGM)
		{ /* failed magic number check   */
		/* be tidy: close the file       */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		/* and return                    */
		return EXIT_BAD_INPUT_FILE;
		} /* failed magic number check   */

	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");

	/* check for a comment line              */
	char nextChar = fgetc(inputFile);
	if (nextChar == '#')
		{ /* comment line                */
		/* allocate buffer               */
		img1.commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(img1.commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);
		/* NULL means failure            */
		if (commentString == NULL)
			{ /* NULL comment read   */
			/* free memory           */
			free(img1.commentLine);
			/* close file            */
			fclose(inputFile);

			/* print an error message */
			printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
			/* and return            */
			return EXIT_BAD_INPUT_FILE;
			} /* NULL comment read   */
		} /* comment line */
	else
		{ /* not a comment line */
		/* put character back            */
		ungetc(nextChar, inputFile);
		} /* not a comment line */

	/* read in width, height, grays          */
	/* whitespace to skip blanks             */
	scanCount = fscanf(inputFile, " %u %u %u", &(img1.width), &(img1.height), &(img1.maxGray));

	/* sanity checks on size & grays         */
	/* must read exactly three values        */
	if 	(
		(scanCount != 3				)	||
		(img1.width 	< MIN_IMAGE_DIMENSION	) 	||
		(img1.width 	> MAX_IMAGE_DIMENSION	) 	||
		(img1.height < MIN_IMAGE_DIMENSION	) 	||
		(img1.height > MAX_IMAGE_DIMENSION	) 	||
		(img1.maxGray	!= 255		)
		)
		{ /* failed size sanity check    */
		/* free up the memory            */
		free(img1.commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		/* and return                    */
		return EXIT_BAD_INPUT_FILE;
		} /* failed size sanity check    */

	/* allocate the data pointer             */
	long nImageBytes = img1.width * img1.height * sizeof(unsigned char);
	img1.imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
	if (img1.imageData == NULL)
		{ /* malloc failed */
		/* free up memory                */
		free(img1.commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		/* return error code             */
		return EXIT_BAD_INPUT_FILE;
		} /* malloc failed */

	/* pointer for efficient read code       */
	for (unsigned char *nextGrayValue = img1.imageData; nextGrayValue < img1.imageData + nImageBytes; nextGrayValue++)
		{ /* per gray value */
		/* read next value               */
		int grayValue = -1;
		int scanCount = fscanf(inputFile, " %u", &grayValue);

		/* sanity check	                 */
		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
			{ /* fscanf failed */
			/* free memory           */
			free(img1.commentLine);
			free(img1.imageData);	

			/* close file            */
			fclose(inputFile);

			/* print error message   */
			printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
			/* and return            */
			return EXIT_BAD_INPUT_FILE;
			} /* fscanf failed */

		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
		} /* per gray value */

	/* we're done with the file, so close it */
	fclose(inputFile);


	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */
