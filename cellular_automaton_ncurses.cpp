#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <array>
#include <chrono>
#include <thread>
#include <stdlib.h> //system access
// #include <curses.h>
#include <ncurses.h>

using namespace std;
//global values
const int rowsize = 60;	
const int colsize = 60;

// void clrscr() {
// 	cout << "\033[2J\033[1;1H";
// }


void randintMatrix(array<array<int,rowsize>, colsize> &matrix) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			matrix[y][x] = rand() % 2; // 0 or 1
		}
	}
}

void copyMatrix(array<array<int, rowsize>, colsize> &change_matrix, array<array<int, rowsize>, colsize> &matrix) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			matrix[y][x] = change_matrix[y][x];
		}
	}
}

int adjacent(array<array<int,rowsize>, colsize> &matrix, int row, int col) {
	int adj_val;
	if (row == 0) {
		if (col == 0) {
			adj_val = matrix[0][1] + matrix[1][0];
			// cout<< "top left" << endl;
		} else if (col == colsize - 1) {
			adj_val =  matrix[0][col - 1] + matrix[1][col];
			// cout<< "top right" << endl;
		} else {
			adj_val =  matrix[0][col - 1] + matrix[0][col + 1] + matrix[1][col];
			// cout<< "top" << endl;
		}
	} else if (row == rowsize - 1) {
		if (col == 0) {
			adj_val = matrix[row - 1][col] + matrix[row][col + 1];
			// cout << "bottom left" << endl;
		} else if (col == colsize - 1) {
			adj_val = matrix[row][col - 1] + matrix[row - 1][col];
			// cout << "bottom right" << endl;
		} else {
			adj_val = matrix[row][col - 1] + matrix[row][col + 1] + matrix[row - 1][col];
			// cout << "bottom" << endl;
		}
	} else if (col == 0) {
		adj_val = matrix[row - 1][col] + matrix[row + 1][col] + matrix[row][col + 1];
		// cout << "left" << endl;
	} else if (col == colsize - 1) {
		adj_val = matrix[row - 1][col] + matrix[row + 1][col] + matrix[row][col - 1];
		// cout << "right" << endl;
	} else {
		adj_val = matrix[row][col - 1] + matrix[row][col + 1] + matrix[row - 1][col] + matrix[row + 1][col];
		// cout << "middle" << endl;
	}
	return adj_val;
}

int diagonal_adjacent(array<array<int,rowsize>, colsize> &matrix, int row, int col) {
	int adj_val;
	if (row == 0) {
		if (col == 0) {
			adj_val = matrix[0][1] + matrix[1][0] + matrix[1][1];
			// cout<< "top left" << endl;
		} else if (col == colsize - 1) {
			adj_val =  matrix[0][col - 1] + matrix[1][col] + matrix[1][col - 1];
			// cout<< "top right" << endl;
		} else {
			adj_val =  matrix[0][col - 1] + matrix[0][col + 1] + matrix[1][col] + matrix[1][col - 1] + matrix[1][col + 1];
			// cout<< "top" << endl;
		}
	} else if (row == rowsize - 1) {
		if (col == 0) {
			adj_val = matrix[row - 1][0] + matrix[row][1] + matrix[row - 1][1];
			// cout << "bottom left" << endl;
		} else if (col == colsize - 1) {
			adj_val = matrix[row][col - 1] + matrix[row - 1][col] + matrix[row - 1][col - 1];
			// cout << "bottom right" << endl;
		} else {
			adj_val = matrix[row][col - 1] + matrix[row][col + 1] + matrix[row - 1][col] + matrix[row - 1][col - 1] + matrix[row - 1][col + 1];
			// cout << "bottom" << endl;
		}
	} else if (col == 0) {
		adj_val = matrix[row - 1][0] + matrix[row + 1][0] + matrix[row][1] + matrix[row - 1][1] + matrix[row + 1][1];
		// cout << "left" << endl;
	} else if (col == colsize - 1) {
		adj_val = matrix[row - 1][col] + matrix[row + 1][col] + matrix[row][col - 1] + matrix[row - 1][col - 1] + matrix[row + 1][col -1];
		// cout << "right" << endl;
	} else {
		adj_val = matrix[row][col - 1] + matrix[row][col + 1] + matrix[row - 1][col] + matrix[row + 1][col] + matrix[row - 1][col - 1] + matrix[row - 1][col + 1] + matrix[row + 1][col + 1] + matrix[row + 1][col - 1];
		// cout << "middle" << endl;
	}
	return adj_val;
}

void AnimationPrint(array<array<int,rowsize>, colsize> &matrix, WINDOW * windows) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			if (matrix[y][x] == 1) {
				waddch(windows, '@');
			} else {
				waddch(windows, ' ');
			}
		}
	}
	wmove(windows, 0, 0);
	wrefresh(windows);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main() {
	srand(time(NULL)); // set rand seed
	array<array<int, rowsize>, colsize> grid; // initialize 2D array
	array<array<int, rowsize>, colsize> change_grid = {};
	initscr(); // Needed to use any curses packages
	WINDOW * win = newwin(rowsize, colsize, 0, 0); // create the window object 
	for (int runs = 0; runs < 1; runs++) { // sets different initial conditions
		randintMatrix(grid);
		// zerofillMatrix(change_grid); // zero fill is broken. gives random numbers.
		// cout << "before" << endl;
		// prettyPrintArray(grid); 
		AnimationPrint(grid, win);
		// cout << "change grid" << endl;
		// prettyPrintArray(change_grid); 
		for (int iterations = 0; iterations < 1000; iterations++) { // iterations in each condition.
			for (int y = 0; y < rowsize; y++) {
				for (int x = 0; x < colsize; x++) {
					if (grid[y][x] == 1) {
						if (diagonal_adjacent(grid, y, x) < 2) {
							change_grid[y][x] = 0; // underpopulation
						} else if (diagonal_adjacent(grid, y, x) > 3) {
							change_grid[y][x] = 0; // overpopulation
						} else {
							change_grid[y][x] = 1; // lives on
						}
					} else if (diagonal_adjacent(grid, y, x) == 3) { //implicit grid value to be zero.
						change_grid[y][x] = 1; // reproduction
					} else {
						change_grid[y][x] = 0;
					}
				}
			}
			copyMatrix(change_grid, grid);
			// cout << endl;
			// cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
			// system("CLS");
			// this_thread::sleep_for(chrono::milliseconds(100));
			// prettyPrintArray(grid); 
			AnimationPrint(grid, win); 
		} // different iteration.
		// cout << "after" << endl;
		// prettyPrintArray(grid); 

	} // different initial conditions.
	// system("pause");
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	endwin();
}