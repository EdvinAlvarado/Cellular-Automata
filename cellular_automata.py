import numpy as np
# import sys2aq
np.set_printoptions(threshold=np.inf)


# Change the size of the matrix here.
shape = (50, 50)
rowsize = shape[0]
colsize = shape[1]
# grid = np.zeros(shape, dtype='b')


def diagonal_adjacent(x, y, matrix):
	if y == 0:
		if x == 0:
			return np.sum(matrix[:2, :2])
		elif x == colsize - 1:
			return np.sum(matrix[:2, colsize - 2:])
		else:
			return np.sum(matrix[:2, x - 1:x + 2])
	elif y == rowsize - 1:
		if x == 0:
			return np.sum(matrix[y - 1:, :2])
		if x == colsize - 1:
			return np.sum(matrix[y - 1:, x - 1:])
		else:
			return np.sum(matrix[y - 1:, x - 1:x +2])
	elif x == 0:
		return np.sum(matrix[y - 1:y + 2, :2])
	elif x == colsize - 1:
		return np.sum(matrix[y - 1:y + 2, x - 1:])
	else:
		return np.sum(matrix[y - 1:y + 2, x - 1:x + 2])


# def adjacent(x, y, matrix):
# 	if y == 0:
# 		if x == 0:
# 			return matrix[0, 1] + matrix[1, 0]
# 		elif x == colsize - 1:
# 			return matrix[0, x - 1] + matrix[1, x]
# 		else:
# 			return matrix[0, x - 1] + matrix[0, x + 1] + matrix[1, x]
# 	elif y == rowsize - 1:
# 		if x == 0:
# 			return matrix[y - 1, 0] + matrix[y, 1]
# 		if x == colsize - 1:
# 			return matrix[y, x - 1] + matrix[y - 1, x]
# 		else:
# 			return matrix[y, x - 1] + matrix[y - 1, x] + matrix[y, x + 1]
# 	elif x == 0:
# 		return matrix[y - 1, 0] + matrix[y + 1, 0] + matrix[y, 1]
# 	elif x == colsize - 1:
# 		return matrix[y - 1, x] + matrix[y + 1, x] + matrix[y, x - 1]
# 	else:
# 		return matrix[y, x - 1] + matrix[y - 1, x] + matrix[y, x + 1] + matrix[y + 1, x]


max_ratio = 0
# Change the amount of unique initial conditions.
for runs in range(1):
	grid = np.random.randint(2, size=shape, dtype='?')
	change_grid = np.zeros(shape, dtype='?')
	print("before:")
	print(grid)
	print("after:")
	# how many iterations for each initial conditions
	for runs in range(100):
		for j in range(rowsize):
			for i in range(colsize):
				change_grid[j][i] = diagonal_adjacent(i, j, grid) == 3
		grid = change_grid.copy()

	print(grid)
	print(grid.shape)
	print(grid.dtype)