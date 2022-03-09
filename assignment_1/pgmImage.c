#include <stdio.h>
#include <stdlib.h>
#include "pgmImage.h"

int readData(image *ptr_img1,long nImageBytes){

	if (ptr_img1->imageData == NULL)
		{
		free(ptr_img1->commentLine);

		fclose(ptr_img1->inputFile);

		printf("1Error: Failed to read pgm image from file %s\n", ptr_img1->fileName);	
		
		return 1;
	}
	for (unsigned char *nextGrayValue = ptr_img1->imageData; nextGrayValue < ptr_img1->imageData + nImageBytes; nextGrayValue++)
		{
		int grayValue = -1;
		int scanCount = fscanf(ptr_img1->inputFile, " %u", &grayValue);

		if ((scanCount != 1) || (grayValue < 0) || (grayValue > ptr_img1->maxGray))
			{
			free(ptr_img1->commentLine);
			free(ptr_img1->imageData);	

			fclose(ptr_img1->inputFile);

			printf("Error: Failed to read pgm image from file %s\n", ptr_img1->fileName);	
		
			return 1;
			}

		*nextGrayValue = (unsigned char) grayValue;
		}
    return 0;
}
int writeData(image *ptr_img2,long nImageBytes){
    if (ptr_img2->outputFile == NULL)
		{
		free(ptr_img2->commentLine);
		free(ptr_img2->imageData);

		printf("2Error: Failed to write pgm image to file %s\n", ptr_img2->fileName);	

		return 1;
		}
	
	size_t nBytesWritten = fprintf(ptr_img2->outputFile, "P2\n%d %d\n%d\n", ptr_img2->width, ptr_img2->height, ptr_img2->maxGray);
    if (nBytesWritten < 0)
		{ /* dimensional write failed    */
		/* free memory                   */
		free(ptr_img2->commentLine);
		free(ptr_img2->imageData);

		/* print an error message        */
		printf("4Error: Failed to write pgm image to file %s\n", ptr_img2->fileName);	

		/* return an error code          */
		return 1;
	} /* dimensional write failed    */
    for (unsigned char *nextGrayValue = ptr_img2->imageData; nextGrayValue < ptr_img2->imageData + nImageBytes; nextGrayValue++)
            { /* per gray value */
		/* get next char's column        */
		int nextCol = (nextGrayValue - ptr_img2->imageData + 1) % ptr_img2->width;

		/* write the entry & whitespace  */
		nBytesWritten = fprintf(ptr_img2->outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		/* sanity check on write         */
		if (nBytesWritten < 0)
			{ /* data write failed   */
			/* free memory           */
			free(ptr_img2->commentLine);
			free(ptr_img2->imageData);

			/* print error message   */
			printf("5Error: Failed to write pgm image to file %s\n", ptr_img2->fileName);	

			/* return an error code  */
			return 1;
			} /* data write failed   */
		} /* per gray value */
    return 0;
}