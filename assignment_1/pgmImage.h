#ifndef _PGMIMAGE_H_
#define _PGMIMAGE_H_

typedef struct Image{
    int height;
    int width;
    int maxGray;
    char *commentLine;
    FILE *fileStream;
    char *fileName;
    unsigned char **imageData;
    unsigned short *magic_Number;
    unsigned char magic_number[2];
}image;


// int writeData(image *ptr_img2,long nImageBytes);
// int readData(image *ptr_img1,long nImageBytes);
int readInFile(image *ptr_img, int intendedFormat);
int writeToFile(image *ptr_img, char *fileName, int nImageBytes);
int initialiseImage(image *ptr_img,char *fileName);

#endif