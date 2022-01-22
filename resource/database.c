// Created by Farez

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

int databaseCreate(int table){
    int result = 0;
    if (table == 1) {
        result = sqlite3_exec(db, "CREATE TABLE inventory (id INTEGER PRIMARY KEY AUTOINCREMENT, item_name TEXT, price REAL, quantity INT);", NULL, NULL, &db_error);
    }
    else if (table == 2) {
        result = sqlite3_exec(db, "CREATE TABLE tables (id INTEGER PRIMARY KEY AUTOINCREMENT, resit_id INT, status INT);", NULL, NULL, &db_error);
    }
    else if (table == 3) {
        result = sqlite3_exec(db, "CREATE TABLE customer (resit_id INTEGER PRIMARY KEY AUTOINCREMENT, bill REAL, status INT);", NULL, NULL, &db_error);
    }
    else if (table == 4) {
        result = sqlite3_exec(db, "INSERT INTO customer VALUES (100000, NULL, 1)", NULL, NULL, &db_error);
    }
    if (result != SQLITE_OK) return 0;
    return 1;
}

// function for table ---------------------------------

int tablesRegister(int quantity){

    if (quantity > 10) return 0; // too many table
    else if (quantity <= 0) return 0; // invalid numbers

    for (int i = 0; i < quantity; ++i) {
        int result = sqlite3_exec(db, "INSERT INTO tables (resit_id, status) VALUES (NULL, 0);", NULL, NULL, &db_error);
        if (result != SQLITE_OK) return 0; // error adding table into database
    }
    return 1;
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
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0; // table not found
    table->id = sqlite3_column_int(stmt, 0);
    table->resit_id = sqlite3_column_int(stmt, 1);
    table->status = sqlite3_column_int(stmt, 2);

    return 1;
}

// function for inventory -----------------------------

int inventoryAddStock(char *item_name, double price, int quantity){
    char query[100];
    int result;

    sprintf(query,"INSERT INTO inventory (item_name, price, quantity) VALUES ('%s', %.2f, %d);", item_name, price, quantity);
    result = sqlite3_exec(db, query, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0; // error adding item into database

    return 1;
}

int inventorySetQuantity(short id, short quantity){
    char query[100];
    sprintf(query,"UPDATE inventory SET quantity = %d WHERE id = %d;", quantity, id);
    int result = sqlite3_exec(db,query, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0;
    return 1;
}

int inventorySetPrice(short id, short price){
    char query[100];
    sprintf(query,"UPDATE inventory SET price = %d WHERE id = %d;", price, id);
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
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0; // item not found
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
    if (result != SQLITE_OK) return 0; // error adding customer information into database

    stmt = NULL;

    char second_query[] = "SELECT seq FROM sqlite_sequence WHERE name='customer'"; // get the resit_id
    sqlite3_prepare_v2(db, second_query, -1, &stmt, 0);
    sqlite3_step(stmt);
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0; // somehow resit_id not found

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
    sprintf(query,"SELECT * FROM customer WHERE resit_id = %d;", resit_id);
    sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    sqlite3_step(stmt);
    if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) return 0;

    customer->resit_id = sqlite3_column_int(stmt, 0);
    customer->bill = sqlite3_column_int(stmt, 1);
    customer->status = sqlite3_column_int(stmt, 2);

    if (customer->status) return -1; // customer already made a payment.

    stmt = NULL;
    sprintf(query,"SELECT id FROM tables WHERE resit_id = %d;", resit_id);
    sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    sqlite3_step(stmt);

    customer->table = sqlite3_column_int(stmt, 0);

    return 1;
}

int customerPayment(resCustomer *customer){
    stmt = NULL;
    char query[100];
    sprintf(query,"UPDATE customer SET status = 0 WHERE resit_id = %d;", customer->resit_id);

    int result = sqlite3_exec(db, query, NULL, NULL, &db_error);
    if (result != SQLITE_OK) return 0; // error update customer in database

    customer->status = 0;

    int update_result = tablesUpdate(customer->table, customer->resit_id, 1);
    if (!update_result) return 0;

    customer->resit_id = sqlite3_column_int(stmt, 0);
    customer->bill = sqlite3_column_int(stmt, 1);
    customer->status = sqlite3_column_int(stmt, 2);
    return 1;
}