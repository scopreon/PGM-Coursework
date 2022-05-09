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

	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}

	int returnVal;

	//read in magic number first
	//parse in intended read format (if it matters),0 if doesnt, 1 if ascii, 2 if binary
	
	returnVal = readInFile(ptr_img1,0);
	if(returnVal!=0){
		return returnVal;
	}

	
	long nImageBytes = ptr_img1->width * ptr_img1->height * sizeof(unsigned char);
	/*pointer to second image struct, allocating memoty size of image struct*/
	image *ptr_img2=ptr_img1;
	ptr_img2->fileName=argv[2];
	/*writing to file with same image data*/
	returnVal=writeToFile(ptr_img2, argv[2],nImageBytes);
	if(returnVal!=0){
		return returnVal;
	}

	/* at this point, we are done and can exit with a success code */
	printf("ECHOED\n");
	return EXIT_NO_ERRORS;
	} /* main() */
