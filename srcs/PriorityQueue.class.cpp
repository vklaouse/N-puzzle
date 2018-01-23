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

PriorityQueue::PriorityQueue()
{
    iSize = 0;
    beginQueue = new Queue *;
    *beginQueue = NULL;
}

PriorityQueue::~PriorityQueue()
{
    Queue * tmp = *beginQueue;
    Queue * sdTmp;

    while (beginQueue)
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
		Queue * newQueue = new Queue;
   	 	newQueue->content.push_back(elt);
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
				tmp->content.push_back(elt);
				return;
            }
			else if (tmp->iPriority < elt->iGetPriority())
			{
				Queue * newQueue = new Queue;
   	 			newQueue->content.push_back(elt);
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
		Queue * newQueue = new Queue;
   	 	newQueue->content.push_back(elt);
		newQueue->iPriority = elt->iGetPriority();
    	newQueue->next = NULL;
		sdTmp->next = newQueue;
    }
}

void PriorityQueue::pop()
{
	Queue *tmp = *beginQueue;

	iSize--;
	if (tmp->content.size() == 1)
	{
		*beginQueue = tmp->next;
		delete tmp;	
	}
	else
	{
		tmp->content.pop_back();
	}
}

Puzzle * PriorityQueue::bIsInQueue(Puzzle * elt)
{
	Queue * tmp = *beginQueue;
	Queue * sdTmp = NULL;

	while (tmp)
	{
		if (tmp->iPriority < elt->iGetPriority())
		{
			return NULL;
		}
		else if (tmp->iPriority == elt->iGetPriority())
		{
			for (size_t i = 0; i < tmp->content.size(); i++)
			{
				if (tmp->content[i] == elt)
				{
					iSize--;
					Puzzle * tmpPuzzle = tmp->content[i];
					if (tmp->content.size() == 1)
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
					else
					{
						tmp->content.erase(tmp->content.begin() + i);
					}
					return tmpPuzzle;
				}
			}
			return NULL;
		}
		else
		{
			sdTmp = tmp;
			tmp = tmp->next;
		}
	}
	return NULL;
}