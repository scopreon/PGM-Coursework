/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>
/* methods for checking file information is valid */
#include "fileCheck.h"
/* contains reading and writing functions */
#include "pgmImage.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: comp1 file name        */
/* argv[2]: comp2 file name        */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int main(int argc, char **argv){
	/* checking for correct number of arguments */
	if (argc == 1){
		/* print error message if only 1 argument */	
		printf("Usage: %s inputImage.pgm inputImage.pgm\n", argv[0]);
		/* return according error code */
		return EXIT_NO_ERRORS;
	}
	
	/* checking for correct number of arguments */
	if (argc != 3){
		/* print error message if wrong number of arguments */
		printf("ERROR: Bad Argument Count\n");
		/* return according error code */
		return EXIT_WRONG_ARG_COUNT;
	} 

	/* pointer to first image struct, allocating memory size of image struct */
	image *ptr_img1 = malloc(sizeof(image));
	/* initialising first image with simple data*/
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}

	/* pointer to second image struct, allocating memory size of image struct */
	image *ptr_img2 = malloc(sizeof(image));
	/* initialising second image*/
	if(initialiseImage(ptr_img2,argv[2])){
		return EXIT_BAD_MALLOC;
	}

	int returnVal;
	/* read in first image*/
	if((returnVal=readInFile(ptr_img1,0))!=0){
		return returnVal;
	}
	/* read in second image*/
	if((returnVal=readInFile(ptr_img2,0))!=0){
		return returnVal;
	}
	/* compare widths and heights initially */
	if(ptr_img1->width != ptr_img2->width || ptr_img1->height != ptr_img2->height){
		printf("DIFFERENT\n");
		return EXIT_NO_ERRORS;
	}

	/* loop though each pixel in first image and compare it to second */
	for(int loopRow = 0; loopRow < ptr_img1->height; loopRow++){
		for(int loopCol = 0; loopCol < ptr_img1->width; loopCol++){
			/* compare data, scale it according to max gray value */
			if(((float) ptr_img1->imageData[loopRow][loopCol])/ptr_img2->maxGray != ((float) ptr_img2->imageData[loopRow][loopCol])/ptr_img1->maxGray){
				/* if something doesn't match they are different */
				printf("DIFFERENT\n");
				return EXIT_NO_ERRORS;
			}
		}
	}

	/* the files are identical if it gets to this point, compared correctly */
	printf("IDENTICAL\n");
	return EXIT_NO_ERRORS;
}
