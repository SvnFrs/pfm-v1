#include <stdio.h>
#include <time.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
void printMenu();
// int fun(char date[]);
void enterExpenses();
void printDateChoice();
char *getDate();
char *chooseDate();
int main()
{
    
    int choice, invalidChoice;
    do
    {
        invalidChoice = 0; // Reset the flag for each iteration
        printMenu();
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            // If scanf fails to read an integer
            printf("Invalid input. Please enter a valid integer.\n");
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
            break;
        case 3:
            printf("Statistic total expenses\n");
            break;
        case 4:
            printf("Exit\n");
            break;
        default:
            printf("Invalid choice\n");
            invalidChoice = 1;
            break;
        }
    } while (choice > 4 || invalidChoice == 1);

    return 0;
}

void printMenu()
{
    printf("Personal Finance Management\n");
    printf("1. Enter expenses\n");
    printf("2. List expenses\n");
    printf("3. Statistic total expenses\n");
    printf("4. Exit\n");
}


void enterExpenses() {
    printDateChoice();

}
void printDateChoice() {
    printf("What day should it be?\n");
    printf("1. Today\n");
    printf("2. Other\n");
    printf("Your choice:");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        char *today = getDate();
        printf("Today is %s\n", today);
        break;
    case 2:
        char *notToday = chooseDate();
        printf("You choose %s\n", notToday);
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}

char *getDate() {
    time_t rawtime;
    struct tm *info;
    char *buffer = (char *)malloc(80 * sizeof(char)); // Allocate dynamic memory

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, 80, "%d/%m/%Y", info);

    return buffer;
}

char *chooseDate() {
    char *date = (char *)malloc(80 * sizeof(char)); // Allocate dynamic memory

    if (date == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter date (dd/mm/yyyy): ");
    scanf("%s", date);

    return date;
}


// int fun(char date[])
// {
//     printf("%s", date);
//     cJSON *json = cJSON_CreateObject();
//     cJSON_AddStringToObject(json, "Date", date);
//     char *json_str = cJSON_Print(json);

//     // write the JSON string to a file
//     FILE *fp = fopen("data/expenses.json", "w");
//     if (fp == NULL)
//     {
//         printf("Error: Unable to open the file.\n");
//         return 1;
//     }
//     printf("%s\n", json_str);
//     fputs(json_str, fp);
//     fclose;
//     // free the JSON string and cJSON object
//     cJSON_free(json_str);
//     cJSON_Delete(json);
//     return 0;
// }