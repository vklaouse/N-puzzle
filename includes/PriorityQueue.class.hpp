// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PriorityQueue.template.hpp                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/01/23 13:30:58 by semartin          #+#    #+#             //
//   Updated: 2018/01/23 13:30:59 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <vector>
#include "Puzzle.class.hpp"

class PriorityQueue
{

private:
    int iSize;
    int iNbStates;

    class Queue
    {
    public:

        int iPriority;
        std::vector<Puzzle *> content;
        Queue * next;
    };

    Queue ** beginQueue;

public:

    PriorityQueue();
    ~PriorityQueue();

    bool empty();
    size_t size() { return iSize; };
    void push(Puzzle * elt);
	Puzzle * back() { return (*beginQueue)->content.back(); };
	void pop();
    Puzzle * bIsInQueue(Puzzle * elt); //POP THE ELT OUT

};