#include <stdio.h>

int magicNumberCheck(unsigned short magic_Number, int MAGIC_NUMBER_ASCII_PGM){
    if (magic_Number != MAGIC_NUMBER_ASCII_PGM)
		{ /* failed magic number check   */
		/* be tidy: close the file       */

		/* print an error message */
		// printf("Error: Failed to read pgm image from file");	
		
		/* and return                    */
		return 1;
		} /* failed magic number check   */
    else{
        return 0;
    }
	
}

int * commentLine(){

}

int sizeCheck(){

}

int imageAllocationCheck(){

}

int grayValueCheck(){

}

