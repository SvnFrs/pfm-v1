# This  is my project, and it is mine so I'm going to take full marks for it

for compiling the code, you need to have the cjson library installed on your machine.
these are the commands to compile the code.

```shell
gcc -c save.c -o save.o  
```

```shell
gcc -c table.c -o table.o    
```

```shell
gcc -c listExpenses.c -o listExpenses.o
```

```shell
gcc -c  statisticizeExpenses.c -o statisticizeExpenses.o
```

```shell
gcc main.c save.o table.o listExpenses.o statisticizeExpenses.o -o main -lcjson  
```

## TODO

- [ ] Learn Cmake and use it to compile the code.
- [x] Auto generate the month and its days if not exists in the data.  
- [x] List all the expenses in the data file with specific table format.
- [x] Update table format to be more precise and clear.
- [x] Create table method specific for the period of time.
<!-- - [ ] Add the ability to delete an expense from the data file. -->
<!-- - [ ] Add the ability to update an expense from the data file. -->
- [x] Add the ability to list all the expenses in the data file for a specific month / quarter / year.
- [x] Add the ability to list all the expenses in the data file for a specific period.
- [x] List statistics for the expenses in the data file by month.
