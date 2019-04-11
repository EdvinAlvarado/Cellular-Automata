#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<array>

using namespace std;

// void fill_rand(int matrix[][10], int rows, int cols) {
// 	for (int y = 0; y < rows; y++) {
// 		for (int x = 0; x < cols; x++) {
// 			matrix[y][x] = rand() % 2;
// 		}
// 	}
// }

int main() {
	srand(time(NULL));
	// int a;
	// for (int i = 0; i < 10; i++) {
	// 	a = rand() % 2;
	// 	cout << a << endl;
	// }
	
	const int rows = 10;
	
	const int cols = 10;
	array<array<int,rows>, cols> grid;
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			grid[y][x] = rand() % 2;
		}
	}

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			cout << grid[y][x] << "\t"; 
		}
		cout << endl;
	}
	
}