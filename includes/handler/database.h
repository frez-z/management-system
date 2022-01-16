
#include <sql/sqlite3.h>
#include <stdio.h>

sqlite3 *db;
sqlite3_stmt *stmt;
char *db_error; // global db error message


/*
 * struct for restaurant information
 */
typedef struct restaurantInfo {
    const unsigned char *name;
    const unsigned char * admin_name;
    const unsigned char * password;
} restaurantInfo;


/*
 * open a new connection to database
 * argument: database file directory
 */
void sql_open(char *fileDir){
    sqlite3_open(fileDir, &db);
}


/*
 * close the connection to database
 */
void sql_close(void){
    sqlite3_close(db);
}


/*
 * create new restaurant table and populated it with data.
 *
 * argument:
 *      name: name of the restaurant.
 *      admin_name: name created used to access administrator screen.
 *      admin_password: password created to access administrator screen.
 *
 * return value:
 *       0 = error creating database
 *       1 = execution success
 *      -1 = restaurant already exist
 */
int createRestaurant(char *name, char *admin_name, char* admin_password){
    int ic; // error handling variable

    ic = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS restaurant (id INT PRIMARY KEY, restaurant_name VARCHAR(50), admin_name VARCHAR(20), admin_pass VARCHAR(20));", NULL, NULL, &db_error);

    if (ic != SQLITE_OK) return 0; // error creating table.

    char string[100];
    sprintf(string,"INSERT INTO restaurant VALUES (1, '%s', '%s', '%s');", name, admin_name, admin_password);
    ic = sqlite3_exec(db, string, NULL, NULL, &db_error);

    if (ic != SQLITE_OK) return -1; // restaurant already exist

    return 1;
}


/*
 * fetch restaurant data without error handling
 *
 * argument:
 *      restaurantInfo struct pointer.
 */
void fetchRestaurant(restaurantInfo *data){
    stmt = NULL; // reinitialize stmt into NULL

    sqlite3_prepare_v2(db, "SELECT * FROM restaurant;", -1, &stmt, 0);
    sqlite3_step(stmt);

    data->name = sqlite3_column_text(stmt, 1);
    data->admin_name = sqlite3_column_text(stmt, 2);
    data->password = sqlite3_column_text(stmt, 3);
}