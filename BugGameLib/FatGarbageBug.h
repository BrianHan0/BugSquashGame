/**
 * @file FatGarbageBug.h
 * @author Sungu Han
 *
 * class for fat garbage bug
 */

#ifndef PROJECT_1_BUGGAMELIB_FATGARBAGEBUG_H
#define PROJECT_1_BUGGAMELIB_FATGARBAGEBUG_H

#include "Game.h"

///class for fat garbage bug
class FatGarbageBug : public Bug
{
private:
	/// The underlying Bug image
	std::unique_ptr<wxImage> mBugImage;

	/// The bitmap we can display for this Bug
	std::unique_ptr<wxBitmap> mBugBitmap;



public:


};

#endif //PROJECT_1_BUGGAMELIB_FATGARBAGEBUG_H
