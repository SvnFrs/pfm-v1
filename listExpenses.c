#include "listExpenses.h"

// Default column names and widths
char *columnNames[] = {"Year", "Month", "Day", "ID", "Amount", "    Category", "  Description"};
int columnWidths[7];
char year[80], month[80], day[80], ID[80], category[80], description[80], money[80], des[80];
long amount;

// Struct to store the start and end date
struct Date
{
    char day[80];
    char month[80];
    char year[80];
} startDate, endDate;

int getChoice(const char *prompt, int min, int max)
{
    int choice;
    int isValidChoice = 0;

    do
    {
        printf("%s", prompt);
        if (scanf("%d", &choice) != 1 || getchar() != '\n' || choice < min || choice > max)
        {
            printf("Invalid input. Please enter a valid choice between %d and %d.\n", min, max);
            isValidChoice = 0;
            while (getchar() != '\n')
                ; // Clear the input buffer
        }
        else
        {
            isValidChoice = 1;
        }
    } while (!isValidChoice);

    return choice;
}

int getInput(const char *prompt, int min, int max)
{
    int value;
    int isValidInput = 0;

    do
    {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1 || value < min || value > max)
        {
            printf("Invalid input. Please enter a valid value between %d and %d.\n", min, max);
            isValidInput = 0;
            while (getchar() != '\n')
                ; // Clear the input buffer
        }
        else
        {
            isValidInput = 1;
        }
    } while (!isValidInput);

    return value;
}

int yearInput()
{
    const char *prompt = "Enter the year: ";
    int minYear = 1970;
    int maxYear = 2024;
    return getInput(prompt, minYear, maxYear);
}

int monthInput()
{
    const char *prompt = "Enter the month: ";
    int minMonth = 1;
    int maxMonth = 12;
    return getInput(prompt, minMonth, maxMonth);
}

int listExpenses()
{
    system("./new.sh");
    int choice, invalidChoice;

    do
    {
        invalidChoice = 0; // Reset the flag for each iteration
        printListExpensesMenu();
        if (scanf("%d", &choice) != 1 || getchar() != '\n')
        {
            // If scanf fails to read an integer
            printf("Invalid input. Please enter a valid choice.\n");
            invalidChoice = 1;
            // Clear the input buffer to prevent an infinite loop on invalid input
            while (getchar() != '\n')
                ;
            continue;
        }

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

    } while (choice > 5 || invalidChoice == 1);

    return 0;
}

void printListExpensesMenu()
{
    printf("Choose an option:\n");
    printf("1. Monthly\n");
    printf("2. Quarterly\n");
    printf("3. Yearly\n");
    printf("4. All\n");
    printf("5. Custom\n");
    printf("Your choice: ");
}

void printMonthlyExpenses()
{
    int year = yearInput();
    int month = monthInput();

    // Load and parse the JSON data
    FILE *fp = fopen("data/Cache.json", "r");
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
                        bool expensesFound = createTableBodyMonthly(yearObj, monthObj, 7, columnNames, columnWidths);

                        if (expensesFound)
                        {
                            calculateColumnWidths(7, columnNames, columnWidths);
                            createTableHeader(7, columnNames, columnWidths);
                            createTableBodyMonthly(yearObj, monthObj, 7, columnNames, columnWidths);
                            cJSON_Delete(root);
                        }
                        else
                        {
                            printf("No expenses available in this month.\n");
                        }
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

bool createTableBodyMonthly(cJSON *yearObj, cJSON *monthObj, int columnCount, char *columnNames[], int columnWidths[])
{
    int padding = 6;
    // calculate spaces based on padding
    char spaces[padding + 1];

    for (int i = 0; i < padding; i++)
    {
        spaces[i] = ' ';
    }
    spaces[padding] = '\0';

    bool expensesPrinted = false; // Initialize a flag

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

            strcpy(money, abbreviateMoney(amount));

            // Print the expense information in the table
            printf("|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|\n",
                   columnWidths[0], year, spaces,
                   columnWidths[1], month, spaces,
                   columnWidths[2], day, spaces,
                   columnWidths[3], ID, spaces,
                   columnWidths[4], money, spaces,
                   columnWidths[5], category, spaces,
                   columnWidths[6], description, spaces);

            createTableSeparator(7, columnWidths);

            expensesPrinted = true; // Set the flag to true

            expenseObj = expenseObj->next;
        }

        dayObj = dayObj->next;
    }

    return expensesPrinted; // Return the flag
}

void printQuarterlyExpenses()
{
    int year = yearInput();
    int quarter = printQuarterlyChoice();

    // Load and parse the JSON data
    FILE *fp = fopen("data/Cache.json", "r");
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
    int padding = 6;
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
    const char *prompt = "Choose a quarter:\n1. Q1\n2. Q2\n3. Q3\n4. Q4\nYour choice: ";
    int minChoice = 1;
    int maxChoice = 4;
    return getChoice(prompt, minChoice, maxChoice);
}

void printYearlyExpenses()
{
    int year = yearInput();

    // Load and parse the JSON data
    FILE *fp = fopen("data/Cache.json", "r");
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
    int padding = 6;
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
    FILE *fp = fopen("data/Cache.json", "r");
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
    int padding = 6;
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

                    strcpy(money, abbreviateMoney(amount));
                    strcpy(des, abbreviateDescription(description));

                    // Print the expense information in the table
                    printf("|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|\n",
                           columnWidths[0], year, spaces,
                           columnWidths[1], month, spaces,
                           columnWidths[2], day, spaces,
                           columnWidths[3], ID, spaces,
                           columnWidths[4], money, spaces,
                           columnWidths[5], category, spaces,
                           columnWidths[6], des, spaces);

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
    getStartDateInput();
    getEndDateInput();

    // Load and parse the JSON data
    FILE *fp = fopen("data/Cache.json", "r");
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
    int padding = 6;
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

                                strcpy(money, abbreviateMoney(amount));

                                // Print the expense information in the table
                                printf("|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|%*s%s|\n",
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

void getStartDateInput()
{
    const char *prompt = "Enter the start date (DD/MM/YYYY): ";
    char startDatee[11];

    do
    {
        printf("%s", prompt);
        scanf("%s", startDatee);
    } while (!validateDate(startDatee));
}

void getEndDateInput()
{
    const char *prompt = "Enter the end date (DD/MM/YYYY): ";
    char endDatee[11];

    do
    {
        printf("%s", prompt);
        scanf("%s", endDatee);
    } while (!validateDate(endDatee) || !validateEndDateVSStartDate());
}

void separateStartDate(char date[])
{
    char *token = strtok(startDate.day, "/");
    int count = 0;
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

void separateEndDate(char date[])
{
    char *token = strtok(endDate.day, "/");
    int count = 0;
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

bool validateEndDateVSStartDate()
{
    if (strcmp(endDate.year, startDate.year) < 0)
    {
        printf("End date cannot be earlier than start date.\n");
        return false;
    }
    else if (strcmp(endDate.year, startDate.year) == 0)
    {
        if (strcmp(endDate.month, startDate.month) < 0)
        {
            printf("End date cannot be earlier than start date.\n");
            return false;
        }
        else if (strcmp(endDate.month, startDate.month) == 0)
        {
            if (strcmp(endDate.day, startDate.day) < 0)
            {
                printf("End date cannot be earlier than start date.\n");
                return false;
            }
        }
    }
    return true;
}

char *abbreviateMoney(long amount)
{
    const char *suffixes[] = {"", "k", "m", "b"};
    int index = 0;

    while (amount >= 1000 && index < sizeof(suffixes) / sizeof(suffixes[0]) - 1)
    {
        amount /= 1000;
        index++;
    }

    char *result = (char *)malloc(10 * sizeof(char));
    snprintf(result, 10, "%ld%s", amount, suffixes[index]);

    return result;
}

char *abbreviateDescription(const char *description)
{
    size_t descriptionLength = strlen(description);

    if (descriptionLength <= 16)
    {
        // No need to abbreviate, return a copy of the original description
        return strdup(description);
    }
    else
    {
        // Abbreviate the description
        char *result = (char *)malloc(20 * sizeof(char));
        snprintf(result, 17, "%.13s...", description);
        return result;
    }
}