#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<array>


using namespace std;
//global values
const int rowsize = 20;	
const int colsize = 30;


void randintMatrix(array<array<int,rowsize>, colsize> &matrix) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			matrix[y][x] = rand() % 2; // 0 or 1
		}
	}
}
void zerofillMatrix(array<array<int, rowsize>, colsize> &matrix) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			matrix[y][x] = 0; // 0 or 1
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

void printArray(array<array<int,rowsize>, colsize> &matrix) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			cout << matrix[y][x] << "\t"; 
		}
		cout << endl;
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

void prettyPrintArray(array<array<int,rowsize>, colsize> &matrix) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			if (matrix[y][x] == 1) {
				cout << "@";
			} else if (matrix[y][x] == 0) {
				if (adjacent(matrix, y, x) == 0) {
					cout << "~";
				} else {
					cout << "-";
				}				
			}
			cout << " "; 
		}
		cout << endl;
	}
}

struct grid_data_struct {
	int drydirt;
	int water;
	int wetdirt;
};

grid_data_struct grid_data (array<array<int,rowsize>, colsize> &matrix) {
	int drydirt_num = 0;
	int water_num = 0;
	int wetdirt_num = 0;
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			water_num += matrix[y][x];
			if ((adjacent(matrix, y, x) == 0) && (matrix[y][x] == 0)) {
				drydirt_num += 1;
			}
			if ((adjacent(matrix, y, x) > 0) && (matrix[y][x] == 0)) {
				wetdirt_num += 1;
			}
		}
	}
	return {drydirt_num, water_num, wetdirt_num};
}

int main() {
	srand(time(NULL)); // set rand seed
	array<array<int, rowsize>, colsize> grid; // initialize 2D array
	array<array<int, rowsize>, colsize> change_grid;
	float max_ratio = 0; 
	for (int runs = 0; runs < 1; runs++) { // sets different initial conditions
		randintMatrix(grid);
		// zerofillMatrix(change_grid);
		// cout << "before" << endl;
		// prettyPrintArray(grid); 
		for (int iterations = 0; iterations < 10; iterations++) { // iterations in each condition.
			for (int y = 0; y < rowsize; y++) {
				for (int x = 0; x < colsize; x++) {
					if ((grid[y][x] == 0) && (adjacent(grid, y, x) == 0)) {
						change_grid[y][x] = 1;
					} else if ((grid[y][x] == 1) && (diagonal_adjacent(grid, y, x) > 0)) {
						change_grid[y][x] = 0;
					} else {
						change_grid[y][x] = grid[y][x];
					}
				}
			}
			copyMatrix(change_grid, grid);
			prettyPrintArray(grid); 
		} // different iteration.
		// cout << "after" << endl;
		// prettyPrintArray(grid); 

		// Stats
		auto gridstats = grid_data(grid);
		float gridsize = rowsize * colsize;
		// float wetdirt = gridsize - gridstats.drydirt - gridstats.water;
		float dirtper = gridstats.wetdirt / gridsize;
		cout << "wet dirt % " << dirtper * 100 << "%" << endl;
		max_ratio = max(max_ratio, dirtper);
		cout << endl;
	} // different initial conditions.
	cout << "wet dirt percentage:  " << max_ratio * 100 << "%" << endl;
}