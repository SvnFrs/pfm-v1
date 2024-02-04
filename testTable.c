#include <stdio.h>

void testTable() {

}

void createTable() {
    
}

void createTableHeader(int columnCount, char *columnNames[]) {
    printf("Creating table with %d columns\n", columnCount);
    for (int i = 0; i < columnCount; i++) {
        printf("%s\t", columnNames[i]);
    }
    printf("\n");

}

int main() {
    char *columnNames[] = {"Name", "Hello", "World"};
    createTableHeader(3, columnNames);
    return 0;
}