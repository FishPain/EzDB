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
    if (phonebookPtr == NULL) {
        perror("Error opening file");
        return 1;
    }
    int c = 0; // counter
    char text[MAX_CHAR_LEN];
    
    // Read and discard the header line
    if (fgets(text, MAX_CHAR_LEN, phonebookPtr) == NULL) {
        fclose(phonebookPtr);
        return 1; // Error reading the header
    }

    while (fgets(text, MAX_CHAR_LEN, phonebookPtr) != NULL) {
        text[strcspn(text, "\n")] = '\0'; // Remove trailing \n and change it to \0 (represents the end of line)
        if (sscanf(text, "%s %s", table[c].key, table[c].value) == 2) {
            printf("%s %s\n", table[c].key, table[c].value); // Print out to show
            c++; // Increment and count the records
        }
    }

    fclose(phonebookPtr); // close the file
    return c; // Return the number of records loaded
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

int query(struct kvPair *table, int numRecords, char key[])
{
    // Convert the input key to lowercase for case-insensitive comparison
    char lowerKey[MAX_CHAR_LEN];
    strcpy(lowerKey, key);
    for (int i = 0; lowerKey[i]; i++) {
        lowerKey[i] = tolower(lowerKey[i]);
    }

    // Iterate through the records in the table to find a matching key
    for (int i = 0; i < numRecords; i++) {
        // Get the stored key and convert it to lowercase for comparison
        char storedKey[MAX_CHAR_LEN];
        strcpy(storedKey, table[i].key);
        char lowerStoredKey[MAX_CHAR_LEN];
        strcpy(lowerStoredKey, storedKey);

        for (int j = 0; lowerStoredKey[j]; j++) {
            lowerStoredKey[j] = tolower(lowerStoredKey[j]);
        }

        // Compare the lowercase stored key with the lowercase input key
        if (strcmp(lowerStoredKey, lowerKey) == 0) {
            // Record found, print the key and its associated value
            printf("A record of Key=%s, Value=%s is found in the database.\n", storedKey, table[i].value);
            return 0; // Record found
        }
    }

    // If no matching record is found, print a "not found" message
    printf("There is no record with Key=%s found in the database.\n", key);
    return 1; // Record not found
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
