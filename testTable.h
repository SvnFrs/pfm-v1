#include <cjson/cJSON.h>

extern void createTable();
extern void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableBody(cJSON *root, int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableSeparator(int columnCount, int columnWidths[]);
extern int* calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[]);