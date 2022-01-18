#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "file_checker.h"
#include "database.h"

#define DB_FILE "database\\database.sqlite"
#define DB_DIR "database"

void runSetup();

int main() {
    runSetup();
    sql_close();
    getch();
    return 0;
}

void runSetup(){
    int result;
    int table_count;
    int dir = createDirIfNotExist(DB_DIR);
    int file = createFileIfNotExist(DB_FILE);

    if (dir && file) {
        sql_open(DB_FILE); // open database
        return; // return to main as database exist
    } else if (!file && dir){
        printf(">> ERROR: file not found\n\n");
    }

    printf(">> Running setup wizard\n");
    sql_open(DB_FILE); // open database
    result  = databaseSetup();

    if (result == 0){
        printf(">> ERROR: Failed to create table in database, traceback: %s\n", databaseError());
        printf(">> exiting application.");
        exit(-1); // exit the application
    }
    printf(">> all table successfully created.\n");

    printf(">> inserting data into database\n");
    do {
        printf(">> table count in restaurant :");
        scanf("%d", &table_count);
        if (table_count > 10) printf(">> max table in restaurant is 10\n");
        else if (table_count <= 0) printf(">> invalid table quantity\n");

    } while (table_count > 10 || table_count <= 0);

    result = tablesRegister(table_count);
    char ignore;
    if (result != -1){
        printf(">> error occur, only %d table register into database.\n");
        printf("Ignore error (Y/n) :");
        scanf("%c", &ignore);
        if (!(ignore == 'Y' || ignore == 'y')){
            printf(">> deleting database to rerun setup wizard.\n");
            sql_close();
            if (remove(DB_FILE) != 0) {
                printf(">> database unable to remove.\n");
                printf(">> please delete it manually\n");
                printf(">> exiting application.");
                exit(-1); // exit the application
            } else printf(">> database file successfully removed\n");
            printf(">> rerun application to start setup wizard\n");
            exit(-1); // exit the application
        }
    } else {
        printf(">> all table successfully registered into database");
    }
}
