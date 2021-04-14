
#ifndef LIFEBOARDLOGIC_H
#define LIFEBOARDLOGIC_H

#pragma once

#include "LifeBoard.h"

class LifeBoardLogic
{
public:
	LifeBoardLogic();
	~LifeBoardLogic();

	void Step(LifeBoard& board);
};

#endif
