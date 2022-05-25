README

Task: assignment_2
Author: Saul Cooperman
StudentID: 201492462

gtopoEcho
    Copies a file from one location to another
    Usage: ./gtopoEcho inputFile width height outputFile
gtopoComp
    Compares two files
    Usage: ./gtopoComp firstFile width height secondFile
gtopoReduce
    Reduces image by a factor
    Usage: ./gtopoReduce input width height reduction_factor output
gtopoTile
    Tiles an image into nxn tiles
    Usage: ./gtopoTile inputFile width height tiling_factor outputFile_<row>_<column>
gtopoAssemble
    Assembles a larger image from smaller images
    Usage: ./gtopoAssemble outputFile width height (row column inputFile width height)+
gtopoAssembleReduce
    Assembles an image then reduces by a factor
    Usage: ./gtopoAssembleReduce outputArray.gtopo width height (row column inputArray.gtopo width height)+
gtopoPrintLand.c
    Prints .dem file as an ascii image
    Usage: ./gtopoPrintLand inputFile width height outputFile sea hill mountain