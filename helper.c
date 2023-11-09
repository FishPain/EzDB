#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "table.h"
#define HASHTABLE_FLAG "-h"

void lower(char *str) // to lower a string.
{
    for (int i = 0; str[i]; i++)
        if (str[i] != '_')
            str[i] = tolower((unsigned char)str[i]);
}

int compare(const void *tmp1, const void *tmp2)
{
    phonebook *data1 = (phonebook *)tmp1;
    phonebook *data2 = (phonebook *)tmp2;
    // check if key (contact name) is same
    int chCompare = strcmp(data1->name, data2->name);
    if (chCompare == 0)
    {
        // return value (number) in ascending order if key (contact name) is same
        return data1->number - data2->number;
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
        line[strcspn(line, "\n")] = '\0';
        printf("%s\n", line);
    }

    fclose(declarationPtr);
    printf("\n");
    return 0;
}

int getFlag(int argc, char *argv[])
{
    if (argc != 2) // if no flag is passed when running ezdb then return;
        return 0;
    if (strcmp(argv[1], HASHTABLE_FLAG) == 0)
        return 1;
    return 0;
}
