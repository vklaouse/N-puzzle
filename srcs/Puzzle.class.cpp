// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Puzzle.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/12/08 17:26:07 by semartin          #+#    #+#             //
//   Updated: 2017/12/08 17:26:07 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Puzzle.class.hpp"

Puzzle::Puzzle(size_t i)
{
	for (size_t j = 0; j < i; j++)
	{
		vecPuzzle.push_back(-1);
		iEmptyPos = -1;
	}
}


Puzzle::Puzzle(std::vector<int> & puzzle) : vecPuzzle(puzzle)
{
	for (size_t i = 0; i < puzzle.size(); i++)
	{
		if (puzzle[i] == 0)
		{
			iEmptyPos = i;
			return;
		}
	}
	std::cerr << "Wrong Puzzle" << std::endl;
	exit(0);
}

void Puzzle::setNewPuzzle(Puzzle * rhs, int iIndex)
{
	for (int i = 0; static_cast<size_t>(i) < rhs->vecGetPuzzle().size(); i++)
	{
		if (iIndex == TURN_NOCHANGE)
			vecPuzzle[i] = rhs->vecGetPuzzle()[i];
		else if (iIndex == TURN_LEFT)
		{
			if (i == rhs->iGetEmptyPos() + 1)
			{
				vecPuzzle[i] = 0;
				iEmptyPos = i;
			}
			else if (i == rhs->iGetEmptyPos())
				vecPuzzle[i] = rhs->vecGetPuzzle()[i + 1];
			else
				vecPuzzle[i] = rhs->vecGetPuzzle()[i];
		}
		else if (iIndex == TURN_RIGHT)
		{
			if (i == rhs->iGetEmptyPos() - 1)
			{
				vecPuzzle[i] = 0;
				iEmptyPos = i;
			}
			else if (i == rhs->iGetEmptyPos())
				vecPuzzle[i] = rhs->vecGetPuzzle()[i - 1];
			else
				vecPuzzle[i] = rhs->vecGetPuzzle()[i];
		}
		else if (iIndex == TURN_BOT)
		{
			if (i == rhs->iGetEmptyPos() - sqrt(vecPuzzle.size()))
			{
				vecPuzzle[i] = 0;
				iEmptyPos = i;
			}
			else if (i == rhs->iGetEmptyPos())
				vecPuzzle[i] = rhs->vecGetPuzzle()[i - sqrt(vecPuzzle.size())];
			else
				vecPuzzle[i] = rhs->vecGetPuzzle()[i];
		}
		else if (iIndex == TURN_TOP)
		{
			if (i == rhs->iGetEmptyPos() + sqrt(vecPuzzle.size()))
			{
				vecPuzzle[i] = 0;
				iEmptyPos = i;
			}
			else if (i == rhs->iGetEmptyPos())
				vecPuzzle[i] = rhs->vecGetPuzzle()[i + sqrt(vecPuzzle.size())];
			else
				vecPuzzle[i] = rhs->vecGetPuzzle()[i];
		}
		
	}
}

bool Puzzle::operator==(Puzzle & rhs) // TODO
{
	if (vecPuzzle.size() != rhs.vecGetPuzzle().size())
	{
		std::cerr << "Wrong Puzzle size comp" << std::endl;
		exit(0);
	}
	for (size_t i = 0; i < vecPuzzle.size(); i++)
	{
		if (vecPuzzle[i] != rhs.vecGetPuzzle()[i])
		{
			return false;
		}
	}
	return true;
}

bool ComparePuzzle::operator()(Puzzle * Puzzle1, Puzzle * Puzzle2)
{
	if (Puzzle1->iGetPriority() < Puzzle2->iGetPriority())
		return true;
	else
		return false;
}