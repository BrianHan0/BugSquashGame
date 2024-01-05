/**
 * @file FatBug.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_FATBUG_H
#define PROJECT_1_BUGGAMELIB_FATBUG_H

#include "Bug.h"

/**
 * The class for FatBug derived from Bug
 */
class FatBug : public Bug
{
private:
	/// The Code to fix
	std::string mCode;

public:

	/**
	 * Fat Bug Constructor
	 * @param game game bug is is apart of
	 */
	FatBug(Game *game);

	/**
	 * Function when item is Double clicked
	 * @param x X location in pixels
	 * @param y Y location in pixels
	 */
	void DoubleClick(int x, int y) override;

	/**
	 * Function to draw the fat bug
	 * @param graphics The graphics context to draw on
	 */
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

};

#endif //PROJECT_1_BUGGAMELIB_FATBUG_H
