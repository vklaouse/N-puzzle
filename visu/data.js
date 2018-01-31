let size = 5;
let puzzleStates = [
	[4, 15, 2, 3, 5, 16, 17, 1, 8, 6, 14, 24, 19, 7, 0, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[4, 15, 2, 3, 5, 16, 17, 1, 8, 6, 14, 24, 19, 0, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[4, 15, 2, 3, 5, 16, 17, 1, 8, 6, 14, 24, 0, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[4, 15, 2, 3, 5, 16, 17, 1, 8, 6, 14, 0, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[4, 15, 2, 3, 5, 16, 0, 1, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[4, 0, 2, 3, 5, 16, 15, 1, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[0, 4, 2, 3, 5, 16, 15, 1, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 4, 2, 3, 5, 0, 15, 1, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 4, 2, 3, 5, 15, 0, 1, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 4, 2, 3, 5, 15, 1, 0, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 4, 0, 3, 5, 15, 1, 2, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 0, 4, 3, 5, 15, 1, 2, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 4, 3, 5, 15, 0, 2, 8, 6, 14, 17, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 4, 3, 5, 15, 17, 2, 8, 6, 14, 0, 24, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 4, 3, 5, 15, 17, 2, 8, 6, 14, 24, 0, 19, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 4, 3, 5, 15, 17, 2, 8, 6, 14, 24, 19, 0, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 4, 3, 5, 15, 17, 2, 0, 6, 14, 24, 19, 8, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 4, 0, 5, 15, 17, 2, 3, 6, 14, 24, 19, 8, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 0, 4, 5, 15, 17, 2, 3, 6, 14, 24, 19, 8, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 0, 3, 6, 14, 24, 19, 8, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 0, 6, 14, 24, 19, 8, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 0, 14, 24, 19, 8, 7, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 14, 24, 19, 8, 0, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 14, 24, 19, 0, 8, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 14, 24, 0, 19, 8, 23, 12, 18, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 14, 24, 18, 19, 8, 23, 12, 0, 20, 9, 13, 21, 22, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 14, 24, 18, 19, 8, 23, 12, 22, 20, 9, 13, 21, 0, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 14, 24, 18, 19, 8, 23, 12, 22, 20, 9, 13, 0, 21, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 14, 24, 18, 19, 8, 23, 0, 22, 20, 9, 13, 12, 21, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 14, 24, 18, 19, 8, 0, 23, 22, 20, 9, 13, 12, 21, 11, 10],
	[16, 1, 2, 4, 5, 15, 17, 3, 6, 7, 0, 24, 18, 19, 8, 14, 23, 22, 20, 9, 13, 12, 21, 11, 10],
	[16, 1, 2, 4, 5, 0, 17, 3, 6, 7, 15, 24, 18, 19, 8, 14, 23, 22, 20, 9, 13, 12, 21, 11, 10],
	[0, 1, 2, 4, 5, 16, 17, 3, 6, 7, 15, 24, 18, 19, 8, 14, 23, 22, 20, 9, 13, 12, 21, 11, 10],
	[1, 0, 2, 4, 5, 16, 17, 3, 6, 7, 15, 24, 18, 19, 8, 14, 23, 22, 20, 9, 13, 12, 21, 11, 10],
	[1, 2, 0, 4, 5, 16, 17, 3, 6, 7, 15, 24, 18, 19, 8, 14, 23, 22, 20, 9, 13, 12, 21, 11, 10],
	[1, 2, 3, 4, 5, 16, 17, 0, 6, 7, 15, 24, 18, 19, 8, 14, 23, 22, 20, 9, 13, 12, 21, 11, 10],
	[1, 2, 3, 4, 5, 16, 17, 18, 6, 7, 15, 24, 0, 19, 8, 14, 23, 22, 20, 9, 13, 12, 21, 11, 10],
	[1, 2, 3, 4, 5, 16, 17, 18, 6, 7, 15, 24, 22, 19, 8, 14, 23, 0, 20, 9, 13, 12, 21, 11, 10],
	[1, 2, 3, 4, 5, 16, 17, 18, 6, 7, 15, 24, 22, 19, 8, 14, 23, 21, 20, 9, 13, 12, 0, 11, 10],
	[1, 2, 3, 4, 5, 16, 17, 18, 6, 7, 15, 24, 22, 19, 8, 14, 23, 21, 20, 9, 13, 12, 11, 0, 10],
	[1, 2, 3, 4, 5, 16, 17, 18, 6, 7, 15, 24, 22, 19, 8, 14, 23, 21, 20, 9, 13, 12, 11, 10, 0],
	[1, 2, 3, 4, 5, 16, 17, 18, 6, 7, 15, 24, 22, 19, 8, 14, 23, 21, 20, 0, 13, 12, 11, 10, 9],
	[1, 2, 3, 4, 5, 16, 17, 18, 6, 7, 15, 24, 22, 19, 0, 14, 23, 21, 20, 8, 13, 12, 11, 10, 9],
	[1, 2, 3, 4, 5, 16, 17, 18, 6, 0, 15, 24, 22, 19, 7, 14, 23, 21, 20, 8, 13, 12, 11, 10, 9],
	[1, 2, 3, 4, 5, 16, 17, 18, 0, 6, 15, 24, 22, 19, 7, 14, 23, 21, 20, 8, 13, 12, 11, 10, 9],
	[1, 2, 3, 4, 5, 16, 17, 18, 19, 6, 15, 24, 22, 0, 7, 14, 23, 21, 20, 8, 13, 12, 11, 10, 9],
	[1, 2, 3, 4, 5, 16, 17, 18, 19, 6, 15, 24, 22, 20, 7, 14, 23, 21, 0, 8, 13, 12, 11, 10, 9],
	[1, 2, 3, 4, 5, 16, 17, 18, 19, 6, 15, 24, 22, 20, 7, 14, 23, 0, 21, 8, 13, 12, 11, 10, 9],
	[1, 2, 3, 4, 5, 16, 17, 18, 19, 6, 15, 24, 0, 20, 7, 14, 23, 22, 21, 8, 13, 12, 11, 10, 9]];