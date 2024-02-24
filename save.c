#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

// Function to check if a year is a leap year
bool isLeapYear(int year) {
    if (year % 4 != 0) {
        return false;
    } else if (year % 100 != 0) {
        return true;
    } else if (year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}

// Function to get the last day of a month in a specific year
int getLastDayOfMonth(int month, int year) {
    int lastDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return lastDays[month - 1];
}

// Function to generate a skeleton of days for a month
void generateSkeletonDays(cJSON *monthObj, int lastDay) {
    for (int day = 1; day <= lastDay; day++) {
        char dayStr[3];
        snprintf(dayStr, sizeof(dayStr), "%02d", day);
        cJSON_AddObjectToObject(monthObj, dayStr);
    }
}

int save(char day[80], char month[80], char year[80], char category[80], char description[80], long amount) {
    cJSON *root = NULL;
    FILE *fp = fopen("testExpenses.json", "r");

    if (fp != NULL) {
        // Load existing JSON data from the file
        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (file_size > 0) {
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
            // The file is empty, create a new JSON structure
            root = cJSON_CreateObject();
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

        // Generate a skeleton of months for the year
        for (int month = 1; month <= 12; month++) {
            char monthStr[3];
            snprintf(monthStr, sizeof(monthStr), "%02d", month);
            cJSON *monthObj = cJSON_CreateObject();
            cJSON_AddItemToObject(yearObj, monthStr, monthObj);

            // Generate a skeleton of days for the month
            int lastDay = getLastDayOfMonth(month, atoi(year));
            generateSkeletonDays(monthObj, lastDay);
        }
    }

    cJSON *monthObj = cJSON_GetObjectItem(yearObj, month);
    if (monthObj == NULL) {
        printf("Error: The specified month '%s' does not exist.\n", month);
        cJSON_Delete(root);
        return 1;
    }

    cJSON *dayObj = cJSON_GetObjectItem(monthObj, day);
    if (dayObj == NULL) {
        printf("Error: The specified day '%s' does not exist.\n", day);
        cJSON_Delete(root);
        return 1;
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