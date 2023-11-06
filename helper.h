#ifndef HELPER_H
#define HELPER_H
#define MAX_LEN 64
#define MAX_CHAR_LEN 256
#define MAX_TABLE_SIZE 10

typedef struct kvPair {
    char key[MAX_CHAR_LEN];
    char value[MAX_CHAR_LEN];
} kvPair;

typedef struct phonebook
{
    char name[MAX_CHAR_LEN];   // the key
    char number[MAX_CHAR_LEN]; // the value
    struct phonebook *next;       // chaining to tackle collision
} phonebook;

// Helper functions
void lower(char *str);
int compare(const void *tmp1, const void *tmp2);

// Hashtable
unsigned long hash(unsigned char *str);
int initTable();
int getRecord(char *name);
int insertRecord(phonebook *record);
int updateRecord(char *name, char *number);
int delRecord(char *name);
void printRecords();

#endif