#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]);
extern void createTableSeparator(int columnCount, int columnWidths[]);
extern int *calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[]);