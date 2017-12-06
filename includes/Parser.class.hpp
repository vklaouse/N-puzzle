#pragma once

# include <iostream>
# include <vector>
# include <cstdlib>

class Parser {
	
private:
	std::vector< std::vector<int *> *> *vTaquinBoard;

	Parser(void);
	bool checkDoublon(int, size_t, size_t);

public:
	Parser(std::vector< std::vector<int *> *> *);
	~Parser(void) { return ; };

};