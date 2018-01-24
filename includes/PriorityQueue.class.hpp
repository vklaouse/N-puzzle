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
#include "ClosedSetTree.class.hpp"

class PriorityQueue
{

private:
    size_t iSizePuzzle;
    int iSize;
    int iNbStates;

    class Queue
    {
    public:
        Queue(size_t iSize) : content(iSize) {};
        int iPriority;
        ClosedSetTree content;
        Queue * next;
    };

    Queue ** beginQueue;

    PriorityQueue();

public:

    PriorityQueue(size_t size);
    ~PriorityQueue();

    bool empty();
    size_t size() { return iSize; };
    void push(Puzzle * elt);
	Puzzle * pop_back() { return (*beginQueue)->content.pop_back(); };
	void pop();
    bool bIsInQueue(Puzzle * elt); //POP THE ELT OUT
    Puzzle * PopOutOfQueue(Puzzle * elt); //POP THE ELT OUT

};