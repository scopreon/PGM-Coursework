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
#include "gtopoImage.h"

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
    ptr_img->fileStream=NULL;
	ptr_img->fileName=malloc(sizeof(char)*(strlen(fileName)+1));
	strcpy(ptr_img->fileName,fileName);
    ptr_img->imageData=NULL;
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

	int scanCount;
	/* looping through gray values to read in and store in image struct*/
	for(int loopRow=0; loopRow<ptr_img->height; loopRow++){
		for(int loopCol=0; loopCol<ptr_img->width; loopCol++){
			unsigned short int grayValue1 = 0;
			/* read in data according to a specific format */
			/* read in a single byte for each gray value, binary format */
			scanCount = fread(&grayValue1,2,1,ptr_img->fileStream);

			grayValue1 = (unsigned short int) grayValue1;
			/* ensuring a gray value read in and it is valid */
			if ((scanCount != 1) || (grayValue1 < 0)){
				return EXIT_BAD_INPUT;
			}
			/* save the value in image data */
			unsigned short int grayValue2=(grayValue1>>8)|(grayValue1<<8);
			ptr_img->imageData[loopRow][loopCol]=(short int) grayValue2;
		}
	}
	int grayValue=-1;
	/* try read in another value, if this passes we have too much data */
	/* check if too much data was read in, return bad input if it did */
	if(fread(&grayValue,1,1,ptr_img->fileStream)!=0){	
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
	size_t nBytesWritten;

	/* loop through all pixel values in 2D array and write each one to file */
	for(int loopRow=0; loopRow<ptr_img->height; loopRow++){
		for(int loopCol=0; loopCol<ptr_img->width; loopCol++){
			/* writing a single byte to file, binary format */ 
			unsigned short int grayValue = (unsigned short int) ptr_img->imageData[loopRow][loopCol];
			grayValue=(grayValue>>8)|(grayValue<<8);
			nBytesWritten = fwrite(&grayValue, 2, 1, ptr_img->fileStream);

			/* checking if each write passed, return error if failed */
			if (nBytesWritten < 0){
				return 1;
			}
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
/*                                 */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int readInFile(image *ptr_img){
	/* reading in file to filestream using fopen */
	ptr_img->fileStream =  fopen(ptr_img->fileName, "r");
	
	/* checking if fileStream is NULL when reading in file */
	if (ptr_img->fileStream == NULL){
		printf("ERROR: Bad File Name (%s)\n",ptr_img->fileName);
		return EXIT_BAD_FILE_NAME;
	}
	
	/* allocate memory to store image data */
	ptr_img->imageData = malloc(ptr_img->height * sizeof(*ptr_img->imageData));
	/* check if memoery was allocated correctly */
	if (ptr_img->imageData == NULL){
		printf("ERROR: Image Malloc Failed\n");
		return EXIT_BAD_MALLOC;
	}

	/* loop through image data and allocate memory to each pointer, thereby creating a 2D array */
	for(int mallocRow=0; mallocRow<ptr_img->height; mallocRow++){
		ptr_img->imageData[mallocRow]=malloc(ptr_img->width * sizeof(short int));
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