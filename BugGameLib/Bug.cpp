/**
 * @file Bug.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "Bug.h"
#include "Game.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedY = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedY = 20;

/**
* Destructor
*/
Bug::~Bug()
{

}

/**
 * Constructor for the bug class
 * @param game
 * @param filename
 * @param splatFilename
 */
Bug::Bug(Game *game, const std::wstring &filename,const std::wstring &splatFilename) :
	Item(game, filename, splatFilename)
{
	std::uniform_real_distribution<> distributionX(MinSpeedX, MaxSpeedX);
	mSpeedX = distributionX(game->GetRandom());
	std::uniform_real_distribution<> distributionY(MinSpeedY, MaxSpeedY);
	mSpeedY = distributionY(game->GetRandom());
	mProgramLocationX = game->GetProgramLocX();
	mProgramLocationY = game->GetProgramLocY();
	mSplatImageItem = std::make_shared<wxImage>(splatFilename, wxBITMAP_TYPE_ANY);
}

/**
 * Compute the distance from this item to another Bug
 * @param bug Bug we are computing the distance to
 * @return Distance in pixels
 */
double Bug::DistanceTo(std::shared_ptr<Bug> bug)
{
	auto dx = bug->GetX() - GetX();
	auto dy = bug->GetY() - GetY();
	return sqrt(dx * dx + dy * dy);
}

/**
 * Compute the distance from this item to the program
 * @return Distance in pixels
 */
double Bug::DistanceToProgram()
{
	auto dx = mProgramLocationX - GetX();
	auto dy = mProgramLocationY - GetY();
	return sqrt(dx * dx + dy * dy);
}

/**
 * Updates the bug according to the elapsed time
 * @param elapsed The elapsed time
 */
void Bug::Update(double elapsed) {
	double angle = atan2(mProgramLocationY - this->GetY(), mProgramLocationX - this->GetX());
	SetAngle(angle);
	SetLocation(this->GetX() + elapsed * mSpeedX * cos(angle),
				this->GetY() + elapsed * mSpeedY * sin(angle));

	///Statements to keep bugs in range speed
	if (!mSplat)
	{
		if (mSpeedX >= 100){
			mSpeedX = 20;
		}
		if (mSpeedX <= -100){
			mSpeedX = -20;
		}
		if (mSpeedY >= 100){
			mSpeedY = 20;
		}
		if (mSpeedY <= -100){
			mSpeedY = -20;
		}
		if (mSpeedX > -20 && mSpeedX <= 0){
			mSpeedX = -50;
		}
		if (mSpeedX < 20 && mSpeedX >= 0){
			mSpeedX = 50;
		}
		if (mSpeedY > -20 && mSpeedY <= 0){
			mSpeedY = -50;
		}
		if (mSpeedY < 20 && mSpeedY >= 0){
			mSpeedY = 50;
		}
	}

}
/**
 * A function to call when a bug has been splattered
 */
void Bug::Splat()
{
	// Change the speed of the bug to 0
	mSplat = true;
	mSpeedX = 0;
	mSpeedY = 0;
//	mGame->GetScoreboard()->IncrementFixedScore();

}
/**
 * A function to call when a bug has been splattered
 */
void Bug::SplatFeature()
{
	// Change the speed of the bug to 0
	mSplat = true;
	mSpeedX = 0;
	mSpeedY = 0;
//	mGame->IncreaseOops();
}


void Bug::SetBugProgramX(){
	mProgramLocationX = mGame->GetProgramLocX();
}

void Bug::SetBugProgramY(){
	mProgramLocationY = mGame->GetProgramLocY();
}
/**
 * Checks to see if the bug has been clicked
 * @param x X coordinate of the event
 * @param y Y coordinate of the event
 * @return a bool to confirm whether the bug was clicked
 */
bool Bug::HitTest(double x, double y)
{
	if(mSplat)
	{
		return false;
	}
	double dx = x - GetX();
	double dy = y - GetY();

	return sqrt(dx * dx + dy * dy) < mBugHitRange;
}
/**
 * A function to check if the bug is splattered
 * @return status of the bug
 */
bool Bug::IsSplat()
{
	return mSplat;
}

/**
 * A function to check if the bug is fat
 * @return status of the bug
 */
bool Bug::IsFat()
{
	mFat = true;
	return mFat;
}

/**
 * A setter for the bug speed
 * @param x X coordinate of the event
 * @param y Y coordinate of the event
 */
void Bug::SetSpeed(double x, double y)
{
	mSpeedX = x;
	mSpeedY = y;
}
