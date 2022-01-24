// Created by Farez

#include <conio.h>
#include <stdlib.h>

#include "resource/database.h"
#include "resource/file_checker.h"
#include "resource/test.h"

#define DB_FILE "test_database\\test_database.sqlite"
#define DB_DIR "test_database"

void runSetup();

int main() {
    system("cls");
    // testing creation file
    test_int(createDirIfNotExist(DB_DIR), 0, "CreateDirectory");


    test_int(createFileIfNotExist(DB_FILE), 0, "CreateFile");

    // testing file exist
    test_int(createDirIfNotExist(DB_DIR), -1, "ExistDirectory");
    test_int(createFileIfNotExist(DB_FILE), 1, "ExistFile");

    sql_open(DB_FILE);

    // testing table creation
    test_int(databaseCreate(1), 1, "NewTable-inventory");
    test_int(databaseCreate(2), 1, "NewTable-tables");
    test_int(databaseCreate(3), 1, "NewTable-customer");

    // testing useless data populate
    test_int(databaseCreate(4), 1, "Populate-useless");

    // testing user input for registering table.
    test_int(tablesRegister(-10), 0, "InputTable-negative");
    test_int(tablesRegister(0), 0, "InputTable-0");
    test_int(tablesRegister(20), 0, "InputTable-moreThan10");
    test_int(tablesRegister(5), 1, "InputTable-valid");

    // testing fetching tables
    resTables table1, table2;
    test_int(tablesFetch(&table1, 1), 1, "FetchTable-exist");
    test_int(tablesFetch(&table2, 7), 0, "FetchTable-nonExist");

    // testing adding inventory
    test_int(inventoryAddStock("nasi lemak", 2.50, 10), 1, "InventoryAdd1");
    test_int(inventoryAddStock("watermelon", 1.50, 5), 1, "InventoryAdd2");

    // testing update quantity inventory
    test_int(inventorySetQuantity(1, 100), 1, "InventoryQuantity1");
    test_int(inventorySetQuantity(2, 500), 1, "InventoryQuantity2");

    // testing update price inventory
    test_int(inventorySetPrice(1, 3.0), 1, "InventoryPrice1");
    test_int(inventorySetPrice(2, 2.0), 1, "InventoryPrice2");

    // testing fetching inventory
    resInventory item1, item2;
    test_int(inventoryFetch(&item1, 1), 1, "InventoryFetch1");
    test_int(inventoryFetch(&item2, 2), 1, "InventoryFetch2");

    resCustomer customer;
    test_int(customerGenerateBill(&customer, 100.00, 1), 1, "CustomerGenerate");
    test_int(customerInfo(&customer, 100001), 1, "CustomerInfo");
    test_int(customerPayment(&customer), 1, "CustomerPayment");


    sql_close();

    getch();
}