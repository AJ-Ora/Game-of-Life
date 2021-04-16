
#include "LifeBoardDrawing.h"

#include <wx/wx.h>

LifeBoardDrawing::LifeBoardDrawing(wxWindow* parent, LifeBoard* boardToDraw) : wxPanel(parent)
{
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(LifeBoardDrawing::OnPaint));
	this->Centre();
	
	board = boardToDraw;
}

void LifeBoardDrawing::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);

	if (!board->IsInitialized())
	{
		evt.Skip();
		return;
	}

	int rescaledWidth, rescaledHeight;
	dc.GetSize(&rescaledWidth, &rescaledHeight);

	if (rescaledWidth <= 0 || rescaledHeight <= 0)
	{
		evt.Skip();
		return;
	}

	unsigned char* imageData = board->ToRGB();
	wxImage image(board->GetWidth(), board->GetHeight(), imageData, true);

	wxBitmap bitmap = wxBitmap(image.Scale(rescaledWidth, rescaledHeight), wxBITMAP_SCREEN_DEPTH);

	dc.DrawBitmap(bitmap, 0, 0, false);

	delete[] imageData;
	evt.Skip();
}
