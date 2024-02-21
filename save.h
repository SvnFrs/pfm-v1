#include <stdbool.h>
#include <cjson/cJSON.h>
extern bool isLeapYear(int year);
extern int getLastDayOfMonth(int month, int year);
extern void generateSkeletonDays(cJSON *monthObj, int lastDay);
extern int testSave(char day[80], char month[80], char year[80], char category[80], char description[80], long amount);