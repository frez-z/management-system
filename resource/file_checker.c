// Created by Farez

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "file_checker.h"

int createFileIfNotExist(char *fileName){
    FILE *fp;
    fp = fopen(fileName, "rb+"); // check if file exist
    fclose(fp); // close file stream

    if(fp == NULL) {
        fp = fopen(fileName, "wb"); // create new file
        fclose(fp); // close file stream again
        return 0;
    }
    return 1;
}

int createDirIfNotExist(char *directory){
    // return 1 if directory exist and 0 if not exist.
    return mkdir(directory);
}