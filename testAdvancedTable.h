#include <cjson/cJSON.h>

extern void printAllExpenses();
extern void printMonthlyExpenses();
extern void printYearlyExpenses();
extern void printCustomExpenses();
extern void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyAll(cJSON *root, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBodyMonthly(cJSON *yearObj, cJSON *monthObj, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableSeparator(int columnCount, int columnWidths[]);
extern int* calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[]);
