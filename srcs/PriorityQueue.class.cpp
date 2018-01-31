// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PriorityQueue.class.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/01/23 14:17:09 by semartin          #+#    #+#             //
//   Updated: 2018/01/23 14:17:09 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PriorityQueue.class.hpp"

void PriorityQueue::PrintQueue()
{
	Queue * tmp = *beginQueue;
	while (tmp)
	{
		std::cout << "Priority = " << tmp->iPriority <<  " et " <<  tmp->next << std::endl;
		tmp->content.PrintFullTree();
		tmp = tmp->next;
	}
}

PriorityQueue::PriorityQueue(size_t size) : iSizePuzzle(size)
{
    iSize = 0;
    beginQueue = new Queue *;
    *beginQueue = NULL;
}

PriorityQueue::~PriorityQueue()
{
    Queue * tmp = *beginQueue;
    Queue * sdTmp;

    while (tmp)
    {
        sdTmp = tmp->next;
        delete tmp;
        tmp = sdTmp;
    }
    delete beginQueue;
}

bool PriorityQueue::empty()
{
    if (iSize == 0)
        return true;
    else return false;
}

void PriorityQueue::push(Puzzle * elt)
{
    Queue * tmp;
	Queue * sdTmp;
    if (iSize == 0)
    {
		Queue * newQueue = new Queue(iSizePuzzle);
   	 	newQueue->content.add(elt);
		newQueue->iPriority = elt->iGetPriority();
    	newQueue->next = NULL;
        *beginQueue = newQueue;
		iSize++;
		iNbStates++;
    }
    else
    {
		iSize++;
		iNbStates++;
        tmp = *beginQueue;
		sdTmp = NULL;
        while (tmp)
        {
            if (tmp->iPriority == elt->iGetPriority())
            {
				tmp->content.add(elt);
				return;
            }
			else if (tmp->iPriority > elt->iGetPriority())
			{
				Queue * newQueue = new Queue(iSizePuzzle);
   	 			newQueue->content.add(elt);
				newQueue->iPriority = elt->iGetPriority();
    			newQueue->next = tmp;
				if (sdTmp == NULL)
				{
					*beginQueue = newQueue;
				}
				else
				{
					sdTmp->next = newQueue;
				}
				return;
			}
            else
            {
				sdTmp = tmp;
				tmp = tmp->next;
            }
        }
		Queue * newQueue = new Queue(iSizePuzzle);
   	 	newQueue->content.add(elt);
		newQueue->iPriority = elt->iGetPriority();
    	newQueue->next = NULL;
		sdTmp->next = newQueue;
    }
}

bool PriorityQueue::bIsInQueue(Puzzle * elt)
{
	Queue * tmp = *beginQueue;

	while (tmp)
	{
		if (tmp->iPriority > elt->iGetPriority())
		{
			return false;
		}
		else if (tmp->iPriority == elt->iGetPriority())
		{
			if (tmp->content.find(elt))
				return true;
			else
				return false;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	return false;
}

bool PriorityQueue::PopOutOfQueue(Puzzle * elt, bool * bBetterWay)
{
	Queue * tmp = *beginQueue;
	Queue * sdTmp = NULL;

	while (tmp)
	{
		bool bTest = false;
		bool bPuzzle = tmp->content.findToPop(elt, &bTest, bBetterWay);
		if (bTest)
		{
			if (sdTmp == NULL)
			{
				*beginQueue = tmp->next;
			}
			else
			{
				sdTmp->next = tmp->next;
			}
			delete tmp;
		}
		if (bPuzzle)
		{
			iSize--;
			return bPuzzle;
		}
		else
		{
			sdTmp = tmp;
			tmp = tmp->next;
		}
	}
	return false;
}

Puzzle * PriorityQueue::pop_back() 
{ 
	iSize--;
	bool test = false;
	Puzzle * tmp = (*beginQueue)->content.pop_back(&test); 
	if (test)
	{
		Queue * tmpQueue = (*beginQueue)->next;
		delete (*beginQueue);
		*beginQueue = tmpQueue;
	}
	return tmp;
}