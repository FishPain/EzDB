#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "table.h"
#define HASHTABLE_FLAG "-h"

/**
 * Converts a string to lowercase.
 *
 * @param str The string to be converted to lowercase.
 */
char *lower(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] != '_')
            str[i] = tolower((unsigned char)str[i]);
    return str;
}

/**
 * Comparator function for qsort to compare two phonebook records.
 *
 * @param tmp1 Pointer to the first phonebook record.
 * @param tmp2 Pointer to the second phonebook record.
 * @return An integer less than, equal to, or greater than zero if the first record is found to be less than, equal to, or greater than the second one.
 */
int compare(const void *tmp1, const void *tmp2)
{
    phonebook *data1 = *(phonebook **)tmp1;
    phonebook *data2 = *(phonebook **)tmp2;

    // Check if key (contact name) is the same
    int chCompare = strcmp(data1->name, data2->name);

    if (chCompare == 0)
    {
        // Return the value (number) in ascending order if the key (contact name) is the same
        return strcmp(data1->number, data2->number);
    }
    else
    {
        return chCompare;
    }
}

/**
 * Prints the contents of the declaration file to the console.
 *
 * @return 0 if the operation is successful, -1 otherwise.
 */
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

/**
 * Gets the feature flag based on command-line arguments.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return 1 if the hashtable feature flag is present, 0 otherwise.
 */
int getFlag(int argc, char *argv[])
{
    if (argc != 2) // If no flag is passed when running ezdb, then return 0;
        return 0;
    if (strcmp(argv[1], HASHTABLE_FLAG) == 0)
        return 1;
    return 0;
}

/**
 * Validates an 8-digit phone number represented as a string and starts with 6, 8, or 9.
 *
 * @param phoneNumber A string representing the phone number to be validated.
 * @return 1 if the phoneNumber is a valid 8-digit number starting with 6, 8, or 9, otherwise 0.
 */
int isValidPhoneNumber(const char *phoneNumber)
{
    // Check if the phone number is exactly 8 digits or if the first digit is 6, 8, or 9
    if (
        (strlen(phoneNumber) != 8) ||
        (phoneNumber[0] != '6' && phoneNumber[0] != '8' && phoneNumber[0] != '9'))
        return 0;

    // Check if all characters in the phone number are digits
    for (int i = 0; i < 8; ++i)
    {
        if (!isdigit(phoneNumber[i]))
            return 0;
    }

    return 1;
}
