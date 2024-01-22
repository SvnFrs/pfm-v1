#include <stdio.h>
#include <time.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *filename = "expenses.json";
    struct Expense
    {
        char date[80];
        char category[80];
        char description[80];
        long amount;
    } expense;

    struct Date
    {
        char day[80];
        char month[80];
        char year[80];
    } date;

    const char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September",
    "October", "November", "December"};

    char *tempDay = (char *)malloc(80 * sizeof(char));
    char *tempMonth = (char *)malloc(80 * sizeof(char));
    char *tempYear = (char *)malloc(80 * sizeof(char));

    char *ID = "ex1";

    cJSON *root = cJSON_CreateObject();

    printf("Enter date (DD/MM/YYYY):\n");
    printf("Day: ");
    fgets(tempDay, 80, stdin);
    printf("Month: ");
    fgets(tempMonth, 80, stdin);
    printf("Year: ");
    fgets(tempYear, 80, stdin);

    tempDay[strcspn(tempDay, "\n")] = '\0';
    tempMonth[strcspn(tempMonth, "\n")] = '\0';
    tempYear[strcspn(tempYear, "\n")] = '\0';

    // format year to year_yyyy
    strcpy(date.year, "year_");
    strcat(date.year, tempYear);

    // format month to month_mm
    strcpy(date.month, "month_");
    strcat(date.month, months[atoi(tempMonth) - 1]);

    // format day to day_dd
    strcpy(date.day, "day_");
    strcat(date.day, tempDay);

    // from date to expense.date
    strcpy(expense.date, tempDay);
    strcat(expense.date, "/");
    strcat(expense.date, tempMonth);
    strcat(expense.date, "/");
    strcat(expense.date, tempYear);

    printf("Date: %s\n", expense.date);

    // printf("Day: %s\n", date.day);

    printf("Enter amount: ");
    scanf("%ld", &expense.amount);

    printf("Enter category: ");
    scanf("%s", expense.category);

    printf("Enter description: ");
    scanf("%s", expense.description);

    cJSON_AddItemToObject(root, date.year, cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(root, date.year), date.month, cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(root, date.year), date.month), date.day, cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, date.year), date.month), date.day), "expenses", cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, date.year), date.month), date.day), "expenses"), ID, cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, date.year), date.month), date.day), "expenses"), ID), "amount", cJSON_CreateNumber(expense.amount));
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, date.year), date.month), date.day), "expenses"), ID), "category", cJSON_CreateString(expense.category));
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, date.year), date.month), date.day), "expenses"), ID), "description", cJSON_CreateString(expense.description));

    char *jsonString = cJSON_Print(root);
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%s", jsonString);
    fclose(fp);

    free(tempDay);
    free(tempMonth);
    free(tempYear);

    return 0;

}