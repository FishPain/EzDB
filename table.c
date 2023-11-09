#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "table.h"

/**
 * djb2 hash function by Dan Bernstein [Mckenzie et al. Selecting a Hashing Algorithm, SP&E 20(2):209-224, Feb 1990]
 * 
 * @param str The string to be hashed.
 * @return The hash value.
 */
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MAX_TABLE_SIZE;
}

/**
 * Initializes an empty hashtable with a fixed size.
 * 
 * @return 0 if the operation is successful.
 */
int initTable() {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        table[i] = NULL; // Set to null pointers for all at the start
    }
    printf("---Table Created---\n");
    return 0;
}

/**
 * Inserts a record into the hashtable using linked list for collision handling.
 * 
 * @param record The phonebook record to be inserted.
 * @return 0 if the operation is successful.
 */
int insertRecord(phonebook *record) {
    unsigned long key = hash(record->name);
    phonebook *head = table[key];

    if (head == NULL)
        table[key] = record;
    else {
        while (head->next != NULL)
            head = head->next;

        head->next = record;
    }

    printf("---Record Added %s-%s---\n", record->name, record->number);
    return 0;
}

/**
 * Updates a record in the hashtable.
 * 
 * @param name The name of the record to be updated.
 * @param number The new number to be associated with the record.
 * @return 0 if the operation is successful, 1 if no record is found.
 */
int updateRecord(char *name, char *number) {
    unsigned long key = hash(name);
    phonebook *head = table[key];

    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            strcpy(head->number, number);
            printf("Record Updated---%s-%s---\n", head->name, number);
            return 0;
        } else {
            head = head->next;
        }
    }
    printf("---No Record Found---\n");
    return 1;
}

/**
 * Deletes a record from the hashtable.
 * 
 * @param name The name of the record to be deleted.
 * @return 0 if the operation is successful, 1 if no record is found.
 */
int delRecord(char *name) {
    unsigned long key = hash(name);
    phonebook *head = table[key];
    phonebook *prevHead = NULL;

    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            printf("Deleted---%s-%s---\n", head->name, head->number);
            if (prevHead == NULL)
                table[key] = head->next;
            else
                prevHead->next = head->next;

            free(head);
            return 0;
        } else {
            prevHead = head;
            head = head->next;
        }
    }
    printf("---Failed to delete---\n");
    return 1;
}

/**
 * Retrieves a record from the hashtable.
 * 
 * @param name The name of the record to be retrieved.
 * @return 0 if the operation is successful, 1 if no record is found.
 */
int getRecord(char *name) {
    unsigned long key = hash(name);
    phonebook *head = table[key];

    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            printf("Record Found---%s-%s---\n", head->name, head->number);
            return 0;
        } else {
            head = head->next;
        }
    }
    printf("---No Record Found---\n");
    return 1;
}

/**
 * Prints all records in the hashtable.
 * 
 * @return 0 if the operation is successful.
 */
int printRecords() {
    printf("-----START-----\n");

    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        phonebook *head = table[i];

        if (head == NULL) {
            printf("------\n");
            continue;
        }

        while (head != NULL) {
            printf("---%s-%s---\n", head->name, head->number);
            head = head->next;
        }
    }

    printf("-----END-----\n");
    return 0;
}
