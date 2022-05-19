/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>
/* methods for checking file information is valid */
#include "fileCheck.h"
/* contains reading and writing functions */
#include "pgmImage.h"

/***********************************/
/* freeMemory function      	   */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: pointer to image struct*/
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int freeMemory(image *ptr_img){
	/* free filename if it has been allocated */
	if(ptr_img->fileName != NULL){
		free(ptr_img->fileName);
	}
	/* close filestream if it has been allocated */
	if(ptr_img->fileStream != NULL){
		fclose(ptr_img->fileStream);
	}
	return 0;
}

/***********************************/
/* magicNumberCheck function       */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: pointer to image struct*/
/* argv[1]: format to read in file */
/*  -> 0 if binary/ascii           */
/*  -> 1 if ascii                  */
/*  -> 2 if binary                 */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
 
int magicNumberCheck(image *ptr_img,int magicNumberVerify){
    /* checks if magic number is the one we want, binary/ascii/either */
	if ((*ptr_img->magic_Number != MAGIC_NUMBER_ASCII_PGM && *ptr_img->magic_Number != MAGIC_NUMBER_RAW_PGM)||
	 	(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM && magicNumberVerify==1)							||
	 	(*ptr_img->magic_Number ==  MAGIC_NUMBER_ASCII_PGM && magicNumberVerify==2)){
		/* if magic number does not match exit with bad magic number, free memory */
		printf("ERROR: Bad Magic Number (%s)\n", ptr_img->fileName);
		freeMemory(ptr_img);
		return 1;
	}
    else{
        return 0;
    }
	
}

/***********************************/
/* getCommentLine function         */
/*                                 */
/* parameters:                     */
/* argv[0]: pointer to image struct*/
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int getCommentLine(image *ptr_img){
	/* get next character in file stream, if it is a # the line is a comment */
    char nextChar = fgetc(ptr_img->fileStream);
    if (nextChar == '#'){
		/* created pointer which points to commment line in file */
		char commentChar;
		/* counter which counts number of characters */
		int count=0;

		/* loop until you reach end of comment or comment is too big */
		for(;;){
			/* get next character and check if it is a newline, if so then exit */
			commentChar=fgetc(ptr_img->fileStream);
			if(commentChar == '\n' || commentChar == '\0'){
				break;
			}
            
			/* increment count */
        	++count;
			/* if count is too big comment is too big, exit with bad comment line */
			if(count>127){
				
				printf("ERROR: Bad Comment Line (%s)\n",ptr_img->fileName);	
				freeMemory(ptr_img);
				return 1;
			}
		}
		/* if it has left the for loop the comment is valid and we can exit with 0 */
		return 0;
	}
    else{
		/* if the character wasn't a # it was useful data so put the character back in the stream and return */
        ungetc(nextChar, ptr_img->fileStream);
        return 0;
    }
}


/***********************************/
/* getCommentLine function         */
/*                                 */
/* parameters:                     */
/* argv[0]: pointer to image struct*/
/* argv[1]: numebr of items read in*/
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int sizeCheck(image *ptr_img,int scanCount){
	/* check if scancount is 2 (read in both width and height) */
	/* check he width and height read in is in a valid range */
    if 	((scanCount != 2)							||
		(ptr_img->width < MIN_IMAGE_DIMENSION	) 	||
		(ptr_img->width >= MAX_IMAGE_DIMENSION	) 	||
		(ptr_img->height < MIN_IMAGE_DIMENSION	) 	||
		(ptr_img->height >= MAX_IMAGE_DIMENSION	)){
		/* free everything up if width/height aren't valid */
		
		printf("ERROR: Bad Dimensions (%s)\n", ptr_img->fileName);	
		freeMemory(ptr_img);
		return 1;
	}
    else{
		/* if everything is valid return 0 */
        return 0;
    }
}

/***********************************/
/* grayCheck function              */
/*                                 */
/* parameters:                     */
/* argv[0]: pointer to image struct*/
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int grayCheck(image *ptr_img){
	/* checking if max gray value is valid 1->255, if not return error and string */
    if 	((ptr_img->maxGray	> 255		)||
		(ptr_img->maxGray	< 1		)){
		/* free memory and exit with string */
		
		printf("ERROR: Bad Max Gray Value (%s)\n", ptr_img->fileName);	
		freeMemory(ptr_img);
		return 1;
	}
    else{
		/* max gray value is valid, return with no errorand continue to read data */
        return 0;
    }
}