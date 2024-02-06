#include "testSave.h"

#include <stdio.h>
#include <time.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>

int testSave(char day[80], char month[80], char year[80], char category[80], char description[80], long amount) {
    cJSON *root = NULL;
    FILE *fp = fopen("testExpenses.json", "r");

    if (fp != NULL) {
        // Load existing JSON data from the file
        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char *json_str = (char *)malloc(file_size + 1);
        fread(json_str, 1, file_size, fp);
        fclose(fp);

        // Parse the JSON data
        root = cJSON_Parse(json_str);
        free(json_str);

        if (root == NULL) {
            printf("Error: Failed to parse JSON data.\n");
            return 1;
        }
    } else {
        // The file doesn't exist, create a new JSON structure
        root = cJSON_CreateObject();
    }

    // Check if the year/month/day structure already exists
    cJSON *yearObj = cJSON_GetObjectItem(root, year);
    if (yearObj == NULL) {
        yearObj = cJSON_CreateObject();
        cJSON_AddItemToObject(root, year, yearObj);
    }

    cJSON *monthObj = cJSON_GetObjectItem(yearObj, month);
    if (monthObj == NULL) {
        monthObj = cJSON_CreateObject();
        cJSON_AddItemToObject(yearObj, month, monthObj);
    }

    cJSON *dayObj = cJSON_GetObjectItem(monthObj, day);
    if (dayObj == NULL) {
        dayObj = cJSON_CreateObject();
        cJSON_AddItemToObject(monthObj, day, dayObj);
    }

    // Generate a unique ID for the new expense
    char ID[80];
    snprintf(ID, sizeof(ID), "ex%d", cJSON_GetArraySize(dayObj) + 1);

    // Create the new expense object
    cJSON *expense = cJSON_CreateObject();
    cJSON_AddNumberToObject(expense, "amount", amount);
    cJSON_AddStringToObject(expense, "category", category);
    cJSON_AddStringToObject(expense, "description", description);

    // Add the new expense to the existing JSON structure
    cJSON_AddItemToObject(dayObj, ID, expense);

    // Save the updated JSON structure to the file
    char *json_str = cJSON_Print(root);
    fp = fopen("testExpenses.json", "w");
    fprintf(fp, "%s", json_str);
    fclose(fp);

    // Free the JSON structure
    cJSON_Delete(root);

    return 0;
}

void testPrint() {
    FILE *fp = fopen("testExpenses.json", "r");
    char buff[255];
    while (fgets(buff, 255, (FILE*)fp)) {
        printf("%s", buff);
    }
    fclose(fp);
    //
    //
    //
    //
    //
    //
}