
#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#pragma once

#include <wx/wx.h>
#include "LifeBoard.h"

class DrawBoard : public wxPanel
{
public:
	DrawBoard(wxWindow* parent, LifeBoard* boardToDraw);

	void OnPaint(wxPaintEvent& evt);

private:
	LifeBoard* board;
};

#endif
