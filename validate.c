#include "validate.h"

// Function to check if a year is a leap year
bool isLeapYear(int year)
{
    if (year % 4 != 0)
    {
        return false;
    }
    else if (year % 100 != 0)
    {
        return true;
    }
    else if (year % 400 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Function to get the last day of a month in a specific year
int getLastDayOfMonth(int month, int year)
{
    int lastDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
    {
        return 29;
    }
    return lastDays[month - 1];
}

bool validateDate(char date[])
{
    int day, month, year;
    char *token = strtok(date, "/");
    int count = 0;
    while (token != NULL)
    {
        if (count == 0)
        {
            day = atoi(token);
        }
        else if (count == 1)
        {
            month = atoi(token);
        }
        else if (count == 2)
        {
            year = atoi(token);
        }
        token = strtok(NULL, "/");
        count++;
    }

    if (count != 3)
    {
        printf("Invalid input. Please enter a valid date in the format dd/mm/yyyy.\n");
        return false;
    }

    if (day < 1 || day > 31)
    {
        printf("Invalid day. Please enter a valid choice between 1 and 31\n");
        return false;
    }

    if (month < 1 || month > 12)
    {
        printf("Invalid month. Please enter a valid choice between 1 and 12\n");
        return false;
    }

    if (year < 1970 || year > 2024)
    {
        printf("Invalid input. Please enter a valid choice between 1970 and 2024.\n");
        return false;
    }

    int lastDayOfMonth = getLastDayOfMonth(month, year);
    if (day > lastDayOfMonth)
    {
        printf("Invalid day. The selected month does not have %d days.\n", day);
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

bool checkDataFileExists()
{
    FILE *fp = fopen("data/Cache.json", "r");
    FILE *temp = fopen("data/Expenses.json", "r");
    if (fp != NULL && temp != NULL)
    {
        fclose(fp);
        return true;
    }
    
    printf("Error: The data file does not exist. Please enter expenses first.\n");
    return false;
}