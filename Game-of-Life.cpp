// Game-of-Life.cpp : Defines the entry point for the application.
//

#include <string>

#include "wx/wx.h"
#include "wx/wfstream.h"

#include "source/LifeBoard.h"
#include "source/LifeBoardLogic.h"
#include "source/LifeBoardDrawing.h"

/*
------------------------------------------
---------- FORWARD DECLARATIONS ----------
------------------------------------------
*/

class golMain : public wxApp
{
public:
	virtual bool OnInit();
};

// Implements main() or WinMain(), and enters OnInit() after wxWidgets is initialized.
wxIMPLEMENT_APP(golMain);

class golFrame : public wxFrame
{
public:
	golFrame();

private:
	void OnSize(wxSizeEvent& evt);
	void OnExit(wxCommandEvent& evt);

	void OnImport(wxCommandEvent& evt);
	void OnSimulate(wxCommandEvent& evt);
	void OnStep(wxCommandEvent& evt);

	void OnRender();

	LifeBoard board;
	LifeBoardDrawing* draw;
	wxBoxSizer* sizer;
};

/*
------------------------------------------
----------- EVENT NUMBER TABLE -----------
------------------------------------------
*/

enum
{
	ID_Import = 1,
	ID_PlayPause = 2,
	ID_Step = 3
};

/*
------------------------------------------
----------- MAIN FUNCTIONALITY -----------
------------------------------------------
*/

bool golMain::OnInit()
{
	golFrame* rootFrame = new golFrame();
	rootFrame->Show(true);
	return true;
}

/*
------------------------------------------
---------- FRAME FUNCTIONALITY -----------
------------------------------------------
*/

golFrame::golFrame() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxDefaultPosition, wxSize(640, 480))
{
	sizer = new wxBoxSizer(wxHORIZONTAL);
	draw = new LifeBoardDrawing(this, &board);
	sizer->Add(draw, 1, wxSHAPED | wxALIGN_CENTER);
	this->SetSizer(sizer);
	
	wxMenu* file = new wxMenu;
	file->Append(ID_Import, "Import...", "Import an image file to get started.");
	file->AppendSeparator();
	file->Append(wxID_EXIT, "Exit", "Exit the program.");

	wxMenu* simulation = new wxMenu;

	// Remove auto-advance feature for now, as it's not implemented yet.

	//simulation->AppendCheckItem(ID_PlayPause, "Auto-advance\tCtrl-Space", "Step the simulation forward automatically.");
	//simulation->AppendSeparator();

	simulation->Append(ID_Step, "Step\tSpace", "Step the simulation forward by one frame.");

	wxMenuBar* topBar = new wxMenuBar;
	topBar->Append(file, "File");
	topBar->Append(simulation, "Simulation");

	SetMenuBar(topBar);

	CreateStatusBar();
	SetStatusText("Welcome to Conway's Game of Life!");

	Bind(wxEVT_SIZE, &golFrame::OnSize, this);
	Bind(wxEVT_MENU, &golFrame::OnExit, this, wxID_EXIT);

	Bind(wxEVT_MENU, &golFrame::OnImport, this, ID_Import);
	Bind(wxEVT_MENU, &golFrame::OnSimulate, this, ID_PlayPause);
	Bind(wxEVT_MENU, &golFrame::OnStep, this, ID_Step);
}

void golFrame::OnSize(wxSizeEvent& evt)
{
	if (draw == nullptr)
	{
		return;
	}

	OnRender();
	evt.Skip();
}

void golFrame::OnImport(wxCommandEvent& evt)
{
	wxFileDialog openFileDialog(this, _("Import image file"), "", "", "Portable Network Graphics (*.png)|*.png|Bitmap image file (*.bmp)|*.bmp", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
	{
		return;
	}

	wxFileInputStream input(openFileDialog.GetPath());
	if (!input.IsOk())
	{
		wxLogError("Cannot open file '%s'!", openFileDialog.GetFilename());
		SetStatusText("Failed to import image!");
		return;
	}

	board.ImportImage(openFileDialog.GetPath().ToStdString());

	if (!board.IsInitialized())
	{
		wxLogError("Couldn't initialize board with '%s'!", openFileDialog.GetFilename());
		SetStatusText("Failed to import image!");
		return;
	}
	
	std::string printText;
	printText.append(openFileDialog.GetFilename());
	printText.append(" | Width: ");
	printText.append(std::to_string(board.GetWidth()));
	printText.append("px | Height: ");
	printText.append(std::to_string(board.GetHeight()));
	printText.append("px");

	SetStatusText(printText);
	OnRender();
}

void golFrame::OnExit(wxCommandEvent& evt)
{
	Close(true);
}

void golFrame::OnSimulate(wxCommandEvent& evt)
{
	wxLogError("OnSimulate not implemented!");
}

void golFrame::OnStep(wxCommandEvent& evt)
{
	LifeBoardLogic logic;
	logic.Step(board);
	OnRender();
}

void golFrame::OnRender()
{
	draw->Refresh();
}
