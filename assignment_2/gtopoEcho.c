/* library for I/O routines */
#include <stdio.h>
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
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int main(int argc, char **argv){
	/* checking if only 1 argument */
	if (argc == 1){
		/* print error message if only 1 argument */
		printf("Usage: %s inputFile width height outputFile\n", argv[0]);
		/* return according error code */
		return EXIT_NO_ERRORS;
	}

	/* checking for correct number of arguments */
	if (argc != 5)	{
		/* print error message if wrong number of arguments */
		printf("ERROR: Bad Argument Count\n");
		/* return according error code */
		return EXIT_WRONG_ARG_COUNT;
	} 

	/*pointer to image struct, allocating memory size of image struct*/
	image *ptr_img1 = malloc(sizeof(image));

	/* initialising data in struct */
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}

	if(!isNumber(argv[2]) || !isNumber(argv[3])){
		printf("ERROR: Miscellaneous (invalid dimensions)\n");
		return EXIT_MISC;
	}
	ptr_img1->width = atoi(argv[2]);
	ptr_img1->height = atoi(argv[3]);
	/* read in file and save all necessary data to struct parsed in */
	/* parse in intended read format (if it matters),0 if doesnt, 1 if ascii, 2 if binary */
	int returnVal = readInFile(ptr_img1);
	/* if it doesn return 0 it has failed, return according error code */
	if(returnVal!=0){
		return returnVal;
	}
	
	/* the ammount of memory needed for each row of the image to store */

	/*pointer to second image struct, allocating memoty size of image struct*/
	image *ptr_img2=ptr_img1;
	/* all data the same as first image except for file name */
	
	ptr_img2->fileName=argv[4];
	/*writing second image to file*/
	returnVal=writeToFile(ptr_img2);
	/* if it doesn return 0 it has failed, return according error code */
	if(returnVal!=0){
		return returnVal;
	}

	/* if it reaches this point is has echoed correctly */
	printf("ECHOED\n");
	/* return no error code */
	return EXIT_NO_ERRORS;
}
