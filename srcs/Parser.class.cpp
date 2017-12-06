#include "Parser.class.hpp"

Parser::Parser(std::vector< std::vector<int *> *> *TaquinBoard)
	: vTaquinBoard(TaquinBoard) {
	for (size_t i = 0; i < vTaquinBoard->size(); i++) {
		for (size_t j = 0; j < vTaquinBoard->at(i)->size(); j++) {
			if (!checkDoublon(*(vTaquinBoard->at(i)->at(j)), i, j + 1)) {
				std::cerr << "Invalid puzzle : wrong content" << std::endl;
				exit(0);
			}
		}
	}
}

bool Parser::checkDoublon(int iToCheck, size_t i, size_t j) {
	for (; i < vTaquinBoard->size(); i++) {
		for (; j < vTaquinBoard->at(i)->size(); j++) {
			if (iToCheck == *(vTaquinBoard->at(i)->at(j)) 
				|| static_cast<size_t>(iToCheck) >= vTaquinBoard->size() * vTaquinBoard->size())
				return false;
		}
		j = 0;
	}
	return true;
}