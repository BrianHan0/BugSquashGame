/**
 * @file Game.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_GAME_H
#define PROJECT_1_BUGGAMELIB_GAME_H

#include <memory>
#include <random>
#include "Scoreboard.h"
#include "Laptop.h"
#include "Bug.h"
#include "Message.h"
#include "Item.h"

#include "ItemVisitor.h"

/**
 * The main game class
 */
class Game
{
private:
	/// Scoreboard for the program
	std::unique_ptr<Scoreboard> mScoreboard;

	/// Laptop for the program
	std::unique_ptr<Laptop> mLaptop;

	/// Game area in virtual pixels
	const static int Width = 1250;

	/// Game area height in virtual pixels
	const static int Height = 1000;

	/// The state of the window to see if it's shrunk
	bool mShrinked = false;

	/// The scale
	double mScale = 1;

	/// How much the X is offset by
	double mXOffset = 0;

	/// How much the Y is offset by
	double mYOffset = 0;

	/// The scale to shrink the window
	double ShrinkScale = 0.5;

	/// All of the items to populate our game
	std::vector<std::shared_ptr<Item>> mItems;

	/// Random number generator
	std::mt19937 mRandom;

	/// A boolean that shows the status of whether the program was added
	bool mProgramAdded = false;

	/// Beginning state of game
	bool mBegin = true;

	/// Ending state of game
	bool mEnd = false;

	/// Starting and ending message length
	double mMessageLength = 0;

	/// Current level in the game
	int mCurrentLevel = 1;

	/// Messages for the program
	Message mMessage;
	/// The current program X
	double mCurrentProgramX = 0;
	/// The current program Y
	double mCurrentProgramY = 0;

public:
	void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
	void OnLeftDown(int x, int y);
	void Add(std::shared_ptr<Item> bug);
	void Update(double elapsed);
	Game();

	/**
	 * Gets the scoreboard scores
	 * @return the scoreboard
	 */
	Scoreboard *GetScoreboard() { return mScoreboard.get(); }

	/// reset the game
	void Reset();

	/**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
	std::mt19937 &GetRandom() {return mRandom;}

	/**
	* Get the width of the aquarium
	* @return Game width in pixels
	*/
	int GetWidth() const { return 1000; }

	/**
	 * Get the height of the aquarium
	 * @return Game height in pixels
	 */
	int GetHeight() const { return 1000; }

	void Save(const wxString &filename);
	void Load(const wxString &filename);
	void Clear();
	void XmlItem(wxXmlNode *node);
	std::shared_ptr<Item> HitTest(int x, int y);
	void MoveToFront(std::shared_ptr<Item> item);


	void Accept(ItemVisitor *visitor);

	double GetProgramLocX();
	double GetProgramLocY();

	/**
	 * Sets the location of X
	 * @param ProgramLocX
	 */
	void SetProgramLocX(double ProgramLocX ){
		mCurrentProgramX = ProgramLocX;
	}
	/**
	 * Sets the location of Y
	 * @param ProgramLocY
	 */
	void SetProgramLocY(double ProgramLocY){
		mCurrentProgramY = ProgramLocY;
	}

	/// Starts level zero by keeping track of level variables
	void StartLevelZero();
	//// Starts level one by keeping track of level variables
	void StartLevelOne();
	/// Starts level two by keeping track of level variables
	void StartLevelTwo();
	/// Starts level three by keeping track of level variables
	void StartLevelThree();
	/**
	 * Checks to see if it was shrunk
	 * @return A bool on whether if it was shrunk
	 */
	bool GetShrink() {return mShrinked;}
	int GetNumberOfPrograms();
	int GetNumberOfItems();
};

#endif //PROJECT_1_BUGGAMELIB_GAME_H
