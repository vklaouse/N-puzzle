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

bool ComparePuzzle::operator()(Puzzle & Puzzle1, Puzzle & Puzzle2)
{
	if (Puzzle1.iGetPriority() < Puzzle2.iGetPriority())
		return true;
	else
		return false;
}