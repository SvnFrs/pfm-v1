#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include "table.h"
#include "validate.h"

extern char *abbreviateMoney(long amount);
extern char *abbreviateDescription(const char *description);
extern int getChoice(const char* prompt, int min, int max);
extern int getInput(const char* prompt, int min, int max);
extern int yearInput();
extern int monthInput();
extern int listExpenses();
extern void printListExpensesMenu();
extern void printAllExpenses();
extern void printMonthlyExpenses();
extern void printQuarterlyExpenses();
extern void printYearlyExpenses();
extern void printCustomExpenses();
extern void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyAll(cJSON *root, int columnCount, char *columnNames[], int columnWidths[]);
extern bool createTableBodyMonthly(cJSON *yearObj, cJSON *monthObj, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyQuarterly(cJSON *yearObj, int startMonth, int endMonth, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyYearly(cJSON *yearObj, int columnCount, char *columnNames[], int columnWidths[]);
extern bool createTableBodyCustom(cJSON *root, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableSeparator(int columnCount, int columnWidths[]);
extern int* calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[]);
extern int printQuarterlyChoice();
extern void separateStartDate();
extern void separateEndDate();
extern void getStartDateInput();
extern void getEndDateInput();
extern bool validateEndDateVSStartDate();
extern bool validateDate();