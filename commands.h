#ifndef COMMANDS_H
#define COMMANDS_H
#define MAX_LEN 1000
#define MAX_CHAR_LEN 50

struct kvPair {
    char key[MAX_CHAR_LEN];
    char value[MAX_CHAR_LEN];
};

int open(struct kvPair *table);
int save(struct kvPair *table);
int insert(void);
int query(void);
int update(void);
int del(void);
int showAll(void);

#endif