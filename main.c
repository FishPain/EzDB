#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR_LEN 256
#define MAX_LEN 64
#define MAX_TABLE_SIZE 10
#define HASHTABLE_FLAG "-h"
#define OPEN "open"
#define SAVE "save"
#define SHOW_ALL "show_all"
#define UPDATE "update"
#define QUERY "query"
#define EXIT "exit"
#define FILE_HEADER "Key Value"

typedef struct phonebook
{
    char name[MAX_CHAR_LEN];   // the key
    char number[MAX_CHAR_LEN]; // the value
    struct phonebook *next;    // chaining to tackle collision
} phonebook;

// Function prototypes
int open(char *key, int isHash);
int save(char *key, int isHash);
int insert(void);
int query(int numRecords, char *key, int isHash);
int update(char *key, char *newValue, int isHash);
int del(void);
int showAll(void);

// Helper functions
void lower(char *str);
int compare(const void *tmp1, const void *tmp2);
int printDeclaration();
int getFlag(int argc, char *argv[]);

// Hashtable
unsigned long hash(unsigned char *str);
int initTable();
int getRecord(char *name);
int insertRecord(phonebook *record);
int updateRecord(char *name, char *number);
int delRecord(char *name);
void printRecords();

struct phonebook *table[MAX_TABLE_SIZE];

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

// djb2 hash function by dan bernstein [Mckenzie et al. Selecting a Hashing Algorithm, SP&E 20(2):209-224, Feb 1990]
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MAX_TABLE_SIZE;
}

// initialise an empty table w fixed size
int initTable()
{
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        table[i] = NULL; // set to null pointers for all at the start
    }
    printf("---Table Created---\n");
    return 0;
}

// used a linked list for collision handling
int insertRecord(phonebook *record)
{
    unsigned long key = hash(record->name);
    phonebook *head = table[key];

    if (head == NULL)
        table[key] = record;

    else
    {
        while (head->next != NULL)
            head = head->next;

        head->next = record;
    }

    printf("---Record Added %s-%s---\n", record->name, record->number);
    return 0;
}

int updateRecord(char *name, char *number)
{
    unsigned long key = hash(name);
    phonebook *head = table[key];

    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            strcpy(head->number, number);
            printf("Record Updated---%s-%s---\n", head->name, number);
            return 0;
        }
        else
        {
            head = head->next;
        }
    }
    printf("---No Record Found---\n");
    return 1;
}

int delRecord(char *name)
{
    unsigned long key = hash(name);
    phonebook *head = table[key];
    phonebook *prevHead = NULL;
    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            printf("Deleted---%s-%s---\n", head->name, head->number);
            if (prevHead == NULL)
                table[key] = head->next;
            else
                prevHead->next = head->next;
            return 0;
        }
        else
        {
            prevHead = head;
            head = head->next;
        }
    }
    printf("---Failed to delete---\n");
    return 1;
}

int getRecord(char *name)
{
    unsigned long key = hash(name);
    phonebook *head = table[key];

    while (head != NULL)
    {
        if (strcmp(head->name, name) == 0)
        {
            printf("Record Found---%s-%s---\n", head->name, head->number);
            return 0;
        }
        else
        {
            head = head->next;
        }
    }
    printf("---No Record Found---\n");
    return 1;
}

void printRecords()
{
    printf("-----START-----\n");
    for (int i = 0; i < MAX_TABLE_SIZE; i++)
    {
        phonebook *head = table[i];
        if (head == NULL)
        {
            printf("------\n");
            continue;
        }
        while (head != NULL)
        {
            printf("---%s-%s---\n", head->name, head->number);
            head = head->next;
        }
    }
    printf("-----END-----\n");
}

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

int insert(void)
{
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

    for (int i = 0; i < MAX_LEN; i++)
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

int del(void)
{
    return 0;
}

int showAll(void)
{
    return 0;
}

int main(int argc, char *argv[])
{

    char choice[MAX_CHAR_LEN];
    char operation[MAX_CHAR_LEN], key[MAX_CHAR_LEN], value[MAX_CHAR_LEN];
    int numRecords = 0;

    int isHash = getFlag(argc, argv); // feature flag for hashtable. Default to 0;
    printDeclaration();

    if (isHash)
        initTable();

    while (1)
    {
        printf("Enter Your Choice (%s):\n", isHash ? "Hashtable" : "Linear Search"); // indicator if it is hashtable or linear search
        fgets(choice, MAX_CHAR_LEN, stdin);                                          // get the user input
        int argCount = sscanf(choice, "%s %s %s", operation, key, value);            // split user input into 3 variables
        lower(operation);                                                            // to lower the operation command

        if (strcmp(operation, OPEN) == 0)
        {
            if (argCount != 2) // check if all required commands are present.
            {
                printf("Missing Filename. Expecting: OPEN <FILE_NAME>\n");
                continue;
            }

            numRecords = open(key, isHash); // calling the function and storing the number of records
            if (numRecords == -1)
            {
                printf("Failed to open the file. %d\n", numRecords);
                continue;
            }
        }

        else if (strcmp(operation, SAVE) == 0)
        {
            if (argCount != 2)
            {
                printf("Missing Filename. Expecting: SAVE <FILE_NAME>\n");
                continue;
            }
            int result = save(key, isHash);
            if (result != 0)
            {
                printf("Failed to save the file. %d\n", result);
                continue;
            }
        }

        else if (strcmp(operation, UPDATE) == 0)
        {
            if (argCount != 3)
            {
                printf("Invalid number of arguments for UPDATE. Expecting: UPDATE <KEY> <NEW_VALUE>\n");
                continue;
            }

            int result = update(key, value, isHash);

            if (result != 0)
            {
                printf("Failed to update the key. %d\n", result);
                continue;
            }
        }

        else if (strcmp(operation, QUERY) == 0)
        {
            int result = query(numRecords, key, isHash);
            if (result == 0)
            {
                // Query was successful
                printf("Query executed successfully.\n");
            }
            else
            {
                // Query failed
                printf("Query failed. The key '%s' was not found in the database.\n", key);
            }
        }

        else if (strcmp(operation, EXIT) == 0)
        {
            break;
        }
        else
        {
            continue;
        }
    }
    return 0;
}
