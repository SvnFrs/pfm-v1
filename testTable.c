#include <stdio.h>

void testTable() {

}

void createTable() {
    
}

void createTableHeader(int columnCount, char *columnNames[], int columnWidths[]) {
    printf("|");
    for (int i = 0; i < columnCount; i++) {
        printf("%*s|", columnWidths[i], columnNames[i]);
    }
    printf("\n");
    

}

int main() {
    char *columnNames[] = {"Name", "Date", "Time"};
    int columnWidths[] = {10, 10, 10};
    createTableHeader(3, columnNames, columnWidths);
    return 0;
    
}