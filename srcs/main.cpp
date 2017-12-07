#include "Lexer.class.hpp"
#include "Parser.class.hpp"

// static void printTable(std::vector< std::vector<int *> *> iTaquinBoard) {
// 	for (size_t i = 0; i < iTaquinBoard.size(); i++) {
// 		for (size_t j = 0; j < iTaquinBoard[i]->size(); j++) {
// 			std::cout << *(iTaquinBoard[i]->at(j)) << "  ";
// 		}
// 		std::cout << std::endl;
// 	}
// }

int main(int ac, char **av) {
	std::vector< std::vector<int> *> vTaquinBoard;

	if (ac >= 2) {
		Lexer(av[1], &vTaquinBoard);

		std::vector< std::vector<int> > vBoard(vTaquinBoard.size(), std::vector<int>(vTaquinBoard[0]->size(), 0));
		for (size_t i = 0; i < vBoard.size(); i++)
		{
			for (size_t j = 0; j < vBoard[i].size(); j++)
			{
				vBoard[i][j] = vTaquinBoard[i]->at(j);
			}
			delete vTaquinBoard[i];
		}


		Parser((std::vector< std::vector<int> > )vBoard);
	//	N8Solver();
		// printTable(vTaquinBoard);
	}
	return 0;
}

