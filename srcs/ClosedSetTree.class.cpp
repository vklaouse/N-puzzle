// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ClosedSetTree.class.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/01/24 14:31:56 by semartin          #+#    #+#             //
//   Updated: 2018/01/24 14:31:57 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ClosedSetTree.class.hpp"

static void printTable(std::vector<int> iTaquinBoard) {
	for (size_t i = 0; i < iTaquinBoard.size(); i++) 
	{
		std::cout << iTaquinBoard[i] << "  ";
	}
	std::cout << std::endl;
	
}

ClosedSetTree::ClosedSetTree(size_t size) : iSize(size)
{
	iSizeCloseSet = 0;
	beginTree = new Node;
	beginTree->content = -1;
	beginTree->currentPuzzle = NULL;
}

ClosedSetTree::~ClosedSetTree()
{
	//TODO
}

void ClosedSetTree::FillTree(Puzzle * elt, size_t i, bool bExist, Node * current)
{
	int iValue = elt->vecGetPuzzle()[i];

	std::list<Node *>::const_iterator k = current->nextNode.begin();

	if (bExist)
	{
		while (k != current->nextNode.end())
		{
			if (iValue == (*k)->content)
			{
				FillTree(elt, ++i, true, *k);
				return ;
			}
			else if (iValue > (*k)->content)
			{
				break ;
			}
			k++;
		}
		k--;
	}
	Node * tmp = new Node;
	tmp->content = iValue;
	if (i < iSize - 1)
	{
		tmp->currentPuzzle = NULL;
		current->nextNode.insert(k, tmp);
		FillTree(elt, ++i, false, tmp);
	}
	else
	{
		current->nextNode.insert(k, tmp);
		tmp->currentPuzzle = elt;
	}
}

void ClosedSetTree::add(Puzzle *elt)
{
	iSizeCloseSet++;
	FillTree(elt, 0, true, beginTree);
}

bool ClosedSetTree::findElt(Puzzle *elt, size_t i, Node * current)
{
	if (i == iSize)
		return true;
	else
		return false;

	int iValue = elt->vecGetPuzzle()[i];
	std::list<Node *>::iterator k = current->nextNode.begin();

	while (k != current->nextNode.end())
	{
		if (iValue == (*k)->content)
		{
			return findElt(elt, ++i, *k);
		}
		else if (iValue > (*k)->content)
		{
			return false;
		}
		k++;
	}
}

bool ClosedSetTree::find(Puzzle *elt)
{
	return findElt(elt, 0, beginTree);
}

bool ClosedSetTree::recPopBack(size_t i, Node * current)
{
	if (i == iSize)
	{
		tmpMemory = current->currentPuzzle;
		std::cout << "LOL 1 " <<  current <<  " et "<<  current->content << " et "<< current->nextNode.size() << std::endl;
		delete current;
		return true;
	}
	if (current->nextNode.front() == NULL)
	{
		std::cerr << "WTF BUG" << i << std::endl;
		exit (0);
	}
	bool btest = recPopBack(++i, current->nextNode.front());
	if (btest == true)
	{
		current->nextNode.pop_front();
	}
	if (current->nextNode.size() == 0 && btest)
	{
		std::cout << "LOL 2" <<  current <<  " et "<<  current->content << " et "<< current->nextNode.size() << std::endl;
		delete current;
		return true;
	}
	else
	{
		std::cout << "LOL 3" << std::endl;
		return false;
	}
}

Puzzle * ClosedSetTree::pop_back(bool * bTest)
{
	tmpMemory = NULL;
	*bTest = recPopBack(0, beginTree);
	return tmpMemory;
}

bool ClosedSetTree::findEltToPop(Puzzle *elt, size_t i, Node * current)
{
	if (i == iSize)
	{
		std::cout << "+++++++++++++++++++++++++++++" <<  i << " et " << current->content << std::endl;
		printTable(elt->vecGetPuzzle());
		printTable(current->currentPuzzle->vecGetPuzzle());
		if (*(current->currentPuzzle) == *elt)
		{
			std::cout << "***************************" << std::endl;
			tmpMemory = current->currentPuzzle;
			delete current;
			return true;
		}
		else
			return false;
	}

	int iValue = elt->vecGetPuzzle()[i];
	printTable(elt->vecGetPuzzle());
	std::cout << " HELLO BIS " << iValue <<  " et " << i << std::endl;
	std::list<Node *>::iterator k = current->nextNode.begin();

	while (k != current->nextNode.end())
	{
		std::cout << " HELLO : " << iValue <<  " et " << (*k)->content << std::endl;
		if (iValue == (*k)->content)
		{
			std::cout << iValue << " et " << (*k)->content<<  " et " << i << std::endl;
			bool btest = findEltToPop(elt, ++i, *k);
			if (btest == true)
			{
				current->nextNode.erase(k);
			}
			if (current->nextNode.size() == 0 && btest)
			{
				std::cout << " 15 fois ici " << std::cout;
				delete current;
				bMemory = true;
				return true;
			}
			else if (btest)
			{
				std::cout << "YOU ARE THE PROBLEME 2 " << std::endl;
				bMemory = false;
				return true;
			}
		}
		else if (iValue < (*k)->content)
		{
			std::cout << "PLEASE WE WANT YOU LIKE TEEMO" << std::endl;
			return false;
		}
		k++;
	}
	std::cout << "PLEASE WE WANT YOU LIKE WW" << std::endl;
	return false;
}

Puzzle *ClosedSetTree::findToPop(Puzzle * elt, bool * bTest)
{
	bMemory = false;
	tmpMemory = NULL;
	std::cout << "/////////////////////////////" << std::endl;
	findEltToPop(elt, 0, beginTree);
	*bTest = bMemory;
	return tmpMemory;
}