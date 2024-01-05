/**
 * @file Bug.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_BUG_H
#define PROJECT_1_BUGGAMELIB_BUG_H

#include <random>
#include "Item.h"

/**
 * The main bug class derived from item
 */
class Bug : public Item
{
private:
	///The game this bug is associated with.
	Game *mGame;

	/// Bug speed in the X direction
	/// in pixels per second
	double mSpeedX;

	/// Bug speed in the Y direction
	/// in pixels per second
	double mSpeedY;

	/// The location of the bug
	/// X coordinate
	double mProgramLocationX = 0;
	/// Y coordinate
	double mProgramLocationY = 0;

	/// Splatter
	bool mSplat = false;

	/// The hit range of the bug
	double mBugHitRange = 50;

	/// The underlying splatterd image
	std::shared_ptr<wxImage> mSplatImageItem;

	/// The bitmap we can display for this item
	wxGraphicsBitmap mSplatItemBitmap;

	/// Bool for sprite image
	bool mIsSprite = false;

	/// Bool for fat bug
	bool mFat = false;

public:
	/**
	 * Destructor for Bug
	 */
	virtual ~Bug();

	/// Default constructor (disabled)
	Bug() = delete;

	/// Copy constructor
	Bug(const Bug &) = delete;

	///Bug constructor
	Bug(Game *game, const std::wstring &filename,const std::wstring &splatFilename);

	/// Assignment operator
	void operator=(const Bug &) = delete;

	/**
	 * Changes location of the bug
	 * @param bug the location of bug to change
	 */
	void ChangeLocation(std::shared_ptr<Bug> bug);

	/// Computes the distance from this item to another bug
	double DistanceTo(std::shared_ptr<Bug> bug);
	/// Computes the distance from this item to the program
	double DistanceToProgram();

	/// Updates the bug according to the elapsed time
	void Update(double elapsed);

	/**
	* Accept a visitor
	* @param visitor The visitor we accept
	*/
	virtual void Accept(ItemVisitor* visitor) = 0;

	/// When the bug is clicked, run the splat function
	/// Sets the speed to 0 and the image to the splat image
	void Splat() override;

	/// Same as Splat(), but increments Oops counter instead of Fixed counter
	void SplatFeature();

	/// Sets the X location of the bug to program
	void SetBugProgramX();

	/// Sets the Y location of the bug to program
	void SetBugProgramY();

	bool HitTest(double x, double y) override;

	bool IsSplat() override;

	bool IsFat() override;

	/// set speed of bug
	void SetSpeed(double x, double y);
};

#endif //PROJECT_1_BUGGAMELIB_BUG_H
