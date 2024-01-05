/**
 * @file MainFrame.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
	Create(nullptr, wxID_ANY, L"Bug Squash",
		   wxDefaultPosition,  wxSize( 1000,800 ));

	// Create a sizer that will lay out child windows vertically
	// one above each other
	auto sizer = new wxBoxSizer( wxVERTICAL );

	// Create the view class object as a child of MainFrame
	auto gameView = new GameView();
	mGameView = gameView;

	mGameView->Initialize(this);

	// Add it to the sizer
	sizer->Add(gameView ,1, wxEXPAND | wxALL );

	// Set the sizer for this frame
	SetSizer( sizer );

	// Layout (place) the child windows.
	Layout();

	auto menuBar = new wxMenuBar();

	auto fileMenu = new wxMenu();
	auto levelMenu = new wxMenu();
	auto helpMenu = new wxMenu();
	auto shrinkMenu = new wxMenu();
	auto bugMenu = new wxMenu();

	fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save city as...");
	fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open city file...");

	bugMenu->Append(IDM_BUGS_GARBAGE, L"&Garbage Bug", L"Add a Garbage Bug");
	bugMenu->Append(IDM_BUGS_GARBAGE_FAT, L"&Fat Garbage Bug", L"Add a Fat Garbage Bug");
	bugMenu->Append(IDM_BUGS_NULL, L"&Null Bug", L"Add a Null Bug");
	bugMenu->Append(IDM_BUGS_NULL_FAT, L"Fat N&ull Bug", L"Add a fat Null Bug");
	bugMenu->Append(IDM_BUGS_REDUNDANCY, L"Redundancy Fly", L"Add a Redundancy Fly");
	bugMenu->Append(IDM_BUGS_FEATURE, L"F&eature", L"Add a Feature \"Bug\"");
	bugMenu->Append(IDM_LAPTOP, L"&Laptop", L"Add a Laptop");

	levelMenu->Append(LEVEL_0, L"&Level 0", L"Loads level 0");
	levelMenu->Append(LEVEL_1, L"&Level 1", L"Loads level 1");
	levelMenu->Append(LEVEL_2, L"&Level 2", L"Loads level 2");
	levelMenu->Append(LEVEL_3, L"&Level 3", L"Loads level 3");

	shrinkMenu->Append(SHRINK, L"&Shrink", L"Shrinks game");

	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFileSaveAs, this, wxID_SAVEAS);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFileOpen, this, wxID_OPEN);

	menuBar->Append(fileMenu, L"&File" );
	menuBar->Append(bugMenu, L"&Add Bug");
	menuBar->Append(levelMenu, L"&Level");
	menuBar->Append(shrinkMenu, L"&View");
	menuBar->Append(helpMenu, L"&Help");

	SetMenuBar(menuBar);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent &event)
{
	Close(true);
}

/**
 * Application about box menu handler
 * @param event Menu event
 */
void MainFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox(L"Flora Team's Project 1",
				 L"Bug Squash",
				 wxOK | wxCENTRE,
				 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent &event)
{
	Destroy();
}

/**
 * File>Save As menu handler
 * @param event Menu event
 */
void MainFrame::OnFileSaveAs(wxCommandEvent &event)
{

}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void MainFrame::OnFileOpen(wxCommandEvent &event)
{

}
