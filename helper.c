#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
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

int printDeclaration()
{
    FILE *declarationPtr;
    char line[100000];

    declarationPtr = fopen("data/declaration.txt", "r");
    if (declarationPtr == NULL)
    {
        perror("Error opening declaration file");
        return -1;
    }

    while (fgets(line, 100000, declarationPtr) != NULL)
    {
        line[strcspn(line, "\n")]='\0';
        printf("%s\n", line);
    }

    fclose(declarationPtr);
    printf("\n");
    return 0;
}

// define globally the hash table
phonebook *table[MAX_TABLE_SIZE];

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
int initTable()
{
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        table[i] = NULL; // set to null pointers for all at the start
    }
    printf("---Table Created---\n");
    return 1;
}

// used a linked list for collision handling
int insertRecord(phonebook *record)
{
    unsigned long key = hash(record->name);
    phonebook *head = table[key];

    if (head == NULL)
    {
        table[key] = record;
    }
    else
    {
        while (head->next != NULL)
        {
            head = head->next;
        }
        head->next = record;
    }
    printf("---Record Added---\n");
    return 1;
}

// used a linked list for collision handling
int updateRecord(char *name, char *number)
{
    unsigned long key = hash(name);
    phonebook *head = table[key];

    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            strcpy(head->number, number);
            printf("Record Updated---%s-%s---\n", head->name, number);
            return 1;
        }
        else
        {
            head = head->next;
        }
    }
    printf("---No Record Found---\n");
    return 1;
}

int delRecord(char *name)
{
    unsigned long key = hash(name);
    phonebook *head = table[key];
    phonebook *prevHead = NULL;
    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            printf("Deleted---%s-%s---\n", head->name, head->number);
            if (prevHead == NULL)
                table[key] = head->next;
            else
                prevHead->next = head->next;
            return 1;
        }
        else
        {
            prevHead = head;
            head = head->next;
        }
    }
    printf("---Failed to delete---\n");
    return 0;
}

int getRecord(char *name)
{
    unsigned long key = hash(name);
    phonebook *head = table[key];

    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            printf("Record Found---%s-%s---\n", head->name, head->number);
            return 1;
        }
        else
        {
            head = head->next;
        }
    }
    printf("---No Record Found---\n");
    return 0;
}

void printRecords()
{
    printf("-----START-----\n");
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        phonebook *head = table[i];
        if (head == NULL)
        {
            printf("------\n");
            continue;
        }
        while (head != NULL)
        {
            printf("---%s-%s---\n", head->name, head->number);
            head = head->next;
        }
    }
    printf("-----END-----\n");
}
/* Testing code
int main()
{
    initTable();
    phonebook Tom = {.name = "Tom", .number = "12345"};
    insertRecord(&Tom);
    phonebook marry = {.name = "marry", .number = "34234"};
    insertRecord(&marry);
    phonebook peter = {.name = "peter", .number = "2424"};
    insertRecord(&peter);
    phonebook gran = {.name = "gran", .number = "64745612"};
    insertRecord(&gran);
    phonebook tony = {.name = "tony", .number = "13452"};
    insertRecord(&tony);
    phonebook grape = {.name = "grape", .number = "6735566"};
    insertRecord(&grape);
    phonebook apple = {.name = "apple", .number = "43523"};
    insertRecord(&apple);
    printRecords();
    printf("\n");
    getRecord("tony");
    printf("\n");
    getRecord("peter");
    printf("\n");
    getRecord("fakename");
    printf("\n");
    delRecord("grape");
    printf("\n");
    delRecord("peter");
    printf("\n");
    delRecord("mockName");
    printf("\n");
    printRecords();
    updateRecord("tony", "new number");
    printf("\n");
    updateRecord("mockName", "new number");
    printf("\n");
    printRecords();
}
*/