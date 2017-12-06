#include "Lexer.class.hpp"
#include "Parser.class.hpp"

static void printTable(std::vector< std::vector<int *> *> iTaquinBoard) {
	for (size_t i = 0; i < iTaquinBoard.size(); i++) {
		for (size_t j = 0; j < iTaquinBoard[i]->size(); j++) {
			std::cout << *(iTaquinBoard[i]->at(j)) << "  ";
		}
		std::cout << std::endl;
	}
}

int main(int ac, char **av) {
	std::vector< std::vector<int *> *> vTaquinBoard;

	if (ac >= 2) {
		Lexer(av[1], &vTaquinBoard);
		Parser((std::vector< std::vector<int *> *> *)&vTaquinBoard);
		printTable(vTaquinBoard);
	}
	return 0;
}

