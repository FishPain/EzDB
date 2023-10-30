#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

int open(struct kvPair *table, char key[])
{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];
    snprintf(filePath, sizeof(filePath), "data/%s", key);
    phonebookPtr = fopen(filePath, "r");
    if (phonebookPtr == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    // set c = 1 to ignore header row.
    int c = 0;
    char text[MAX_CHAR_LEN];
    while (fgets(text, MAX_CHAR_LEN, phonebookPtr)!= NULL)
    {
        text[strcspn(text, "\n")] = '\0';

        if (strcmp(text, "Key Value")!=0 && sscanf(text, "%s %s", table[c].key, table[c].value) == 2)
        {
            printf("%s\n", text);
            c++;
        }
    }

    fclose(phonebookPtr);
    return 0;
}

int save(struct kvPair *table, char key[])
{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];
    snprintf(filePath, sizeof(filePath), "data/%s", key);
    phonebookPtr = fopen(filePath, "r");
    if (phonebookPtr == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    
    for (int i = 0; i < sizeof(table); ++i)
    {
        char c[MAX_CHAR_LEN];
        snprintf(c, sizeof(c), "%s %s\n", table[i].key, table[i].value);
        c[sizeof(c) - 1] = '\0';
        fputs(c, phonebookPtr);
        printf("%s\n", c);
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