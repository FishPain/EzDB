#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "commands.h"

int main() {
    int result = insert();
    printf("Result of insert: %d\n", result);

    result = query();
    printf("Result of query: %d\n", result);

    return 0;
}
