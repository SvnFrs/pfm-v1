#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include "testCal.h"

int listStatistics()
{
    printf("List expenses statistics\n");
    printf("Choose an option:\n");
    printf("1. Print monthly statistics\n");
    printf("2. Print quarterly statistics\n");
    printf("3. Print yearly statistics\n");
    printf("4. Print all statistics\n");
    printf("5. Print custom statistics\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printMonthlyStatistics();
        break;
    case 2:
        // printQuarterlyStatistics();
        break;
    case 3:
        // printYearlyStatistics();
        break;
    case 4:
        // printAllStatistics();
        break;
    case 5:
        // printCustomStatistics();
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}

void printMonthlyStatistics() {
    int year, month;
    printf("Enter the year: ");
}
