#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helper.h"

void lower(char *str) // to lower a string.
{
    for (int i = 0; str[i]; i++)
        if (str[i] != '_')
            str[i] = tolower((unsigned char)str[i]);
}

/*
comparison function to sort an array of kvPair
*/
int compare(const void *tmp1, const void *tmp2)
{
    kvPair *data1 = (kvPair *)tmp1;
    kvPair *data2 = (kvPair *)tmp2;
    // check if key (contact name) is same
    int chCompare = strcmp(data1->key, data2->key);
    if (chCompare == 0)
    {
        // return value (number) in ascending order if key (contact name) is same
        return data1->value - data2->value;
    }
    else
    {
        return chCompare;
    }
}

/* Hashtable implimentation */

typedef struct person
{
    char name[MAX_CHAR_LEN];   // the key
    char number[MAX_CHAR_LEN]; // the value
    struct person *next;       // chaining to tackle collision
} person;

// define globally the hash table
person *table[MAX_TABLE_SIZE];

// djb2 hash function by dan bernstein [Mckenzie et al. Selecting a Hashing Algorithm, SP&E 20(2):209-224, Feb 1990]
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MAX_TABLE_SIZE;
}

// initialise an empty table w fixed size
void initTable()
{
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        table[i] = NULL; // set to null pointers for all at the start
    }
}

// used a linked list for collision handling
void insertRecord(person *record)
{
    unsigned long hashedName = hash(record->name);
    if (table[hashedName] == NULL)
    {
        table[hashedName] = record;
    }
    else
    {
        person *head = table[hashedName];
        while (head->next != NULL)
        {
            head = head->next;
        }
        head->next = record;
    }
}

int getRecord(char *name)
{
    char key = hash(name);
    person *head = table[key];
    if (head == NULL)
    {
        printf("---No Record Found---\n");
        return 0;
    }

    do
    {
        if (strcmp(head->name, name))
        {
            printf("Record Found---%s-%s---\n", head->name, head->number);
            return 1;
        }

        head = head->next;
    } while (head != NULL);

    return 0;
}

void printRecords()
{
    printf("-----START-----\n");
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        if (table[i] == NULL)
        {
            printf("------\n");
        }
        else
        {
            person *head = table[i];
            do
            {
                printf("---%s-%s---\n", head->name, head->number);
                head = head->next;
            } while (head != NULL);
        }
    }
    printf("-----END-----\n");
}

int main()
{
    initTable();
    person record = {.name = "Tom", .number = "12345"};
    insertRecord(&record);
    person marry = {.name = "marry", .number = "34234"};
    insertRecord(&marry);
    person peter = {.name = "peter", .number = "2424"};
    insertRecord(&peter);
    person gran = {.name = "gran", .number = "64745612"};
    insertRecord(&gran);
    person tony = {.name = "tony", .number = "13452"};
    insertRecord(&tony);
    person grape = {.name = "grape", .number = "6735566"};
    insertRecord(&grape);
    person apple = {.name = "apple", .number = "43523"};
    insertRecord(&apple);

    printRecords();

    getRecord("tony");
    getRecord("peter");
    getRecord("fakename");
}