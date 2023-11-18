#ifndef TABLE_H
#define TABLE_H
#define MAX_TABLE_SIZE 50
#define MAX_CHAR_LEN 256

typedef struct phonebook
{
    char name[MAX_CHAR_LEN];   // the key
    char number[MAX_CHAR_LEN]; // the value
    struct phonebook *next;    // chaining to tackle collision
} phonebook;

extern struct phonebook *table[MAX_TABLE_SIZE];

unsigned long hash(unsigned char *str);
int initTable();
int getRecord(char *name);
int insertRecord(phonebook *record);
int updateRecord(char *name, char *number);
int delRecord(char *name);
int printRecords();
#endif