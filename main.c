#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "commands.h"

char *lower(char *str) // to lower a string.
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i]!= '_')
        {
            str[i] = tolower(str[i]);

        }
    }
    return str;
}


int main()
{
    struct kvPair table[MAX_LEN];
    char choice[MAX_CHAR_LEN];
    char operation[MAX_CHAR_LEN], key[MAX_CHAR_LEN], value[MAX_CHAR_LEN];
    int numRecords = 0;
    
    while (1)
    {
        printf("Enter Your Choice:\n");
        fgets(choice, MAX_CHAR_LEN, stdin); // get the user input
        int argCount = sscanf(choice, "%s %s %s", operation, key, value); // split user input into 3 variables
        // Eg. Req: operation, key, value but only input operation, key -> argCount = 2;
        char *loweredOperation = lower(operation); // to lower the operation command
        if (strcmp(loweredOperation, OPEN) == 0)
        {
            /* OPEN Command
                Takes in OPEN <FILE_NAME> and saves data from file into memory.
                Defined by struct kvPair table[MAX_LEN]

                struct kvPair {
                    char key[MAX_CHAR_LEN];
                    char value[MAX_CHAR_LEN];
                };

            */
            if (argCount != 2) // check if all required commands are present.
            {
                printf("Missing Filename. Expecting: OPEN <FILE_NAME>\n");
                continue;
            }
            numRecords = open(table, key); // calling the function and storing the number of records
            if (numRecords == 0)
            {
                printf("Failed to open the file. %d\n", result);
                continue;
            }
        }
        else if (strcmp(loweredOperation, SAVE) == 0)
        {
            /* SAVE Command
                Takes in SAVE <FILE_NAME> and writes data into file from memory.
                Defined by struct kvPair table[MAX_LEN]

                struct kvPair {
                    char key[MAX_CHAR_LEN];
                    char value[MAX_CHAR_LEN];
                };
            */
            if (argCount != 2)
            {
                printf("Missing Filename. Expecting: SAVE <FILE_NAME>\n");
                continue;
            }
            int result = save(table, key);
            if (result != 0)
            {
                printf("Failed to save the file. %d\n", result);
                continue;
            }
        }
        else if (strcmp(loweredOperation, QUERY) == 0)
        {
            int result = query(table, numRecords, key);
            if (result == 0) {
                // Query was successful
                printf("Query executed successfully.\n");
            } else {
                // Query failed
                printf("Query failed. The key '%s' was not found in the database.\n", key);
            }
        }
            
        else if (strcmp(loweredOperation, EXIT) == 0)
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
