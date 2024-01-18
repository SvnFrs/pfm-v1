#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the CustomTable structure
typedef struct {
    int ColumnGAP;
    int DATA;
    int NUMBER;
} CustomTable;

// Function to create a CustomTable instance
CustomTable createCustomTable() {
    CustomTable table;
    table.ColumnGAP = 2;
    table.DATA = 0;
    table.NUMBER = 1;
    return table;
}

// Function to create a menu
char* createMenu(CustomTable table, char* title, char** option, int ReturnMode, int len) {
    int mode = 0;
    printf("\t%s\n", title);
    for (int i = 0; i < len; i++) {
        printf("%d. %s\n", i + 1, option[i]);
    }
    printf("\tPlease choose: ");

    do {
        char input[100];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            exit(EXIT_FAILURE);
        }

        int ret = sscanf(input, "%d", &mode);
        if (ret != 1 || !(mode >= 1 && mode <= len)) {
            printf("Please input integer from 1 to %d!\n", len);
            printf("\tPlease choose: ");
        }
    } while (!(mode >= 1 && mode <= len));

    if (ReturnMode == table.DATA) {
        return option[mode - 1];
    } else {
        char* result = malloc(10 * sizeof(char));
        sprintf(result, "%d", mode);
        return result;
    }
}

// Function to get Yes/No statement
char* YesNoStatement(char* content) {
    char* option = malloc(3 * sizeof(char)); // Allocate enough space for "Y\0" or "N\0"
    do {
        printf("%s\n", content);
        if (fgets(option, 3, stdin) == NULL) {
            exit(EXIT_FAILURE);
        }

        // Remove newline character
        option[strcspn(option, "\n")] = 0;

        if (!(strcmp(option, "Y") == 0 || strcmp(option, "N") == 0)) {
            printf("Please input Y or N\n");
        }
    } while (!(strcmp(option, "Y") == 0 || strcmp(option, "N") == 0));

    return option;
}

// Function to create table header
void createTH(CustomTable table, char** TableHeader, int len) {
    int total_Table_Length = 0;
    for (int i = 0; i < len; i++) {
        total_Table_Length += (table.ColumnGAP * 3 + strlen(TableHeader[i]));
    }
    total_Table_Length++;

    for (int i = 0; i < 3; i++) {
        int SpaceCounting = 0;
        int next = 0;

        for (int j = 0; j < total_Table_Length; j++) {
            if (next < len && SpaceCounting - table.ColumnGAP == (strlen(TableHeader[next]) + table.ColumnGAP * 2)) {
                if (i == 0 || i == 2) {
                    printf("+");
                } else if (i == 1) {
                    printf("|");
                }
                SpaceCounting = 1;
                next++;
            } else {
                if ((i == 2 || i == 0) && (j == 0 || j == total_Table_Length - 1)) {
                    printf("+");
                } else if (i == 1 && (j == 0 || j == total_Table_Length - 1)) {
                    printf("|");
                } else if (i == 0 || i == 2) {
                    printf("-");
                } else if (next < len && i == 1 && (SpaceCounting - table.ColumnGAP < table.ColumnGAP ||
                                                    SpaceCounting - table.ColumnGAP > strlen(TableHeader[next]) + table.ColumnGAP)) {
                    printf(" ");
                } else if (next < len) {
                    printf("%s", TableHeader[next]);
                    for (int k = 0; k < table.ColumnGAP; k++) {
                        printf(" ");
                    }
                    j += (strlen(TableHeader[next]) + table.ColumnGAP - 1);
                    SpaceCounting += ((strlen(TableHeader[next])) + table.ColumnGAP - 1);
                }
                SpaceCounting++;
            }
        }
        printf("\n");
    }
}

// Function to create table body
void createTB(CustomTable table, char** TableHeader, char** DataRow, int len) {
    int total_Table_Length = 0;
    for (int i = 0; i < len; i++) {
        total_Table_Length += (table.ColumnGAP * 3 + strlen(TableHeader[i]));
    }
    total_Table_Length++;

    int SpaceCounting = 0;
    int next = 0;
    int SpaceBetweenColumns = 0;

    for (int i = 0; i < total_Table_Length; i++) {
        if (next < len && SpaceCounting - table.ColumnGAP == strlen(TableHeader[next]) + table.ColumnGAP * 2) {
            printf("|");
            SpaceCounting = 1;
            next++;
            if (next < len)
                SpaceBetweenColumns = table.ColumnGAP * 2 + 1 + strlen(TableHeader[next]);
        } else {
            if (i == 0) {
                printf("|");
                SpaceBetweenColumns = table.ColumnGAP * 2 + 1 + strlen(TableHeader[next]);
            } else {
                for (int j = 0; j < table.ColumnGAP + 1; j++) {
                    printf(" ");
                }
                printf("%s", DataRow[next]);
                for (int j = 0; j < SpaceBetweenColumns - strlen(DataRow[next]) - table.ColumnGAP - 1; j++) {
                    printf(" ");
                }

                SpaceCounting += (SpaceBetweenColumns - 1);
                i += (SpaceBetweenColumns - 1);
            }
            SpaceCounting++;
        }
    }
    printf("\n");
}

// Function to create table footer
void createTF(CustomTable table, char** TableFooter, int len) {
    int total_Table_Length = 0;
    for (int i = 0; i < len; i++) {
        total_Table_Length += (table.ColumnGAP * 3 + strlen(TableFooter[i]));
    }
    total_Table_Length++;

    int SpaceCounting = 0;
    int next = 0;

    for (int j = 0; j < total_Table_Length; j++) {
        if (next < len && SpaceCounting - table.ColumnGAP == (strlen(TableFooter[next]) + table.ColumnGAP * 2)) {
            printf("+");
            SpaceCounting = 1;
            next++;
        } else {
            if (j == 0) {
                printf("+");
            } else {
                printf("-");
            }
            SpaceCounting++;
        }
    }
    printf("\n");
}

// Function to create a line break
void createHR() {
    printf("\n-------------------------------------------------------\n");
}

int main() {
    // Example usage
    CustomTable table = createCustomTable();
    char* menuOptions[] = {"Option 1", "Option 2", "Option 3"};
    char* tableHeader[] = {"Header 1", "Header 2", "Header 3"};
    char* tableData[] = {"Data 1", "Data 2", "Data 3"};
    char* tableFooter[] = {"Footer 1", "Footer 2", "Footer 3"};

    char* userChoice = createMenu(table, "Menu Title", menuOptions, table.DATA, 3);
    printf("User choice: %s\n", userChoice);

    char* yesNoChoice = YesNoStatement("Yes or No?");
    printf("User choice: %s\n", yesNoChoice);

    createTH(table, tableHeader, 3);
    createTB(table, tableHeader, tableData, 3);
    createTF(table, tableFooter, 3);
    createHR();

    return 0;
}
