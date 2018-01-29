// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Puzzle.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/12/08 17:26:17 by semartin          #+#    #+#             //
//   Updated: 2017/12/08 17:26:17 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <vector>
#include <ctgmath>

#define TURN_NOCHANGE 0
#define TURN_LEFT 1
#define TURN_RIGHT 2
#define TURN_BOT 3 
#define TURN_TOP 4

class Puzzle
{

private:
	std::vector<int> vecPuzzle;
	int iPriority;
	int igScore;
	int iEmptyPos;

	Puzzle *cameFrom;

	Puzzle() {};

public:
	Puzzle(size_t i);
	Puzzle(std::vector<int> &);
	~Puzzle() {};

	void setNewPuzzle(Puzzle * rhs, int iIndex);
	void SetgScore(int GScore) { igScore = GScore; };
	void SetPriority(int Prio) { iPriority = Prio; };
	void SetCameFrom(Puzzle * old) { cameFrom = old; } ;

	int iGetgScore() const { return igScore; };
	int iGetPriority() const { return iPriority; };
	int iGetEmptyPos() const { return iEmptyPos; };
	std::vector<int> & vecGetPuzzle() { return vecPuzzle; };
	Puzzle * GetCameFrom() { return cameFrom; };

	bool operator==(Puzzle & rhs);

};

class ComparePuzzle
{

public:
	bool operator()(Puzzle * Puzzle1, Puzzle * Puzzle2);

};
