#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int createFileIfNotExist(char *fileName){
    // return 1 if file exist and 0 if not exist.

    if(fopen(fileName, "rb+") == NULL) {
        fopen(fileName, "wb"); // create file if not exist yet.
        return 0;
    }
    return 1;
}

int createDirIfNotExist(char *directory){
    // return 1 if directory exist and 0 if not exist.
    return mkdir(directory);
}