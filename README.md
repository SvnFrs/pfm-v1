# This  is my project, and it is mine so I'm going to take full marks for it

for compiling the code, you need to have the cjson library installed on your machine.
these are the commands to compile the code.

```shell
gcc -c testSave.c -o testSave.o  
```

```shell
gcc -c testTable.c -o testTable.o    
```

```shell
gcc main.c testSave.o -o main -lcjson
```

for testing the advanced table.

```shell
gcc testAdvancedTable.c -lcjson ; ./a.out
```

## TODO

- [x] Auto generate the month and its days if not exists in the data.
  
- [x] List all the expenses in the data file with specific table format.
- [x] Update table format to be more precise and clear.
- [ ] Add another data file to store the expenses with quarter period.
- [x] Create table method specific for the period of time.
- [ ] Add the ability to delete an expense from the data file.
- [ ] Add the ability to update an expense from the data file.
- [x] Add the ability to list all the expenses in the data file for a specific month / quarter / year.
- [x] Add the ability to list all the expenses in the data file for a specific period.
- [ ] List statistics for the expenses in the data file by month / quarter / year.
