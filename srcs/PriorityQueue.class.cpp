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
		std::cout << "Priority = " << tmp->iPriority << std::endl;
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
//	std::cout << " COMPTEUR PUSH" << iSize << std::endl;
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
//		std::cout << "YOLO?? : " <<  tmp << std::endl;
        while (tmp)
        {
            if (tmp->iPriority == elt->iGetPriority())
            {
//				std::cout << "YOLO" << std::endl;
				tmp->content.add(elt);
				return;
            }
			else if (tmp->iPriority > elt->iGetPriority())
			{
//				std::cout << "YOLO3" << std::endl;
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
//				std::cout << "YOLO2" << std::endl;
				sdTmp = tmp;
				tmp = tmp->next;
            }
        }
		Queue * newQueue = new Queue(iSizePuzzle);
   	 	newQueue->content.add(elt);
		newQueue->iPriority = elt->iGetPriority();
    	newQueue->next = NULL;
//		std::cout << "HERE : "<< iSize << std::endl;
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

Puzzle * PriorityQueue::PopOutOfQueue(Puzzle * elt, bool * bBetterWay)
{
//	std::cout << " COMPTEUR POP_OUT_OF_QUEUE " << iSize << std::endl;
	Queue * tmp = *beginQueue;
	Queue * sdTmp = NULL;

	while (tmp)
	{
		if (tmp->iPriority > elt->iGetPriority())
		{
//			std::cout << "OUT 1" << std::endl;
			return NULL;
		}
		else if (tmp->iPriority == elt->iGetPriority())
		{
			bool bTest = false;
			Puzzle * tmpPuzzle = tmp->content.findToPop(elt, &bTest, bBetterWay);
//			std::cout << "HERE = " <<  tmpPuzzle << " et " <<  bTest << std::endl;
			if (bTest)
			{
//				std::cout << "-----------------------------------" << std::endl;
				if (sdTmp == NULL)
				{
//					std::cout << "YOU ARE THE PROBLEME" << std::endl;
					*beginQueue = tmp->next;
				}
				else
				{
					sdTmp->next = tmp->next;
				}
				delete tmp;
			}
//			std::cout << "OUT 2 " <<  tmpPuzzle<< std::endl;
			if (tmpPuzzle)
				iSize--;
			return tmpPuzzle;
		}
		else
		{
			sdTmp = tmp;
			tmp = tmp->next;
		}
	}
//	std::cout << "OUT 1" << std::endl;
	return NULL;
}

Puzzle * PriorityQueue::pop_back() 
{ 
//	std::cout << " COMPTEUR POP_BACK " << iSize << std::endl;
	iSize--;
	bool test = false;
	Puzzle * tmp = (*beginQueue)->content.pop_back(&test); 
	if (test)
	{
		Queue * tmpQueue = (*beginQueue)->next;
		delete (*beginQueue);
		*beginQueue = tmpQueue;
	}
//	std::cout << " COMPTEUR POP_BACK END " << iSize << std::endl;
	return tmp;
}