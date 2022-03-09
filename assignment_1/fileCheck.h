#ifndef _FILECHECK_H_
#define _FILECHECK_H_
#include "pgmImage.h"
int magicNumberCheck(image *ptr_img1, int MAGIC_NUMBER_ASCII_PGM);
int getCommentLine(image *ptr_img1, int MAX_COMMENT_LINE_LENGTH);
int sizeCheck(image *ptr_img1,int scanCount,int MIN_IMAGE_DIMENSION, int MAX_IMAGE_DIMENSION);

#endif