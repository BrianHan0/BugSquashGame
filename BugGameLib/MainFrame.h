/**
 * @file MainFrame.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_MAINFRAME_H
#define PROJECT_1_BUGGAMELIB_MAINFRAME_H

#include "GameView.h"

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
	/// A pointer to the window's GameView
	GameView* mGameView = nullptr;

public:
	void Initialize();

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

	void OnFileSaveAs(wxCommandEvent& event);
	void OnFileOpen(wxCommandEvent& event);

};

#endif //PROJECT_1_BUGGAMELIB_MAINFRAME_H
