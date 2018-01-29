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

	void Compute();
	int fillValidNeighbor(Puzzle * current, std::vector<Puzzle *> & neighbor);

	int ManhattanHeuristic(Puzzle * current, Puzzle * goal);

	AStar();
	
public:
	AStar(std::vector<int> & Start, std::vector<int> & Goal);
	~AStar() { };

};