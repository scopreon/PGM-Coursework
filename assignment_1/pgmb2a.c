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
/* argv[1]: input binary file name */
/* argv[2]: output ascii file name */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int main(int argc, char **argv)
{
	/* checking for correct number of arguments */
	if (argc == 1)	
	{
		/* print error message if only 1 argument */
		printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
		/* return according error code */
		return EXIT_NO_ERRORS;
	}

	/* checking for correct number of arguments */
	if (argc != 3)	
	{
		/* print error message if wrong number of arguments */
		printf("ERROR: Bad Argument Count\n");
		/* return according error code */
		return EXIT_WRONG_ARG_COUNT;
	} 

	/* pointer to image struct, allocating memory size of image struct */
	image *ptr_img1 = malloc(sizeof(image));
	/* initialises image struct with basid data */
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}

	/* readInFile reads in data to struct */
	int returnVal;
	if((returnVal=readInFile(ptr_img1,2))!=0){
		return returnVal;
	}
	/* pointer to image struct same as original image, jsut different magic number */
	image *ptr_img2=ptr_img1;
	ptr_img2->fileName=argv[2];

	/* magic number values being set for output file */
	ptr_img2->magic_number[0] = 'P';
	ptr_img2->magic_number[1] = '2';
	ptr_img2->magic_Number=(unsigned short *) ptr_img2->magic_number;
	
	/*calling write file on new image struct, writing converted data*/
	returnVal=writeToFile(ptr_img2);
	if(returnVal!=0){
		return returnVal;
	}

	/* at this point the image has been converted, exit accordingly */
	printf("CONVERTED\n");
	return EXIT_NO_ERRORS;
}
