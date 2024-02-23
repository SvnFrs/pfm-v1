extern int listStatistics();
extern void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]);
extern void statisticizeExpensesYearly(cJSON *yearObj, int columnCount, char *columnNames[], int columnWidths[]);
extern void statisticizeExpensesMonthly(cJSON *yearObj, cJSON *monthObj, int columnCount, char *columnNames[], int columnWidths[]);