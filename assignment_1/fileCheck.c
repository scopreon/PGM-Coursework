#include <stdio.h>
#include <stdlib.h>
#include "fileCheck.h"
int magicNumberCheck(FILE *inputFile,unsigned short magic_Number, int MAGIC_NUMBER_ASCII_PGM, char *arg1){
    if (magic_Number != MAGIC_NUMBER_ASCII_PGM)
		{ /* failed magic number check   */
		/* be tidy: close the file       */
        fclose(inputFile);
		/* print an error message */
		printf("Magic number %s\n", arg1);
		/* and return                    */
		return 1;
		} /* failed magic number check   */
    else{
        return 0;
    }
	
}

int getCommentLine(int MAX_COMMENT_LINE_LENGTH,char *commentLine,FILE *inputFile, char *arg1){
    char nextChar = fgetc(inputFile);
    if (nextChar == '#')
		{ /* comment line                */
		/* allocate buffer               */
		commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);
		/* NULL means failure            */
		if (commentString == NULL)
			{ /* NULL comment read   */
			/* free memory           */
			free(commentLine);
			/* close file            */
			fclose(inputFile);

			/* print an error message */
			printf("Comment %s\n", arg1);	
		
			/* and return            */
			return 1;
			} /* NULL comment read   */
        else{
            return 0;
        }
	} /* comment line */
    else{
        
        return 0;
    }
}



// int sizeCheck(){

// }

// int imageAllocationCheck(){

// }

// int grayValueCheck(){

// }

