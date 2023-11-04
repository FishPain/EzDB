#ifndef COMMANDS_H
#define COMMANDS_H
#define MAX_LEN 64
#define MAX_CHAR_LEN 256
#define OPEN "open"
#define SAVE "save"
#define SHOW_ALL "show_all"
#define EXIT "exit"
#define FILE_HEADER "Key Value"
#define QUERY "query"

struct kvPair {
    char key[MAX_CHAR_LEN];
    char value[MAX_CHAR_LEN];
};

int open(struct kvPair *table, char key[]);
int save(struct kvPair *table, char key[]);
int insert(void);
int query(struct kvPair *table, int numRecords, char key[]);
int update(void);
int del(void);
int showAll(void);

// Helper functions
void lower(char *str);
int compare(const void *s1, const void *s2);

#endif