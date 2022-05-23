/* library for I/O routines */
#include <stdio.h>
/* library for checking variable types */
#include <ctype.h>
/* library for memory routines */
#include <stdlib.h>
/* methods for checking file information is valid */
#include "fileCheck.h"
/* contains reading and writing functions */
#include "gtopoImage.h"

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: reduction factor       */
/* argv[3]: output file            */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int main(int argc, char **argv)
{
	/* checking for correct number of arguments */
	if (argc == 1)	
	{
		/* print error message if only 1 argument */
		printf("Usage: %s width height reduction_factor output\n", argv[0]);
		/* return according error code */
		return EXIT_NO_ERRORS;
	}
	
	/* checking for correct number of arguments */
	if (argc != 6)	
	{
		/* print error message if wrong number of arguments */
		printf("ERROR: Bad Argument Count\n");
		/* return according error code */
		return EXIT_WRONG_ARG_COUNT;
	} 

	/* checking if scaling factor is a number */
	if(!isNumber(argv[2]) || !isNumber(argv[3]) || !isNumber(argv[4])){
		printf("ERROR: Miscellaneous (width/height/reduction invalid)\n");
		return EXIT_MISC;
	}

	/* store scaling factor in variable size */
    int size = atoi(argv[4]);

	/* creating pointer to image struct */
	image *ptr_img1 = malloc(sizeof(image));

	/* initialising image 1 with basic data */
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}
	ptr_img1->width = atoi(argv[2]);
	ptr_img1->height = atoi(argv[3]);
	/* read in file to reduce */
	int returnVal;
	if((returnVal = readInFile(ptr_img1))!=0){
		return returnVal;
	}

	image *ptr_img2 = malloc(sizeof(image));
	/* initialising image 2 */
	if(initialiseImage(ptr_img2,argv[5])){
		return EXIT_BAD_MALLOC;
	}

	/* heights and widths created fo image 2 */
	ptr_img2->width=(int)((float)ptr_img1->width+size-1)/size;
	ptr_img2->height=(int)((float)ptr_img1->height+size-1)/size;

	/* malloc data for output file */
	ptr_img2->imageData = malloc(ptr_img2->height * sizeof(*ptr_img2->imageData));
	for(int rowMalloc = 0; rowMalloc < ptr_img2->height; rowMalloc++){
		ptr_img2->imageData[rowMalloc]=malloc(ptr_img2->width * sizeof(short int));
	}

	/* loop through data selecting every size'th value */
	for(int loopRow = 0; loopRow < ptr_img2->height; loopRow++){
		for(int loopCol = 0; loopCol < ptr_img2->width;loopCol++){
			/* move data from first pgm to second pgm */
			ptr_img2->imageData[loopRow][loopCol]=ptr_img1->imageData[loopRow*size][loopCol*size];
		}
	}

	/* write image 2 data to file, contains reduced image 1 */
	returnVal=writeToFile(ptr_img2);
    if(returnVal!=0){
		return returnVal;
	}

	/* at this point, the file has been reduced */
	printf("REDUCED\n");
	return EXIT_NO_ERRORS;
}
