#include "testSave.h"

#include <stdio.h>
#include <time.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>

int testSave(char day[80], char month[80], char year[80], char category[80], char description[80], long amount) {
    cJSON *root = cJSON_CreateObject();
    char ID[80] = "ex1";
    
    cJSON_AddItemToObject(root, year, cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(root, year), month, cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(root, year), month), day, cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, year), month), day), "expenses", cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, year), month), day), "expenses"), ID, cJSON_CreateObject());
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, year), month), day), "expenses"), ID), "amount", cJSON_CreateNumber(amount));
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, year), month), day), "expenses"), ID), "category", cJSON_CreateString(category));
    cJSON_AddItemToObject(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(cJSON_GetObjectItem(root, year), month), day), "expenses"), ID), "description", cJSON_CreateString(description));

    char *string = cJSON_Print(root);
    FILE *fp = fopen("testExpenses.json", "w");
    fprintf(fp, "%s", string);
    fclose(fp);

    return 0;
}