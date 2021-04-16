
#ifndef LIFEBOARDDRAWING_H
#define LIFEBOARDDRAWING_H

#pragma once

/*
* Implements the functionality to turn LifeBoard data into renderable bitmaps.
* Not thread safe, but it should never write any data, only read.
*/

#include <wx/wx.h>

#include "LifeBoard.h"

class LifeBoardDrawing : public wxPanel
{
public:
	LifeBoardDrawing(wxWindow* parent, LifeBoard* boardToDraw);

	void OnPaint(wxPaintEvent& evt);

private:
	LifeBoard* board;
};

#endif
