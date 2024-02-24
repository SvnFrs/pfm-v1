#include "listExpenses.h"

// Default column names and widths
char *columnNames[] = {"Year", "Month", "Day", "ID", "Amount", "Category", "Description"};
int columnWidths[7];
char year[80], month[80], day[80], ID[80], category[80], description[80];
long amount;

// Struct to store the start and end date
struct Date
{
    char day[80];
    char month[80];
    char year[80];
} startDate, endDate;

int listExpenses()
{
    printf("List expenses\n");
    printf("Choose an option:\n");
    printf("1. Print monthly expenses\n");
    printf("2. Print quarterly expenses\n");
    printf("3. Print yearly expenses\n");
    printf("4. Print all expenses\n");
    printf("5. Print custom expenses\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printMonthlyExpenses();
        break;
    case 2:
        printQuarterlyExpenses();
        break;
    case 3:
        printYearlyExpenses();
        break;
    case 4:
        printAllExpenses();
        break;
    case 5:
        printCustomExpenses();
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}

void printMonthlyExpenses()
{
    int year, month;
    printf("Enter the year: ");
    scanf("%d", &year);
    printf("Enter the month: ");
    scanf("%d", &month);

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
                    char monthStr[3];
                    snprintf(monthStr, sizeof(monthStr), "%02d", month);
                    cJSON *monthObj = cJSON_GetObjectItem(yearObj, monthStr);
                    if (monthObj != NULL)
                    {
                        calculateColumnWidths(7, columnNames, columnWidths);
                        createTableHeader(7, columnNames, columnWidths);
                        createTableBodyMonthly(yearObj, monthObj, 7, columnNames, columnWidths);
                    }
                    else
                    {
                        printf("No expenses available in this month.\n");
                    }
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

void createTableBodyMonthly(cJSON *yearObj, cJSON *monthObj, int columnCount, char *columnNames[], int columnWidths[])
{
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

            cJSON *categoryObj = cJSON_GetObjectItem(expenseObj, "category");
            if (categoryObj != NULL)
            {
                strcpy(category, categoryObj->valuestring);
            }

            cJSON *descriptionObj = cJSON_GetObjectItem(expenseObj, "description");
            if (descriptionObj != NULL)
            {
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
}

void printQuarterlyExpenses()
{
    int quarter, year;
    printf("Enter the year: ");
    scanf("%d", &year);
    quarter = printQuarterlyChoice();

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
                    cJSON *startMonthObj, *endMonthObj;
                    int startMonth, endMonth;

                    switch (quarter)
                    {
                    case 1:
                        startMonth = 1;
                        endMonth = 3;
                        break;
                    case 2:
                        startMonth = 4;
                        endMonth = 6;
                        break;
                    case 3:
                        startMonth = 7;
                        endMonth = 9;
                        break;
                    case 4:
                        startMonth = 10;
                        endMonth = 12;
                        break;
                    default:
                        printf("Invalid quarter choice.\n");
                        cJSON_Delete(root);
                        return;
                    }

                    calculateColumnWidths(7, columnNames, columnWidths);
                    createTableHeader(7, columnNames, columnWidths);
                    createTableBodyQuarterly(yearObj, startMonth, endMonth, 7, columnNames, columnWidths);
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

void createTableBodyQuarterly(cJSON *yearObj, int startMonth, int endMonth, int columnCount, char *columnNames[], int columnWidths[])
{
    int padding = 5;
    char spaces[padding + 1];
    for (int i = 0; i < padding; i++)
    {
        spaces[i] = ' ';
    }
    spaces[padding] = '\0';

    char startMonthStr[3], endMonthStr[3];
    snprintf(startMonthStr, sizeof(startMonthStr), "%02d", startMonth);
    snprintf(endMonthStr, sizeof(endMonthStr), "%02d", endMonth);

    cJSON *monthObj = yearObj->child;
    while (monthObj != NULL)
    {
        if (strcmp(monthObj->string, startMonthStr) >= 0 && strcmp(monthObj->string, endMonthStr) <= 0)
        {
            createTableBodyMonthly(yearObj, monthObj, 7, columnNames, columnWidths);
        }
        monthObj = monthObj->next;
    }
}

int printQuarterlyChoice()
{
    printf("Choose a quarter:\n");
    printf("1. Q1\n");
    printf("2. Q2\n");
    printf("3. Q3\n");
    printf("4. Q4\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

void printYearlyExpenses()
{
    int year;
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
                    calculateColumnWidths(7, columnNames, columnWidths);
                    createTableHeader(7, columnNames, columnWidths);
                    createTableBodyYearly(yearObj, 7, columnNames, columnWidths);
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

void createTableBodyYearly(cJSON *yearObj, int columnCount, char *columnNames[], int columnWidths[])
{
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
        createTableBodyMonthly(yearObj, monthObj, 7, columnNames, columnWidths);
        monthObj = monthObj->next;
    }
}

void printAllExpenses()
{
    system("./new.sh");

    calculateColumnWidths(7, columnNames, columnWidths);

    createTableHeader(7, columnNames, columnWidths);

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
                createTableBodyAll(root, 7, columnNames, columnWidths);
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

void createTableBodyAll(cJSON *root, int columnCount, char *columnNames[], int columnWidths[])
{
    int padding = 5;
    // calculate spaces based on padding
    char spaces[padding + 1];

    for (int i = 0; i < padding; i++)
    {
        spaces[i] = ' ';
    }
    spaces[padding] = '\0';
    cJSON *yearObj = root->child;
    while (yearObj != NULL)
    {
        cJSON *monthObj = yearObj->child;
        while (monthObj != NULL)
        {
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

                    cJSON *categoryObj = cJSON_GetObjectItem(expenseObj, "category");
                    if (categoryObj != NULL)
                    {
                        strcpy(category, categoryObj->valuestring);
                    }

                    cJSON *descriptionObj = cJSON_GetObjectItem(expenseObj, "description");
                    if (descriptionObj != NULL)
                    {
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

void printCustomExpenses()
{
    char startDatee[11], endDatee[11];
    printf("Enter the start date (DD-MM-YYYY): ");
    scanf("%s", startDatee);
    printf("Enter the end date (DD-MM-YYYY): ");
    scanf("%s", endDatee);

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
                bool expensesFound = createTableBodyCustom(root, 7, columnNames, columnWidths);

                if (expensesFound)
                {
                    calculateColumnWidths(7, columnNames, columnWidths);
                    createTableHeader(7, columnNames, columnWidths);
                    separateSEDate(startDatee, 1);
                    separateSEDate(endDatee, 2);
                    createTableBodyCustom(root, 7, columnNames, columnWidths);
                    cJSON_Delete(root);
                }
                else
                {
                    printf("No expenses found for the entered period.\n");
                }
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

bool createTableBodyCustom(cJSON *root, int columnCount, char *columnNames[], int columnWidths[])
{
    int padding = 5;
    char spaces[padding + 1];
    for (int i = 0; i < padding; i++)
    {
        spaces[i] = ' ';
    }
    spaces[padding] = '\0';

    cJSON *yearObj = root->child;

    bool expensesPrinted = false; // Initialize a flag
    
    while (yearObj != NULL)
    {
        if (strcmp(yearObj->string, startDate.year) >= 0 && strcmp(yearObj->string, endDate.year) <= 0)
        {
            cJSON *monthObj = yearObj->child;
            while (monthObj != NULL)
            {
                if (strcmp(monthObj->string, startDate.month) >= 0 && strcmp(monthObj->string, endDate.month) <= 0)
                {
                    cJSON *dayObj = monthObj->child;
                    while (dayObj != NULL)
                    {
                        if (strcmp(dayObj->string, startDate.day) >= 0 && strcmp(dayObj->string, endDate.day) <= 0)
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

                                cJSON *categoryObj = cJSON_GetObjectItem(expenseObj, "category");
                                if (categoryObj != NULL)
                                {
                                    strcpy(category, categoryObj->valuestring);
                                }

                                cJSON *descriptionObj = cJSON_GetObjectItem(expenseObj, "description");
                                if (descriptionObj != NULL)
                                {
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

                                expensesPrinted = true; // Set the flag to true
                                
                                expenseObj = expenseObj->next;
                            }
                        }

                        dayObj = dayObj->next;
                    }
                }

                monthObj = monthObj->next;
            }
        }

        yearObj = yearObj->next;
    }
    return expensesPrinted; // Return the flag
}

void separateSEDate(char input[], int choice)
{
    char *token = strtok(input, "/");
    int count = 0;
    if (choice == 1)
    {
        while (token != NULL)
        {
            if (count == 0)
            {
                strcpy(startDate.day, token);
            }
            else if (count == 1)
            {
                strcpy(startDate.month, token);
            }
            else if (count == 2)
            {
                strcpy(startDate.year, token);
            }
            token = strtok(NULL, "/");
            count++;
        }
    }
    else if (choice == 2)
    {
        while (token != NULL)
        {
            if (count == 0)
            {
                strcpy(endDate.day, token);
            }
            else if (count == 1)
            {
                strcpy(endDate.month, token);
            }
            else if (count == 2)
            {
                strcpy(endDate.year, token);
            }
            token = strtok(NULL, "/");
            count++;
        }
    }
}