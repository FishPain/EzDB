#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "table.h"

/**
 * djb2 hash function by Dan Bernstein
 * [Mckenzie et al. Selecting a Hashing Algorithm, SP&E 20(2):209-224, Feb 1990]
 *
 * @param str The string to be hashed.
 * @return The hash value.
 */
unsigned long hash(unsigned char *str)
{
    // Initialize the hash value to 5381
    unsigned long hash = 5381;
    int c;

    // Iterate through each character in the string
    while (c = *str++)
    {
        // Update the hash value using the DJB2 algorithm: hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }

    // Return the hash value modulo the maximum table size
    return hash % MAX_TABLE_SIZE;
}

/**
 * Initializes an empty hashtable with a fixed size.
 *
 * @return 0 if the operation is successful.
 */
int initTable()
{
    // Iterate through each element in the hash table array
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        // Set each element to NULL, indicating an empty linked list
        table[i] = NULL;
    }

    // Return 0 to indicate successful initialization
    return 0;
}

/**
 * Inserts a record into the hashtable using linked list for collision handling.
 *
 * @param record The phonebook record to be inserted.
 * @return 0 if the operation is successful.
 */
int insertRecord(phonebook *record)
{
    // Calculate the hash value using the name of the record
    unsigned long key = hash(record->name);

    // Get the head of the linked list at the calculated hash
    phonebook *head = table[key];

    // If the list is empty at this hash, insert the record as the head
    if (head == NULL)
        table[key] = record;

    else
    {
        // If there are elements in the list, traverse to the end
        while (head->next != NULL)
        {
            head = head->next;
            if (strcmp(head->name, record->name) == 0)
            {
                printf("The record with Key=%s already exists in the database.\n", record->name);
                return 1;
            }
        }

        // Add the new record to the end of the list
        head->next = record;
    }

    // Print a message indicating that the record has been added
    printf("A new record of Key=%s, Value=%s is successfully inserted.\n", record->name, record->number);
    return 0;
}

/**
 * Updates a record in the hashtable.
 *
 * @param name The name of the record to be updated.
 * @param number The new number to be associated with the record.
 * @return 0 if the operation is successful, 1 if no record is found.
 */
int updateRecord(char *name, char *number)
{
    // Calculate the hash value using the name
    unsigned long key = hash(name);

    // Get the head of the linked list at the calculated hash
    phonebook *head = table[key];

    // Traverse the linked list to find the record with the matching name
    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            // Update the phone number of the found record
            strcpy(head->number, number);

            // Print a message indicating that the record has been updated
            printf("“The value for the record of Key=%s is successfully updated.\n", head->name);
            return 0;
        }
        else
        {
            head = head->next;
        }
    }

    // If no matching record is found, print a message and return an error code
    printf("There is no record with Key=%s found in the database.\n", name);
    return 1;
}

/**
 * Deletes a record from the hashtable.
 *
 * @param name The name of the record to be deleted.
 * @return 0 if the operation is successful, 1 if no record is found.
 */
int delRecord(char *name)
{
    // Calculate the hash value using the name
    unsigned long key = hash(name);

    // Get the head of the linked list at the calculated hash
    phonebook *head = table[key];
    phonebook *prevHead = NULL;

    // Traverse the linked list to find the record with the matching name
    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            // Print a message indicating that the record has been deleted
            printf("The record of Key=%s is successfully deleted.\n", head->name);

            // Update the pointers to remove the record from the linked list
            if (prevHead == NULL)
                table[key] = head->next;
            else
                prevHead->next = head->next;

            // Free the memory occupied by the deleted record
            free(head);

            // Return 0 to indicate a successful deletion
            return 0;
        }
        else
        {
            // Move to the next node in the linked list
            prevHead = head;
            head = head->next;
        }
    }

    // If no matching record is found, print a message and return an error code
    printf("There is no record with Key=%s found in the database.\n", name);
    return 1;
}

/**
 * Retrieves a record from the hashtable.
 *
 * @param name The name of the record to be retrieved.
 * @return 0 if the operation is successful, 1 if no record is found.
 */
int getRecord(char *name)
{
    // Calculate the hash value for the given name
    unsigned long key = hash(name);
    // Get the pointer to the head of the linked list at the calculated hash index
    phonebook *head = table[key];

    // Iterate through the linked list at the hash index
    while (head != NULL)
    {
        // Check if the name of the current record matches the target name
        if (strcmp(head->name, name) == 0)
        {
            // Print the found record's information
            printf("A record of Key=%s, Value=%s is found in the database\n", head->name, head->number);
            return 0; // Return 0 to indicate success
        }
        else
        {
            // Move to the next node in the linked list
            head = head->next;
        }
    }

    // If the loop completes without finding the record, print a message
    printf("There is no record with Key=%s found in the database.\n", name);
    return 1; // Return 1 to indicate failure
}

/**
 * Prints all records in the hashtable.
 *
 * @return 0 if the operation is successful.
 */
int printRecords()
{
    int counter = 0;
    // Iterate through each index in the hash table
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        // Get the pointer to the head of the linked list at the current index
        phonebook *head = table[i];

        // Iterate through the linked list at the current index
        while (head != NULL)
        {
            counter++;
            // Move to the next node in the linked list
            head = head->next;
        }
    }

    printf("There are in total %d records found:\n", counter);

    // Iterate through each index in the hash table
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        // Get the pointer to the head of the linked list at the current index
        phonebook *head = table[i];

        // Iterate through the linked list at the current index
        while (head != NULL)
        {
            // Print the information of each record in the linked list
            printf("%-10s %-10s\n", head->name, head->number);
            // Move to the next node in the linked list
            head = head->next;
        }
    }
    return 0;
}
