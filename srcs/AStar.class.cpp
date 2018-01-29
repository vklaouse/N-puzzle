// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AStar.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/12/08 17:09:39 by semartin          #+#    #+#             //
//   Updated: 2017/12/08 17:09:40 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AStar.class.hpp"

static void printTable(std::vector<int> iTaquinBoard) {
	for (size_t i = 0; i < iTaquinBoard.size(); i++) 
	{
		std::cout << iTaquinBoard[i] << "  ";
	}
	std::cout << std::endl;
	
}

AStar::AStar(std::vector<int> & vecStart, std::vector<int> & vecGoal, std::string h) : closedSet(vecStart.size()), openSet(vecStart.size()), Heuristic(h)
{
	start = new Puzzle(vecStart);
	goal = new Puzzle(vecGoal);
	iSizePuzzle = vecStart.size();
	iNpuzzle = sqrt(iSizePuzzle);
	Compute();
	/*
	if (iNpuzzle * iNpuzzle != iSizePuzzle)
	{
		std::cerr << "Error : Wrong Puzzle size" << std::endl;
		exit(0);
	}*/
}

void AStar::Compute()
{
	std::vector<int> wayTaken;

	start->SetgScore(0);
	start->SetPriority(LinearConflict(start, goal));
	openSet.push(start);
	
	int iAttemptScore;

	std::vector<Puzzle *> neighbor;

	int l = 0;
	while (openSet.size() > 0)
	{
		Puzzle * current = openSet.pop_back();
		/*std::cout << "Priority = " << current->iGetPriority() << " et empty pos = " << current->iGetEmptyPos() << " ___ ";
		printTable(current->vecGetPuzzle());*/

		/*if (l % 5 == 0)
		{
			std::cout << "--------------1" << std::endl;
			closedSet.PrintFullTree();
			std::cout << "--------------2" << std::endl;
		}*/
		if (l < current->iGetPriority())
		{
			l = current->iGetPriority();
			std::cout << "Priority = " << current->iGetPriority()  << " et empty pos = " << current->iGetEmptyPos() << std::endl;
			std::cout << "Size openset = " << openSet.size() << " et Size closedset = " << closedSet.size() << std::endl;
			printTable(current->vecGetPuzzle());
			// std::cout << "-------------2" << std::endl;
			// openSet.PrintQueue();
			// std::cout << "-------------3" << std::endl;
			// closedSet.PrintFullTree();
			// std::cout << "--------------4" << std::endl;
		}
//		std::cout << "TEST 1 " <<  current <<std::endl;
		if (*current == *goal)
		{
			std::cout << "Priority = " << current->iGetPriority()  << " et empty pos = " << current->iGetEmptyPos() << std::endl;
			printTable(current->vecGetPuzzle());
			return; // WIN
		}
//		std::cout << "--------------1" << std::endl;
//		closedSet.PrintFullTree();
//		std::cout << "--------------2" << std::endl;
		closedSet.add(current);
//		std::cout << "-------------3" << std::endl;
//		closedSet.PrintFullTree();
//		std::cout << "--------------4" << std::endl;
//		std::cout << "TEST 2" << std::endl;
		int iNumNeighbor = fillValidNeighbor(current, neighbor);
		for (int i = 0; i < iNumNeighbor; i++)
		{
			if (neighbor[i] == NULL)
			{
				std::cerr << "NEW ERROR" << std::endl;
				exit(0); 
			}
		}
		Puzzle * EltInOpenset;
		for (int i = 0; i < iNumNeighbor; i++)
		{
//			std::cout << "TEST 3" << std::endl;
			iAttemptScore = current->iGetgScore() + 1;
			neighbor[i]->SetgScore(iAttemptScore);
			neighbor[i]->SetPriority(iAttemptScore + LinearConflict(neighbor[i], goal));
			if (closedSet.find(neighbor[i]))
			{
				delete neighbor[i];
				continue;
			}
			bool bBetterWay = true;
			if ((EltInOpenset = openSet.PopOutOfQueue(neighbor[i], &bBetterWay)) != NULL)
			{
				openSet.push(neighbor[i]);
				neighbor[i]->SetCameFrom(current);
			}
			else if (!bBetterWay)
			{
				delete neighbor[i];
			}
			else
			{
				if (neighbor[i]->iGetgScore() >= iAttemptScore)
				{
					neighbor[i]->SetCameFrom(current);;
					openSet.push(neighbor[i]);
					delete EltInOpenset;
				}
				else
				{
					delete neighbor[i];
				}
			}
		}
		neighbor.clear();
	}
}

int AStar::fillValidNeighbor(Puzzle * current, std::vector<Puzzle *> & neighbor)
{
	if (current->iGetEmptyPos() == 0)
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_LEFT);
		neighbor[1]->setNewPuzzle(current, TURN_TOP);
		return 2;
	}
	else if (current->iGetEmptyPos() == iNpuzzle - 1)
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_RIGHT);
		neighbor[1]->setNewPuzzle(current, TURN_TOP);
		return 2;
	}
	else if (current->iGetEmptyPos() == iNpuzzle * (iNpuzzle - 1))
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_LEFT);
		neighbor[1]->setNewPuzzle(current, TURN_BOT);
		return 2;
	}
	else if (current->iGetEmptyPos() == iSizePuzzle - 1)
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_RIGHT);
		neighbor[1]->setNewPuzzle(current, TURN_BOT);
		return 2;
	}
	else if (current->iGetEmptyPos() / iNpuzzle == 0)
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_LEFT);
		neighbor[1]->setNewPuzzle(current, TURN_RIGHT);
		neighbor[2]->setNewPuzzle(current, TURN_TOP);
		return 3;
	}
	else if (current->iGetEmptyPos() / iNpuzzle == iNpuzzle - 1)
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_LEFT);
		neighbor[1]->setNewPuzzle(current, TURN_RIGHT);
		neighbor[2]->setNewPuzzle(current, TURN_BOT);
		return 3;
	}
	else if (current->iGetEmptyPos() % iNpuzzle == 0)
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_LEFT);
		neighbor[1]->setNewPuzzle(current, TURN_TOP);
		neighbor[2]->setNewPuzzle(current, TURN_BOT);
		return 3;
	}
	else if (current->iGetEmptyPos() % iNpuzzle == iNpuzzle - 1)
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_RIGHT);
		neighbor[1]->setNewPuzzle(current, TURN_TOP);
		neighbor[2]->setNewPuzzle(current, TURN_BOT);
		return 3;
	}
	else
	{
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor.push_back(new Puzzle(current->vecGetPuzzle()));
		neighbor[0]->setNewPuzzle(current, TURN_LEFT);
		neighbor[1]->setNewPuzzle(current, TURN_RIGHT);
		neighbor[2]->setNewPuzzle(current, TURN_BOT);
		neighbor[3]->setNewPuzzle(current, TURN_TOP);
		return 4;
	}
}

int AStar::ManhattanHeuristic(Puzzle * current, Puzzle * goal)
{
	int h = 0;

	for (int i = 0; i < iSizePuzzle; i++)
	{
		if (i == current->iGetEmptyPos())
			continue;
		for (int j = 0; j < iSizePuzzle; j++)
		{
			if (current->vecGetPuzzle()[i] == goal->vecGetPuzzle()[j])
			{
				h += abs((i % iNpuzzle) - (j % iNpuzzle)); 
				h += abs((i / iNpuzzle) - (j / iNpuzzle));
				break;
			}
		}
	}
 	return h;
}

int AStar::LinearConflict(Puzzle * current, Puzzle * goal)
{
	int h = 0;
//	static int cmpt = 0;

	for (int i = 0; i < iSizePuzzle; i++)
	{
		if (i == current->iGetEmptyPos())
			continue;
		for (int j = 0; j < iSizePuzzle; j++)
		{
			if (current->vecGetPuzzle()[i / iNpuzzle] == goal->vecGetPuzzle()[j / iNpuzzle])
			{
				int startLine = (goal->vecGetPuzzle()[j / iNpuzzle]) * iNpuzzle;
				for (int k = startLine; k < startLine + iNpuzzle; k++)
				{
					if (k == i)
						continue ;
					for (int l = startLine; l < startLine + iNpuzzle; l++)
					{
						if (current->vecGetPuzzle()[k / iNpuzzle] == goal->vecGetPuzzle()[l / iNpuzzle])
						{
							if ((i <= k && j <= l) || (i >= k && j >= l))
								continue;
							else
							{
								if (i < k && j > l)
								{
									std::cout << "__ i = " << i << " k = " << k << " j = " << j << " l = " << l << std::endl;
									h += 2;
								}
								else
									continue;
							}
						}
					}
				}	
			}
			if (current->vecGetPuzzle()[i % iNpuzzle] == goal->vecGetPuzzle()[j % iNpuzzle])
			{
				int startRow = goal->vecGetPuzzle()[j % iNpuzzle];
				for (int k = startRow; k < startRow + iNpuzzle;)
				{
					if (k == i)
					{
						k += iNpuzzle;
						continue ;
					}
					for (int l = startRow; l < startRow + iNpuzzle;)
					{
						if (current->vecGetPuzzle()[k % iNpuzzle] == goal->vecGetPuzzle()[l % iNpuzzle])
						{
							if ((i <= k && j <= l) || (i >= k && j >= l))
							{
								l += iNpuzzle;
								continue;
							}
							else
							{
								if (i < k && j > l)
								{
									std::cout << "**i = " << i << " k = " << k << " j = " << j << " l = " << l << std::endl;
									h += 2;
								}
								else
								{
									l += iNpuzzle;
									continue;
								}
							}
						}
						l += iNpuzzle;
					}
					k += iNpuzzle;
				}	
			}
		}
	}
//	h += ManhattanHeuristic(current, goal);
	std::cout << "HELLO WOLRD : " << h << std::endl;
//	if (cmpt++ > 5)
		exit(0);
 	return h;
}

int AStar::MisplaceTiles(Puzzle * current, Puzzle * goal)
{
	int h = 0;

	for (int i = 0; i < iSizePuzzle; i++)
	{
		if (i == current->iGetEmptyPos())
			continue;
		if (current->vecGetPuzzle()[i] != goal->vecGetPuzzle()[i])
		{
			h++;
		}
	}
 	return h;
}

int AStar::TOORAC(Puzzle * current, Puzzle * goal) // If you dont get it, google it
{
	int h = 0;

	for (int i = 0; i < iSizePuzzle; i++)
	{
		if (i == current->iGetEmptyPos())
			continue;
		for (int j = 0; j < iSizePuzzle; j++)
		{
			if (current->vecGetPuzzle()[i] == goal->vecGetPuzzle()[j])
			{
				if (abs((i % iNpuzzle) - (j % iNpuzzle)) != 0)
					h++;
				if (abs((i / iNpuzzle) - (j / iNpuzzle)) != 0)
					h++;
				break;
			}
		}
	}
 	return h;
}

int AStar::NMaxSwap(Puzzle * current, Puzzle * goal)
{
	Puzzle tmp(current->vecGetPuzzle());

	int h = 0;

	while (!(tmp == *goal))
	{
		if (tmp.iGetEmptyPos() != goal->iGetEmptyPos())
		{
			int iValue = goal->vecGetPuzzle()[tmp.iGetEmptyPos()];
			for (int i = 0; i < iSizePuzzle; i++)
			{
				if (tmp.vecGetPuzzle()[i] == iValue)
				{
					h++;
					tmp.vecGetPuzzle()[tmp.iGetEmptyPos()] = iValue;
					tmp.vecGetPuzzle()[i] = 0;
					tmp.SetEmptyPos(i);
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < iSizePuzzle; i++)
			{
				if (tmp.vecGetPuzzle()[i] != goal->vecGetPuzzle()[i])
				{
					h++;
					tmp.vecGetPuzzle()[tmp.iGetEmptyPos()] = tmp.vecGetPuzzle()[i];
					tmp.vecGetPuzzle()[i] = 0;
					tmp.SetEmptyPos(i);
					break;
				}
			}
		}
	}
	std::cout << h << std::endl;
 	return h;
}
