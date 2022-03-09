#include <stdio.h>
#include <stdlib.h>
#include "fileCheck.h"
#include "pgmImage.h"
int magicNumberCheck(image *ptr_image1, int MAGIC_NUMBER_ASCII_PGM){
    if (*ptr_image1->magic_Number != MAGIC_NUMBER_ASCII_PGM)
		{ /* failed magic number check   */
		/* be tidy: close the file       */
        fclose(ptr_image1->inputFile);
		/* print an error message */
		printf("Magic number %s\n", ptr_image1->fileName);
		/* and return                    */
		return 1;
		} /* failed magic number check   */
    else{
        return 0;
    }
	
}

int getCommentLine(image *ptr_img1, int MAX_COMMENT_LINE_LENGTH){
    char nextChar = fgetc(ptr_img1->inputFile);
    if (nextChar == '#')
        
		{ /* comment line                */
		/* allocate buffer               */
		ptr_img1->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(ptr_img1->commentLine, MAX_COMMENT_LINE_LENGTH, ptr_img1->inputFile);
		/* NULL means failure            */
		if (commentString == NULL)
			{ /* NULL comment read   */
			/* free memory           */
			free(ptr_img1->commentLine);
			/* close file            */
			fclose(ptr_img1->inputFile);

			/* print an error message */
			printf("Comment %s\n",ptr_img1->fileName);	
		
			/* and return            */
			return 1;
			} /* NULL comment read   */
        else{
            return 0;
        }
	} /* comment line */
    else{
        ungetc(nextChar, ptr_img1->inputFile);
        return 0;
    }
}



int sizeCheck(image *ptr_img1,int scanCount,int MIN_IMAGE_DIMENSION, int MAX_IMAGE_DIMENSION){
    if 	(
		(scanCount != 3				)	||
		(ptr_img1->width 	< MIN_IMAGE_DIMENSION	) 	||
		(ptr_img1->width 	> MAX_IMAGE_DIMENSION	) 	||
		(ptr_img1->height < MIN_IMAGE_DIMENSION	) 	||
		(ptr_img1->height > MAX_IMAGE_DIMENSION	) 	||
		(ptr_img1->maxGray	> 255		)
		)
		{ /* failed size sanity check    */
		/* free up the memory            */
		free(ptr_img1->commentLine);

		/* be tidy: close file pointer   */
		fclose(ptr_img1->inputFile);

		/* print an error message */
		printf("3Error: Failed to read pgm image from file %s\n", ptr_img1->fileName);	
		
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

