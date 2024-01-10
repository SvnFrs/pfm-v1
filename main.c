#include <stdio.h>
#include <time.h>
#include <cjson/cJSON.h>
void printMenu();
int fun(char date[]);
int main()
{
    time_t rawtime;
    struct tm *info;
    char buffer[80];

    time(&rawtime);

    info = localtime(&rawtime);

    strftime(buffer, 80, "%x - %I:%M%p", info);
    printf("|%s|\n", buffer);
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
            fun(buffer);
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

int fun(char date[])
{
    printf("%s", date);
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "Date", date);
    char *json_str = cJSON_Print(json);

    // write the JSON string to a file
    FILE *fp = fopen("data/expenses.json", "w");
    if (fp == NULL)
    {
        printf("Error: Unable to open the file.\n");
        return 1;
    }
    printf("%s\n", json_str);
    fputs(json_str, fp);
    fclose;
    // free the JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);
    return 0;
}