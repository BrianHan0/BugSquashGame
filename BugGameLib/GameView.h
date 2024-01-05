/**
 * @file GameView.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_GAMEVIEW_H
#define PROJECT_1_BUGGAMELIB_GAMEVIEW_H

#include "pch.h"
#include "ids.h"
#include "Game.h"

/**
 * The class for GameView derived from wxWindow
 */
class GameView : public wxWindow
{
private:
	/// The GameView's game
	Game mGame;

	/// The timer that allows for animation
	wxTimer mTimer;

	/// Stopwatch used to measure elapsed time
	wxStopWatch mStopWatch;

	/// The last stopwatch time
	long mTime = 0;

	/// any object that is being dragged
	std::shared_ptr<Item> mGrabbedItem;

public:
	void Initialize(wxFrame *parent);
	void OnPaint(wxPaintEvent &event);
	void OnClick(wxMouseEvent& event);
	void AddMenus(wxFrame *mainFrame, wxMenuBar *menuBar, wxMenu *fileMenu);
	void AddBugMenuOption(wxFrame *mainFrame, wxMenu *menu, int id, const std::wstring &text, const std::wstring &help);
	void OnAddBugMenuOption(wxCommandEvent &event);
	void OnLeftDown(wxMouseEvent &event);
	void OnAddBugFeature(wxCommandEvent &event);
	void OnAddBugNull(wxCommandEvent &event);
	void OnAddBugGarbage(wxCommandEvent &event);
	void OnAddBugRedundancy(wxCommandEvent &event);
	void OnAddLaptop(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);
	void Reset(wxCommandEvent &event);
	void OnSwitchLevelZero(wxCommandEvent &event);
	void OnSwitchLevelOne(wxCommandEvent &event);
	void OnSwitchLevelTwo(wxCommandEvent &event);
	void OnSwitchLevelThree(wxCommandEvent &event);
	void OnShrink(wxCommandEvent &event);
};
#endif //PROJECT_1_BUGGAMELIB_GAMEVIEW_H
