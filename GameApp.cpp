/**
 * @file GameApp.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "GameApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return
 */
bool GameApp::OnInit()
{
	wxInitAllImageHandlers();
	if (!wxApp::OnInit())
		return false;

	auto frame = new MainFrame();
	frame->Initialize();
	frame->Show(true);


	return true;
}