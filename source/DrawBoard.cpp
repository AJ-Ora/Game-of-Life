
#include "DrawBoard.h"

DrawBoard::DrawBoard(wxWindow* parent, LifeBoard* boardToDraw) : wxPanel(parent)
{
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(DrawBoard::OnPaint));
	this->Centre();
	
	board = boardToDraw;
}

void DrawBoard::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
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
}
