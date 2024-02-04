#include <stdio.h>
#include <string.h>

void testTable();
void createTable();
void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]);
int* calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[]);

void testTable() {

}

void createTable() {
    
}

void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]) {
    int padding = 5;
    // calculate spaces based on padding
    char spaces[padding + 1];

    for (int i = 0; i < padding; i++) {
        spaces[i] = ' ';
    }
    // add padding to columnWidths
    for (int i = 0; i < columnCount; i++) {
        columnWidths[i] += padding;
    }

    // print headlines consisting of dashes based on columnWidths
    printf("+");
    // also print a plus sign whenerver there is a column
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < columnWidths[i] + padding; j++) {
            printf("-");
        }
        printf("+");
    }
    
    printf("\n");
    
    printf("|");

    for (int i = 0; i < columnCount; i++) {
        printf("%*s%s|", columnWidths[i], columnNames[i], spaces);
    }
    printf("\n");

    printf("+");
    
    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < columnWidths[i] + padding; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

}

int main() {
    char *columnNames[] = {"Year", "Month", "Day", "ID", "Amount", "Category", "Description"};
    // int columnWidths[] = {10, 10, 10, 10, 10, 10, 10};
    int columnWidths[7];
    calculateColumnWidths(7, columnNames, columnWidths);

    createTableHeader(7, columnNames, columnWidths);
    return 0;
    
}

int* calculateColumnWidths(int columnCount, char *columnNames[], int columnWidths[]) {
    for (int i = 0; i < columnCount; i++) {
        columnWidths[i] = strlen(columnNames[i]);
    }
    return columnWidths;
}