#include <stdio.h>
#include <time.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>
#include "listExpenses.h"
#include "statisticizeExpenses.h"
#include "save.h"
#include "table.h"
#include "validate.h"

void printMenu();
int startProgram();
void enterExpenses();
// void listExpenses();
int printDateChoice();
void printDateChoiceMenu();
void printExpenseAmount();
int printCategoryChoice();
void printCategoryChoiceMenu();
void printDescription();
void separateDate(char date[]);
char *getDate();
char *chooseDate();
int saveExpense();

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

const char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int main()
{
    startProgram();
}

int startProgram()
{
    int choice, invalidChoice, result;
    do
    {
        invalidChoice = 0; // Reset the flag for each iteration
        printMenu();
        printf("Enter your choice: ");

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
            printf("Enter expenses\n");
            enterExpenses();
            break;
        case 2:
            printf("List expenses\n");
            result = listExpenses();
            result == 0 ? startProgram() : printf("Error listing expenses\n"), startProgram();
            break;
        case 3:
            printf("Statistic total expenses\n");
            result = listStatistics();
            result == 0 ? startProgram() : printf("Error listing statistics\n"),  startProgram();
            break;
        case 4:
            printf("Options\n");
            break;
        case 5:
            printf("Thank you for using our software\n");
            break;
        default:
            printf("Invalid choice\n");
            invalidChoice = 1;
            break;
        }
    } while (choice > 5 || invalidChoice == 1);

    return 0;
}

void printMenu()
{
    printf("Personal Finance Management\n");
    printf("1. Enter expenses\n");
    printf("2. List expenses\n");
    printf("3. Statistic total expenses\n");
    printf("4. Options\n");
    printf("5. Exit\n");
}

void enterExpenses()
{
    printDateChoice();
    printExpenseAmount();
    printCategoryChoice();
    printDescription();
    printf("Expense date: %s\n", expense.date);
    printf("Expense amount: %ld\n", expense.amount);
    printf("Expense category: %s\n", expense.category);
    printf("Expense description: %s\n", expense.description);
    separateDate(expense.date);
    // printf("Day: %s\n", date.day);
    // printf("Month: %s\n", date.month);
    // printf("Year: %s\n", date.year);
    // saveExpense();
    // testSave(date.day, date.month, date.year, expense.category, expense.description, expense.amount);
    int result = saveExpense();
    result == 0 ? printf("Expense saved\n") : printf("Error saving expense\n");
    startProgram();
}
int printDateChoice()
{
    int choice, invalidChoice;

    do
    {
        invalidChoice = 0; // Reset the flag for each iteration
        printDateChoiceMenu();
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
            char *today = getDate();

            printf("Today is %s\n", today);
            strcpy(expense.date, today);
            // snprintf(expense.date, sizeof(expense.date), "%s", today);
            free(today);
            break;
        case 2:
            char *notToday = chooseDate();
            // printf("You choose %s\n", notToday);
            strcpy(expense.date, notToday);
            // snprintf(expense.date, sizeof(expense.date), "%s", notToday);
            free(notToday);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice > 2 || invalidChoice == 1);
}

void printDateChoiceMenu()
{
    printf("Choose date\n");
    printf("1. Today\n");
    printf("2. Not today\n");
    printf("Your choice:");
}

void printExpenseAmount()
{
    const char *prompt = "Enter expense amount: ";
    long amount = getInput(prompt, 1, 1000000000);
    expense.amount = amount;
}

int printCategoryChoice()
{
    int choice, invalidChoice;
    do
    {
        invalidChoice = 0; // Reset the flag for each iteration
        printCategoryChoiceMenu();
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
            printf("You choose Food\n");
            strcpy(expense.category, "Food");
            break;
        case 2:
            printf("You choose Transportation\n");
            strcpy(expense.category, "Transportation");
            break;
        case 3:
            printf("You choose Housing\n");
            strcpy(expense.category, "Housing");
            break;
        case 4:
            printf("You choose Entertainment\n");
            strcpy(expense.category, "Entertainment");
            break;
        case 5:
            printf("You choose Other\n");
            strcpy(expense.category, "Other");
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice > 5 || invalidChoice == 1);
}

void printCategoryChoiceMenu()
{
    printf("Choose category\n");
    printf("1. Food\n");
    printf("2. Transportation\n");
    printf("3. Housing\n");
    printf("4. Entertainment\n");
    printf("5. Other\n");
    printf("Your choice:");
}

void printDescription()
{
    const char *prompt = "Enter expense description: ";
    char *temp = (char *)malloc(80 * sizeof(char)); // Allocate dynamic memory

    if (temp == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    bool isValidDescription = false;

    while (!isValidDescription)
    {
        printf("%s", prompt);
        fgets(temp, 80, stdin);

        // Remove trailing newline character
        if (temp[strlen(temp) - 1] == '\n')
            temp[strlen(temp) - 1] = '\0';

        isValidDescription = checkDescription(temp);
    }

    strcpy(expense.description, temp);
    free(temp);
}

char *getDate()
{
    time_t rawtime;
    struct tm *info;
    char *buffer = (char *)malloc(80 * sizeof(char)); // Allocate dynamic memory

    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, 80, "%d/%m/%Y", info);

    return buffer;
}

char *chooseDate()
{
    char *date = (char *)malloc(80 * sizeof(char)); // Allocate dynamic memory
    char tempDate[11];
    const char *prompt = "Enter date (DD/MM/YYYY): ";

    if (date == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        printf("%s", prompt);
        scanf("%s", tempDate);
    } while (!validateDate(tempDate));

    snprintf(date, 11, "%s", tempDate);

    return date;
    free(date);
}

int saveExpense()
{
    // cJSON *json = cJSON_CreateObject();
    // cJSON_AddStringToObject(json, "Date", expense.date);
    // cJSON_AddStringToObject(json, "Category", expense.category);
    // cJSON_AddNumberToObject(json, "Amount", expense.amount);
    // char *json_str = cJSON_Print(json);

    // // write the JSON string to a file
    // FILE *fp = fopen("data/expenses.json", "w");
    // if (fp == NULL)
    // {
    //     printf("Error: Unable to open the file.\n");
    //     return 1;
    // }
    // printf("%s\n", json_str);
    // fputs(json_str, fp);
    // fclose;
    // // free the JSON string and cJSON object
    // cJSON_free(json_str);
    // cJSON_Delete(json);
    // return 0;
    return save(date.day, date.month, date.year, expense.category, expense.description, expense.amount);
}

void separateDate(char input[])
{
    char *token = strtok(input, "/");
    int count = 0;
    while (token != NULL)
    {
        if (count == 0)
        {
            strcpy(date.day, token);
        }
        else if (count == 1)
        {
            strcpy(date.month, token);
        }
        else if (count == 2)
        {
            strcpy(date.year, token);
        }
        token = strtok(NULL, "/");
        count++;
    }
}

// void listExpenses() {
//     printPeriodChoice();
// }

// void printPeriodChoice() {
//     printf("Choose expense period\n");
//     printf("1. Monthly\n");
//     printf("2. Yearly\n");
//     printf("3. All\n");
//     printf("4. Custom\n");
//     printf("Your choice:");
//     int choice;
//     do
//     {
//         if (scanf("%d", &choice) != 1)
//         {
//             // If scanf fails to read an integer
//             printf("Invalid input. Please enter a valid integer.\n");
//             // Clear the input buffer to prevent an infinite loop on invalid input
//             while (getchar() != '\n')
//                 ;
//             continue;
//         }
//     } while (choice > 4);
//     switch (choice)
//     {
//     case 1:
//         printf("You choose Monthly\n");
//         break;
//     case 2:
//         printf("You choose Yearly\n");
//         break;
//     case 3:
//         printf("You choose All\n");
//         break;
//     case 4:
//         printf("You choose Custom\n");
//         break;
//     default:
//         printf("Invalid choice\n");
//         break;
//     }
// }