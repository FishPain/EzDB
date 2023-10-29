#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_LEN 1000

struct kvPair {
    char *key;
    char *value;
};

void insert(void)
{
    return 0;
}

int query(void)
{
    return 0;
}

int update(void)
{
    return 0;
}

int del(void)
{
    return 0;
}

int showAll(void)
{
    return 0;
}

int open(void)
{
    FILE *db;

    struct kvPair table[MAX_LEN];
    // opens a file and saves the data into memory
    db = fopen("data/PhoneBook.txt", "r");
    if (db == NULL) return 1;
    // Read and process each line
    while (fscanf(db, "%s %d", table.key, table.value) == 2) {
        printf("Key: %s, Value: %d\n", key, value);
        // You can store the key-value pairs in a data structure or process them as needed
    }
    return 0;
}

int close(void)
{
    return 0;
}