
#ifndef LIFEBOARDLOGIC_H
#define LIFEBOARDLOGIC_H

#pragma once

/*
* Implements the rules used in Conway's Game of Life.
*
* When using Step(), it creates a local copy of the board,
* and writes the new information back to the original board.
* 
* NOT THREAD SAFE!
*/

#include "LifeBoard.h"

class LifeBoardLogic
{
public:
	void Step(LifeBoard& board);
};

#endif
