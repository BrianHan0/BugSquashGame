/**
 * @file Scoreboard.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "Scoreboard.h"
#include "Game.h"

using namespace std;

/// Score font size to use
const int ScoreSize = 85;

/// Lable for score font size to use
const int LabelSize = 40;

/// The font color to use
const wxColour FontColor = wxColour(0, 200, 200);

/// Left score X location. The right score is
/// the width minus this value.
const int LeftScoreX = 150;

/// Score Y location
const int ScoreY = 20;

/// Score label Y location
const int ScoreLabelY = 100;

/// fixed score
string FixedScore = "0";

/// missed score
string MissedScore = "0";

/// oops score
string OopsScore = "0";

/// Start time for timer
auto startTime = wxDateTime::Now();

/**
 * Constructor for Scoreboard
 * @param game Game that scoreboard is part of
 */
Scoreboard::Scoreboard(Game* game) : mGame(game)
{
}

/**
 * Draws the scoreboard
 * @param graphics Graphics that the scoreboard is drawn on
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	wxFont font(wxSize(0, ScoreSize),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_BOLD);
	graphics->SetFont(font, FontColor);

	double width = 0;
	double height = 0;

	// fixed score
	graphics->GetTextExtent(FixedScore, &width, &height);
	graphics->DrawText(FixedScore, LeftScoreX - width,  ScoreY);
	// missed score
	graphics->GetTextExtent(MissedScore, &width, &height);
	graphics->DrawText(MissedScore,  650 - LeftScoreX - width / 2, ScoreY);
	// oops score
	graphics->GetTextExtent(OopsScore, &width, &height);
	graphics->DrawText(OopsScore, 1000 - LeftScoreX - width / 2, ScoreY);

	if (true)//if (mGame->GetNumberOfItems() != mGame->GetNumberOfPrograms())
	{
		auto currTime = (wxDateTime::Now() - startTime).GetSeconds().ToString();
		graphics->DrawText(currTime, LeftScoreX - width, 500);
	}

	wxFont nameFont(wxSize(0, LabelSize),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_BOLD);
	graphics->SetFont(nameFont, wxColour(FontColor));
	graphics->GetTextExtent("Fixed", &width, &height);
	graphics->DrawText(L"Fixed", LeftScoreX - width, ScoreLabelY);
	graphics->GetTextExtent("Missed", &width, &height);
	graphics->DrawText(L"Missed", 650 - LeftScoreX - width / 2, ScoreLabelY);
	graphics->GetTextExtent("Fixed", &width, &height);
	graphics->DrawText(L"Oops", 1000 - LeftScoreX - width / 2, ScoreLabelY);

}

/**
 * Increases fixed count on scoreboard
 */
void Scoreboard::IncrementFixedScore()
{
	FixedScore = to_string(stoi(FixedScore) + 1);
}

/**
 * Increases missed count on scoreboard
 */
void Scoreboard::IncrementMissedScore()
{
	MissedScore = to_string(stoi(MissedScore) + 1);
}

/**
 * Increases oops count on scoreboard
 */
void Scoreboard::IncrementOopsScore()
{
	OopsScore = to_string(stoi(OopsScore) + 1);
}

/**
 * Makes scoreboard reset all counts
 */
void Scoreboard::ResetScoreboard()
{
	FixedScore = to_string(stoi("0"));
	MissedScore = to_string(stoi("0"));
	OopsScore = to_string(stoi("0"));
	startTime = wxDateTime::Now();
}

