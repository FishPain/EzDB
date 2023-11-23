#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "commands.h"
#include "table.h"
#include "helper.h"

/**
 * Opens a file and loads data into memory.
 *
 * @param key The name of the file to open.
 * @param isHash Flag indicating whether to use a hash table for data storage.
 * @return The number of records loaded on success, or -1 on failure.
 */
int open(char *key, int isHash)
{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];
    char text[MAX_CHAR_LEN];
    int c = 0; // counter

    // Construct the file path
    snprintf(filePath, sizeof(filePath), "data/%s", key);

    // Open the file for reading
    phonebookPtr = fopen(filePath, "r");

    // Check for file opening errors
    if (phonebookPtr == NULL)
    {
        printf("Error opening file.\n");
        return -1;
    }

    // Read the header line
    if (fgets(text, MAX_CHAR_LEN, phonebookPtr) == NULL)
    {
        printf("Failed to read the header.\n");
        fclose(phonebookPtr);
        return -1;
    }

    // Process the remaining lines in the file
    while (fgets(text, MAX_CHAR_LEN, phonebookPtr) != NULL)
    {
        // Allocate memory for a new phonebook record
        phonebook *record = malloc(sizeof(phonebook));

        // Check for memory allocation errors
        if (record == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(phonebookPtr);
            return -1;
        }

        // Parse the line and populate the record fields
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

    // Sort the data using qsort (commented out)
    if (!isHash)
        qsort(table, c, sizeof(phonebook *), compare);

    // Print the loaded records
    printRecords();

    // Close the file
    fclose(phonebookPtr);

    // Return the number of records loaded
    return c;
}

/**
 * Saves data to a file.
 *
 * @param key The name of the file to save.
 * @param isHash Flag indicating whether to use a hash table for data storage.
 * @return 0 on success, -1 on failure.
 */
int save(char *key, int numRecords, int isHash)
{
    FILE *phonebookPtr;
    char filePath[MAX_CHAR_LEN];

    numRecords = isHash ? MAX_TABLE_SIZE : numRecords;

    // Check if there is data to save
    int isEmpty = 1;
    for (int i = 0; i < numRecords; i++)
    {
        if (table[i] != NULL)
        {
            isEmpty = 0;
            break;
        }
    }

    if (isEmpty)
    {
        printf("No data to save. Have you opened the file?\n");
        return -1;
    }

    // Construct the file path
    snprintf(filePath, sizeof(filePath), "data/%s", key);

    if(access(filePath, F_OK) == -1)
    {
        printf("File does not exist. Cannot save data.\n");
        return -1;
    }

    // Open the file for writing
    phonebookPtr = fopen(filePath, "w");

    // Check for file opening errors
    if (phonebookPtr == NULL)
    {
        printf("Error opening file.\n");
        return -1;
    }

    // Add file header
    fprintf(phonebookPtr, "%s\n", FILE_HEADER);

    // Write data to the file
    for (int i = 0; i < numRecords; i++)
    {
        phonebook *head = table[i];
        while (head != NULL)
        {
            fprintf(phonebookPtr, "%s %s\n", head->name, head->number);
            printf("Saved: %-10s %-10s\n", head->name, head->number);
            head = head->next;
        }
    }

    // Close the file
    fclose(phonebookPtr);

    // Return success
    return 0;
}

/**
 * Inserts a new record into the data structure.
 *
 * @param key The key of the record.
 * @param value The value of the record.
 * @param isHash Flag indicating whether to use a hash table for data storage.
 * @return 0 on success, -1 on failure.
 */
int insert(int *numRecords, char *key, char *value, int isHash)
{
    // Allocate memory for a new phonebook record
    phonebook *record = malloc(sizeof(phonebook));

    // Check for memory allocation errors
    if (record == NULL)
    {
        perror("Memory allocation failed");
        return -1;
    }

    snprintf(record->name, sizeof(record->name), "%s", key);
    snprintf(record->number, sizeof(record->number), "%s", value);

    // hash table implementation of insert
    if (isHash)
        return insertRecord(record);

    // Iterate through the records in the table to find a matching key
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        // Insert the record into the first available slot
        if (table[i] == NULL)
        {
            table[i] = record;
            (*numRecords)++; // Increment the number of records
            printf("The value for the record of Key=%s Value=%s is successfully inserted.\n", key, value);
            return 0;
        }

        // If the key already exists, abort insert
        if (strcmp(table[i]->name, key) == 0)
        {
            printf("The record with Key=%s already exists in the database.\n", key);
            return 1;
        }
    }
    // Return success
    return 0;
}

/**
 * Queries for a record based on the key.
 *
 * @param key The key to search for.
 * @param isHash Flag indicating whether to use a hash table for data storage.
 * @return 0 if the record is found, 1 if not found.
 */
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

/**
 * Updates the value of a record based on the key.
 *
 * @param key The key of the record to update.
 * @param newValue The new value for the record.
 * @param isHash Flag indicating whether to use a hash table for data storage.
 * @return 0 on success, 1 on failure.
 */
int update(char *key, char *newValue, int isHash)
{
    if (isHash)
        return updateRecord(key, newValue);

    // Iterate through the records in the table to find a matching key
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        if (strcmp(table[i]->name, key) == 0)
        {
            // Update the value for the specific key
            snprintf(table[i]->number, sizeof(table[i]->number), "%s", newValue);
            printf("The value for the record of Key=%s is successfully updated.\n", key);
            return 0;
        }
    }

    // If the key is not found, print an error message
    printf("There is no record with Key=%s found in the database.\n", key);
    return 1;
}

/**
 * Deletes a record based on the key.
 *
 * @param numRecords Pointer to the number of records.
 * @param KeyToDelete The key of the record to delete.
 * @param isHash Flag indicating whether to use a hash table for data storage.
 * @return 0 on success, 1 on failure.
 */
int del(int *numRecords, char *KeyToDelete, int isHash)
{
    if (isHash)
        return delRecord(KeyToDelete);

    // Check if the key is found in the records
    for (int i = 0; i < *numRecords; i++)
    {
        if (strcmp(table[i]->name, KeyToDelete) == 0)
        {
            // Key found, delete the record
            for (int j = i; j < *numRecords - 1; j++)
            {
                table[j] = table[j + 1];
            }
            (*numRecords)--; // Decrement the number of records
            printf("The record of Key=%s is successfully deleted.\n", KeyToDelete);
            return 0;
        }
    }
    printf("There is no record with Key=%s found in the database.\n", KeyToDelete);
    // Return failure
    return 1;
}

/**
 * Displays all records.
 *
 * @param isHash Flag indicating whether to use a hash table for data storage.
 * @return 0 on success, -1 on failure.
 */
int showAll(int numRecords, int isHash)
{
    if (isHash)
        return printRecords();

    printf("There are in total %d records found:\n", numRecords);

    // Sort the data using qsort (commented out)
    qsort(table, numRecords, sizeof(phonebook *), compare);

    for (int i = 0; i < numRecords; i++)
    {
        if (table[i] != NULL)
        {
            printf("%-10s %-10s\n", table[i]->name, table[i]->number);
        }
    }

    return 0;
}
