/**
 * @file Message.cpp
 * @author Sungu Han
 */

#include "Message.h"
#include "Game.h"

/**
 * Constructor for Message
 * @param currentLevel level that message is for
 * @param graphics Context that is drawn on
 * @param end state if level is completed
 */
void Message::Draw(std::shared_ptr<wxGraphicsContext> graphics, int currentLevel, bool end)
{
	wxFont font(wxSize(0,90),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_BOLD);
	graphics->SetFont(font, wxColour(255, 0, 0));

	if (currentLevel == 0)
	{
		if (end)
		{
			graphics->DrawText(L"Level Complete!", 50, 300);
		}
		else
		{
			graphics->DrawText(L"Level Zero Begin", 50, 300);
		}
	}
	else if (currentLevel == 1)
	{
		if (end)
		{
			graphics->DrawText(L"Level Complete!", 50, 300);
		}
		else
		{
			graphics->DrawText(L"Single Team Begin", 50, 300);
		}
	}
	else if (currentLevel == 2)
	{
		if (end)
		{
			graphics->DrawText(L"Level Complete!", 50, 300);
		}
		else
		{
			graphics->DrawText(L"Many Teams Begin", 50, 300);
		}
	}
	else if (currentLevel == 3)
	{
		if (end)
		{
			graphics->DrawText(L"Level Complete!", 50, 300);
		}
		else
		{
			graphics->DrawText(L"Level Three Begin", 50, 300);
		}
	}
}