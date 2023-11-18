#ifndef HELPER_H
#define HELPER_H

char *lower(char *str);
int compare(const void *tmp1, const void *tmp2);
int printDeclaration();
int getFlag(int argc, char *argv[]);
int isValidPhoneNumber(const char *phoneNumber);
#endif