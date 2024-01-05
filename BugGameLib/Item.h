/**
 * @file Item.h
 * @author Sungu Han
 *
 * Base class for items in program
 */

#ifndef PROJECT_1_BUGGAMELIB_ITEM_H
#define PROJECT_1_BUGGAMELIB_ITEM_H

#include "ItemVisitor.h"

class Game;

/**
 * The main class for Item
 */
class Item
{
private:
	///The game this item is associated with.
	Game *mGame;

	/// can the item be split default yes
	bool mSplit = true;

	/// Bool for sprite image
	bool mIsSprite = false;

	/// The underlying item image
	std::shared_ptr<wxImage> mImageItem;

	/// The bitmap we can display for this item
	wxGraphicsBitmap mItemBitmap;

	/// The underlying item image
	std::shared_ptr<wxImage> mSplatImageItem;

	/// The bitmap we can display for this item
	wxGraphicsBitmap mSplatItemBitmap;

	/// The initial sprite image location
	/// In x
	double mSpriteImageLocX = 0;
	/// In Y
	double mSpriteImageLocY = 0;

	/// Location of bug
	/// In X
	double mX = 0;
	/// In Y
 	double mY = 0;
	/// The angel the bug is facing in
	double mAngle = 0;

	/// Used to mark items to delete
	int mMarkedForDelete = 0;

public:
	/// Default constructor (disabled)
	Item() = delete;

	/// Copy constructor (disabled)
	Item(const Item &) = delete;

	~Item();

	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	/**
	 * If the item can be splated then do it
	 */
	virtual void Splat(){};

	///Laptop constructor
	Item(Game *game, const std::wstring &filename);
	///
	Item(Game *game, const std::wstring &filename,const std::wstring &splatFilename);
	/**
	 * Set the Bug location
	 * @param x X location in pixels
	 * @param y Y location in pixels
	 */
	void SetLocation(double x, double y) { mX = x; mY = y; }

	/**
	 * Set the Bug location
	 * @param Angle an angle in radians
	 */
	void SetAngle( double Angle) {mAngle = Angle;}

	/**
	 * Function when item is Double clicked
	 * @returns a double x member value
	 */
	double GetX() const { return mX; }

	/**
	 * The Y location of the item
	 * @returns a double y member value
	 */
	double GetY() const { return mY; }

	/**
	 * Getter for mMarkedForDelete
	 * @return mMarkedForDelete
	 */
	int GetMarkedForDelete() { return mMarkedForDelete; }

	/**
	 * Setter for mMarkedForDelete
	 * @param status The value to set mMarkedForDelete to
	 */
	void SetMarkedForDelete(int status) { mMarkedForDelete = status; }

	double DistanceTo(std::shared_ptr<Item> item);

	/**
	 * Fucntion when item is single clicked
	 * @param x X location in pixels
	 * @param y Y location in pixels
	 */
	virtual void DoubleClick(int x, int y){}

	/**
     * Change location of item
     * @param item
     */
	virtual void ChangeLocation(std::shared_ptr<Item> item);

	/**
	 * Handle updates for animation
	 * @param elapsed The time since the last update
	 */
	virtual void Update(double elapsed) {}

	/**
	 * Draws sprite image
	 * @param graphics The graphics context to draw on
	 */
	void DrawSpriteImage(std::shared_ptr<wxGraphicsContext> graphics);
	/// Change the image of the sprite
	void ChangeSpriteImage();

	/**
	 * Get the pointer to the Aquarium object
	 * @return Pointer to Aquarium object
	 */
	Game *GetGame() { return mGame;  }

	wxXmlNode *XmlSave(wxXmlNode *node);
	void XmlLoad(wxXmlNode *node);

	virtual bool HitTest(double x, double y);

	/**
 	* Handle a double-click on an item
 	* @param x X location in the aquarium of the double-click
 	* @param y Y location in the aquarium of the double-click
 	*/
 	virtual void Click(int x, int y){};

	/**
	* Accept a visitor
	* @param visitor The visitor we accept
	*/
	virtual void Accept(ItemVisitor* visitor) = 0;
	void DrawSpriteImageSevenHundred(std::shared_ptr<wxGraphicsContext> graphics);
	void DrawSpriteImageSixHundred(std::shared_ptr<wxGraphicsContext> graphics);
	void DrawFatBug(std::shared_ptr<wxGraphicsContext> graphics);

	/**
	 * A function to check if the bug is splattered
 	* @return status of the bug
 	*/
	virtual bool IsSplat(){return false;};

	/**
	 * A function to check if the bug is fat
 	* @return status of the bug
 	*/
	virtual bool IsFat(){return false;};

	/**
	 * A function to check if the bug can split
 	* @return bug split status
 	*/
	virtual bool CanSplit(){return false;};


	/// set the bug to not be splitable anymore
	virtual void NotSplitable(){};

};

#endif //PROJECT_1_BUGGAMELIB_ITEM_H
