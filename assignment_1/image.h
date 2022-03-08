#ifndef IMAGE_STRUCT
#define IMAGE_STRUCT

struct Images
{ 
    char *commentLine;
    unsigned short *magic_Number;
    unsigned char magic_number[2];
	/* the logical width & height	         */
	/* note: cannot be negative	         */
	unsigned int width;
    unsigned int height;

	/* maximum gray value (assumed)	         */
	/* make it an integer for ease	         */
	unsigned int maxGray;

	/* pointer to raw image data	         */
	unsigned char *imageData;
	
	/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */
	FILE *inputFile;
};

#endif
