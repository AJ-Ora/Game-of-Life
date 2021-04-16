
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

	float ratio = (float)board->GetWidth() / (float)board->GetHeight();

	if (ratio <= 1.0f)
	{
		// Width is smaller
		rescaledWidth = (int)round(rescaledWidth * ratio);
	}
	else
	{
		// Height is smaller
		rescaledHeight = (int)round(rescaledHeight / ratio);
	}

	unsigned char* imageData = board->ToRGB();
	wxImage image(board->GetWidth(), board->GetHeight(), imageData, true);

	wxBitmap bitmap = wxBitmap(image.Scale(rescaledWidth, rescaledHeight), wxBITMAP_SCREEN_DEPTH);

	if (ratio <= 1.0f)
	{
		dc.DrawBitmap(bitmap, (int)round((float)(rescaledHeight - rescaledWidth) / 2.0f), 0, false);
	}
	else
	{
		dc.DrawBitmap(bitmap, 0, (int)round((float)(rescaledWidth - rescaledHeight) / 2.0f), false);
	}

	delete[] imageData;
	evt.Skip();
}
