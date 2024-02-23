#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include "testCal.h"
#include "table.h"

char *columnNames[] = {"Year", "Month", "Status", "Amount"};
int columnWidths[7];
char year[80], month[80], day[80], ID[80], status[80];
char* exist = "A";
char* notExist = "N/A";
long amount;

int listStatistics()
{   int year;
    printf("List expenses statistics\n");
    printf("Enter the year: ");
    scanf("%d", &year);

    // Load and parse the JSON data
    FILE *fp = fopen("testCache.json", "r");
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (file_size > 0)
        {
            char *json_str = (char *)malloc(file_size + 1);
            fread(json_str, 1, file_size, fp);
            fclose(fp);

            cJSON *root = cJSON_Parse(json_str);
            free(json_str);

            if (root != NULL)
            {
                char yearStr[5];
                snprintf(yearStr, sizeof(yearStr), "%d", year);
                cJSON *yearObj = cJSON_GetObjectItem(root, yearStr);
                if (yearObj != NULL)
                {
                    calculateColumnWidths(4, columnNames, columnWidths);
                    createTableHeader(4, columnNames, columnWidths);
                    statisticizeExpensesYearly(yearObj, 4, columnNames, columnWidths);
                }
                else
                {
                    printf("No expenses available in this year.\n");
                }
                cJSON_Delete(root);
            }
            else
            {
                printf("Error: Failed to parse JSON data.\n");
            }
        }
        else
        {
            printf("No data available.\n");
        }
    }
    else
    {
        printf("Error: Failed to open the file.\n");
    }    
}

void statisticizeExpensesMonthly(cJSON *yearObj, cJSON *monthObj, int columnCount, char *columnNames[], int columnWidths[]) {
    int padding = 5;
    // calculate spaces based on padding
    char spaces[padding + 1];

    for (int i = 0; i < padding; i++)
    {
        spaces[i] = ' ';
    }
    spaces[padding] = '\0';

    cJSON *dayObj = monthObj->child;
    while (dayObj != NULL)
    {
        cJSON *expenseObj = dayObj->child;
        while (expenseObj != NULL)
        {
            // Extract the expense information
            strcpy(year, yearObj->string);
            strcpy(month, monthObj->string);
            strcpy(day, dayObj->string);
            strcpy(ID, expenseObj->string);

            cJSON *amountObj = cJSON_GetObjectItem(expenseObj, "amount");
            if (amountObj != NULL)
            {
                amount = amountObj->valueint;
            }

            // Print the expense information in the table
            printf("|%*s%s|%*s%s|%*s%s|%*ld%s|\n",
                   columnWidths[0], year, spaces,
                   columnWidths[1], month, spaces,
                   columnWidths[2], status, spaces,
                   columnWidths[3], amount, spaces);

            createTableSeparator(4, columnWidths);

            expenseObj = expenseObj->next;
        }

        dayObj = dayObj->next;
    }
}

void statisticizeExpensesYearly(cJSON *yearObj, int columnCount, char *columnNames[], int columnWidths[]) {
    int padding = 5;
    // calculate spaces based on padding
    char spaces[padding + 1];

    for (int i = 0; i < padding; i++)
    {
        spaces[i] = ' ';
    }
    spaces[padding] = '\0';

    cJSON *monthObj = yearObj->child;
    while (monthObj != NULL)
    {
        statisticizeExpensesMonthly(yearObj, monthObj, 4, columnNames, columnWidths);
        monthObj = monthObj->next;
    }
}

int main() {
    listStatistics();
    return 0;
}
