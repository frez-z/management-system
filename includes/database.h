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
 * argument:-
 * 1 = inventory, 2 = tables
 * 3 = customer, 4 = useless data
 *
 * return value:-
 * 1 = success
 * 0 = fail
 */
int databaseCreate(int table);

/*
 * add tables information into database
 *
 * return value:-
 * 1 = success
 * 0 = fail
 */
int tablesRegister(int quantity);

/*
 * update tables information
 * argument:-
 * table_id = table number, resit_id = customer resit number
 * status: 1 = unavailable, 0 = available
 *
 * return value:-
 * 1 = success
 * 0 = fail
 */
int tablesUpdate(int table_id, int resit_id, int status);

/*
 * fetch information from the selected table
 *
 * return value:-
 * 1 = found
 * 0 = not found
 */
int tablesFetch(resTables* table,int table_id);

/*
 * add new inventory into restaurant
 * Note!! to update quantity used inventorySetQuantity() instead
 *
 * return value:-
 * 1 = success
 * 0 = fail
 */
int inventoryAddStock(char *item_name, double price,int quantity);

/*
 * update inventory quantity as customer buy or the administrator restock the inventory
 *
 * return value:-
 * 1 = success
 * 0 = fail
 */
int inventorySetQuantity(short id, short quantity);

/*
 * update inventory price ( admin function interface )
 *
 * return value:-
 * 1 = success
 * 0 = fail
 */
int inventorySetPrice(short id, short price);

/*
 * fetch information of selected inventory
 * if inventory not found. the function return 0
 *
 * return value:-
 * 1 = found
 * 0 = not found
 */
int inventoryFetch(resInventory *item,int id);

/*
 * generate resit then save it into database
 *
 * return value:-
 * 1 = success
 * 0 = fail
 */
int customerGenerateBill(resCustomer *customer,double price, int table_id);

/*
 * fetch customer information from database
 *
 * return value:-
 * 1 = success
 * 0 = fail
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
