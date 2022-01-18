//
// Created by Farez on 18/1/2022.
//

#ifndef MANAGEMENT_SYSTEM_DATABASE_H
#define MANAGEMENT_SYSTEM_DATABASE_H

#include "sql/sqlite3.h"

/* hold table information */
typedef struct resTables {
    unsigned int id;
    unsigned short status; // 0 = unavailable, 1 = available
    unsigned int resit_id; // customer resit id
} resTables;

/* hold food or drink information */
typedef struct resInventory {
    unsigned int id; // unique id
    const unsigned char *item_name;
    double price;
    unsigned int quantity;
} resInventory;

/* hold customer information */
typedef struct resCustomer {
    unsigned int resit_id; // unique id
    int table;
    double bill;
    int status;
} resCustomer;

/* open a new connection to database */
void sql_open(char* fileDir);

/* close the connection to database */
void sql_close(void);

/* fetch database error */
char* databaseError(void);

/*
 * create new database for restaurant
 * table created: 'items', 'tables' and 'customer'
 *
 * return value:
 *       1 = execution success
 *       0 = execution fail
 */
int databaseSetup(void);

/*
 * populated table 'tables' with default value data
 *
 * return value:
 *       0 : execution success
 *       return value >= 0 : rows of data successfully added into database
 */
int tablesRegister(int quantity);

/*
 * update 'tables' data
 *
 * return value:
 *       1 : execution success
 *       0 : execution fail
 */
int tablesUpdate(int table_id, int resit_id, int status);

/*
 * fetch information of selected table id
 *
 * return value:
 *       1 : table found
 *       0 : table not found
 */
int tablesFetch(resTables* table,int table_id);

/*
 * add new inventory into restaurant
 * Note!! to update quantity used inventorySetQuantity() instead
 *
 * return value:
 *       1 : execution success
 *       0 : execution fail
 */
int inventorAddyStock(const unsigned char *item_name, double price,unsigned int quantity);

/*
 * update inventory quantity as customer buy or the administrator restock the inventory
 *
 * return value:
 *       1 : execution success
 *       0 : execution fail
 */
int inventorySetQuantity(short id, short quantity);

/*
 * update inventory price ( admin function interface )
 *
 * return value:
 *       1 : execution success
 *       0 : execution fail
 */
int inventorySetPrice(short id, short quantity);

/*
 * fetch information of selected inventory
 * if inventory not found. the function return 0
 *
 * return value:
 *       1 : inventory found
 *       0 : inventory not found
 */
int inventoryFetch(resInventory *item,int id);

/*
 * add customer into database
 *
 * return value:
 *       1 : execution success
 *       0 : execution fail
 */
int customerGenerateBill(resCustomer *customer,double price, int table_id);

/*
 * fetch customer information from database
 *
 * return value:
 *       1 : execution success
 *       0 : execution fail
 */
int customerInfo(resCustomer *customer, int resit_id);

/*
 * fetch customer information from database
 *
 * return value:
 *       1 : the customer not pay the bill yet, table id available
 *       0 : resit id not in database
 *      -1 : the customer have paid the bill, table id is null
 */
int customerPayment(resCustomer *customer);

#endif //MANAGEMENT_SYSTEM_DATABASE_H
