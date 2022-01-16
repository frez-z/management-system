#include <stdio.h>
#include <conio.h>
#include "handler/file.h"
#include "handler/colour.h"
#include "handler/database.h"

#define DB_FILE "database\\database.sqlite"
#define DB_DIR "database"

void runSetup(short, short);

int main() {
    short run[2];
    run[0] = createDirIfNotExist(DB_DIR);
    run[1] = createFileIfNotExist(DB_FILE);
    runSetup(run[0], run[1]);

    getch();
    return 0;
}

void runSetup(short dir, short file){
    if (dir && file) return; // exit setup as both directory and file exist.

    else if (!file && dir) {
        printf("file not found, executed rerun setup..\n");
    } else {
        printf("running setup for database\n");
    }
    printf("database has setup\n");
}
