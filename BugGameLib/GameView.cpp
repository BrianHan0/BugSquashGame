/**
 * @file GameView.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include "BugGarbage.h"
#include "BugFeature.h"
#include "BugNull.h"
#include <memory>
#include "BugRedundancy.h"
#include "Laptop.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
	Create(parent, wxID_ANY,
		   wxDefaultPosition, wxDefaultSize,
		   wxFULL_REPAINT_ON_RESIZE);
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	Bind(wxEVT_PAINT, &GameView::OnPaint, this);
	Bind(wxEVT_TIMER, &GameView::OnTimer, this);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddBugFeature, this, IDM_BUGS_FEATURE);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddBugNull, this, IDM_BUGS_NULL);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddBugGarbage, this, IDM_BUGS_GARBAGE);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddBugRedundancy, this, IDM_BUGS_REDUNDANCY);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddLaptop, this, IDM_LAPTOP);
	Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnSwitchLevelZero, this, LEVEL_0);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnSwitchLevelOne, this, LEVEL_1);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnSwitchLevelTwo, this, LEVEL_2);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnSwitchLevelThree, this, LEVEL_3);

	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnShrink, this, SHRINK);

	auto filename = "../data/level1.xml";
	mGame.Load(filename);
	mGame.StartLevelOne();
	Refresh();

	mTimer.SetOwner(this);
	mTimer.Start(FrameDuration);
	mStopWatch.Start();
}

/**
 * Draws the game window class
 * @param event Paint event
 */
void GameView::OnPaint(wxPaintEvent &event)
{
	// Compute the time that has elapsed
	// since the last call to OnPaint.
	auto newTime = mStopWatch.Time();
	auto elapsed = (double)(newTime - mTime) * 0.001;
	mTime = newTime;

	mGame.Update(elapsed);

	// Create a double-buffered display context
	wxAutoBufferedPaintDC dc(this);

	// Clear the image to black
	wxBrush background(*wxWHITE);
	dc.SetBackground(background);
	dc.Clear();

	// Create a graphics context
	auto gc =
		std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

	// Tell the game class to draw
	wxRect rect = GetRect();
	mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

}

/**
 * Add menus specific to the view
 * @param mainFrame The main frame that owns the menu bar
 * @param menuBar The menu bar to add menus to
 * @param fileMenu The file menu, so we can add to it if we wish
 */
void GameView::AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* fileMenu)
{
	auto bugMenu = new wxMenu();

	AddBugMenuOption(mainFrame, bugMenu, IDM_BUGS_GARBAGE, L"&Garbage Bug", L"Add a Garbage Bug");
	AddBugMenuOption(mainFrame, bugMenu, IDM_BUGS_GARBAGE_FAT, L"Fat Ga&rbage Bug", L"Add a fat Garbage Bug");
	AddBugMenuOption(mainFrame, bugMenu, IDM_BUGS_NULL, L"&Null Bug", L"Add a Null Bug");
	AddBugMenuOption(mainFrame, bugMenu, IDM_BUGS_NULL_FAT, L"Fat N&ull Bug", L"Add a fat Null Bug");
	AddBugMenuOption(mainFrame, bugMenu, IDM_BUGS_REDUNDANCY, L"Redundancy Fly", L"Add a Redundancy Fly");
	AddBugMenuOption(mainFrame, bugMenu, IDM_BUGS_REDUNDANCY_FAT, L"Fat Redundancy Fly", L"Add a fat Redundancy Fly");
	AddBugMenuOption(mainFrame, bugMenu, IDM_BUGS_FEATURE, L"Feature", L"Add a Feature \"Bug\"");
	AddBugMenuOption(mainFrame, bugMenu, IDM_LAPTOP, L"Laptop", L"Add a Laptop");

	menuBar->Append(bugMenu, L"A&dd Bug");
}

/**
 * A menu to add bug
 * @param mainFrame add the bug
 * @param menu the menu option
 * @param id the unique id to get the type of bug
 * @param text text to add
 * @param help help option(?)
 */
void GameView::AddBugMenuOption(wxFrame *mainFrame, wxMenu *menu, int id,
								const std::wstring& text, const std::wstring& help)
{
	menu->Append(id, text, help);
	mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAddBugMenuOption, this, id);
}

/**
 * Menu event handler for all known types of bugs
 * @param event Menu event
 */
void GameView::OnAddBugMenuOption(wxCommandEvent& event)
{

}

/**
 * Handles the mouse left down event
 * @param event Mouse event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
	mGrabbedItem = mGame.HitTest(event.GetX(),event.GetY());
	if(mGrabbedItem != nullptr)
	{

		if (mGrabbedItem->CanSplit())
		{
			// get the location of the bug
			auto x = mGrabbedItem->GetX();
			auto y = mGrabbedItem->GetY();

			// create a new bug that is the same type as the one we just split
			auto bug = std::make_shared<BugRedundancy>(&mGame);
			// generate a random number to offset the new bugs
			auto randX = rand() % 100 * 1.5;
			auto randY = rand() % 100 * 1.5;
			bug->SetLocation(x + randX, y + randY);
			mGame.Add(bug);


			bug->NotSplitable();
			auto bug1 = std::make_shared<BugRedundancy>(&mGame);
			randX = rand() % 100 * 1.5;
			randY = rand() % 100 * 1.5;
			bug1->SetLocation(x + randX, y + randY);
			mGame.Add(bug1);
			bug1->NotSplitable();


			auto bug2 = std::make_shared<BugRedundancy>(&mGame);
			randX = rand() % 100 * 1.5;
			randY = rand() % 100 * 1.5;
			bug2->SetLocation(x + randX, y + randY);
			bug2->NotSplitable();
			mGame.Add(bug2);
		}
		mGrabbedItem->Splat();
		mGame.GetScoreboard()->IncrementFixedScore();
		Refresh();
	}
}


/**
 * A handler to add the Feature Bug
 * @param event Mouse event
 */
void GameView::OnAddBugFeature(wxCommandEvent& event)
{
	auto bug = std::make_shared<BugFeature>(&mGame);
	mGame.Add(bug);
	Refresh();
}

/**
 * A handler to add the Feature Bug
 * @param event Mouse event
 */
void GameView::OnAddBugNull(wxCommandEvent& event)
{
	auto bug = std::make_shared<BugNull>(&mGame);
	mGame.Add(bug);
	Refresh();
}

/**
 * A handler to add the Garbage Bug
 * @param event Mouse event
 */
void GameView::OnAddBugGarbage(wxCommandEvent& event)
{
	auto bug = std::make_shared<BugGarbage>(&mGame);
	mGame.Add(bug);
	Refresh();
}

/**
 * A handler to add the Redundancy Bug
 * @param event Mouse event
 */
void GameView::OnAddBugRedundancy(wxCommandEvent& event)
{
	auto bug = std::make_shared<BugRedundancy>(&mGame);
	mGame.Add(bug);
	Refresh();
}

/**
 * A handler to add Laptop
 * @param event Mouse event
 */
void GameView::OnAddLaptop(wxCommandEvent& event)
{
	auto laptop = std::make_shared<Laptop>(&mGame);
	mGame.Add(laptop);
	Refresh();
}

/**
 * Refresh the game
 * @param event Mouse event
 */
void GameView::OnTimer(wxTimerEvent &event){
	Refresh();
}

/**
 * An event on what to do when a bug is clicked
 * @param event Mouse event
 */
void GameView::OnClick(wxMouseEvent& event)
{

}

/**
 * Helps load level zero and calls starting function
 * @param event Mouse event
 */
void GameView::OnSwitchLevelZero(wxCommandEvent &event)
{
	auto filename = "../data/level0.xml";
	mGame.Load(filename);
	mGame.StartLevelZero();
	Refresh();
}

/**
 * Helps load level one and calls starting function
 * @param event Mouse event
 */
void GameView::OnSwitchLevelOne(wxCommandEvent &event)
{
	auto filename = "../data/level1.xml";
	mGame.Load(filename);
	mGame.StartLevelOne();
	Refresh();
}

/**
 * Helps load level two and calls starting function
 * @param event Mouse event
 */
void GameView::OnSwitchLevelTwo(wxCommandEvent &event)
{
	auto filename = "../data/level2.xml";
	mGame.Load(filename);
	mGame.StartLevelTwo();
	Refresh();
}

/**
 * Helps load level three and calls starting function
 * @param event Mouse event
 */
void GameView::OnSwitchLevelThree(wxCommandEvent &event)
{
	auto filename = "../data/level3.xml";
	mGame.Load(filename);
	mGame.StartLevelThree();
	Refresh();
}

/**
 * Resets the screen to the default
 * @param event The WX event
 */
void GameView::Reset(wxCommandEvent &event)
{
	mGame.Reset();
	Refresh();

	// add the laptop
	auto laptop = std::make_shared<Laptop>(&mGame);
	mGame.Add(laptop);
	Refresh();

	auto bug = std::make_shared<BugFeature>(&mGame);
	mGame.Add(bug);
}

/**
 * Shrinks the screen
 * @param event The WX event
 */
void GameView::OnShrink(wxCommandEvent &event)
{
	bool shrunk = mGame.GetShrink();
	if (shrunk)
	{

	}
}
