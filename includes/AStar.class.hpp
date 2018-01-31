// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AStar.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/12/08 17:09:52 by semartin          #+#    #+#             //
//   Updated: 2017/12/08 17:09:52 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <ctgmath>
#include <fstream>
#include "Puzzle.class.hpp"
#include "PriorityQueue.class.hpp"
#include "ClosedSetTree.class.hpp"

class AStar
{

private:
	Puzzle * start;
	Puzzle * goal;

	ClosedSetTree closedSet;
	PriorityQueue openSet;

	int iSizePuzzle;
	int iNpuzzle;
	std::string Heuristic;

	void Compute();
	int fillValidNeighbor(Puzzle * current, std::vector<Puzzle *> & neighbor);

	int ManhattanHeuristic(Puzzle * current, Puzzle * goal);
	int LinearConflict(Puzzle * current, Puzzle * goal);
	int MisplaceTiles(Puzzle * current, Puzzle * goal);
	int TOORAC(Puzzle * current, Puzzle * goal); //Tiles out of row and column
	int NMaxSwap(Puzzle * current, Puzzle * goal);

	void printCameFrom(Puzzle *, int, int);
	void encodeDataVisu(Puzzle *, int, int);
	void getDataVisu(std::vector< std::vector<int> > *, int, Puzzle *);

	AStar();
	
public:
	AStar(std::vector<int> & Start, std::vector<int> & Goal, std::string);
	~AStar();

};