#include "table.h"

void createTableHeader(int columnCount, char *columnNames[], int columnWidths[])
{
    int padding = 6;
    // calculate spaces based on padding
    char spaces[padding + 1];

    for (int i = 0; i < padding; i++)
    {
        spaces[i] = ' ';
    }
    // add padding to columnWidths
    for (int i = 0; i < columnCount; i++)
    {
        columnWidths[i] += padding;
    }

    // print headlines consisting of dashes based on columnWidths
    printf("+");
    // also print a plus sign whenever there is a column
    for (int i = 0; i < columnCount; i++)
    {
        for (int j = 0; j < columnWidths[i] + padding; j++)
        {
            printf("-");
        }
        printf("+");
    }

    printf("\n");

    printf("|");

    for (int i = 0; i < columnCount; i++)
    {
        printf("%*s%s|", columnWidths[i], columnNames[i], spaces);
    }
    printf("\n");

    printf("+");

    for (int i = 0; i < columnCount; i++)
    {
        for (int j = 0; j < columnWidths[i] + padding; j++)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

void createTableSeparator(int columnCount, int columnWidths[])
{
    printf("+");
    for (int i = 0; i < columnCount; i++)
    {
        for (int j = 0; j < columnWidths[i] + 6; j++)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

int *calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[])
{
    for (int i = 0; i < columnCount; i++)
    {
        columnWidths[i] = strlen(columnNames[i]);
    }
    return columnWidths;
}
