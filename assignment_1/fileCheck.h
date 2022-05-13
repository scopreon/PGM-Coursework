#ifndef _FILECHECK_H_
#define _FILECHECK_H_
#include "pgmImage.h"

/* ERROR codes to exit with */
#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_FILE_NAME 2
#define EXIT_BAD_MAGIC_NUMBER 3
#define EXIT_BAD_COMMENT_LINE 4
#define EXIT_BAD_DIMENSIONS 5
#define EXIT_BAD_MAX_GRAY 6
#define EXIT_BAD_MALLOC 7
#define EXIT_BAD_INPUT 8
#define EXIT_BAD_OUTPUT 9
#define EXIT_BAD_LAYOUT 10
#define EXIT_MISC 100

/* constants regarding image data */
#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

/* functions: */
/* validates magic number for image */
int magicNumberCheck(image *ptr_img1,int magicNumberVerify);
/* validates length of comment line (if applicable) */
int getCommentLine(image *ptr_img1);
/* check dimensions of image, width/height */
int sizeCheck(image *ptr_img1,int scanCount);
/* checks max gray value of image */
int grayCheck(image *ptr_img);

#endif