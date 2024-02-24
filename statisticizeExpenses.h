#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include "table.h"

extern int listStatistics();
extern void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]);
extern void statisticizeExpensesYearly(cJSON *yearObj, int columnCount, char *columnNames[], int columnWidths[]);
extern void statisticizeExpensesMonthly(cJSON *yearObj, cJSON *monthObj, int columnCount, char *columnNames[], int columnWidths[]);