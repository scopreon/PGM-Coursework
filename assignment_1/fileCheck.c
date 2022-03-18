#include <stdio.h>
#include <stdlib.h>
#include "fileCheck.h"
#include "pgmImage.h"

//error for wrong intended format
int magicNumberCheck(image *ptr_img,int magicNumberVerify){
    if ((*ptr_img->magic_Number != MAGIC_NUMBER_ASCII_PGM && *ptr_img->magic_Number != MAGIC_NUMBER_RAW_PGM && magicNumberVerify==0)||
	(*ptr_img->magic_Number != MAGIC_NUMBER_ASCII_PGM && magicNumberVerify==1)||
	(*ptr_img->magic_Number != MAGIC_NUMBER_RAW_PGM && magicNumberVerify==2))
		{ /* failed magic number check   */
		/* be tidy: close the file       */
        fclose(ptr_img->fileStream);
		/* print an error message */
		printf("ERROR: Bad Magic Number %s\n", ptr_img->fileName);
		/* and return                    */
		return 1;
		} /* failed magic number check   */
    else{
        return 0;
    }
	
}

int getCommentLine(image *ptr_img){
    char nextChar = fgetc(ptr_img->fileStream);
    if (nextChar == '#')
        
		{ /* comment line                */
		/* allocate buffer               */
		ptr_img->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		char *pointerToData=ptr_img->commentLine;
		/* fgets() reads a line          */
		/* capture return value          */
		int count=0;
		for(;;){
			*pointerToData=fgetc(ptr_img->fileStream);
			if(*pointerToData == '\n')
            	break;
			pointerToData++;
        	++count;
			if(count>127 || *pointerToData=='\0'){
				free(ptr_img->commentLine);
			/* close file            */
				fclose(ptr_img->fileStream);

			/* print an error message */
				printf("ERROR: Bad Comment Line %s\n",ptr_img->fileName);	
		
			/* and return            */
				return 1;
			}
		}
		return 0;
	} /* comment line */
    else{
        ungetc(nextChar, ptr_img->fileStream);
        return 0;
    }
}



int sizeCheck(image *ptr_img,int scanCount){
    if 	(
		(scanCount != 3				)	||
		(ptr_img->width 	< MIN_IMAGE_DIMENSION	) 	||
		(ptr_img->width 	> MAX_IMAGE_DIMENSION	) 	||
		(ptr_img->height < MIN_IMAGE_DIMENSION	) 	||
		(ptr_img->height > MAX_IMAGE_DIMENSION	) 
		)
		{ /* failed size sanity check    */
		/* free up the memory            */
		free(ptr_img->commentLine);

		/* be tidy: close file pointer   */
		fclose(ptr_img->fileStream);

		/* print an error message */
		printf("ERROR: Bad Dimensions %s\n", ptr_img->fileName);	
		
		/* and return                    */
		return 1;
	}
		 /* failed size sanity check    */
    else{
        return 0;
    }
}

int grayCheck(image *ptr_img){
    if 	(
		(ptr_img->maxGray	> 255		)||
		(ptr_img->maxGray	< 1		)
		)
		{ /* failed size sanity check    */
		/* free up the memory            */
		free(ptr_img->commentLine);

		/* be tidy: close file pointer   */
		fclose(ptr_img->fileStream);

		/* print an error message */
		printf("ERROR: Bad Max Gray Value %s\n", ptr_img->fileName);	
		
		/* and return                    */
		return 1;
		} /* failed size sanity check    */
    else{
        return 0;
    }
}