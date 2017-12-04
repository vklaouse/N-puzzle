#pragma once

# include <iostream>
# include <fstream>
# include <vector>
# include <cstdlib>

class Lexer {
	
private:
	bool bError;
	int **iTaquinBoard;
	std::ifstream *CFileStream;
	std::vector<std::string> vError;

	Lexer(void);

public:
	Lexer(std::string, int **);
	~Lexer(void) { return ; };

};