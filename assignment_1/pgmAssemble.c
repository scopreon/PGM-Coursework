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
	
	 /* wrong arg count */
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
	int returnVal;
	image *ptr_img1 = malloc(sizeof(image));
	/*initialising image 1*/
	if(initialiseImage(ptr_img1,argv[1])){
		return EXIT_BAD_MALLOC;
	}
	/*read in first file*/
	ptr_img1->width=atoi(argv[2]);
	ptr_img1->height=atoi(argv[3]);
	ptr_img1->maxGray=255;
	long nImageBytes = ptr_img1->width * sizeof(unsigned char);
	ptr_img1->imageData = malloc(ptr_img1->height * sizeof(*ptr_img1->imageData));
	if (ptr_img1->imageData == NULL)
		{
		printf("ERROR: Image Malloc Failed\n");
		return EXIT_BAD_MALLOC;
	}
	for(int i=0;i<ptr_img1->height ;i++)
	{
		ptr_img1->imageData[i]=malloc(nImageBytes);
		if (ptr_img1->imageData[i] == NULL)
		{
			printf("ERROR: Image Malloc Failed\n");
			return EXIT_BAD_MALLOC;
		}
	}
	// if((returnVal = readInFile(ptr_img1,0))!=0){
	// 	return returnVal;
	// }

	image *ptr_img2 = malloc(sizeof(image));
	/*initialising image 2*/
	if(initialiseImage(ptr_img2,argv[3])){
		return EXIT_BAD_MALLOC;
	};
	for(int i  = 0; i < argc;i++){
		
	}
	for(int i = 4;i<argc-2;i+=3){
		// printf("%s\n",argv[i+2]);
		
		ptr_img2->fileName=argv[i+2];
		for(int x = 0; argv[i][x]!='\0';x++){
			if(!isdigit(argv[i][x])){
				printf("ERROR: Miscellaneous (invalid scaling factor)\n");
				return 100;
			}
		}
		for(int x = 0; argv[i+1][x]!='\0';x++){
			if(!isdigit(argv[i+1][x])){
				printf("ERROR: Miscellaneous (invalid scaling factor)\n");
				return 100;
			}
		}
		if((returnVal = readInFile(ptr_img2,0))!=0){
			return returnVal;
		}
		
		for(int h = 0;h < ptr_img2->height;h++){
			for(int w = 0;w < ptr_img2->width;w++){
				//printf("%d %d %d %d\n",atoi(argv[i+1])+w,w,atoi(argv[i])+h,h);
				ptr_img1->imageData[atoi(argv[i])+h][atoi(argv[i+1])+w]=ptr_img2->imageData[h][w];
			}
		}
		ptr_img1->magic_Number=ptr_img2->magic_Number;
		
	}
	// for(int h = 0;h < ptr_img1->height;h++){
	// 	for(int w = 0;w < ptr_img1->width;w++){
	// 		printf("%d %d %d\n",ptr_img1->imageData[h][w],h,w);
	// 	}
	// }
	returnVal=writeToFile(ptr_img1, ptr_img1->fileName,nImageBytes);
    if(returnVal!=0){
		return returnVal;
	}
	
	
	// ptr_img2->magic_Number=ptr_img1->magic_Number;
	

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
	printf("ASSEMBLED\n");
	return EXIT_NO_ERRORS;
	} /* main() */
