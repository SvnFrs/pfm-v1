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
gcc main.c save.o table.o -o main -lcjson
```

## TODO

- [ ] Learn Cmake and use it to compile the code.
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
