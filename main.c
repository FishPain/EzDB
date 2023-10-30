#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "commands.h"

char *lower(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }

    return str;
}

int main()
{
    struct kvPair table[MAX_LEN];
    char choice[MAX_CHAR_LEN];
    char operation[MAX_CHAR_LEN], key[MAX_CHAR_LEN], value[MAX_CHAR_LEN];

    while (1)
    {
        printf("Enter Your Choice:\n");
        fgets(choice, MAX_CHAR_LEN, stdin);
        int argCount = sscanf(choice, "%s %s %s", operation, key, value);
        char *loweredOperation = lower(operation);

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
            if (argCount != 2)
            {
                printf("Missing Filename. Expecting: OPEN <FILE_NAME>\n");
                continue;
            }
            int result = open(table, key);
            if (result != 0)
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
        // add your commands here...
        // to access data, simply use the table variable.
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
