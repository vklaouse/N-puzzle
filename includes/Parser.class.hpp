#pragma once

# include <iostream>
# include <vector>
# include <cstdlib>

class Parser {
	
private:
	std::vector< std::vector<int *> *> *iTaquinBoard;

	Parser(void);

public:
	Parser(std::vector< std::vector<int *> *> *);
	~Parser(void) { return ; };

};