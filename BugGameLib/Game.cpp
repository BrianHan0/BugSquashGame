/**
 * @file Game.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "Game.h"
#include "BugGarbage.h"
#include "BugFeature.h"
#include "BugNull.h"
#include "BugRedundancy.h"
#include "ItemVisitor.h"
#include "DeleteCloseBugs.h"
#include "Laptop.h"
#include "Scoreboard.h"
#include <algorithm>
#include <vector>

using namespace std;

/// Program name font size
const int ProgramNameFontSize = 22;

/// The initial Y starting point
const int InitialY = 1000;

/// Game area in virtual pixels
const static int Width = 1250;

/// Game area height in virtual pixels
const static int Height = 1000;

Game::Game()
{
	// Seed the random number generator
	std::random_device rd;
	mRandom.seed(rd());

	// Make a ControlLevel object to use
	// Uncomment when Load() works
	// mControlLevel = std::unique_ptr<ControlLevel>(new ControlLevel());
}

/**
 * Draw the game area
 * @param graphics The graphics context to draw on
 * @param width Width of the client window
 * @param height Height of the client window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
	//
	// Automatic Scaling
	//
	auto scaleX = double(width) / double(Width);
	auto scaleY = double(height) / double(Height);
	mScale = std::min(scaleX, scaleY);

	if(mShrinked)
	{
		mScale *= ShrinkScale;
	}

	mXOffset = (width - Width * mScale) / 2;
	mYOffset = (height - Height * mScale) / 2;

	graphics->PushState();

	graphics->Translate(mXOffset, mYOffset);
	graphics->Scale(mScale, mScale);

	// From here on you are drawing virtual pixels
	auto virtualHeight = height / mScale;
	auto virtualWidth = width / mScale;

	//
	// Your drawing code goes here
	//

	for (auto items : mItems){
		items->Draw(graphics);
	}

	graphics->PopState();

	mScoreboard->Draw(graphics);
	if (mBegin)
	{
		mMessage.Draw(graphics, mCurrentLevel, mEnd);
	}
}

/**
* Handle a mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDown(int x, int y)
{
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;
}

/**
* Add an item to the aquarium
* @param item New item to add
*/
void Game::Add(std::shared_ptr<Item> item)
{

		std::uniform_real_distribution<> distributionX(0, Width);
		double randomX = distributionX(this->GetRandom());
		std::uniform_real_distribution<> distributionY(0, Height);
		double randomY = distributionY(this->GetRandom());

		item->SetLocation(item->GetX(), item->GetY());
		std::shared_ptr<Item> LastItem = nullptr;
		mItems.push_back(item);
		/**
		for(auto bugs : mItems)
		{
			for(auto bugs : mItems)
			{
				double distance = bugs->DistanceTo(item);
				if(bugs == item)
				{
					break;
				}
				if(LastItem != nullptr)
				{
					if(distance < 1)
					{
						item->ChangeLocation(item);
						break;
					}
				}
			}
			LastItem = bugs;
		}
		*/

}

/**
 * Clear the aquarium data.
 *
 * Deletes all known items in the aquarium.
 */
void Game::Clear()
{
	mItems.clear();
}

/**
 * Saves the game
 * @param filename the file to save the game to
 */
void Game::Save(const wxString &filename)
{
	wxXmlDocument xmlDoc;

	auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"game");
	xmlDoc.SetRoot(root);

	// Iterate over all items and save them
	for (auto item : mItems)
	{
		item->XmlSave(root);
	}

	if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
	{
		wxMessageBox(L"Write to XML failed");
		return;
	}
}

/**
 * Load the game from a .game XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the aquarium from.
 */
void Game::Load(const wxString &filename)
{
	wxXmlDocument xmlDoc;

	if(!xmlDoc.Load(filename))
	{
		wxMessageBox(L"Unable to load level");
		return;
	}

	Clear();

	// Get the XML document root node
	auto root = xmlDoc.GetRoot();
	auto child = root->GetChildren();
	for( ; child; child = child->GetNext())
	{
		XmlItem(child);
		auto nestedChild = child->GetChildren();
		for( ; nestedChild; nestedChild = nestedChild->GetNext())
		{
			XmlItem(nestedChild);
		}
	}
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlItem(wxXmlNode *node){
	// A pointer for the item we are loading
	std::shared_ptr<Item> item;

	auto type = node->GetAttribute(L"type");
	auto name = node->GetName();
	if (name == L"feature")
	{
		item = std::make_shared<BugFeature>(this);
	}
	if (type == L"garbage")
	{
		item = std::make_shared<BugGarbage>(this);
	}
	else if (type == L"null")
	{
		item = std::make_shared<BugNull>(this);
	}
	else if (type == L"redundancy")
	{
		item = std::make_shared<BugRedundancy>(this);
	}
	else if (name == L"program")
	{
		item = std::make_shared<Laptop>(this);
	}

	if (item != nullptr)
	{
		item->XmlLoad(node);
		if(name == L"program"){
			SetProgramLocY(item->GetY());
			SetProgramLocX(item->GetX());
		}
		Add(item);
	}
}

/**
 * Handle updates for animation and deletion
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
	mMessageLength += elapsed;

	if (mMessageLength >= 2)
	{
		mBegin = false;
		mMessageLength = 0;
	}

	DeleteCloseBugs visitor;
	this->Accept(&visitor);

	vector<shared_ptr<Item>> itemsToDelete;
	for (auto item : mItems)
	{
		if (item->GetMarkedForDelete() != 0)
		{
			itemsToDelete.push_back(item);
		}

		item->Update(elapsed);
	}

	for (auto item : itemsToDelete)
	{
		auto loc = find(std::begin(mItems), std::end(mItems), item);
		if (loc != std::end(mItems))
		{
			if (item->GetMarkedForDelete() != 2)
			{
				mScoreboard->IncrementMissedScore();
			}
			mItems.erase(loc);
		}
	}
}

/**
 * Moves the clicked item to the front
 * @param item The item to be moved to the front of the vector of items
 */
void Game::MoveToFront(std::shared_ptr<Item> item)
{
	auto loc = find(std::begin(mItems), std::end(mItems), item);
	if (loc != std::end(mItems))
	{
		mItems.erase(loc);
	}
	mItems.push_back(item);
}

/**
 * Starts level zero by setting variables
 */
void Game::StartLevelZero()
{
	mLaptop->SetLevelName("Bug Squash");
	mScoreboard->ResetScoreboard();
	mCurrentLevel = 0;
	mMessageLength = 0;
	mBegin = true;
}

/**
 * Starts level one by setting variables
 */
void Game::StartLevelOne()
{
	mLaptop->SetLevelName("Bug Squash");
	mScoreboard->ResetScoreboard();
	mCurrentLevel = 1;
	mMessageLength = 0;
	mBegin = true;
}

/**
 * Starts level two by setting variables
 */
void Game::StartLevelTwo()
{
	mLaptop->SetLevelName("Receivables");
	mScoreboard->ResetScoreboard();
	mCurrentLevel = 2;
	mMessageLength = 0;
	mBegin = true;
}

/**
 * Starts level three by setting variables
 */
void Game::StartLevelThree()
{
	mLaptop->SetLevelName("Fish Tank");
	mScoreboard->ResetScoreboard();
	mCurrentLevel = 3;
	mMessageLength = 0;
	mBegin = true;
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
	/// Adjusting coordinates for scaling
	double newX = (x- mXOffset) / mScale;
	double newY = (y- mXOffset) / mScale;
	for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
	{
		if ((*i)->HitTest(newX, newY))
		{
			return *i;
		}
	}
	return  nullptr;
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor* visitor)
{
	for (auto item : mItems)
	{
		item->Accept(visitor);
	}
}

/**
 * Resets Game and clears all items
 */
void Game::Reset()
{
	mItems.clear();
	mProgramAdded = false;
}

/**
 * Gets the item x location
 * @returns First item's X location
 */
double Game::GetProgramLocX(){
	return mCurrentProgramX;
}

/**
 * Gets the item y location
 * @returns First item's Y location
 */
double Game::GetProgramLocY(){
	return mCurrentProgramY;
}

/**
 * Gets the number of programs in the game
 * @returns Number of programs in game
 */
int Game::GetNumberOfPrograms()
{
	if (mCurrentLevel < 2)
	{
		return 1;
	}
	else
	{
		return 3;
	}
}

/**
 * Gets the number of items in the game
 * @returns Number of items in game
 */
int Game::GetNumberOfItems()
{
	return mItems.size();
}
