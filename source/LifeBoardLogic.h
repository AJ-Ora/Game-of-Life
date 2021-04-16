
#ifndef LIFEBOARDLOGIC_H
#define LIFEBOARDLOGIC_H

#pragma once

/*
* Implements the rules used in Conway's Game of Life.
*
* When using Step(), it creates a local copy of the board,
* and writes the new information back to the original board.
* 
* WARNING! Only use a single logic class
* to handle a single board at a time!
*/

#include "LifeBoard.h"

class LifeBoardLogic
{
public:
	void Step(LifeBoard& board);
};

#endif
