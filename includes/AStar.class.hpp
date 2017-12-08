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
#include "Puzzle.class.hpp"

class AStar
{

private:
	std::vector<int> vecStart;
	std::vector<int> vecGoal;

	void Compute();

	AStar();
	
public:
	AStar(std::vector<int> & Start, std::vector<int> & Goal);
	~AStar();

};