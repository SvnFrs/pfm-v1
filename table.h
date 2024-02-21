#include <cjson/cJSON.h>

extern void printAllExpenses();
extern void printMonthlyExpenses();
extern void printQuarterlyExpenses();
extern void printYearlyExpenses();
extern void printCustomExpenses();
extern void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyAll(cJSON *root, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyMonthly(cJSON *yearObj, cJSON *monthObj, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyQuarterly(cJSON *yearObj, int startMonth, int endMonth, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyYearly(cJSON *yearObj, int columnCount, char *columnNames[], int columnWidths[]);
extern bool createTableBodyCustom(cJSON *root, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableSeparator(int columnCount, int columnWidths[]);
extern int* calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[]);
extern int printQuarterlyChoice();
extern void separateDate();