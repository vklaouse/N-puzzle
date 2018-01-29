#pragma once

# include <iostream>
# include <vector>
# include <cstdlib>
# include <iterator>

class Parser {
	
private:
	std::vector< std::vector<int> > vTaquinBoard;

	Parser(void);
	bool checkDoublon(int, size_t, size_t);
	bool isSolvable();
	std::vector<std::vector<int> > buildGoal(size_t);
	int inversion(size_t, std::vector< std::vector<int> > = std::vector< std::vector<int> >());

public:

	Parser(std::vector< std::vector<int> >);
	~Parser(void) { return ; };

};