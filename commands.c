#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

int open(struct kvPair *table, char key[])
{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];
    snprintf(filePath, sizeof(filePath), "data/%s", key); // "data/PhoneBook.txt"
    phonebookPtr = fopen(filePath, "r");                  // open file
    if (phonebookPtr == NULL)                             // Check if file open
    {
        perror("Error opening file");
        return 1;
    }
    int c = 0; // counter
    char text[MAX_CHAR_LEN];
    while (fgets(text, MAX_CHAR_LEN, phonebookPtr) != NULL) // get each row of text file and save to text[]
    {
        // text[] => Marry 88776655\n
        text[strcspn(text, "\n")] = '\0'; // Remove tailing \n and change it to \0 (represents the end of line)

        if (strcmp(text, FILE_HEADER) != 0 &&                        // Ignore the column header in txt file
            sscanf(text, "%s %s", table[c].key, table[c].value) == 2 // Split the string into 2 parts.
            // sscanf will return num of variables retrieved.
        )
        {
            printf("%s\n", text); // print out to show
            c++;                  // increment
        }
    }

    fclose(phonebookPtr); // close the file
    return 0;
}

int save(struct kvPair *table, char key[])
{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];
    char c[MAX_CHAR_LEN]; // define temp string to contain the concat Key Value Pair

    snprintf(c, sizeof(c), "%s %s\n", table[0].key, table[0].value); // concatation.
    if (strlen(c) <= 2)
    {
        fclose(phonebookPtr); // close file
        perror("File was never opened. Aborted Save.");
        return 1;
    }
    
    snprintf(filePath, sizeof(filePath), "data/%s", key);
    phonebookPtr = fopen(filePath, "w");
    if (phonebookPtr == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < sizeof(table); i++)
    {
        char c[MAX_CHAR_LEN]; // define temp string to contain the concat Key Value Pair
        if (i == 0)
            snprintf(c, sizeof(c), "%s\n", FILE_HEADER); // concatation.
        else
            snprintf(c, sizeof(c), "%s %s\n", table[i - 1].key, table[i - 1].value); // concatation.

        fputs(c, phonebookPtr); // write back into file.
        printf("%s", c);
    }
    fclose(phonebookPtr); // close file
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