#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include "testTable.h"

void createTable() {
    char *columnNames[] = {"Year", "Month", "Day", "ID", "Amount", "Category", "Description"};
    int columnWidths[7];
    calculateColumnWidths(7, columnNames, columnWidths);

    createTableHeader(7, columnNames, columnWidths);

    // Load and parse the JSON data
    FILE *fp = fopen("testCache.json", "r");
    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (file_size > 0) {
            char *json_str = (char *)malloc(file_size + 1);
            fread(json_str, 1, file_size, fp);
            fclose(fp);

            cJSON *root = cJSON_Parse(json_str);
            free(json_str);

            if (root != NULL) {
                createTableBody(root, 7, columnNames, columnWidths);
                cJSON_Delete(root);
            } else {
                printf("Error: Failed to parse JSON data.\n");
            }
        } else {
            printf("No data available.\n");
        }
    } else {
        printf("Error: Failed to open the file.\n");
    }
}

void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]) {
    int padding = 5;
    // calculate spaces based on padding
    char spaces[padding + 1];

    for (int i = 0; i < padding; i++) {
        spaces[i] = ' ';
    }
    // add padding to columnWidths
    for (int i = 0; i < columnCount; i++) {
        columnWidths[i] += padding;
    }

    // print headlines consisting of dashes based on columnWidths
    printf("+");
    // also print a plus sign whenever there is a column
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < columnWidths[i] + padding; j++) {
            printf("-");
        }
        printf("+");
    }

    printf("\n");

    printf("|");

    for (int i = 0; i < columnCount; i++) {
        printf("%*s%s|", columnWidths[i], columnNames[i], spaces);
    }
    printf("\n");

    printf("+");

    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < columnWidths[i] + padding; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

void createTableBody(cJSON *root, int columnCount, char *columnNames[], int columnWidths[]) {
    int padding = 5;
    // calculate spaces based on padding
    char spaces[padding + 1];

    for (int i = 0; i < padding; i++) {
        spaces[i] = ' ';
    }
    // add padding to columnWidths
    // for (int i = 0; i < columnCount; i++) {
        // columnWidths[i] += padding;
    // }
    cJSON *yearObj = root->child;
    while (yearObj != NULL) {
        cJSON *monthObj = yearObj->child;
        while (monthObj != NULL) {
            cJSON *dayObj = monthObj->child;
            while (dayObj != NULL) {
                cJSON *expenseObj = dayObj->child;
                while (expenseObj != NULL) {
                    // Extract the expense information
                    char year[80], month[80], day[80], ID[80], category[80], description[80];
                    long amount;

                    strcpy(year, yearObj->string);
                    strcpy(month, monthObj->string);
                    strcpy(day, dayObj->string);
                    strcpy(ID, expenseObj->string);

                    cJSON *amountObj = cJSON_GetObjectItem(expenseObj, "amount");
                    if (amountObj != NULL) {
                        amount = amountObj->valueint;
                    }

                    cJSON *categoryObj = cJSON_GetObjectItem(expenseObj, "category");
                    if (categoryObj != NULL) {
                        strcpy(category, categoryObj->valuestring);
                    }

                    cJSON *descriptionObj = cJSON_GetObjectItem(expenseObj, "description");
                    if (descriptionObj != NULL) {
                        strcpy(description, descriptionObj->valuestring);
                    }

                    // Print the expense information in the table
                    printf("|%*s%s|%*s%s|%*s%s|%*s%s|%*ld%s|%*s%s|%*s%s|\n",
                            columnWidths[0], year, spaces,
                            columnWidths[1], month, spaces,
                            columnWidths[2], day, spaces,
                            columnWidths[3], ID, spaces,
                            columnWidths[4], amount, spaces,
                            columnWidths[5], category, spaces,
                            columnWidths[6], description, spaces);
                    
                    createTableSeparator(7, columnWidths);

                    expenseObj = expenseObj->next;
                }

                dayObj = dayObj->next;
            }

            monthObj = monthObj->next;
        }

        yearObj = yearObj->next;
    }
}

void createTableSeparator(int columnCount, int columnWidths[]) {
    printf("+");
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < columnWidths[i] + 5; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

// int main() {
//     system("./new.sh");
//     createTable();
//     return 0;
// }


int* calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[]) {
    for (int i = 0; i < columnCount; i++) {
        columnWidths[i] = strlen(columnNames[i]);
    }
    return columnWidths;
}

