#include "Lexer.class.hpp"

int main(int ac, char **av) {
	int **iTaquinBoard = NULL;

	if (ac >= 2) {
		Lexer(av[1], iTaquinBoard);
	}
	return 0;
}