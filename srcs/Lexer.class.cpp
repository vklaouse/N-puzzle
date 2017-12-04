#include "Lexer.class.hpp"

Lexer::Lexer(std::string sFileName, int **TaquinBoard) : bError(false), iTaquinBoard(TaquinBoard) {
	CFileStream = new std::ifstream(sFileName);

	if (CFileStream->fail())
	{
		std::cerr << "Wrong File !" << std::endl;
		exit(0);
	}
	{
		std::string szLine;
		int i = 0;

		while (std::getline(*CFileStream, szLine))
		{
			std::cout << szLine << std::endl;
			i++;
		}
		if (bError)
		{
			for (size_t i = 0; i < vError.size() ; i++)
			{
				std::cerr << vError[i] << std::endl;
			}
			exit(0);
		}
	}

	return ;
}