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

AStar::AStar(std::vector<int> & Start, std::vector<int> & Goal) : vecStart(Start), vecGoal(Goal)
{
	Compute();
}

void AStar::Compute()
{
	std::priority_queue<Puzzle, vector<Puzzle>, ComparePuzzle> closedSet;
	std::priority_queue<Puzzle, vector<Puzzle>, ComparePuzzle> openSet;
}