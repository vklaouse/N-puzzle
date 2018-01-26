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

AStar::AStar(std::vector<int> & vecStart, std::vector<int> & vecGoal) : closedSet(vecStart.size()), openSet(vecStart.size())
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
	start->SetPriority(ManhattanHeuristic(start, goal));
	openSet.push(start);
	
	int iAttemptScore;

	std::vector<Puzzle *> neighbor;

	//int l = 0;
	while (openSet.size() > 0)
	{
		Puzzle * current = openSet.pop_back();
	/*	if (l < current->iGetPriority())
		{
			l = current->iGetPriority();
			std::cout << "Priority = " << current->iGetPriority()  << " et empty pos = " << current->iGetEmptyPos() << std::endl;
			std::cout << "Size openset = " << openSet.size() << " et Size closedset = " << closedSet.size() << std::endl;
			printTable(current->vecGetPuzzle());
		}*/
		std::cout << "TEST 1 " <<  current <<std::endl;
		if (*current == *goal)
		{
			std::cout << "Priority = " << current->iGetPriority()  << " et empty pos = " << current->iGetEmptyPos() << std::endl;
			printTable(current->vecGetPuzzle());
			return; // WIN
		}
		closedSet.add(current);
		std::cout << "TEST 2" << std::endl;
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
			std::cout << "TEST 3" << std::endl;
			iAttemptScore = current->iGetgScore() + 1;
			neighbor[i]->SetgScore(iAttemptScore);
			neighbor[i]->SetPriority(iAttemptScore + ManhattanHeuristic(neighbor[i], goal));
			if (closedSet.find(neighbor[i]))
			{
				delete neighbor[i];
				continue;
			}
			if ((EltInOpenset = openSet.PopOutOfQueue(neighbor[i])) != NULL)
			{
				std::cout << "PUSH 1" << std::endl;
				printTable(current->vecGetPuzzle());
				openSet.push(neighbor[i]);
				neighbor[i]->SetCameFrom(current);
			}
			else
			{
				if (neighbor[i]->iGetgScore() >= iAttemptScore)
				{
					std::cout << "PUSH 2" << std::endl;
					printTable(current->vecGetPuzzle());
					std::cout << "TEST1" << std::endl;
					neighbor[i]->SetCameFrom(current);;
					std::cout << "TEST2 " <<  neighbor[i] <<std::endl;
					openSet.push(neighbor[i]);
					std::cout << "TEST3" << std::endl;
					delete EltInOpenset;
				}
				else
				{
					delete neighbor[i];
				}
			}
		}
		std::cout << "TEST 4" << std::endl;
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
