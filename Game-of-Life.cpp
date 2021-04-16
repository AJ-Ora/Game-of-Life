// Game-of-Life.cpp : Defines the entry point for the application.
//

#include <string>

#include "wx/wx.h"
#include "wx/wfstream.h"

#include "source/LifeBoard.h"
#include "source/LifeBoardLogic.h"
#include "source/DrawBoard.h"

//void printDebugLoop(LifeBoard& board);

class golMain : public wxApp
{
public:
	virtual bool OnInit();
};

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
	DrawBoard* draw;
};

enum
{
	ID_Import = 1,
	ID_PlayPause = 2,
	ID_Step = 3
};

bool golMain::OnInit()
{
	golFrame* rootFrame = new golFrame();
	rootFrame->Show(true);
	return true;
}

golFrame::golFrame() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxDefaultPosition, wxSize(640, 480))
{
	draw = nullptr;
	
	wxMenu* file = new wxMenu;
	file->Append(ID_Import, "Import...", "Import an image file to get started.");
	file->AppendSeparator();
	file->Append(wxID_EXIT, "Exit", "Exit the program.");

	wxMenu* simulation = new wxMenu;
	simulation->AppendCheckItem(ID_PlayPause, "Auto-advance\tCtrl-Space", "Step the simulation forward automatically.");
	simulation->AppendSeparator();
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
	wxFileDialog openFileDialog(this, _("Import image file"), "", "", ".BMP files (*.bmp)|*.bmp", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

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

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	draw = new DrawBoard(this, &board);
	sizer->Add(draw, 1, wxSHAPED | wxALIGN_CENTER);
	this->SetSizer(sizer);
	
	std::string printText;
	printText.append(openFileDialog.GetFilename());
	printText.append(" | Width: ");
	printText.append(std::to_string(board.GetWidth()));
	printText.append("px | Height: ");
	printText.append(std::to_string(board.GetHeight()));
	printText.append("px");

	SetStatusText(printText);
}

void golFrame::OnExit(wxCommandEvent& evt)
{
	Close(true);
}

void golFrame::OnSimulate(wxCommandEvent& evt)
{
	
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

//int main(int argc, char* argv[])
//{
//	LifeBoard board;
//
//	if (argc == 2)
//	{
//		board.ImportImage(argv[1]);
//	}
//
//	if (!board.IsInitialized())
//	{
//		std::cout << "Board not initialized, returning..." << std::endl;
//		return -1;
//	}
//
//	printDebugLoop(board);
//
//	return 0;
//}

//void printDebugLoop(LifeBoard& board)
//{
//	LifeBoardLogic logic;
//	bool noCellsAlive = false;
//
//	while (!noCellsAlive)
//	{
//		system("cls");
//
//		logic.Step(board);
//
//		noCellsAlive = true;
//		for (int y = 0; y < board.GetHeight(); ++y)
//		{
//			for (int x = 0; x < board.GetWidth(); ++x)
//			{
//				if (board.GetPixelStatus(x, y) == true)
//				{
//					noCellsAlive = false;
//					std::cout << "o ";
//				}
//				else
//				{
//					std::cout << "  ";
//				}
//			}
//			std::cout << std::endl;
//		}
//
//		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 10));
//	}
//}
