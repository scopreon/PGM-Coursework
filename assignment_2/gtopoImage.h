#ifndef _GTOPOIMAGE_H_
#define _GTOPOIMAGE_H_

/* structure to store all information on an image */
typedef struct Image{
    int height;
    int width;
    FILE *fileStream;
    char *fileName;
    short int **imageData;
}image;

/* functions: */
/* handles reading in file */
int readInFile(image *ptr_img);
/* handles writing to file */
int writeToFile(image *ptr_img);
/* initialising image data with basic information (NULL) */
int initialiseImage(image *ptr_img,char *fileName);
/* checking if a string is actually a positive integer */
int isNumber(char *text);

#endif