
#ifndef LIFEBOARDDRAWING_H
#define LIFEBOARDDRAWING_H

#pragma once

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
