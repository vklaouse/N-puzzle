#include "Lexer.class.hpp"

Lexer::Lexer(std::string sFileName, std::vector< std::vector<int *> *> *TaquinBoard)
	: bError(false), vTaquinBoard(TaquinBoard), iTaquinSize(0), iLineNbr(0) {
	CFileStream = new std::ifstream(sFileName);

	if (CFileStream->fail()) {
		std::cerr << "Wrong File !" << std::endl;
		exit(0);
	}

	{
		std::string sLine;
		int i = 0;

		while (std::getline(*CFileStream, sLine)) {
			lexLine(sLine, i);
			i++;
		}
		if (iLineNbr != iTaquinSize)
			iLineNbr < iTaquinSize ? saveError(i, 3) : saveError(i, 4);
		if (bError) {
			for (size_t i = 0; i < vError.size() ; i++)
				std::cerr << vError[i] << std::endl;
			exit(0);
		}
	}

	return ;
}

void Lexer::lexLine(std::string sLine, int iLine) {
	std::string str;
	size_t j = 0;
	bool bTaquinSize = false;
	int iLineSize = 0;
	size_t i = 0;
	bool bLineNbr = true;
	std::vector<int *> *tmpVector = new std::vector<int *>;

	for (; i < sLine.size(); i++) {
		if (sLine[i] == '#')
			break ;
		else if (iTaquinSize == 0 && sLine[i] <= 57 && sLine[i] >= 48) {
			j = i;
			while(sLine[i] && sLine[i] <= 57 && sLine[i] >= 48)
				i++;
			str.append(sLine, j, i - j);
			iTaquinSize = std::stoi(str);
			i--;
			str.clear();
			bTaquinSize = true;
		}
		else if (sLine[i] <= 57 && sLine[i] >= 48 && !bTaquinSize) {
			if (bLineNbr) {
				bLineNbr = false;
				iLineNbr++;
			}
			j = i;
			while(sLine[i] && sLine[i] <= 57 && sLine[i] >= 48)
				i++;
			str.append(sLine, j, i - j);
			iLineSize++;
			if (iLineSize > iTaquinSize)
				saveError(iLine, 1, str);
			else {
				tmpVector->push_back(new int(std::stoi(str)));
			}
			i--;
			str.clear();
		}
		else if (sLine[i] && sLine[i] != 32 && sLine[i] != 9)
			saveError(iLine, 2, sLine.substr(i, 1));
	}
	if (iLineSize < iTaquinSize && !bTaquinSize)
		saveError(iLine);
	if (!bLineNbr)
		vTaquinBoard->push_back(tmpVector);
	else
		delete tmpVector;
}

void Lexer::saveError(int iLine, int iType, std::string sError) {
	bError = true;

	switch (iType) {
		case 1 : {
			vError.push_back("Wrong element : " + sError
				+ " at line : " + std::to_string(iLine));
			break ;
		}
		case 2 : {
			vError.push_back("Unknown char : " + sError
				+ " at line : " + std::to_string(iLine));
			break ;
		}
		case 3 : {
			vError.push_back("To small array");
			break ;
		}
		case 4 : {
			vError.push_back("To big array");
			break ;
		}
		default :
			vError.push_back("Not enough of elements at line : " + std::to_string(iLine));
	}
}