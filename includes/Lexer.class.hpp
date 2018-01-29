#pragma once

# include <iostream>
# include <fstream>
# include <vector>
# include <cstdlib>
# include <string>

class Lexer {
	
private:
	bool bError;
	std::vector< std::vector<int> *> *vTaquinBoard;
	std::ifstream *CFileStream;
	std::vector<std::string> vError;
	int iTaquinSize;
	int iLineNbr;

	Lexer(void);
	void lexLine(std::string, int);
	void saveError(int, int = 0, std::string = "");

public:
	Lexer(std::string, std::vector< std::vector<int> *> *);
	~Lexer(void);

};