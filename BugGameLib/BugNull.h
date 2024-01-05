/**
 * @file BugNull.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_BUGNULL_H
#define PROJECT_1_BUGGAMELIB_BUGNULL_H

#include "Bug.h"
#include "Game.h"
/**
 * The class for BugNull derived from Bug
 */
class BugNull : public Bug
{
private:
	/// The code to fix that will pop up
	std::string FatCodeToFix;

public:
	BugNull() = delete;

	/// Copy constructor (disabled)
	BugNull(const BugNull &) = delete;

	/// Assignment operator
	void operator=(const BugNull &) = delete;

	BugNull(Game *game);

	void Update(double elapsed);

	wxXmlNode *XmlSave(wxXmlNode *node);

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
	void Accept(ItemVisitor* visitor) override { visitor->VisitBugNull(this); }

	/// When the bug is clicked, run the splat function
	/// Sets the speed to 0 and the image to the splat image
	void Splat() override { Bug::Splat(); }

};

#endif //PROJECT_1_BUGGAMELIB_BUGNULL_H

