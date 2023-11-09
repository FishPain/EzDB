#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "commands.h"
#include "table.h"
#include "helper.h"

int open(char *key, int isHash)
{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];
    char text[MAX_CHAR_LEN];
    int c = 0; // counter

    snprintf(filePath, sizeof(filePath), "data/%s", key);
    phonebookPtr = fopen(filePath, "r");

    if (phonebookPtr == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    if (fgets(text, MAX_CHAR_LEN, phonebookPtr) == NULL)
    {
        perror("Failed to read the header");
        fclose(phonebookPtr);
        return -1;
    }

    // Process the remaining lines
    while (fgets(text, MAX_CHAR_LEN, phonebookPtr) != NULL)
    {
        phonebook *record = malloc(sizeof(phonebook)); // Allocate memory

        if (record == NULL)
        {
            perror("Memory allocation failed");
            fclose(phonebookPtr);
            return -1;
        }

        if (sscanf(text, "%s %s", record->name, record->number) == 2)
        {
            lower(record->name);
            if (isHash)
                insertRecord(record);
            else
                table[c] = record;
            c++; // increment
        }
        else
        {
            printf("Error parsing line: %s\n", text);
        }
    }

    // sort using qsort, with comparator function passed in
    // qsort(table, c, sizeof(phonebook), compare);
    printRecords();
    fclose(phonebookPtr); // close the file
    return c;             // Return the number of records loaded
}

int save(char *key, int isHash)

{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];

    int isEmpty = 1;
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        if (table[i] != NULL)
        {
            isEmpty = 0;
            break;
        }
    }

    if (isEmpty)
    {
        printf("No data to save.\n");
        return -1;
    }

    snprintf(filePath, sizeof(filePath), "data/%s", key);
    phonebookPtr = fopen(filePath, "w");

    if (phonebookPtr == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    fprintf(phonebookPtr, "%s\n", FILE_HEADER); // add file header

    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        phonebook *head = table[i];
        while (head != NULL)
        {
            fprintf(phonebookPtr, "%s %s\n", head->name, head->number);
            printf("Saved---%s-%s---\n", head->name, head->number);
            head = head->next;
        }
    }

    fclose(phonebookPtr); // close file
    return 0;
}

int insert(char *key, char *value, int isHash)
{        
    phonebook *record = malloc(sizeof(phonebook)); // Allocate memory
    if (isHash)
    {

        snprintf(record->name, sizeof(record->name), "%s", key);
        snprintf(record->number, sizeof(record->number), "%s", value);
        insertRecord(record);
        return 0;
    }
    return 0;
}

int query(int numRecords, char *key, int isHash)
{
    if (isHash)
        return getRecord(key);

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
        strcpy(storedKey, table[i]->name);
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
            printf("A record of Key=%s, Value=%s is found in the database.\n", storedKey, table[i]->number);
            return 0; // Record found
        }
    }

    // If no matching record is found, print a "not found" message
    printf("There is no record with Key=%s found in the database.\n", key);
    return 1; // Record not found
}

int update(char *key, char *newValue, int isHash)
{
    if (isHash)
        return updateRecord(key, newValue);

    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        if (strcmp(table[i]->name, key) == 0)
        {
            snprintf(table[i]->number, sizeof(table[i]->number), "%s", newValue); // Update the value for the specific key
            printf("The value for the record of Key=%s is successfully updated.\n", key);
            return 0;
        }
    }
    printf("Key=%s not found. Failed to update the value.\n", key);
    return 1;
}

int del(char *key, int isHash)
{
    if (isHash)
        return delRecord(key);
    return 0;
}

int showAll(int isHash)
{
    if (isHash)
        return printRecords();

    return 0;
}
