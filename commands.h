#ifndef COMMANDS_H
#define COMMANDS_H
#define OPEN "open"
#define SAVE "save"
#define SHOW_ALL "show_all"
#define UPDATE "update"
#define EXIT "exit"
#define FILE_HEADER "Key Value"
#define QUERY "query"
#include "helper.h"

int open(kvPair *table, char *key);
int save(kvPair *table, char *key);
int insert(void);
int query(kvPair *table, int numRecords, char key[]);
int update(kvPair *table, char key[], char newValue[]);
int del(void);
int showAll(void);

#endif
