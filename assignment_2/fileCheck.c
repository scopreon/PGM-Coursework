/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>
/* methods for checking file information is valid */
#include "fileCheck.h"
/* contains reading and writing functions */
#include "gtopoImage.h"

/***********************************/
/* freeMemory function      	   */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: pointer to image struct*/
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int freeMemory(image *ptr_img){
	/* free filename if it has been allocated */
	if(ptr_img->fileName != NULL){
		free(ptr_img->fileName);
	}
	/* close filestream if it has been allocated */
	if(ptr_img->fileStream != NULL){
		fclose(ptr_img->fileStream);
	}
	return 0;
}

int sizeCheck(image *ptr_img){
	/* check if scancount is 2 (read in both width and height) */
	/* check he width and height read in is in a valid range */
    if 	((ptr_img->width < MIN_IMAGE_DIMENSION	) 	||
		(ptr_img->width >= MAX_IMAGE_DIMENSION	) 	||
		(ptr_img->height < MIN_IMAGE_DIMENSION	) 	||
		(ptr_img->height >= MAX_IMAGE_DIMENSION	)){
		/* free everything up if width/height aren't valid */
		
		printf("ERROR: Bad Dimensions (%s)\n", ptr_img->fileName);	
		freeMemory(ptr_img);
		return 1;
	}
    else{
		/* if everything is valid return 0 */
        return 0;
    }
}