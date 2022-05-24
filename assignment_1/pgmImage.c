/* library for I/O routines */
#include <stdio.h>
/* library for checking variable types */
#include <ctype.h>
/* library for memory routines */
#include <stdlib.h>
/* library for string routines */
#include <string.h>
/* library for math routines */
#include <math.h>
/* methods for checking file information is valid */
#include "fileCheck.h"
/* contains reading and writing functions */
#include "pgmImage.h"

/***********************************/
/* isNumber function               */
/*                                 */
/* parameters:                     */
/* argv[0]: text to check          */
/* returns 0 if not a number       */
/* returns 1 if a number           */
/***********************************/

int isNumber(char *text){
	/* loop through all letters in text */
	for(int characterPosition = 0; text[characterPosition]!='\0'; characterPosition++){
		/* if any characers aren't string */
		/* note: this also detects . and - as non digits so this function checks if positive integer */
		if(!isdigit(text[characterPosition])){
			return 0;
		}
	}
	/* the number is a positive integer */
	return 1;
}

/***********************************/
/* initialiseImage function        */
/*                                 */
/* parameters:                     */
/* argv[0]: pointer to image struct*/
/* argv[1]: file name              */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int initialiseImage(image *ptr_img,char *fileName){
	/* check if malloc for image pointer failed */
	if(ptr_img==NULL){
		return 1;
	}
	/* initialising imformation with basic data */
	ptr_img->height=0;
    ptr_img->width=0;
    ptr_img->maxGray=255;
    ptr_img->fileStream=NULL;
	ptr_img->fileName=malloc(sizeof(char)*(strlen(fileName)+1));
	strcpy(ptr_img->fileName,fileName);
    ptr_img->imageData=NULL;
    ptr_img->magic_Number=NULL;
	ptr_img->magic_number[0] = '0';
	ptr_img->magic_number[1] = '0';
	return 0;
}

/***********************************/
/* readData function               */
/*                                 */
/* parameters:                     */
/* argv[0]: pointer to image struct*/
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int readData(image *ptr_img){
	/* if it's reading in binary needs to read in newline character */
	if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
		getc(ptr_img->fileStream);
	}

	int scanCount;
	/* looping through gray values to read in and store in image struct*/
	for(int loopRow=0; loopRow<ptr_img->height; loopRow++){
		for(int loopCol=0; loopCol<ptr_img->width; loopCol++){
			int grayValue = -1;
			/* read in data according to a specific format */
			if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
				/* read in a single byte for each gray value, binary format */
				scanCount = fread(&grayValue,1,1,ptr_img->fileStream);
				grayValue = (int)(unsigned char)grayValue;
			}
			else{
				/* read a value seperated by blankspace, ascii format */
				scanCount = fscanf(ptr_img->fileStream, " %u", &grayValue);
				grayValue=(int) (((float) grayValue)/ptr_img->maxGray * 255);
			}
			/* ensuring a gray value read in and it is valid */
			if ((scanCount != 1) || (grayValue < 0) || (grayValue > ptr_img->maxGray)){
				return EXIT_BAD_INPUT;
			}
			/* save the value in image data */
			ptr_img->imageData[loopRow][loopCol]=(unsigned char) grayValue;
		}
	}
	int grayValue=-1;
	/* try read in another value, if this passes we have too mcuh data */
	if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
		/* 1 subtracted from scancount as it returns 0 if nothing is returned, not -1 unlike scanCount */
		scanCount = fread(&grayValue,1,1,ptr_img->fileStream)-1;
	}
	else{
		scanCount = fscanf(ptr_img->fileStream, " %u", &grayValue);
	}
	/* check if too much data was read in, return bad input if it did */
	if(scanCount!=-1){	
		return EXIT_BAD_INPUT;
	}
    return 0;
}

/***********************************/
/* writeData function              */
/*                                 */
/* parameters:                     */
/* argv[0]: pointer to image struct*/
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int writeData(image *ptr_img){
	/* checking if filestream is empty, means file cannot be written to if NULL */
    if (ptr_img->fileStream == NULL){
		return 1;
	}

	/* writing magic number, width and height to file */
	size_t nBytesWritten = fprintf(ptr_img->fileStream, "%s\n%d %d\n%d\n", (char *) ptr_img->magic_Number,ptr_img->width, ptr_img->height, ptr_img->maxGray);
    /* checking if it wrote correctly */
	if (nBytesWritten < 0){
		return 1;
	}

	/* loop through all pixel values in 2D array and write each one to file */
	for(int loopRow=0; loopRow<ptr_img->height; loopRow++){
		for(int loopCol=0; loopCol<ptr_img->width; loopCol++){
			/* check method of writing, ascii or binary */
			if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
				/* writing a single byte to file, binary format */ 
				nBytesWritten = fwrite(&ptr_img->imageData[loopRow][loopCol], 1, 1, ptr_img->fileStream);
			}
			else{
				/* mapping data to intended gray value, 1->255 */
				ptr_img->imageData[loopRow][loopCol]=(int) ((((float) ptr_img->imageData[loopRow][loopCol])/255 * ptr_img->maxGray));
				/* writing that value to file in format " %d", ascii format */
				nBytesWritten = fprintf(ptr_img->fileStream, "%d%c", ptr_img->imageData[loopRow][loopCol],' ');
			}

			/* checking if each write passed, return error if failed */
			if (nBytesWritten < 0){
				return 1;
			}
		}
		/* write newline character at end of each rows */
		if(*ptr_img->magic_Number != MAGIC_NUMBER_RAW_PGM){
			nBytesWritten = fprintf(ptr_img->fileStream, "%c", '\n' );
		}
		
	}

    /* all data has been written successfully, return 0 */
    return 0;
}

/***********************************/
/* readInFile function             */
/*                                 */
/* parameters:                     */
/* argv[0]: pointer to image struct*/
/* argv[1]: format to read in file */
/*  -> 0 if binary/ascii           */
/*  -> 1 if ascii                  */
/*  -> 2 if binary                 */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int readInFile(image *ptr_img, int intendedFormat){
	/* linking magic number characters to magic_Number pointer */
	ptr_img->magic_Number=(unsigned short *) ptr_img->magic_number;
	/* reading in file to filestream using fopen */
	ptr_img->fileStream =  fopen(ptr_img->fileName, "r");
	
	/* checking if fileStream is NULL when reading in file */
	if (ptr_img->fileStream == NULL){
		printf("ERROR: Bad File Name (%s)\n",ptr_img->fileName);
		return EXIT_BAD_FILE_NAME;
	}
	
	/* reading in digits of magic number individually */
	ptr_img->magic_number[0] = getc(ptr_img->fileStream);
	ptr_img->magic_number[1] = getc(ptr_img->fileStream);
	
	/* verifying magic numvber is valid regardless of format (binary/ascii) */
	if(magicNumberCheck(ptr_img,0)){return EXIT_BAD_MAGIC_NUMBER;}
	
	/* check for a comment line */
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	
	/* read in blank space */
	int scanCount = fscanf(ptr_img->fileStream, " ");
	
	/* check for a comment line */
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}

	/* read in image width and height and check if they are valid */
	scanCount = fscanf(ptr_img->fileStream, " %u %u", &(ptr_img->width), &(ptr_img->height));
	/* check if dimensions are valid, reuturn error code if invalid */
	if(sizeCheck(ptr_img,scanCount)){return EXIT_BAD_DIMENSIONS;}

	/* read in blank character */
	scanCount = fscanf(ptr_img->fileStream, " ");
	/* check for comment line */
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}

	/* read in max gray value from file stream */
	scanCount = fscanf(ptr_img->fileStream, " %u", &(ptr_img->maxGray));
	/* check if max gray value is valid, 1 -> 255, return error if invalid */
	if(grayCheck(ptr_img)){return EXIT_BAD_MAX_GRAY;}
	
	/* allocate memory to store image data */
	ptr_img->imageData = malloc(ptr_img->height * sizeof(*ptr_img->imageData));
	/* check if memoery was allocated correctly */
	if (ptr_img->imageData == NULL){
		printf("ERROR: Image Malloc Failed\n");
		return EXIT_BAD_MALLOC;
	}

	/* loop through image data and allocate memory to each pointer, thereby creating a 2D array */
	for(int mallocRow=0; mallocRow<ptr_img->height; mallocRow++){
		ptr_img->imageData[mallocRow]=malloc(ptr_img->width * sizeof(unsigned char));
		/* check if each imageData[i] has been allocated correctly , return error if failed */
		if (ptr_img->imageData[mallocRow] == NULL){
			printf("ERROR: Image Malloc Failed\n");
			return EXIT_BAD_MALLOC;
		}
	}

	/* reading in the gray values of the image */
	int r=0;
	if((r=readData(ptr_img))!=0){
		/* if read data isn't valid free everything and return error code */
		free(ptr_img->imageData);	
		fclose(ptr_img->fileStream);
		printf("ERROR: Bad Data (%s)\n", ptr_img->fileName);	
		return r;
	}

	/* check if magic number is valid for pgma2b amd pgmb2a */
	if(magicNumberCheck(ptr_img,intendedFormat)){
		free(ptr_img->imageData);	
		return EXIT_BAD_MAGIC_NUMBER;
	}
	
	/* at this point we have read in data and all is valid, close filstream and return no errors */
	fclose(ptr_img->fileStream);
    return EXIT_NO_ERRORS;
}

/***********************************/
/* writeToFail function            */
/*                                 */
/* parameters:                     */
/* argv[0]: pointer to image struct*/
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int writeToFile(image *ptr_img){
	/* opens file to write to, stored pointer in fileSteam */
    ptr_img->fileStream = fopen(ptr_img->fileName, "w");

	/* write the data stored in its imageData to the file with fileName */
    if(writeData(ptr_img)){
		/* if it fails free everything and return error with string */
		free(ptr_img->imageData);
		printf("ERROR: Output Failed (%s)\n", ptr_img->fileName);	
		return EXIT_BAD_OUTPUT;
	}

	/* if no write errors we can exit, file has been written successfully */
    return EXIT_NO_ERRORS;
}