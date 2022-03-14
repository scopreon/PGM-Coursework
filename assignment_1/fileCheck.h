#ifndef _FILECHECK_H_
#define _FILECHECK_H_
#include "pgmImage.h"
int magicNumberCheck(image *ptr_img1);
int getCommentLine(image *ptr_img1);
int sizeCheck(image *ptr_img1,int scanCount);

#endif