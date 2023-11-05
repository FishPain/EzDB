#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "commands.h"

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

int open(kvPair *table, char key[])
{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];
    snprintf(filePath, sizeof(filePath), "data/%s", key);
    phonebookPtr = fopen(filePath, "r");
    if (phonebookPtr == NULL)
    {
        perror("Error opening file");
        return -1;
    }
    int c = 0; // counter
    char text[MAX_CHAR_LEN];

    while (fgets(text, MAX_CHAR_LEN, phonebookPtr) != NULL) // get each row of text file and save to text[]
    {
        text[strcspn(text, "\n")] = '\0';                            // Remove tailing \n and change it to \0 (represents the end of line)
        if (strcmp(text, FILE_HEADER) != 0 &&                        // Ignore the column header in txt file
            sscanf(text, "%s %s", table[c].key, table[c].value) == 2 // Split the string into 2 parts.
            // sscanf will return num of variables retrieved.
        )
        {
            lower(table[c].key);
            // printf("%s %s\n", table[c].key, table[c].value); // print out to show
            c++; // increment
        }
    }
    // sort using qsort, with comparator function passed in
    qsort(table, c, sizeof(kvPair), compare);
    for (int i = 0; i < c; i++)
    {
        printf("%s\t%s\n", table[i].key, table[i].value);
    }

    fclose(phonebookPtr); // close the file
    return c;             // Return the number of records loaded
}

int save(kvPair *table, char key[])
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

int query(kvPair *table, int numRecords, char key[])
{
    // Convert the input key to lowercase for case-insensitive comparison
    char lowerKey[MAX_CHAR_LEN];
    strcpy(lowerKey, key);
    for (int i = 0; lowerKey[i]; i++)
    {
        lowerKey[i] = tolower(lowerKey[i]);
    }

    // Iterate through the records in the table to find a matching key
    for (int i = 0; i < numRecords; i++)
    {
        // Get the stored key and convert it to lowercase for comparison
        char storedKey[MAX_CHAR_LEN];
        strcpy(storedKey, table[i].key);
        char lowerStoredKey[MAX_CHAR_LEN];
        strcpy(lowerStoredKey, storedKey);

        for (int j = 0; lowerStoredKey[j]; j++)
        {
            lowerStoredKey[j] = tolower(lowerStoredKey[j]);
        }

        // Compare the lowercase stored key with the lowercase input key
        if (strcmp(lowerStoredKey, lowerKey) == 0)
        {
            // Record found, print the key and its associated value
            printf("A record of Key=%s, Value=%s is found in the database.\n", storedKey, table[i].value);
            return 0; // Record found
        }
    }

    // If no matching record is found, print a "not found" message
    printf("There is no record with Key=%s found in the database.\n", key);
    return 1; // Record not found
}

int update(kvPair *table, char key[], char newValue[])
{
    for (int i = 0; i < MAX_LEN; i++)
    {
        if (strcmp(table[i].key, key) == 0)
        {
            snprintf(table[i].value, sizeof(table[i].value), "%s", newValue); // Update the value for the specific key
            printf("The value for the record of Key=%s is successfully updated.\n", key);
            return 0;
        }
    }
    printf("Key=%s not found. Failed to update the value.\n", key);
    return 1;
}

int del(void)
{
    return 0;
}

int showAll(void)
{
    return 0;
}