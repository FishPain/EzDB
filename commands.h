#ifndef COMMANDS_H
#define COMMANDS_H
#define MAX_LEN 64
#define MAX_CHAR_LEN 256
#define OPEN "open"
#define SAVE "save"
#define SHOW_ALL "show_all"
#define UPDATE "update"
#define EXIT "exit"
#define FILE_HEADER "Key Value"
#define QUERY "query"

typedef struct kvPair {
    char key[MAX_CHAR_LEN];
    char value[MAX_CHAR_LEN];
} kvPair;

int open(kvPair *table, char key[]);
int save(kvPair *table, char key[]);
int insert(void);
int query(kvPair *table, int numRecords, char key[]);
int update(kvPair *table, char key[], char newValue[]);
int del(void);
int showAll(void);

// Helper functions
void lower(char *str);
int compare(const void *tmp1, const void *tmp2);

#endif
