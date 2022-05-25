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
	if (argc != 8)	{
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

	if(!isNumber(argv[2]) || !isNumber(argv[3])/* || !isNumber(argv[5]) || !isNumber(argv[6]) || !isNumber(argv[7])*/){
		printf("ERROR: Miscellaneous (non-numeric data)\n");
		return EXIT_MISC;
	}
	ptr_img1->width = atoi(argv[2]);
	ptr_img1->height = atoi(argv[3]);
	int sea = atoi(argv[5]);
	int hill = atoi(argv[6]);
	int mountain = atoi(argv[7]);
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
	ptr_img2->fileStream = fopen(ptr_img2->fileName, "w");
	/*writing second image to file*/
	char character;
	for(int loopRow = 0; loopRow < ptr_img1->height; loopRow++){
        for(int loopCol = 0; loopCol < ptr_img1->width; loopCol++){
			if(ptr_img1->imageData[loopRow][loopCol]<sea){
				character = ' ';
			}
			else if(ptr_img1->imageData[loopRow][loopCol]<hill){
				character = '.';
			}
			else if(ptr_img1->imageData[loopRow][loopCol]<mountain){
				character = '^';
			}
			else{
				character = 'A';
			}
            int nBytesWritten = fprintf(ptr_img2->fileStream, "%c",character);
        }
		int nBytesWritten = fprintf(ptr_img2->fileStream, "%c",'\n');
    }

	/* if it reaches this point is has echoed correctly */
	printf("PRINTED\n");
	/* return no error code */
	return EXIT_NO_ERRORS;
}
