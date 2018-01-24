#include "Parser.class.hpp"

Parser::Parser(std::vector< std::vector<int> > TaquinBoard)
	: vTaquinBoard(TaquinBoard) {
	for (size_t i = 0; i < vTaquinBoard.size(); i++) {
		for (size_t j = 0; j < vTaquinBoard[i].size(); j++) {
			if (!checkDoublon(vTaquinBoard[i][j], i, j + 1)) {
				std::cerr << "Invalid puzzle : wrong content" << std::endl;
				exit(0);
			}
		}
	}
	if (!isSolvable()) {
		std::cerr << "Invalid puzzle : unsolvable" << std::endl;
		exit(0);
	}
}

bool Parser::checkDoublon(int iToCheck, size_t i, size_t j) {
	for (; i < vTaquinBoard.size(); i++) {
		for (; j < vTaquinBoard[i].size(); j++) {
			if (iToCheck == vTaquinBoard[i][j]
				|| static_cast<size_t>(iToCheck) >= vTaquinBoard.size() * vTaquinBoard.size())
				return false;
		}
		j = 0;
	}
	return true;
}

bool Parser::isSolvable() {
	int iPuzzleInversion = inversion(vTaquinBoard.size(), vTaquinBoard);
	int iGoalInversion = inversion(vTaquinBoard.size());
	return (iPuzzleInversion % 2 != iGoalInversion % 2 ? false : true);
}

int Parser::inversion(size_t puzzleSize, std::vector< std::vector<int> > vPuzzle) {
	int iNbrInversion = 0;
	int cnt = 1;
	std::vector<int> vOneDimenssionPuzzle;
	std::vector<int> vBasicPuzzle;

	if (vPuzzle.empty())
		vPuzzle = buildGoal(puzzleSize);
	size_t y = 0;
	for (size_t i = 0; i < puzzleSize; i++) {
		for (size_t j = 0; j < puzzleSize; j++) {
			if (vPuzzle[i][j] == 0)
			{
				y = j;
			}
			vOneDimenssionPuzzle.push_back(vPuzzle[i][j]);
			cnt = (cnt == static_cast<int>(puzzleSize * puzzleSize) ? 0 : cnt);
			vBasicPuzzle.push_back(cnt++);
		}
	}
	for (size_t i = vOneDimenssionPuzzle.size() - 1; i > 0; i--) {
		if (vOneDimenssionPuzzle[0] == 0) {
			vOneDimenssionPuzzle.erase(vOneDimenssionPuzzle.begin());
			vBasicPuzzle.pop_back();
		}
		else if (vOneDimenssionPuzzle[0] > vBasicPuzzle[0]) {
			size_t j = 0;
			for (; j < i; j++) {
				if (vOneDimenssionPuzzle[0] == vBasicPuzzle[j])
					break ;
				iNbrInversion++;
			}
			vOneDimenssionPuzzle.erase(vOneDimenssionPuzzle.begin());
			vBasicPuzzle.erase(vBasicPuzzle.begin() + j);
		}
		else {
			vOneDimenssionPuzzle.erase(vOneDimenssionPuzzle.begin());
			vBasicPuzzle.erase(vBasicPuzzle.begin());
		}
	}
	size_t h = puzzleSize - 1 - y;
	if (puzzleSize % 2 == 0)
	{
		if (h % 2 == iNbrInversion % 2)
			return 0;
		else
			return 1;
	}
	else
		return iNbrInversion;
}



std::vector<std::vector<int> > Parser::buildGoal(size_t puzzleSize) {
	size_t j;
	size_t k;
	size_t l;
	size_t m;
	size_t cnt = 1;
	std::vector< std::vector<int> > tmpVector(puzzleSize, std::vector<int>(puzzleSize));

	for (size_t i = 0; i < puzzleSize; i++) {
		j = i;
		for (; j < puzzleSize - i; j++) {
			tmpVector[i][j] = cnt++;
			cnt = (cnt == puzzleSize * puzzleSize ? 0 : cnt);
		}
		for (k = i + 1; k < puzzleSize - i; k++) {
			tmpVector[k][j - 1] = cnt++;
			cnt = (cnt == puzzleSize * puzzleSize ? 0 : cnt);
		}
		for (l = j - 1; l > i; l--) {
			tmpVector[k - 1][l - 1] = cnt++;
			cnt = (cnt == puzzleSize * puzzleSize ? 0 : cnt);
		}
		for (m = k - 1; m > i + 1; m--) {
			tmpVector[m - 1][l] = cnt++;
			cnt = (cnt == puzzleSize * puzzleSize ? 0 : cnt);
		}
	}
	return tmpVector;
}
