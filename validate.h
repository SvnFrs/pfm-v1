#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

extern bool isLeapYear(int year);
extern int getLastDayOfMonth(int month, int year);
extern bool validateDate(char date[]);
extern bool checkWhiteSpace(char input[]);
extern bool checkDescription(const char *input);
extern bool checkDataFileExists();