#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pgmImage.h"
#include "fileCheck.h"

/*initialising image*/
int initialiseImage(image *ptr_img,char *fileName){
	if(ptr_img==NULL){
		return 1;
	}
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
/*function to read data*/
int readData(image *ptr_img,long nImageBytes){

	if (ptr_img->imageData == NULL)
		{
		printf("ERROR: Image Malloc Failed\n");
		return EXIT_BAD_MALLOC;
	}
	/*checks ig magic number is binary*/
	if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
		getc(ptr_img->fileStream);
	}
	int scanCount;
	
	/*looping through gray values*/
	for(int i=0; i<ptr_img->height;i++){
		for(int j=0;j<ptr_img->width;j++)
		// for (unsigned char *nextGrayValue = ptr_img->imageData[i]; nextGrayValue < ptr_img->imageData[i] + nImageBytes; nextGrayValue++)
		{
			int grayValue = -1;
			if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
				/*write single byte if in binary format*/
				scanCount = fread(&grayValue,1,1,ptr_img->fileStream);
				grayValue = (int)(unsigned char)grayValue;
			}
			else{
				/*write using fscanf, ascii numbers*/
				scanCount = fscanf(ptr_img->fileStream, " %u", &grayValue);
				grayValue=(int) (((float) grayValue)/ptr_img->maxGray * 255);
			}
			
			if ((scanCount != 1) || (grayValue < 0) || (grayValue > ptr_img->maxGray))
				{
				
				return EXIT_BAD_INPUT;
				}

			// *nextGrayValue = (unsigned char) grayValue;
			ptr_img->imageData[i][j]=(unsigned char) grayValue;;
		}
	}
	
		
		/*checking if there are too many values*/
		int grayValue=-1;
		if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
			scanCount = fread(&grayValue,1,1,ptr_img->fileStream);
			if(scanCount==0){
				scanCount=-1;
			}
			
		}
		else{
			scanCount = fscanf(ptr_img->fileStream, " %u", &grayValue);
		}
		if(scanCount!=-1){	
			
			return EXIT_BAD_INPUT;
		}
    return 0;
}
int writeData(image *ptr_img,long nImageBytes){
	
    if (ptr_img->fileStream == NULL)
		{
		free(ptr_img->commentLine);
		free(ptr_img->imageData);

		printf("ERROR: Output Failed (%s)\n", ptr_img->fileName);	

		return 1;
		}
	size_t nBytesWritten = fprintf(ptr_img->fileStream, "%s\n%d %d\n%d\n", (char *) ptr_img->magic_Number,ptr_img->width, ptr_img->height, ptr_img->maxGray);
    if (nBytesWritten < 0)
		{ /* dimensional write failed    */
		/* free memory                   */
		free(ptr_img->commentLine);
		free(ptr_img->imageData);

		/* print an error message        */
		printf("ERROR: Output Failed (%s)\n", ptr_img->fileName);	

		/* return an error code          */
		return 1;
	} /* dimensional write failed    */
	for(int i=0; i<ptr_img->height;i++){
		for(int j=0;j<ptr_img->width;j++)
		// for (unsigned char *nextGrayValue = ptr_img->imageData[i]; nextGrayValue < ptr_img->imageData[i] + nImageBytes; nextGrayValue++)
            { /* per gray value */
			//printf("%d\n",*nextGrayValue);
		/* get next char's column        */
		// int nextCol = (nextGrayValue - ptr_img->imageData[i] + 1) % ptr_img->width;
		/* write the entry & whitespace  */
		if(*ptr_img->magic_Number == MAGIC_NUMBER_RAW_PGM){
			nBytesWritten = fwrite(&ptr_img->imageData[i][j], 1, 1, ptr_img->fileStream);
		}
		else{
			ptr_img->imageData[i][j]=(int) ((((float) ptr_img->imageData[i][j])/255 * ptr_img->maxGray));
			nBytesWritten = fprintf(ptr_img->fileStream, "%d%c", ptr_img->imageData[i][j],' ');
		
		}

		/* sanity check on write         */
		if (nBytesWritten < 0)
			{ /* data write failed   */
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
	/*magic number check*/
	//return EXIT_BAD_DIMENSIONS;
	
	if(magicNumberCheck(ptr_img,0)){return EXIT_BAD_MAGIC_NUMBER;}
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	
	int scanCount = fscanf(ptr_img->fileStream, " ");
	/*comment line check*/
	
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}

	
	scanCount = fscanf(ptr_img->fileStream, " %u %u", &(ptr_img->width), &(ptr_img->height));
	
	/*check gray value*/
	//printf("%i %i", ptr_img->width, ptr_img->height);
	if(sizeCheck(ptr_img,scanCount)){return EXIT_BAD_DIMENSIONS;}
	//return EXIT_BAD_DIMENSIONS;
	scanCount = fscanf(ptr_img->fileStream, " ");
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	scanCount = fscanf(ptr_img->fileStream, " %u", &(ptr_img->maxGray));
	if(grayCheck(ptr_img)){return EXIT_BAD_MAX_GRAY;}
	if(getCommentLine(ptr_img)){return EXIT_BAD_COMMENT_LINE;}
	/*size check*/

	long nImageBytes = ptr_img->width * sizeof(unsigned char);
	ptr_img->imageData = malloc(ptr_img->height * sizeof(*ptr_img->imageData));
	if (ptr_img->imageData == NULL)
		{
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
	if((r=readData(ptr_img,nImageBytes))!=0){
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
/*writing to file, parses a fileName and number of bytes to write*/
int writeToFile(image *ptr_img, char *fileName, int nImageBytes){
    ptr_img->fileStream = fopen(ptr_img->fileName, "w");
    if(writeData(ptr_img,nImageBytes)){
		return EXIT_BAD_OUTPUT;
	}
    return EXIT_NO_ERRORS;
}