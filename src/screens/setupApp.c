#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "file_checker.h"
#include "console.h"
#include "setupApp.h"
void configDatabase(void);

void setup(){
    createConsoleWindow(60, 20);
    system("cls"); // clear screen

    int databaseStatus[2];
    databaseStatus[0] = createDirIfNotExist(DB_DIR);
    databaseStatus[1] = createFileIfNotExist(DB_FILE);

    if (databaseStatus[0] && databaseStatus[1]) return; // return to main function
    printf("------------------ database setup process -------------------" BR BR); delay(500);

    if (!databaseStatus[1] && databaseStatus[0])
        printf(RED " error finding database, running setup process." RST BR);
    else
        printf(" initializing first run." BR);
    delay(500);

    sql_open(DB_FILE); // open database

    configDatabase();
    system("cls"); // clear command prompt

    printf("---------------- administrator setup process ----------------" BR BR); // setup table count

    int table_count;
    char input;
    printf(" table count in restaurant [1 - 9] :");
    do {
        input = (char)getch();
        table_count = input - '0';
    } while (table_count > 10 || table_count <= 0); // error handling. only accept input in range 1 - 9 only
    printf(" %d" BR, table_count);
    tablesRegister(table_count); // register table count in database.
    printf(BR GREEN " table count successfully saved in database" RST);
    delay(1500); system("cls");

    printf("---------------- administrator setup process ----------------" BR BR); // setup restaurant menu

    getch();
}

void configDatabase(void){
    printf(" confining database for restaurant.." BR);
    delay(400);

    databaseCreate(1); printf(" table" BLUE " 'inventory' " RST "created" BR);
    delay(400);

    databaseCreate(2); printf(" table" BLUE " 'tables' " RST "created" BR);
    delay(400);

    databaseCreate(3); printf(" table" BLUE " 'customer' " RST "created" BR);
    delay(400);

    databaseCreate(4); printf(" autoincrement resit_id setup at 100,000" BR);
    delay(400);

    printf(GREEN " successfully setup default table in database" RST BR BR);
    printf(" enter anything to continue."); getch();
}

void loadingBar(short x, short y){
    const short length = 80;
    moveCursor(x, y);
    for (int i = 0; i < length; ++i) printf("%c", (char)176);
    moveCursor(x,y);
    for (int i = 0; i <= length; ++i) {
        printf("%c", (char)219);
        moveCursor(x, y);
        printf("%d %%", (int)(i/90.0 * 100.0));
        moveCursor(x + 7, y);
        delay(50);
    }
    printf(RST "\n\n done hacking NASA");
}
