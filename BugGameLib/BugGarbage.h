/**
 * @file BugGarbage.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_BUGGARBAGE_H
#define PROJECT_1_BUGGAMELIB_BUGGARBAGE_H

#include "Bug.h"

/**
 * The class for BugGarbage derived from Bug
 */
class BugGarbage : public Bug
{
private:

	/// The code to fix that will pop up
	std::string FatCodeToFix;

public:
	BugGarbage() = delete;

	/// Copy constructor (disabled)
	BugGarbage(const BugGarbage &) = delete;

	/// Assignment operator
	void operator=(const BugGarbage &) = delete;

	BugGarbage(Game *game);

	void Update(double elapsed);

	wxXmlNode *XmlSave(wxXmlNode *node);

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
	void Accept(ItemVisitor* visitor) override { visitor->VisitBugGarbage(this); }

	/// When the bug is clicked, run the splat function
	/// Sets the speed to 0 and the image to the splat image
	void Splat() override { Bug::Splat(); }

};

#endif //PROJECT_1_BUGGAMELIB_BUGGARBAGE_H
