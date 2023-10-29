#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

int open(struct kvPair *table)
{
    FILE *phonebookPtr;

    phonebookPtr = fopen("data/PhoneBook.txt", "r");
    if (phonebookPtr == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int c = 0;
    while (fscanf(phonebookPtr, "%s %s", table[c].key, table[c].value) == 2)
    {
        printf("Key: %s, Value: %s\n", table[c].key, table[c].value);
        c++;
    }

    fclose(phonebookPtr);
    return 0;
}

int save(struct kvPair *table)
{
    FILE *phonebookPtr;
    phonebookPtr = fopen("data/PhoneBook.txt", "w");

    if (phonebookPtr == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < sizeof(table); i++)
    {
        char c[100];
        strcpy(c, table[i].key); // Copy str_1 to a
        strcat(c, " ");  // Append a space
        strcat(c, table[i].value); // Append str_2
        strcat(c, "\n"); // Append str_2
        fputs(c, phonebookPtr);
        printf("Key: %s, Value: %s\n", table[i].key, table[i].value);

    }
    fclose(phonebookPtr);
    return 0;
}

int insert(void)
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