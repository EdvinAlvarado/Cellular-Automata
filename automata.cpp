#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<array>

using namespace std;

//global values
const int rowsize = 30;	
const int colsize = 30;


void randintMatrix(array<array<int,rowsize>, colsize> &matrix) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			matrix[y][x] = rand() % 2; // 0 or 1
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

void prettyPrintArray(array<array<int,rowsize>, colsize> &matrix) {
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			if (matrix[y][x] == 1) {
				cout << "o";
			} else if (matrix[y][x] == 0) {
				cout << "-";
			}
			cout << " "; 
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

int nonzero (array<array<int,rowsize>, colsize> &matrix) {
	int sum;
	for (int y = 0; y < rowsize; y++) {
		for (int x = 0; x < colsize; x++) {
			sum += matrix[y][x];
		}
	}
	return sum;
} 

int main() {
	srand(time(NULL)); // set rand seed
	array<array<int,rowsize>, colsize> grid; // initialize 2D array
	float max_ratio = 0; 
	for (int runs = 0; runs < 30; runs++) { // sets different initial conditions
		randintMatrix(grid);
		cout << "before" << endl;
		prettyPrintArray(grid); 
		for (int iterations = 0; iterations < 10000; iterations++) { // iterations in each condition.
			for (int y = 0; y < rowsize; y++) {
				for (int x = 0; x < colsize; x++) {
					if ((grid[y][x] == 0) && (adjacent(grid, y, x) == 0)) {
						grid[y][x] = 1;
					} else if ((grid[y][x] == 1) && (diagonal_adjacent(grid, y, x) > 0)) {
						grid[y][x] = 0;
					}
				}
			}
		} // different iteration.
		cout << "after" << endl;
		prettyPrintArray(grid); 		

		float gridsize = rowsize * colsize;
		float ratio = gridsize / nonzero(grid);
		cout << "ratio: " << ratio << endl;
		max_ratio = max(max_ratio, ratio);
		cout << endl;
	} // different initial conditions.
	cout << "max grid:water ratio " << max_ratio << endl;
	cout << "dirt percentage: " << (max_ratio - 1) / max_ratio * 100 << "%" << endl;
}