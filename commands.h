#ifndef COMMANDS_H
#define COMMANDS_H
#define MAX_LEN 64
#define MAX_CHAR_LEN 256
#define OPEN "open"
#define SAVE "save"
#define SHOW_ALL "show_all"
#define EXIT "exit"
#define FILE_HEADER "Key Value"


struct kvPair {
    char key[MAX_CHAR_LEN];
    char value[MAX_CHAR_LEN];
};

int open(kvPair *table, char key[]);
int save(kvPair *table, char key[]);
int insert(kvPair *table, char key[], char value[]);
int query(kvPair *table, int numRecords, char key[]);
int update(struct kvPair *table, char key[], char newValue[]);
int del(void);
int showAll(void);

#endif