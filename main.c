#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "commands.h"
#define OPEN "open"
#define SAVE "save"

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
    char choice[MAX_CHAR_LEN];
    struct kvPair table[MAX_LEN];
    char operation[MAX_CHAR_LEN], key[MAX_CHAR_LEN], value[MAX_CHAR_LEN];
    while (1)
    {
        printf("Enter Your Choice:\n");
        fgets(choice, MAX_CHAR_LEN, stdin);
        sscanf(choice, "%s %s %s", operation, key, value);
        char *loweredOperation = lower(operation);
        if (strcmp(loweredOperation, OPEN) == 0)
        {
            int result = open(table);
            if (result != 0)
            {
                printf("Failed to open the file. %d\n", result);
                return 1;
            }
        }
        else if (strcmp(loweredOperation, SAVE) == 0)
        {
            int result = save(table);
            if (result != 0)
            {
                printf("Failed to save the file. %d\n", result);
                return 1;
            }
        }
        // add your commands here...
        // to access data, simply use the table variable.
        else
        {
            return 0;
        }
    }
    return 0;
}
