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

static void printTable(std::vector<int> iTaquinBoard, int size = 0) {
	for (size_t i = 0; i < iTaquinBoard.size(); i++) 
	{
		if (size == 0)
			std::cout << iTaquinBoard[i] << "  ";
		else
		{
			if (!(i % size))
				std::cout << std::endl;
			if (iTaquinBoard[i] == 0)
				std::cout << "\033[33m" << iTaquinBoard[i] << "\033[m  ";
			else
				std::cout << iTaquinBoard[i] << "  ";
		}
	}
	std::cout << std::endl;
	
}


void AStar::printCameFrom(Puzzle * p, int Priority, int size)
{
	if (p->GetCameFrom() && Priority != 0)
	{
		printCameFrom(p->GetCameFrom(), Priority - 1, size);
		printTable(p->GetCameFrom()->vecGetPuzzle(), size);
	}
	return ;
}

void AStar::encodeDataVisu(Puzzle * p, int Priority, int size)
{
	std::vector< std::vector<int> > res(Priority + 1 , std::vector<int>(size * size));
	std::string encodedData = "let size = " + std::to_string(size) + ";\nlet puzzleStates = [\n";

	getDataVisu(&res, Priority, p);
	res[Priority] = p->vecGetPuzzle();
	for (size_t i = 0; i < res.size(); i++)
	{
		encodedData += "\t[";
		for (size_t j = 0; j < res[i].size(); j++)
		{
			encodedData += std::to_string(res[i][j]);
			if ((j + 1) < res[i].size())
				encodedData += ", ";
		}
		encodedData += "]";
		if ((i + 1) < res.size())
			encodedData += ",\n";
		else
			encodedData += "];";
	}

	std::ofstream fichier("visu/data.js", std::ios::out | std::ios::trunc);
	if (fichier)
	{
		fichier << encodedData;
		fichier.close();
	}
	return ;
}

void AStar::getDataVisu(std::vector< std::vector<int> > * res, int Priority, Puzzle * p)
{
	if (p->GetCameFrom() && Priority >= 1)
	{
		getDataVisu(res, Priority - 1, p->GetCameFrom());
		res->at(Priority - 1) = p->GetCameFrom()->vecGetPuzzle();
	}
	return ;

}

AStar::AStar(std::vector<int> & vecStart, std::vector<int> & vecGoal, std::string h) : closedSet(vecStart.size()), openSet(vecStart.size()), Heuristic(h)
{
	start = new Puzzle(vecStart);
	goal = new Puzzle(vecGoal);
	iSizePuzzle = vecStart.size();
	iNpuzzle = sqrt(iSizePuzzle);
	Compute();
}

AStar::~AStar()
{
	delete goal;
}

void AStar::Compute()
{
	std::vector<int> wayTaken;

	start->SetgScore(0);
	start->SetPriority(LinearConflict(start, goal));
	openSet.push(start);
	
	int iAttemptScore;

	std::vector<Puzzle *> neighbor;
	Puzzle * current;

	int l = 0;
	while (openSet.size() > 0)
	{
		current = openSet.pop_back();
		if (l < current->iGetPriority())
		{
			l = current->iGetPriority();
			std::cout << "Priority = " << current->iGetPriority()  << " et empty pos = " << current->iGetEmptyPos() << std::endl;
			std::cout << "Size openset = " << openSet.size() << " et Size closedset = " << closedSet.size() << std::endl;
			printTable(current->vecGetPuzzle());
		}
		if (*current == *goal)
		{
			printCameFrom(current, current->iGetPriority(), iNpuzzle);
			encodeDataVisu(current, current->iGetPriority(), iNpuzzle);
			std::cout << "Priority = " << current->iGetPriority()  << " et empty pos = " << current->iGetEmptyPos() << std::endl;
			printTable(current->vecGetPuzzle());
			delete current;
			return;
		}
		closedSet.add(current);
		int iNumNeighbor = fillValidNeighbor(current, neighbor);
		for (int i = 0; i < iNumNeighbor; i++)
		{
			if (neighbor[i] == NULL)
			{
				std::cerr << "NEW ERROR" << std::endl;
				exit(0); 
			}
		}
		for (int i = 0; i < iNumNeighbor; i++)
		{
			iAttemptScore = current->iGetgScore() + 1;
			neighbor[i]->SetgScore(iAttemptScore);
			neighbor[i]->SetPriority(iAttemptScore + LinearConflict(neighbor[i], goal));
			neighbor[i]->SetCameFrom(current);
			if (closedSet.find(neighbor[i]))
			{
				delete neighbor[i];
				continue;
			}
			bool bBetterWay = true;
			if (openSet.PopOutOfQueue(neighbor[i], &bBetterWay))
			{
				openSet.push(neighbor[i]);
			}
			else if (!bBetterWay)
			{
				delete neighbor[i];
			}
			else
			{
				openSet.push(neighbor[i]);
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
	for (int i = 0; i < iSizePuzzle; i++)
	{
		if (i == current->iGetEmptyPos())
			continue;
		for (int j = 0; j < iSizePuzzle; j++)
		{
			if (current->vecGetPuzzle()[i] == goal->vecGetPuzzle()[j])
			{
				if (i / iNpuzzle == j / iNpuzzle)
				{
					int iStartLine = (i / iNpuzzle) * iNpuzzle;
					for (int k = iStartLine; k < iStartLine + iNpuzzle; k++)
					{
						if (k == current->iGetEmptyPos() || k == i)
							continue;
						for (int l = iStartLine; l < iStartLine + iNpuzzle; l++)
						{
							if (current->vecGetPuzzle()[k] == goal->vecGetPuzzle()[l])
							{
								if (i < j && k > l)
								{
									h += 2;
								}
							}
						}
					}
				}

				if (i % iNpuzzle == j % iNpuzzle)
				{
					int iStartLine = i % iNpuzzle;
					for (int k = iStartLine; k < iStartLine + iNpuzzle * (iNpuzzle - 1);)
					{
						if (k == current->iGetEmptyPos() || k == i)
						{
							k += iNpuzzle;
							continue;
						}
						for (int l = iStartLine; l < iStartLine + iNpuzzle * (iNpuzzle - 1);)
						{
							if (current->vecGetPuzzle()[k] == goal->vecGetPuzzle()[l])
							{
								if (i < j && k > l)
								{
									h += 2;
								}
							}
							l += iNpuzzle;
						}
						k += iNpuzzle;
					}
				}
				h += abs((i % iNpuzzle) - (j % iNpuzzle));
				h += abs((i / iNpuzzle) - (j / iNpuzzle));
				break;
			}
		}
	}
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
					tmp.vecGetPuzzle()[tmp.iGetEmptyPos()] = tmp.vecGetPuzzle()[i];
					tmp.vecGetPuzzle()[i] = 0;
					tmp.SetEmptyPos(i);
					break;
				}
			}
		}
		h++;
	}
 	return h;
}
