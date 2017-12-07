#include "Parser.class.hpp"

Parser::Parser(std::vector< std::vector<int> > TaquinBoard)
	: vTaquinBoard(TaquinBoard) {
	for (size_t i = 0; i < vTaquinBoard.size(); i++) {
		for (size_t j = 0; j < vTaquinBoard[i].size(); j++) {
			std::cout << vTaquinBoard[i][j] << " ";
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
	std::vector<int> *tmpVector = saveSnailArray();
	for (size_t j = 0; j < tmpVector->size(); j++)
		std::cout << tmpVector->at(j) << " ";
	//gros caca
	// bool bFisrtIter = true;
	// int cnt = 0;

	// for (int i = static_cast<int>(tmpVector->size() - 1); i >= 0; i--) {
	// 	for (size_t j = 0; j < tmpVector->size(); j++)
	// 		std::cout << tmpVector->at(j) << " ";
	// 	std::cout << std::endl  << *(max_element(tmpVector->begin(), tmpVector->begin() + i)) << std::endl;
	// 	if (bFisrtIter) {
	// 		bFisrtIter = false;
	// 		if (0 != tmpVector->back()) {
	// 			std::iter_swap(min_element(tmpVector->begin(), tmpVector->begin() + i), tmpVector->begin() + i);
	// 			cnt++;
	// 		}
	// 	}
	// 	else {
	// 		if (i != tmpVector->back()) {
	// 			std::iter_swap(max_element(tmpVector->begin(), tmpVector->begin() + i), tmpVector->begin() + i);
	// 			cnt++;
	// 		}
	// 	}
	// 	tmpVector->pop_back();
	// }
	// std::cout << cnt << std::endl;
	return true;
}

std::vector<int> *Parser::saveSnailArray() {
	size_t j;
	size_t k;
	size_t l;
	size_t m;
	std::vector<int> *tmpVector = new std::vector<int>;

	for (size_t i = 0; i < vTaquinBoard.size(); i++) {
		j = i;
		for (; j < vTaquinBoard[i].size() - i; j++)
			tmpVector->push_back(vTaquinBoard[i][j]);
		for (k = i + 1; k < vTaquinBoard.size() - i; k++)
			tmpVector->push_back(vTaquinBoard[k][j - 1]);
		for (l = j - 1; l > i; l--)
			tmpVector->push_back(vTaquinBoard[k - 1][l - 1]);
		for (m = k - 1; m > i + 1; m--)
			tmpVector->push_back(vTaquinBoard[m - 1][l]);
	}
	return tmpVector;
}
