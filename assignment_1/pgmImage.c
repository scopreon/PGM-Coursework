#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgmImage.h"
#include "fileCheck.h"

#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

int readData(image *ptr_img,long nImageBytes){

	if (ptr_img->imageData == NULL)
		{
		free(ptr_img->commentLine);

		fclose(ptr_img->inputFile);

		printf("1Error: Failed to read pgm image from file %s\n", ptr_img->fileName);	
		
		return 1;
	}
	if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
		getc(ptr_img->inputFile);
	}
	for (unsigned char *nextGrayValue = ptr_img->imageData; nextGrayValue < ptr_img->imageData + nImageBytes; nextGrayValue++)
		{
		int grayValue = -1;
		if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
			//*nextGrayValue = (char) (((int) *nextGrayValue)/ptr_img->maxGray * 255);
			int scanCount = fread(&grayValue,1,1,ptr_img->inputFile);
			//grayValue=(((int) grayValue)/ptr_img->maxGray * 255);
			
		}
		else{
			int scanCount = fscanf(ptr_img->inputFile, " %u", &grayValue);
		}
		
		
		
		// if ((scanCount != 1) || (grayValue < 0) || (grayValue > ptr_img->maxGray))
		// 	{
		// 	free(ptr_img->commentLine);
		// 	free(ptr_img->imageData);	

		// 	fclose(ptr_img->inputFile);

		// 	printf("Error: Failed to read pgm image from file %s\n", ptr_img->fileName);	
		
		// 	return 1;
		// 	}

		*nextGrayValue = (unsigned char) grayValue;
		}
    return 0;
}
int writeData(image *ptr_img,long nImageBytes, int factor){
    if (ptr_img->outputFile == NULL)
		{
		free(ptr_img->commentLine);
		free(ptr_img->imageData);

		printf("2Error: Failed to write pgm image to file %s\n", ptr_img->fileName);	

		return 1;
		}
	// char magicNumber[3];
	// memcpy(magicNumber, (char *) ptr_img->magic_Number , 2);
	// printf("%s",magicNumber);
	int oldWidth=ptr_img->width;
	ptr_img->width=(ptr_img->width+factor-1)/factor;
	ptr_img->height=(ptr_img->height+factor-1)/factor;

	size_t nBytesWritten = fprintf(ptr_img->outputFile, "%s\n%d %d\n%d\n", (char *) ptr_img->magic_Number,ptr_img->width, ptr_img->height, ptr_img->maxGray);
    if (nBytesWritten < 0)
		{ /* dimensional write failed    */
		/* free memory                   */
		free(ptr_img->commentLine);
		free(ptr_img->imageData);

		/* print an error message        */
		printf("4Error: Failed to write pgm image to file %s\n", ptr_img->fileName);	

		/* return an error code          */
		return 1;
	} /* dimensional write failed    */
	int column=0;
	int row=0;
    for (unsigned char *nextGrayValue = ptr_img->imageData; nextGrayValue < ptr_img->imageData + nImageBytes; nextGrayValue++)
            { /* per gray value */
		/* get next char's column        */
		int nextCol = (nextGrayValue - ptr_img->imageData + 1) % ptr_img->width;
		//printf("%x ", *nextGrayValue);
		/* write the entry & whitespace  */

		if(column%factor==0 && row%factor==0){
		if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
			//*nextGrayValue = (char) (((int) *nextGrayValue)/ptr_img->maxGray * 255);
			// *nextGrayValue=(int) *nextGrayValue/2;
			nBytesWritten = fwrite(nextGrayValue, 1, 1, ptr_img->outputFile);
		}
		else{
			nBytesWritten = fprintf(ptr_img->outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );
		}
		}
		column++;
		if(column%(oldWidth) == 0){
			row++;
		}
		/* sanity check on write         */
		if (nBytesWritten < 0)
			{ /* data write failed   */
			/* free memory           */
			free(ptr_img->commentLine);
			free(ptr_img->imageData);

			/* print error message   */
			printf("5Error: Failed to write pgm image to file %s\n", ptr_img->fileName);	

			/* return an error code  */
			return 1;
			} /* data write failed   */
		} /* per gray value */
    return 0;
}

int readInFile(image *ptr_img, char *fileName){
	// unsigned char magic_number[2] = {'0','0'};
	ptr_img->magic_number[0] = '0';
	ptr_img->magic_number[1] = '0';
	ptr_img->magic_Number=(unsigned short *) ptr_img->magic_number;
	//unsigned short *magic_Number = (unsigned short *) ptr_img->magic_number;
	ptr_img->inputFile =  fopen(fileName, "r");
	ptr_img->fileName=fileName;

	if (ptr_img->inputFile == NULL)
		return EXIT_BAD_INPUT_FILE;

	ptr_img->magic_number[0] = getc(ptr_img->inputFile);
	ptr_img->magic_number[1] = getc(ptr_img->inputFile);
	// if(magicNumberCheck(ptr_img)){
	// 	return EXIT_BAD_INPUT_FILE;
	// }

	int scanCount = fscanf(ptr_img->inputFile, " ");

	if(getCommentLine(ptr_img)){
		return EXIT_BAD_INPUT_FILE;
	}

	scanCount = fscanf(ptr_img->inputFile, " %u %u %u", &(ptr_img->width), &(ptr_img->height), &(ptr_img->maxGray));

	if(sizeCheck(ptr_img,scanCount)){
		return EXIT_BAD_INPUT_FILE;
	}

	long nImageBytes = ptr_img->width * ptr_img->height * sizeof(unsigned char);
	ptr_img->imageData = (unsigned char *) malloc(nImageBytes);
	if(readData(ptr_img,nImageBytes)){
		return EXIT_BAD_INPUT_FILE;
	}

	fclose(ptr_img->inputFile);
    return EXIT_NO_ERRORS;
}

int writeToFile(image *ptr_img, char *fileName, int nImageBytes, int factor){
    ptr_img->fileName=fileName;
    ptr_img->outputFile = fopen(fileName, "w");
    if(writeData(ptr_img,nImageBytes,factor)){
		return EXIT_BAD_OUTPUT_FILE;
	}
    return EXIT_NO_ERRORS;
}