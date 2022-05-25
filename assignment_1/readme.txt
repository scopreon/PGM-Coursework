README

Task: assignment_1
Author: Saul Cooperman
StudentID: 201492462

pgmEcho
    Copies a file from one location to another
    Usage: ./pgmEcho inputImage.pgm outputImage.pgm
pgmComp
    Compares two files
    Usage: ./pgmComp inputImage.pgm inputImage.pgm
pgma2b
    Converts ascii image to binary
    Usage: ./pgma2b inputImage.pgm outputImage.pgm
pgmb2a
    Converts binary image to ascii
    Usage: ./pgmb2a inputImage.pgm outputImage.pgm
pgmReduce
    Reduces image by a factor
    Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm
pgmTile
    Tiles an image into nxn tiles
    Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm
pgmAssemble
    Assembles a larger image from smaller images
    Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+