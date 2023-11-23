#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1000

void runTest(int isHash)
{
    FILE *expectedFile, *outputFile;
    char expectedFileName[] = "test/expected_hash_output.txt";
    char outputFileName[] = "test/test_output.txt";

    if (!isHash)
         strcpy(expectedFileName, "test/expected_output.txt");

    expectedFile = fopen(expectedFileName, "r");
    outputFile = fopen(outputFileName, "r");

    if (expectedFile == NULL || outputFile == NULL)
    {
        printf("Error opening files.\n");
        return;
    }

    char expectedLine[MAX_LINE_LENGTH];
    char outputLine[MAX_LINE_LENGTH];

    int lineCount = 1;
    while (fgets(expectedLine, MAX_LINE_LENGTH, expectedFile) != NULL &&
           fgets(outputLine, MAX_LINE_LENGTH, outputFile) != NULL)
    {
        // Compare lines
        if (strcmp(expectedLine, outputLine) != 0)
        {
            printf("Difference found at line %d:\n", lineCount);
            printf("Expected: %s", expectedLine);
            printf("Got     : %s", outputLine);
        }
        lineCount++;
    }

    // Check if one file has more lines than the other
    if (fgets(expectedLine, MAX_LINE_LENGTH, expectedFile) != NULL ||
        fgets(outputLine, MAX_LINE_LENGTH, outputFile) != NULL)
    {
        printf("Files have different line counts.\n");
    }
    else
    {
        printf("Files line count matches.\n");
    }

    // cleanup
    system("rm -r test/test_output.txt");
    fclose(expectedFile);
    fclose(outputFile);
    return;
}

int main()
{
    int isHash = 0;
    printf("\n---RUNNING LINEAR SEARCH---\n");
    system("./ezdb < test/test.txt > test/test_output.txt");
    printf("Generating test_output.txt\n");
    sleep(2);
    printf("test_output.txt generated\n");
    runTest(isHash);
    printf("---LINEAR SEARCH COMPLETED---\n");
    printf("\n");
    isHash = 1;
    printf("\n---RUNNING HASHTABLE---\n");
    system("./ezdb -h < test/test.txt > test/test_output.txt");
    printf("Generating test_output.txt\n");
    sleep(2);
    printf("test_output.txt generated\n");
    runTest(isHash);
    printf("---HASHTABLE COMPLETED---\n");
    printf("\n");
    return 0;
}
