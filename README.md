# Conway-s-Game-of-Life
Simple implementation of John Conway's Game of Life using 2D linked lists in C programming language.
Current state of living cells is displayed in static board of 22 rows and 80 columns (can be modified when compilating with GCC, simply add
-DWIERSZE="number of rows you want", -DKOLUMNY="number of columns you want". 



The input data is in form of coordinates of living cells, every cell has its row and column
To input data, simply write "/", then (without space) index of row, and then (with spaces between) columns of living cells in this row.
After pressing Enter, you can either input another row and columns in the same convention, or signalize end of input, by simply writing "/" and then pressing Enter. Rows and columns should be written in ascending order

Example:
/10 11 12
/11 12 13 14
/13 9 100 101
/

Wrong example:
/10 12 10
/9 11 12
/13 100 0
/

After that, the program accepts 5 commands:
"Enter" - calculating state of next generation,
"0" - writing down in terminal current state of living cells in the same format as input data,
"n", where n is number from 1 INT_MAX - calculating state of n-th generation,
"r c", where "r" and "c" are numbers from INT_MIN to INT_MAX - set upper left corner of the board to (r,c), (initial is 1,1),
"." - exiting program


