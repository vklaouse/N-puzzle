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

// static void printTable(std::vector<int> iTaquinBoard) {
// 	for (size_t i = 0; i < iTaquinBoard.size(); i++) 
// 	{
// 		std::cout << iTaquinBoard[i] << "  ";
// 	}
// 	std::cout << std::endl;
	
// }

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

//	printTable(elt->vecGetPuzzle());
//	std::cout << current << " et " << elt << " et "<< i << std::endl;
	std::list<Node *>::const_iterator k = current->nextNode.begin();

	if (bExist)
	{
		while (k != current->nextNode.end())
		{
			if (iValue == (*k)->content)
			{
//				std::cout << "Exist " <<i << std::endl;
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
	if (i < iSize)
	{
		std::cout << "Addr midle Node = " << current << std::endl;
//		std::cout << "New " <<i << std::endl;
		tmp->currentPuzzle = NULL;
		current->nextNode.insert(k, tmp);
		FillTree(elt, ++i, false, tmp);
	}
	else
	{
		std::cout << "Addr Node = " << tmp << std::endl;
		tmp->currentPuzzle = elt;
	}
}

void ClosedSetTree::add(Puzzle *elt)
{
std::cout << " Begin = " << beginTree << std::endl;
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
	std::cout << "Addr = " << current << std::endl;
	if (i == iSize)
	{
		tmpMemory = current->currentPuzzle;
		delete current;
		return true;
	}
	bool btest = recPopBack(++i, current->nextNode.front());
	if (current->nextNode.size() == 1 && btest)
	{
		delete current;
		return true;
	}
	else
	{
		return false;
	}
}

Puzzle * ClosedSetTree::pop_back()
{
	tmpMemory = NULL;
	std::cout << " Begin 2 = " << beginTree << std::endl;
	recPopBack(0, beginTree);
	return tmpMemory;
}

bool ClosedSetTree::findEltToPop(Puzzle *elt, size_t i, Node * current)
{
	if (i == iSize)
	{
		tmpMemory = current->currentPuzzle;
		delete current;
		return true;
	}
	else
		return false;

	int iValue = elt->vecGetPuzzle()[i];
	std::list<Node *>::iterator k = current->nextNode.begin();

	while (k != current->nextNode.end())
	{
		if (iValue == (*k)->content)
		{
			bool btest = findEltToPop(elt, ++i, *k);
			if (current->nextNode.size() == 1 && btest)
			{
				delete current;
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (iValue > (*k)->content)
		{
			return false;
		}
		k++;
	}
}

Puzzle *ClosedSetTree::findToPop(Puzzle * elt)
{
	tmpMemory = NULL;
	findEltToPop(elt, 0, beginTree);
	return tmpMemory;
}