/**
 * @file BugFeature.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_BUGFEATURE_H
#define PROJECT_1_BUGGAMELIB_BUGFEATURE_H

#include "Bug.h"
#include "Game.h"

/**
 * The class for BugFeature derived from Bug
 */
class BugFeature : public Bug
{
private:
	/// Number of FeatureNumSpriteImages
	int FeatureNumSpriteImages;

public:
	BugFeature() = delete;

	/// Copy constructor (disabled)
	BugFeature(const BugFeature &) = delete;

	/// Assignment operator
	void operator=(const BugFeature &) = delete;

	BugFeature(Game *game);

	void Update(double elapsed);


	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
	void Accept(ItemVisitor* visitor) override { visitor->VisitBugFeature(this); }

	/// When the bug is clicked, run the splat function
	/// Sets the speed to 0 and the image to the splat image
	void Splat() override { Bug::SplatFeature(); }

};

#endif //PROJECT_1_BUGGAMELIB_BUGFEATURE_H
