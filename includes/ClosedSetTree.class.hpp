// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ClosedSetTree.class.hpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/01/24 14:32:05 by semartin          #+#    #+#             //
//   Updated: 2018/01/24 14:32:05 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <list>
#include "Puzzle.class.hpp"

class ClosedSetTree
{

private:
	class Node
	{
	public:
		int content;
		std::list<Node *> nextNode;
		Puzzle * currentPuzzle;
	};

	Puzzle * tmpMemory;
	bool bMemDelete;
	bool bMemory;
	Node * beginTree;
	size_t iSize;
	size_t iSizeCloseSet;
	ClosedSetTree();
	void FillTree(Puzzle * elt, size_t i, bool bExist, Node * current);
	bool findElt(Puzzle *elt, size_t i, Node * current);
	bool recPopBack(size_t i, Node * current);
	bool findEltToPop(Puzzle *elt, size_t i, Node * current, bool *);
	void printTreeRec(size_t i, Node * current);
	void FreeFullTree(size_t i, Node *current);

public:
	ClosedSetTree(size_t);
	~ClosedSetTree();

	void add(Puzzle *);
	size_t size() const { return iSizeCloseSet; };
	bool find(Puzzle *);
	Puzzle * pop_back(bool *);
	bool findToPop(Puzzle *, bool *, bool *);

	void PrintFullTree();

};