#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_TABLE_SIZE 10
#define OPEN "open"
#define SAVE "save"
#define SHOW_ALL "show_all"
#define INSERT "insert"
#define UPDATE "update"
#define QUERY "query"
#define DELETE "delete"
#define INSERT "insert"
#define EXIT "exit"
#define FILE_HEADER "Key Value"


int open(char *key, int isHash);
int save(char *key, int isHash);
int insert(int *numRecords, char *key, char *value, int isHash);
int query(int numRecords, char *key, int isHash);
int update(char *key, char *newValue, int isHash);
int del(int *numRecords, char *KeyToDelete, int isHash);
int showAll(int isHash);
#endif