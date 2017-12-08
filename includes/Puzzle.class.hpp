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

class Puzzle
{

private:
	std::vector<int> vecPuzzle;
	int iPriority;

public:
	int iGetPriority() { return iPriority; };

};

class ComparePuzzle
{

public:
	bool operator()(Puzzle & Puzzle1, Puzzle & Puzzle2);

}