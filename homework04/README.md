## Russian Checkers - Terminal Version

The default board game is designed for human plays with a computer. The computer will make the first move with the white side.

The board game is a square 8x8. It means we have 8 rows and 8 columns starting from 1 to 8. You will be asked to enter a number which is the number of locations of your next move (including your current location). 

For example, you want to move the piece with `(row, column) = (3, 2)` to `(row, column) = (4, 1)`, you need to enter `2` at first. Then the program will ask you for the specific move. In this particular case, you must enter `3 2 4 1`, as shown below: 

![human_computer_mode](https://github.com/trangology/CPP-Assignments/blob/master/homework04/images/human_computer_mode.png?raw=false)

Another mode of this game is designed for 2 computers play with one another. Each computer has its own strategy to make a move. To switch to this mode, uncomment and comment out the **main.cpp** file like the following:

![computer_computer_mode](https://github.com/trangology/CPP-Assignments/blob/master/homework04/images/computer_computer_mode.png?raw=false)
