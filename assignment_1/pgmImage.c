#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "pgmImage.h"
#include "fileCheck.h"

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
	for(int i = 0; text[i]!='\0';i++){
		/* if any characers aren't string */
		/* note: this also detects . and - as non digits so this function checks if positive integer */
		if(!isdigit(text[i])){
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
    ptr_img->commentLine=NULL;
    ptr_img->fileStream=NULL;
    ptr_img->fileName=fileName;
    ptr_img->imageData=NULL;
    ptr_img->magic_Number=NULL;
	ptr_img->magic_number[0] = '0';
	ptr_img->magic_number[1] = '0';
	return 0;
}

/***********************************/
/* readData function               */
/*                                 */
/* CLI parameters:                 */
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
	for(int i=0; i<ptr_img->height;i++){
		for(int j=0;j<ptr_img->width;j++){
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
			ptr_img->imageData[i][j]=(unsigned char) grayValue;;
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
/*-----------------------------------------------------------------------------------*/
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
int writeData(image *ptr_img){
    if (ptr_img->fileStream == NULL)
		{
		free(ptr_img->commentLine);
		free(ptr_img->imageData);
		printf("ERROR: Output Failed (%s)\n", ptr_img->fileName);	
		return 1;
		}
	size_t nBytesWritten = fprintf(ptr_img->fileStream, "%s\n%d %d\n%d\n", (char *) ptr_img->magic_Number,ptr_img->width, ptr_img->height, ptr_img->maxGray);
    if (nBytesWritten < 0){
		 /* dimensional write failed    */
		/* free memory                   */
		free(ptr_img->commentLine);
		free(ptr_img->imageData);

		/* print an error message        */
		printf("ERROR: Output Failed (%s)\n", ptr_img->fileName);	

		/* return an error code          */
		return 1;
	} /* dimensional write failed    */
	for(int i=0; i<ptr_img->height;i++){
		for(int j=0;j<ptr_img->width;j++){
		if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
			nBytesWritten = fwrite(&ptr_img->imageData[i][j], 1, 1, ptr_img->fileStream);
		}
		else{
			ptr_img->imageData[i][j]=(int) ((((float) ptr_img->imageData[i][j])/255 * ptr_img->maxGray));
			nBytesWritten = fprintf(ptr_img->fileStream, "%d%c", ptr_img->imageData[i][j],' ');
		
		}

		/* sanity check on write         */
		if (nBytesWritten < 0){
			/* free memory           */
			free(ptr_img->commentLine);
			free(ptr_img->imageData);

			/* print error message   */
			printf("ERROR: Output Failed (%s)\n", ptr_img->fileName);	

			/* return an error code  */
			return 1;
			} /* data write failed   */
		} /* per gray value */
		if(*ptr_img->magic_Number != MAGIC_NUMBER_RAW_PGM){
			nBytesWritten = fprintf(ptr_img->fileStream, "%c", '\n' );
		}
		
	}
    
    return 0;
}
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
int readInFile(image *ptr_img, int intendedFormat){
	/*initialising magic number*/
	ptr_img->magic_number[0] = '0';
	ptr_img->magic_number[1] = '0';
	ptr_img->magic_Number=(unsigned short *) ptr_img->magic_number;
	ptr_img->fileStream =  fopen(ptr_img->fileName, "r");
	
	
	if (ptr_img->fileStream == NULL){
		printf("ERROR: Bad File Name (%s)\n",ptr_img->fileName);
		return EXIT_BAD_FILE_NAME;
	}
	
	ptr_img->magic_number[0] = getc(ptr_img->fileStream);
	ptr_img->magic_number[1] = getc(ptr_img->fileStream);
	
	if(magicNumberCheck(ptr_img,0)){return EXIT_BAD_MAGIC_NUMBER;}
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	
	int scanCount = fscanf(ptr_img->fileStream, " ");
	/*comment line check*/
	
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}

	
	scanCount = fscanf(ptr_img->fileStream, " %u %u", &(ptr_img->width), &(ptr_img->height));
	
	/*check gray value*/
	if(sizeCheck(ptr_img,scanCount)){return EXIT_BAD_DIMENSIONS;}
	scanCount = fscanf(ptr_img->fileStream, " ");
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	scanCount = fscanf(ptr_img->fileStream, " %u", &(ptr_img->maxGray));
	if(grayCheck(ptr_img)){return EXIT_BAD_MAX_GRAY;}
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	/*size check*/

	long nImageBytes = ptr_img->width * sizeof(unsigned char);
	ptr_img->imageData = malloc(ptr_img->height * sizeof(*ptr_img->imageData));
	if (ptr_img->imageData == NULL){
		printf("ERROR: Image Malloc Failed\n");
		return EXIT_BAD_MALLOC;
	}
	for(int i=0;i<ptr_img->height ;i++){
		ptr_img->imageData[i]=malloc(nImageBytes);
		if (ptr_img->imageData[i] == NULL){
			printf("ERROR: Image Malloc Failed\n");
			return EXIT_BAD_MALLOC;
		}
	}
	int r=0;
	/*reading in data, nImageBytes number of  bytes*/
	if((r=readData(ptr_img))!=0){
		free(ptr_img->commentLine);
		free(ptr_img->imageData);	

		fclose(ptr_img->fileStream);

		printf("ERROR: Bad Data (%s)\n", ptr_img->fileName);	
		return r;
	}
	if(magicNumberCheck(ptr_img,intendedFormat)){return EXIT_BAD_MAGIC_NUMBER;}
	fclose(ptr_img->fileStream);
    return EXIT_NO_ERRORS;
}
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
int writeToFile(image *ptr_img){
    ptr_img->fileStream = fopen(ptr_img->fileName, "w");
    if(writeData(ptr_img)){
		return EXIT_BAD_OUTPUT;
	}
    return EXIT_NO_ERRORS;
}