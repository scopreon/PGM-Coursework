#include <stdio.h>
#include <stdlib.h>
#include "fileCheck.h"
#include "pgmImage.h"

#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

#define MAGIC_NUMBER_RAW_PGM 0x3535
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

int magicNumberCheck(image *ptr_img){
    if (*ptr_img->magic_Number != MAGIC_NUMBER_ASCII_PGM && *ptr_img->magic_Number != MAGIC_NUMBER_RAW_PGM)
		{ /* failed magic number check   */
		/* be tidy: close the file       */
        fclose(ptr_img->inputFile);
		/* print an error message */
		printf("Magic number %s\n", ptr_img->fileName);
		/* and return                    */
		return 1;
		} /* failed magic number check   */
    else{
        return 0;
    }
	
}

int getCommentLine(image *ptr_img){
    char nextChar = fgetc(ptr_img->inputFile);
    if (nextChar == '#')
        
		{ /* comment line                */
		/* allocate buffer               */
		ptr_img->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(ptr_img->commentLine, MAX_COMMENT_LINE_LENGTH, ptr_img->inputFile);
		/* NULL means failure            */
		if (commentString == NULL)
			{ /* NULL comment read   */
			/* free memory           */
			free(ptr_img->commentLine);
			/* close file            */
			fclose(ptr_img->inputFile);

			/* print an error message */
			printf("Comment %s\n",ptr_img->fileName);	
		
			/* and return            */
			return 1;
			} /* NULL comment read   */
        else{
            return 0;
        }
	} /* comment line */
    else{
        ungetc(nextChar, ptr_img->inputFile);
        return 0;
    }
}



int sizeCheck(image *ptr_img,int scanCount){
    if 	(
		(scanCount != 3				)	||
		(ptr_img->width 	< MIN_IMAGE_DIMENSION	) 	||
		(ptr_img->width 	> MAX_IMAGE_DIMENSION	) 	||
		(ptr_img->height < MIN_IMAGE_DIMENSION	) 	||
		(ptr_img->height > MAX_IMAGE_DIMENSION	) 	||
		(ptr_img->maxGray	> 255		)
		)
		{ /* failed size sanity check    */
		/* free up the memory            */
		free(ptr_img->commentLine);

		/* be tidy: close file pointer   */
		fclose(ptr_img->inputFile);

		/* print an error message */
		printf("3Error: Failed to read pgm image from file %s\n", ptr_img->fileName);	
		
		/* and return                    */
		return 1;
		} /* failed size sanity check    */
    else{
        return 0;
    }
}


// void freeMemoryExit(){

// }

// int imageAllocationCheck(){

// }

// int grayValueCheck(){

// }

