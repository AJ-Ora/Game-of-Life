// Game-of-Life.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <thread>
#include <chrono>

#include "wx/wx.h"
#include "wx/wfstream.h"

#include "source/LifeBoard.h"
#include "source/LifeBoardLogic.h"

void printDebugLoop(LifeBoard& board);

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
	void OnImport(wxCommandEvent& cmdEvt);
	void OnExit(wxCommandEvent& cmdEvt);

	LifeBoard board;
};

enum
{
	ID_Import = 1
};

bool golMain::OnInit()
{
	golFrame* rootFrame = new golFrame();
	rootFrame->Show(true);
	return true;
}

golFrame::golFrame() : wxFrame(nullptr, wxID_ANY, "Game of Life")
{
	wxMenu* file = new wxMenu;
	file->Append(ID_Import, "Import...", "Import an image file to get started.");
	file->AppendSeparator();
	file->Append(wxID_EXIT, "Exit", "Exit the program.");

	wxMenuBar* topBar = new wxMenuBar;
	topBar->Append(file, "File");

	SetMenuBar(topBar);

	CreateStatusBar();
	//SetStatusText("Welcome to Conway's Game of Life!");

	Bind(wxEVT_MENU, &golFrame::OnImport, this, ID_Import);
	Bind(wxEVT_MENU, &golFrame::OnExit, this, wxID_EXIT);
}

void golFrame::OnImport(wxCommandEvent& cmdEvt)
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

	SetStatusText("Successfully imported image.");
}

void golFrame::OnExit(wxCommandEvent& cmdEvt)
{
	Close(true);
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

void printDebugLoop(LifeBoard& board)
{
	LifeBoardLogic logic;
	bool noCellsAlive = false;

	while (!noCellsAlive)
	{
		system("cls");

		logic.Step(board);

		noCellsAlive = true;
		for (int y = 0; y < board.GetHeight(); ++y)
		{
			for (int x = 0; x < board.GetWidth(); ++x)
			{
				if (board.GetPixelStatus(x, y) == true)
				{
					noCellsAlive = false;
					std::cout << "o ";
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 10));
	}
}
