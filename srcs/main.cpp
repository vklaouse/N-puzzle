#include "Lexer.class.hpp"
#include "Parser.class.hpp"
#include "AStar.class.hpp"
// static void printTable(std::vector<int> iTaquinBoard) {
// 	for (size_t i = 0; i < iTaquinBoard.size(); i++) 
// 	{
// 		std::cout << iTaquinBoard[i] << "  ";
// 	}
// 	std::cout << std::endl;
	
// }


static std::vector<std::vector<int> > MainBuildGoal(size_t puzzleSize) 
{
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

int main(int ac, char **av) {
	std::vector< std::vector<int> *> vTaquinBoard;

	if (ac >= 2) {
		Lexer(av[1], &vTaquinBoard);
		
		std::vector<int> goal;
		std::vector<int> vABoard;
		std::vector< std::vector<int> > tmpGoal = MainBuildGoal(4);
		std::vector< std::vector<int> > vBoard(vTaquinBoard.size(), std::vector<int>(vTaquinBoard[0]->size(), 0));
		for (size_t i = 0; i < vBoard.size(); i++)
		{
			for (size_t j = 0; j < vBoard[i].size(); j++)
			{
				vABoard.push_back(vTaquinBoard[i]->at(j));
				vBoard[i][j] = vTaquinBoard[i]->at(j);
				goal.push_back(tmpGoal[i].at(j));
			}
			delete vTaquinBoard[i];
		}
		Parser((std::vector< std::vector<int> > )vBoard);
		AStar(vABoard, goal);
	}
	return 0;
}

