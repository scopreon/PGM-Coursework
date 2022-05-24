/* library for I/O routines */
#include <stdio.h>
/* library for checking variable types */
#include <ctype.h>
/* library for memory routines */
#include <stdlib.h>
/* library for string routines */
#include <string.h>
/* methods for checking file information is valid */
#include "fileCheck.h"
/* contains reading and writing functions */
#include "pgmImage.h"

/***********************************/
/* stringExists function           */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: string to check        */
/* argv[1]: substring to find      */
/* returns the index of the string */
/* -1 on not found                 */
/***********************************/

int stringExists(char *string, char *stringToFind){
	/* loop through string */	
	for(int i = 0; i < strlen(string); i++){
		int counter=strlen(stringToFind);
		
		/* loop through next few characters to see if match */		
		for(int j = 0; j < strlen(stringToFind); j++){
			/* if string matches decrement counter */
			if(stringToFind[j]==string[i+j]){
				counter-=1;
			}
		}
		if(counter==0){
			return i;
		}
	}
	/* return -1 if not found */
	return -1;
}

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: tiling factor          */
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
		printf("Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm\n", argv[0]);
		/* return according error code */
		return EXIT_NO_ERRORS;
	}

	/* checking for correct number of arguments */
	if (argc != 4)	
	{
		/* print error message if wrong number of arguments */
		printf("ERROR: Bad Argument Count\n");
		/* return according error code */
		return EXIT_WRONG_ARG_COUNT;
	} 
	/*getting factor size from ascii to int*/
    
	if(!isNumber(argv[2])){
		printf("ERROR: Miscellaneous (invalid scaling factor)\n");
		return EXIT_MISC;
	}
	
	/* for storing the required string at end of */

	int positionRow=stringExists(argv[3],"<row>");
	int positionCol=stringExists(argv[3],"<column>");

	if(positionRow==-1||positionCol==-1){
		printf("ERROR: Miscellaneous (incorrect format)\n");
	 	return EXIT_MISC;
	}
	
	//char *fileName = malloc(64*sizeof(char));
	
    int size = atoi(argv[2]);
	image *ptr_img1 = malloc(sizeof(image));
	/*initialising image 1*/
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}
	
	/*read in first file*/
	int returnVal;
	if((returnVal = readInFile(ptr_img1,0))!=0){
		return returnVal;
	}
	
	image *ptr_img2 = malloc(sizeof(image));
	/*initialising image 2*/
	if(initialiseImage(ptr_img2,argv[3])){
		return EXIT_BAD_MALLOC;
	}
	/* setting information on second image to be the same as first */
	ptr_img2->width=ptr_img1->width/size;
	ptr_img2->height=ptr_img1->height/size;
	ptr_img2->maxGray=ptr_img1->maxGray;
	ptr_img2->magic_Number=ptr_img1->magic_Number;
	
	/* dynamically allocating image data for second image */
	ptr_img2->imageData = malloc(ptr_img2->height * sizeof(*ptr_img2->imageData));
	for(int rowMalloc=0; rowMalloc<ptr_img2->height; rowMalloc++){
		ptr_img2->imageData[rowMalloc]=malloc(ptr_img2->width * sizeof(unsigned char));
	}
	
	/* loop through tiles, _0_0 ... _x_y */
	for(int x=0;x<size;x++){
    	for(int y=0;y<size;y++){
			/* loop through pixels of tile and set each one */
			for(int loopRow=0; loopRow<ptr_img2->height; loopRow++){
				for(int loopCol=0; loopCol<ptr_img2->width; loopCol++){
					/* take data for each tile being created */
					ptr_img2->imageData[loopRow][loopCol]=ptr_img1->imageData[loopRow+ptr_img2->height*x][loopCol+ptr_img2->width*y];
				}
			}
			
			/* name will store formatted name of tile filename */
			//exit(0);
            char *name=(char *) malloc(strlen(argv[3])*sizeof(char));
			name[0]='\0';
			
			/* add characters/numbers to name */
			for(int i = 0; i < strlen(argv[3]); i++){
				if(i==positionRow){
					i+=4;
					sprintf(name,"%s%d",name,x);
				}
				else if(i==positionCol){
					i+=7;
					sprintf(name,"%s%d",name,y);
				}
				else{
					sprintf(name,"%s%c",name,argv[3][i]);
				}
			}

			/* assign filename to new tile and write */
            ptr_img2->fileName=name;
	        returnVal=writeToFile(ptr_img2);
            if(returnVal!=0){
		        return returnVal;
	        }
		}
	}

	/* at this point, we are done and can exit with a success code */
	printf("TILED\n");
	return EXIT_NO_ERRORS;
}
