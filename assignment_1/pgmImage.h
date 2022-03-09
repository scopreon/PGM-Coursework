#ifndef _PGMIMAGE_H_
#define _PGMIMAGE_H_

typedef struct Image{
    int height;
    int width;
    int maxGray;
    char *commentLine;
    FILE *inputFile;
    FILE *outputFile;
    char *fileName;
    unsigned char *imageData;
    unsigned short *magic_Number;
}image;


int writeData(image *ptr_img2,long nImageBytes);
int readData(image *ptr_img1,long nImageBytes);

#endif