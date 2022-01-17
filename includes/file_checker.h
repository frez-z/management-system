//
// Created by Farez on 18/1/2022.
//

#ifndef MANAGEMENT_SYSTEM_FILE_CHECKER_H
#define MANAGEMENT_SYSTEM_FILE_CHECKER_H

/*
 * create a new file if not exist
 *
 * return value:
 *       1 : file is exists
 *       0 : file not exist
 */
int createFileIfNotExist(char *fileName);

/*
 * create a new directory if not exist
 *
 * return value:
 *       1 : directory is exists
 *       0 : directory not exist
 */
int createDirIfNotExist(char *directory);

#endif //MANAGEMENT_SYSTEM_FILE_CHECKER_H