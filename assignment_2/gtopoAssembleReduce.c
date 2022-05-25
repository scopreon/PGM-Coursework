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
#include "gtopoImage.h"


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
		printf("Usage: %s outputFile width height (row column inputFile widthheight)+ \n", argv[0]);
		/* return according error code */
		return EXIT_NO_ERRORS;
	}

	/* checking for correct number of arguments */
	if ((argc)%5 != 0)	
	{
		/* print error message if wrong number of arguments */
		printf("ERROR: Bad Argument Count\n");
		/* return according error code */
		return EXIT_WRONG_ARG_COUNT;
	} 
	
	/* ensure width is an integer */
	if(!isNumber(argv[2]) || !isNumber(argv[3]) || !isNumber(argv[4])){
		printf("ERROR: Miscellaneous (non-numeric command line arguments)\n");
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

	/* allocating memory for storing image data in 2D format*/
	ptr_img1->imageData = malloc(ptr_img1->height * sizeof(*ptr_img1->imageData));
	for(int mallocRow=0; mallocRow<ptr_img1->height; mallocRow++){
		ptr_img1->imageData[mallocRow]=malloc(ptr_img1->width * sizeof(short int));
	}

	/* creating image 2 which stores images incrementally read in */
	image *ptr_img2 = malloc(sizeof(image));
	/* initialising image 1 with basic data */
	if(initialiseImage(ptr_img2,argv[1])){
		return EXIT_BAD_MALLOC;
	};

	/* looping through command line arguments in triplets */
	for(int argumentIndex = 5; argumentIndex<argc-2; argumentIndex+=5){	
		/* the third argument in each triplet is the filename to read in */
		ptr_img2->fileName=argv[argumentIndex+2];

		/* making sure coordinates (x,y) to put the image are integers */
		if(!isNumber(argv[argumentIndex]) || !isNumber(argv[argumentIndex+1]) || !isNumber(argv[argumentIndex+3]) || !isNumber(argv[argumentIndex+4])){
			printf("ERROR: Miscellaneous (non-integer values)\n");
            printf("%s %s %s %s",argv[argumentIndex],argv[argumentIndex+1],argv[argumentIndex+3],argv[argumentIndex+4]);
			return EXIT_MISC;
		}
		ptr_img2->width=atoi(argv[argumentIndex+3]);
		ptr_img2->height=atoi(argv[argumentIndex+4]);
		/* read in each file to assemble */
		if((returnVal = readInFile(ptr_img2))!=0){
			return returnVal;
		}
		
		/* loop through file data and add it to first image blank canvas image data */
		for(int loopRow = 0; loopRow < ptr_img2->height; loopRow++){
			for(int loopCol = 0; loopCol < ptr_img2->width; loopCol++){
				/* move data from image two to image one*/
				ptr_img1->imageData[atoi(argv[argumentIndex])+loopRow][atoi(argv[argumentIndex+1])+loopCol]=ptr_img2->imageData[loopRow][loopCol];
			}
		}

		/* set the magic number of read in file to final assembled image magic number */
	}
	
	/* final assembled image is written to image */


    image *ptr_img3 = malloc(sizeof(image));
	/* initialising image 2 */
	if(initialiseImage(ptr_img3,argv[1])){
		return EXIT_BAD_MALLOC;
	}
    int size = atoi(argv[4]);
	/* heights and widths created fo image 2 */
	ptr_img3->width=(int)((float)ptr_img1->width+size-1)/size;
	ptr_img3->height=(int)((float)ptr_img1->height+size-1)/size;

	/* malloc data for output file */
	ptr_img3->imageData = malloc(ptr_img3->height * sizeof(*ptr_img3->imageData));
	for(int rowMalloc = 0; rowMalloc < ptr_img3->height; rowMalloc++){
		ptr_img3->imageData[rowMalloc]=malloc(ptr_img3->width * sizeof(short int));
	}

	/* loop through data selecting every size'th value */
	for(int loopRow = 0; loopRow < ptr_img3->height; loopRow++){
		for(int loopCol = 0; loopCol < ptr_img3->width;loopCol++){
			/* move data from first pgm to second pgm */
			ptr_img3->imageData[loopRow][loopCol]=ptr_img1->imageData[loopRow*size][loopCol*size];
		}
	}

	/* write image 2 data to file, contains reduced image 1 */
	returnVal=writeToFile(ptr_img3);
    if(returnVal!=0){
		return returnVal;
	}
    printf("width: %d\n", ptr_img3->width);
    printf("height: %d\n", ptr_img3->height);
	/* by this point the image has been assembled correctly and we can exit*/
	printf("ASSEMBLED\n");
	return EXIT_NO_ERRORS;
}
