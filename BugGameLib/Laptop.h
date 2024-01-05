/**
 * @file Laptop.h
 * @author Sungu Han
 *
 * Class for creating laptop
 */

#ifndef PROJECT_1_BUGGAMELIB_LAPTOP_H
#define PROJECT_1_BUGGAMELIB_LAPTOP_H

#include "Item.h"
/**
 * Main Laptop class derived from item
 */
class Laptop : public Item
{
private:
	///The game this laptop is associated with.
	Game *mGame;

	/// The underlying Bug image
	std::unique_ptr<wxImage> mLaptopImage;

	/// The bitmap we can display for this Bug
	std::unique_ptr<wxBitmap> mLaptopBitmap;
public:
	/// Default constructor (disabled)
	Laptop() = delete;

	/// Copy constructor (disabled)
	Laptop(const Laptop &) = delete;

	/// Assignment operator
	void operator=(const Laptop &) = delete;

	Laptop(Game* game);

	void Update(double elapsed);

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
	void Accept(ItemVisitor* visitor) override { visitor->VisitLaptop(this); }

	wxXmlNode *XmlSave(wxXmlNode *node);

	/**
	 * Checks to see if the laptop has been clicked on
	 * @param x coordinate
	 * @param y coordinate
	 * @return Always false so the game doesn't recognize the Laptop as a Bug
	 */
	bool HitTest(double x, double y) override {return false;};

	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	/**
     * Changes the level name
     * @param levelName the string name
     */
	void SetLevelName(std::string levelName);
};

#endif //PROJECT_1_BUGGAMELIB_LAPTOP_H
