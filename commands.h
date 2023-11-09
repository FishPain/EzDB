#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_TABLE_SIZE 10
#define OPEN "open"
#define SAVE "save"
#define SHOW_ALL "show_all"
#define UPDATE "update"
#define QUERY "query"
#define DELETE "delete"
#define INSERT "insert"
#define EXIT "exit"
#define FILE_HEADER "Key Value"

// Function prototypes
int open(char *key, int isHash);
int save(char *key, int isHash);
int insert(char *key, char *value, int isHash);
int query(int numRecords, char *key, int isHash);
int update(char *key, char *newValue, int isHash);
int del(char *key, int isHash);
int showAll(int isHash);
#endif