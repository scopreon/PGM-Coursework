/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "fileCheck.h"
#include "pgmImage.h"

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
int main(int argc, char **argv)
	{ /* main() */
	/* check for correct number of arguments */
	if (argc == 1)	
		{ /* wrong arg count */
		/* print an error message        */
		printf("Usage: %s inputImage.pgm inputImage.pgm\n", argv[0]);
		/* and return an error code      */
		return EXIT_NO_ERRORS;
	}
	if (argc != 3)	
		{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count\n");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */

	/*pointer to image struct, allocating memory size of image struct*/
	image *ptr_img1 = malloc(sizeof(image));
	/*initialising first image*/
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}
	/*pointer to second image struct, allocating memory size of image struct*/
	image *ptr_img2 = malloc(sizeof(image));
	/*initialising second image*/
	if(initialiseImage(ptr_img2,argv[2])){
		return EXIT_BAD_MALLOC;
	}

	int returnVal;
	/*read in image 1*/
	if((returnVal=readInFile(ptr_img1,0))!=0){
		return returnVal;
	}
	/*read in image 2*/
	if((returnVal=readInFile(ptr_img2,0))!=0){
		return returnVal;
	}
	if(ptr_img1->width != ptr_img2->width || ptr_img1->height != ptr_img2->height){
		printf("DIFFERENT\n");
		return EXIT_NO_ERRORS;
	}
	long nImageBytes = ptr_img1->width * ptr_img1->height * sizeof(unsigned char);
	/*pointers to respective image data for each image struct*/
	for(int i = 0; i < ptr_img1->height;i++){
		for(int j = 0; j < ptr_img1->width;j++){
			if(((float) ptr_img1->imageData[i][j])/ptr_img2->maxGray!=((float) ptr_img2->imageData[i][j])/ptr_img1->maxGray){
				printf("DIFFERENT\n");
				return EXIT_NO_ERRORS;
			}
		}
	}
	// unsigned char *nextGrayValue1 = ptr_img1->imageData;
	// unsigned char *nextGrayValue2 = ptr_img2->imageData;
	// while (nextGrayValue1 < ptr_img1->imageData + nImageBytes){
	// 	int nextCol = (nextGrayValue1 - ptr_img1->imageData + 1) % ptr_img1->width;
		
	// 		printf("DIFFERENT\n");
	// 		return EXIT_NO_ERRORS;
	// 	}
	// 	nextGrayValue1++;
	// 	nextGrayValue2++;
	// }
	/*the files are identical if it gets to this point*/
	printf("IDENTICAL\n");
	return EXIT_NO_ERRORS;
	} /* main() */
