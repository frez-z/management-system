// Created by Farez

#include <stdio.h>
#include "test.h"

unsigned int id = 1;

void test_int(int actual, int expected, char* name){
    if (actual == expected)
        printf("%2d. " GREEN "[TEST SUCCESS]"RST" [ %s ]" BR, id, name);
    else
        printf("%2d. " RED "[TEST FAIL]"RST" [ %s ] expect " GREEN "%d" RST " but return " RED "%d" RST BR, id, name, expected, actual);
    id++;
}