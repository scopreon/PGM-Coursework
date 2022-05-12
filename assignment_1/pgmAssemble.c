/* library for I/O routines */
#include <stdio.h>
/* library for checking variable types */
#include <ctype.h>
/* library for math routines */
#include <math.h>
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
/* argv[1]: output file name       */
/* argv[2]: width                  */
/* argv[3]: height                 */
/* argv[i]: position row           */
/* argv[i+1]: position column      */
/* argv[i+2]: input file name      */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int main(int argc, char **argv)
{
	/* checking for correct number of arguments */
	if (argc == 1)	
	{
		/* print error message if only 1 argument */
		printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+\n", argv[0]);
		/* return according error code */
		return EXIT_NO_ERRORS;
	}

	/* checking for correct number of arguments */
	if ((argc-1)%3 != 0)	
	{
		/* print error message if wrong number of arguments */
		printf("ERROR: Bad Argument Count\n");
		/* return according error code */
		return EXIT_WRONG_ARG_COUNT;
	} 
	
	/* ensure width is an integer */
	if(!isNumber(argv[2])){
		printf("ERROR: Miscellaneous (invalid scaling factor)\n");
		return EXIT_MISC;
	}
	/* ensure height is an integer */
	if(!isNumber(argv[3])){
		printf("ERROR: Miscellaneous (invalid scaling factor)\n");
		return EXIT_MISC;
	}

	int returnVal;
	/* creating template image to write over */
	image *ptr_img1 = malloc(sizeof(image));
	/* initialising image 1 with basic data */
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}
	
	/* initialising data for template image */
	ptr_img1->width=atoi(argv[2]);
	ptr_img1->height=atoi(argv[3]);
	ptr_img1->maxGray=255;

	/* allocating memory for storing image data in 2D format*/
	long nImageBytes = ptr_img1->width * sizeof(unsigned char);
	ptr_img1->imageData = malloc(ptr_img1->height * sizeof(*ptr_img1->imageData));
	for(int i=0;i<ptr_img1->height ;i++)
	{
		ptr_img1->imageData[i]=malloc(nImageBytes);
	}

	/* creating image 2 which stores images incrementally read in */
	image *ptr_img2 = malloc(sizeof(image));
	/* initialising image 1 with basic data */
	if(initialiseImage(ptr_img2,argv[3])){
		return EXIT_BAD_MALLOC;
	};

	/* looping through command line arguments in triplets */
	for(int i = 4;i<argc-2;i+=3){
		
		/* the third argument in each triplet is the filename to read in */
		ptr_img2->fileName=argv[i+2];

		/* making sure coordinates (x,y) to put the image are integers */
		if(!isNumber(argv[i])){
			printf("ERROR: Miscellaneous (invalid image position)\n");
			return EXIT_MISC;
		}
		if(!isNumber(argv[i+1])){
			printf("ERROR: Miscellaneous (invalid image position)\n");
			return EXIT_MISC;
		}

		/* read in each file to assemble */
		if((returnVal = readInFile(ptr_img2,0))!=0){
			return returnVal;
		}
		
		/* loop through file data and add it to first image blank canvas image data */
		for(int h = 0;h < ptr_img2->height;h++){
			for(int w = 0;w < ptr_img2->width;w++){
				/* move data from image two to image one*/
				ptr_img1->imageData[atoi(argv[i])+h][atoi(argv[i+1])+w]=ptr_img2->imageData[h][w];
			}
		}

		/* set the magic number of read in file to final assembled image magic number */
		ptr_img1->magic_Number=ptr_img2->magic_Number;
		
	}
	
	/* final assembled image is written to image */
	returnVal=writeToFile(ptr_img1);
    if(returnVal!=0){
		return returnVal;
	}

	/* by this point the image has been assembled correctly and we can exit*/
	printf("ASSEMBLED\n");
	return EXIT_NO_ERRORS;
}
