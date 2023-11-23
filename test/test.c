#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1000

int main() {
    system("./ezdb < test/test.txt > test/test_output.txt");
    printf("Pausing for 2 seconds to wait for test to complete.\n");
    sleep(2);
    printf("Test completed.\n");

    FILE *expectedFile, *outputFile;
    char expectedFileName[] = "test/expected_output.txt";
    char outputFileName[] = "test/test_output.txt";

    expectedFile = fopen(expectedFileName, "r");
    outputFile = fopen(outputFileName, "r");

    if (expectedFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char expectedLine[MAX_LINE_LENGTH];
    char outputLine[MAX_LINE_LENGTH];

    int lineCount = 1;
    while (fgets(expectedLine, MAX_LINE_LENGTH, expectedFile) != NULL &&
           fgets(outputLine, MAX_LINE_LENGTH, outputFile) != NULL) {
        // Compare lines
        if (strcmp(expectedLine, outputLine) != 0) {
            printf("Difference found at line %d:\n", lineCount);
            printf("Expected: %s", expectedLine);
            printf("Got     : %s", outputLine);
        }
        lineCount++;
    }

    // Check if one file has more lines than the other
    if (fgets(expectedLine, MAX_LINE_LENGTH, expectedFile) != NULL ||
        fgets(outputLine, MAX_LINE_LENGTH, outputFile) != NULL) {
        printf("Files have different line counts.\n");
    } else {
        printf("Files line count matches.\n");
    }

    // cleanup
    system("rm -r test/test_output.txt");
    fclose(expectedFile);
    fclose(outputFile);

    return 0;
}
