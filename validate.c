#include "validate.h"

bool validateDate(char date[]) {
    int day, month, year;
    char *token = strtok(date, "/");
    int count = 0;
    while (token != NULL) {
        if (count == 0) {
            day = atoi(token);
        } else if (count == 1) {
            month = atoi(token);
        } else if (count == 2) {
            year = atoi(token);
        }
        token = strtok(NULL, "/");
        count++;
    }

    if (day < 1 || day > 31) {
        printf("Invalid day.\n");
        return false;
    }

    if (month < 1 || month > 12) {
        printf("Invalid month.\n");
        return false;
    }

    if (year < 1970 || year > 2024) {
        printf("Invalid year.\n");
        return false;
    }

    return true;
}

bool checkDescription(const char *input)
{
    // Check if the input is empty or contains only whitespace characters
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] != ' ' && input[i] != '\t')
        {
            return true;
        }
    }
    printf("Description cannot be empty.\n");
    return false;
}