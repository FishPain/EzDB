#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "commands.h"
#include "helper.h"
#include "table.h"

struct phonebook *table[MAX_TABLE_SIZE];

int main(int argc, char *argv[])
{
    char choice[MAX_CHAR_LEN];
    char operation[MAX_CHAR_LEN], key[MAX_CHAR_LEN], value[MAX_CHAR_LEN];
    int numRecords = 0;

    int isHash = getFlag(argc, argv); // feature flag for hashtable. Default to 0;

    printDeclaration(); // print student declaration

    if (isHash)
        initTable();

    while (1)
    {
        printf("Enter Your Choice (%s):\n", isHash ? "Hashtable" : "Linear Search");
        fgets(choice, MAX_CHAR_LEN, stdin);                               // get the user input
        int argCount = sscanf(choice, "%s %s %s", operation, key, value); // split user input into 3 variables
        lower(operation);                                                 // to lower the operation command

        if (strcmp(operation, OPEN) == 0)
        {
            if (argCount != 2) // check if all required commands are present.
            {
                printf("Missing Filename. Expecting: OPEN <FILE_NAME>\n");
                continue;
            }

            numRecords = open(key, isHash); // calling the function and storing the number of records

            if (numRecords == -1) // check if the function failed to open the file.
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
            if (argCount != 2)
            {
                printf("Invalid number of arguments for Query. Expecting: QUERY <KEY>\n");
                continue;
            }

            int result = query(numRecords, key, isHash);

            if (result != 0)
            {
                // Query failed
                printf("Query failed. The key '%s' was not found in the database.\n", key);
            }
            continue;
        }

        else if (strcmp(operation, INSERT) == 0)
        {
            if (argCount != 3)
            {
                printf("Invalid number of arguments for INSERT. Expecting: INSERT <KEY> <VALUE>\n");
                continue;
            }

            int result = insert(&numRecords, key, value, isHash);

            if (result != 0)
            {
                printf("Failed to insert record %d\n", result);
                continue;
            }
        }

        else if (strcmp(operation, DELETE) == 0)
        {
            if (argCount != 2)
            {
                printf("Invalid number of arguments for DELETE. Expecting: DELETE <KEY>\n");
                continue;
            }

            int result = del(&numRecords, key, isHash);

            if (result != 0)
            {
                printf("Failed to delete record %d\n", result);
                continue;
            }
        }

        else if (strcmp(operation, SHOW) == 0 && strcmp(lower(key), ALL) == 0)
        {
            int result = showAll(table);
            if (result == 0)
            {
                // Query was successful
                printf("SHOW ALL executed successfully.\n");
            }
            else
            {
                // Query failed
                printf("SHOW ALL failed. Records could not be found.\n");
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
