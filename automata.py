import numpy as np
# import sys2aq
np.set_printoptions(threshold=np.inf)

shape = (30, 30)
rowsize = shape[0]
colsize = shape[1]
# grid = np.zeros(shape, dtype='b')
grid = np.random.randint(2, size=shape, dtype='b')
# grid[0, 0] = 1
# grid[1, 2] = 1
# grid[0, 1] = 1
# grid[:3, :6] = 1
# grid[0, colsize-1] = 1
# grid[rowsize-1, 0] = 1
# grid[rowsize-1, colsize-1] = 1

def diagonal_adjacent(x, y, matrix):
	if y == 0:
		if x == 0:
			return matrix[:2, :2]
		elif x == colsize - 1:
			return matrix[:2, colsize-2:]
		else:
			return matrix[:2, x-1:x+2]
	elif y == rowsize - 1:
		if x == 0:
			return matrix[y-1:, :2]
		if x == colsize-1:
			return matrix[y-1:, x-1:]
		else:
			return matrix[y-1:, x-1:x+2]
	elif x == 0:
		return matrix[y-1:y+2, :2]
	elif x == colsize-1:
		return matrix[y-1:y+2, x-1:]
	else:
		return matrix[y-1:y+2, x-1:x+2]

def adjacent(x, y, matrix):
	if y == 0:
		if x == 0:
			return (matrix[0, 1], matrix[1, 0])
		elif x == colsize - 1:
			return (matrix[0, x-1], matrix[1, x])
		else:
			return (matrix[0, x-1], matrix[0, x+1], matrix[1, x])
	elif y == rowsize - 1:
		if x == 0:
			return (matrix[y-1, 0], matrix[y, 1])
		if x == colsize-1:
			return (matrix[y, x-1], matrix[y-1, x])
		else:
			return (matrix[y, x-1], matrix[y-1, x], matrix[y, x+1])
	elif x == 0:
		return (matrix[y-1, 0], matrix[y+1, 0], matrix[y, 1])
	elif x == colsize-1:
		return (matrix[y-1, x], matrix[y+1, x], matrix[y, x-1])
	else:
		return (matrix[y, x-1], matrix[y-1, x], matrix[y, x+1], matrix[y+1, x])


print("before:")
print(grid)
print("after:")
for runs in range(3000):
	for j in range(rowsize):
		for i in range(colsize):
			if grid[j][i] == 0 and sum(adjacent(i, j, grid)) == 0:
			# if grid[j][i] == 0 and diagonal_adjacent(i, j, grid).sum() == 0:
				grid[j][i] = 1
			elif grid[j][i] == 1 and diagonal_adjacent(i, j, grid).sum() - 1 > 0:
				grid[j][i] = 0

print(grid)
print(grid.shape)
print(grid.dtype)

nonzero = np.count_nonzero(grid)
gridsize = rowsize * colsize

print("grid:water ratio {0:f}".format(gridsize / nonzero))