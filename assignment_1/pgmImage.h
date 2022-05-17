#ifndef _PGMIMAGE_H_
#define _PGMIMAGE_H_

/* structure to store all information on an image */
typedef struct Image{
    int height;
    int width;
    int maxGray;
    FILE *fileStream;
    char *fileName;
    unsigned char **imageData;
    unsigned short *magic_Number;
    unsigned char magic_number[2];
}image;


/* functions: */
/* handles reading in file */
int readInFile(image *ptr_img, int intendedFormat);
/* handles writing to file */
int writeToFile(image *ptr_img);
/* initialising image data with basic information (NULL) */
int initialiseImage(image *ptr_img,char *fileName);
/* checking if a string is actually a positive integer */
int isNumber(char *text);

#endif