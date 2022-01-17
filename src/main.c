#include <stdio.h>
#include <conio.h>
#include "file_checker.h"
#include "database.h"

#define DB_FILE "database\\database.sqlite"
#define DB_DIR "database"

void runSetup(int, int);

int main() {
    int run[2];
    run[0] = createDirIfNotExist(DB_DIR);
    run[1] = createFileIfNotExist(DB_FILE);
    runSetup(run[0], run[1]);
    sql_open(DB_FILE);
    int result  = databaseSetup();
    if (!result) printf("%s", databaseError());
    sql_close();
    getch();
    return 0;
}

void runSetup(int dir, int file){
    if (dir && file) return; // exit setup as both directory and file exist.

    else if (!file && dir) {
        printf("file not found, executed rerun setup..\n");
    } else {
        printf("running setup for database\n");
    }
    printf("database has setup\n");
}
