/* library for I/O routines        */
#include <stdio.h>
#include <ctype.h>
/* library for memory routines     */
#include <stdlib.h>
#include "fileCheck.h"
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
		printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+\n", argv[0]);
		/* and return an error code      */
		return EXIT_NO_ERRORS;
	}
	if ((argc-1)%3 != 0)	
		{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count\n");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */
	/*getting factor size from ascii to int*/
	for(int i = 0; argv[2][i]!='\0';i++){
		if(!isdigit(argv[2][i])){
			printf("ERROR: Miscellaneous (invalid scaling factor)\n");
			return 100;
		}
	}
	for(int i = 0; argv[3][i]!='\0';i++){
		if(!isdigit(argv[3][i])){
			printf("ERROR: Miscellaneous (invalid scaling factor)\n");
			return 100;
		}
	}
	// if(!isdigit(argv[2])){
	// 	printf("ERROR: Miscellaneous (non-numeric scaling factor)\n");
	// 	return 100;
	// }
	image *ptr_img1 = malloc(sizeof(image));
	/*initialising image 1*/
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}
	/*read in first file*/
	int returnVal;
	ptr_img1->width=atoi(argv[2]);
	ptr_img1->height=atoi(argv[3]);


	// if((returnVal = readInFile(ptr_img1,0))!=0){
	// 	return returnVal;
	// }

	long nImageBytes = ptr_img1->width * ptr_img1->height * sizeof(unsigned char);
	image *ptr_img2 = malloc(sizeof(image));
	/*initialising image 2*/
	if(initialiseImage(ptr_img2,argv[3])){
		return EXIT_BAD_MALLOC;
	}
	ptr_img2->maxGray=ptr_img1->maxGray;
	ptr_img2->imageData=ptr_img1->imageData;
	ptr_img2->magic_Number=ptr_img1->magic_Number;
	

	// /*new heights and widths created*/
	// ptr_img2->width=(int)((float)ptr_img1->width+size-1)/size;
	// ptr_img2->height=(int)((float)ptr_img1->height+size-1)/size;
	// for(int i = 0; i < ptr_img1->height;i++){
	// 	for(int j = 0; j < ptr_img1->width;j++){
	// 		if(i%size==0 && j%size==0){
	// 			ptr_img2->imageData[i/size][j/size]=ptr_img2->imageData[i][j];
	// 		}
	// 	}
	// }

	// // int column=0;
	// // int row=0;
	// // /*pointer to new image data*/
	// // unsigned char *pointerImg2 = ptr_img2->imageData;
	// // for (unsigned char *nextGrayValue = ptr_img1->imageData; nextGrayValue < ptr_img1->imageData + nImageBytes; nextGrayValue++){
	// // 	/*include this data if condition is met*/
	// // 	if(column%size==0 && row%size==0){
	// // 		*pointerImg2=*nextGrayValue;
	// // 		pointerImg2++;
	// // 	}
		
	// // 	column++;
	// // 	if(column%(ptr_img1->width) == 0){
	// // 		row++;
	// // 	}
	// // }
	// nImageBytes = ptr_img2->width * sizeof(unsigned char);
	// returnVal=writeToFile(ptr_img2, argv[3],nImageBytes);
  //   if(returnVal!=0){
	// 	return returnVal;
	// }

	// /* at this point, we are done and can exit with a success code */
	printf("REDUCED\n");
	return EXIT_NO_ERRORS;
	} /* main() */
