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

#include <time.h>


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

static void helper()
{
//	std::cout << std::endl << "Usage: ./npuzzle [ file.txt ] [ heuristics : Manhattan | Linear | Misplaced | Greedy ]" << std::endl << std::endl;
//	std::cout << "	Choose one heuristic :" << std::endl;
//	std::cout << "		Manhattan" << std::endl;
//	std::cout << "		Linear" << std::endl;
//	std::cout << "		Misplaced" << std::endl;
//	std::cout << "		Greedy" << std::endl << std::endl;
	exit(0);
}

int main(int ac, char **av) {
	std::vector< std::vector<int> *> vTaquinBoard;
	std::string heuristic;
	std::string puzzleName;

//	clock_t tStart = clock();
	if (ac >= 2) {

		for (size_t i = 1; i < static_cast<size_t>(ac); i++)
		{
			if ((std::string(av[i]) == "Manhattan" 
				|| std::string(av[i]) == "Linear"
				|| std::string(av[i]) == "Misplaced"
				|| std::string(av[i]) == "Greedy") 
				&& heuristic.empty())
			{
				heuristic = av[i];
			}
			if (std::string(av[i]) != "Manhattan"
				&& std::string(av[i]) != "Linear"
				&& std::string(av[i]) != "Greedy"
				&& std::string(av[i]) != "Misplaced"
				&& puzzleName.empty())
			{
				puzzleName = av[i];
			}
		}
		if (puzzleName.empty())
			helper();
		if (heuristic.empty())
			heuristic = "Manhattan";


		Lexer(puzzleName, &vTaquinBoard);
		
		std::vector<int> goal;
		std::vector<int> vABoard;
		std::vector< std::vector<int> > tmpGoal = MainBuildGoal(vTaquinBoard.size());
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
		AStar(vABoard, goal, heuristic);
	}
//	std::cout << "Time taken: " <<  (double)(clock() - tStart) / CLOCKS_PER_SEC << std::endl;
	return 0;

}

