/* library for I/O routines        */
#include <stdio.h>
/* library for memory routines     */
#include <stdlib.h>

/*methods for checking file information*/
#include "fileCheck.h"
/*contains reading and writing*/
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
		printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
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
	/*initialises image struct with default values
	returns 1 on failiure to successfully allocate memory*/
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}
	/*readInFile reads in data to struct*/
	int returnVal;
	if((returnVal=readInFile(ptr_img1,2))!=0){
		return returnVal;
	}
	/*number of bytes image takes up*/
	long nImageBytes = ptr_img1->width * sizeof(unsigned char);
	image *ptr_img2=ptr_img1;
	ptr_img2->fileName=argv[2];
	/*magic number values being set for output file*/
	ptr_img2->magic_number[0] = 'P';
	ptr_img2->magic_number[1] = '2';
	ptr_img2->magic_Number=(unsigned short *) ptr_img2->magic_number;
	/*calling write file on new image struct, writing converted data*/
	returnVal=writeToFile(ptr_img2, argv[2],nImageBytes);
	if(returnVal!=0){
		return returnVal;
	}

	/* at this point, we are done and can exit with a success code */
	printf("CONVERTED\n");
	return EXIT_NO_ERRORS;
	} /* main() */
