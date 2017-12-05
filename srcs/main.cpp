#include "Lexer.class.hpp"

int main(int ac, char **av) {
	std::vector< std::vector<int *> *> iTaquinBoard;

	if (ac >= 2) {
		Lexer(av[1], &iTaquinBoard);
		for (size_t i = 0; i < iTaquinBoard.size(); i++) {
			for (size_t j = 0; j < iTaquinBoard[i]->size(); j++) {
				std::cout << *((int*)iTaquinBoard[i]->at(j));
			}
			std::cout << std::endl;
		}
	}
	return 0;
}