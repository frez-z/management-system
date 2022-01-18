//
// Created by Farez on 18/1/2022.
//

#include "sql/sqlite3.h"
#include "database.h"
#include <stdio.h>

sqlite3 *db;
sqlite3_stmt *stmt;
char *db_error; // global db error message

void sql_open(char *fileDir){
    sqlite3_open(fileDir, &db);
}

void sql_close(void){
    sqlite3_close(db);
}

char* databaseError(){
    return db_error;
}

int databaseSetup(void){
    int result;
    result = sqlite3_exec(db, "CREATE TABLE inventory (id INT PRIMARY KEY, item_name TEXT, price REAL, quantity INT);", NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0;
    printf(">> table 'inventory' created in database\n");

    result = sqlite3_exec(db, "CREATE TABLE tables (id INT PRIMARY KEY, resit_id INT, status INT);", NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0;
    printf(">> table 'tables' created in database\n");

    result = sqlite3_exec(db, "CREATE TABLE customer (resit_id INTEGER PRIMARY KEY AUTOINCREMENT, bill REAL, status INT);", NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0;
    printf(">> table 'customer' created in database\n");

    result = sqlite3_exec(db, "INSERT INTO customer VALUES (100000, NULL, 1)", NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0; // create useless row to start autoincrement from 10000 instead of 0
    printf(">> populated useless row to start autoincrement from 100000\n");

    return 1;
}

// function for table ---------------------------------

int tablesRegister(int quantity){
    char string[100];
    int result;
    for (int i = 1; i <= quantity; ++i) {

        sprintf(string,"INSERT INTO tables VALUES (%d, NULL, 0);", i);
        result =sqlite3_exec(db, string, NULL, NULL, &db_error);
        if (result != SQLITE_OK) return i; // error adding table into database

    }
    return -1;
}

int tablesUpdate(int table_id, int resit_id, int status){
    char string[100];
    int result;
    sprintf(string,"UPDATE tables SET resit_id = %d, status = %d WHERE id = %d;", resit_id, status, table_id);
    result = sqlite3_exec(db, string, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0; // error adding table into database

    return 1;
}

int tablesFetch(resTables* table,int table_id){
    stmt = NULL;
    char query[100];
    sprintf(query,"SELECT * FROM tables WHERE id = %d;", table_id);
    sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    sqlite3_step(stmt);
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0;
    table->id = sqlite3_column_int(stmt, 0);
    table->resit_id = sqlite3_column_int(stmt, 1);
    table->status = sqlite3_column_int(stmt, 2);

    return 1;
}

// function for inventory -----------------------------

int inventorAddyStock(const unsigned char *item_name, double price,unsigned int quantity){
    char query[100];
    int result;

    sprintf(query,"INSERT INTO inventory (item_name, price, quantity) VALUES ('%s', %.2f, %d);", *item_name, price, quantity);
    result = sqlite3_exec(db, query, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0; // error adding table into database

    return 1;
}

int inventorySetQuantity(short id, short quantity){
    char query[100];
    sprintf(query,"UPDATE inventory SET quantity = %d WHERE id = %d;", quantity, id);
    int result = sqlite3_exec(db,query, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0;
    return 1;
}

int inventorySetPrice(short id, short quantity){
    char query[100];
    sprintf(query,"UPDATE inventory SET price = %d WHERE id = %d;", quantity, id);
    int result = sqlite3_exec(db,query, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0;
    return 1;
}

int inventoryFetch(resInventory *item,int id){
    stmt = NULL;
    char query[100];
    sprintf(query,"SELECT * FROM inventory WHERE id = %d;", id);
    sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    sqlite3_step(stmt);
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0;
    item->id = sqlite3_column_int(stmt, 0);
    item->item_name = sqlite3_column_text(stmt, 1);
    item->price = sqlite3_column_double(stmt, 2);
    item->quantity = sqlite3_column_int(stmt, 3);

    return 1;
}

// function for customer ------------------------------

int customerGenerateBill(resCustomer *customer,double price, int table_id){
    char query[100];
    int result;

    sprintf(query,"INSERT INTO customer (bill, status) VALUES (%.2f, 0);", price);
    result = sqlite3_exec(db, query, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0; // error adding table into database

    stmt = NULL;

    char second_query[] = "SELECT seq from sqlite_sequence where name=customer";
    sqlite3_prepare_v2(db, second_query, -1, &stmt, 0);
    sqlite3_step(stmt);
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0;

    int resit_id = sqlite3_column_int(stmt, 0);

    int update_result = tablesUpdate(table_id, resit_id, 1);
    if (!update_result) return 0;

    customer->resit_id = resit_id;
    customer->bill = price;
    customer->status = 0;
    customer->table = table_id;

    return 1;
}

int customerInfo(resCustomer *customer, int resit_id){
    stmt = NULL;
    char query[100];
    sprintf(query,"SELECT * FROM customer WHERE id = %d;", resit_id);
    sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    sqlite3_step(stmt);
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0;

    customer->resit_id = sqlite3_column_int(stmt, 0);
    customer->bill = sqlite3_column_int(stmt, 1);
    customer->status = sqlite3_column_int(stmt, 2);

    stmt = NULL;
    sprintf(query,"SELECT id FROM tables WHERE resit_id = %d;", resit_id);
    sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    sqlite3_step(stmt);
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return -1;

    customer->table = sqlite3_column_int(stmt, 0);

    return 1;
}

int customerPayment(resCustomer *customer){
    stmt = NULL;
    char query[100];
    sprintf(query,"UPDATE customer SET status = 0 WHERE id = %d;", customer->resit_id);

    int result = sqlite3_exec(db, query, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0; // error update table in database

    customer->status = 0;

    sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    sqlite3_step(stmt);
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0;

    customer->resit_id = sqlite3_column_int(stmt, 0);
    customer->bill = sqlite3_column_int(stmt, 1);
    customer->status = sqlite3_column_int(stmt, 2);
    return 1;
}