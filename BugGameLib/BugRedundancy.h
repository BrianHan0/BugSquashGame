/**
 * @file BugRedundancy.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_BUGREDUNDANCY_H
#define PROJECT_1_BUGGAMELIB_BUGREDUNDANCY_H

#include "Bug.h"
/**
 * The class for BugRedundancy derived from Bug
 */
class BugRedundancy : public Bug
{
private:
	/// The code to fix that will pop up
	std::string FatCodeToFix;

	/// Bool for if bug can be split
	bool splitable = true;

	/// The underlying Bug image (need to add other parts later)
	std::unique_ptr<wxImage> mBugImage;

	/// The bitmap we can display for this Bug (need to add other parts later)
	std::unique_ptr<wxBitmap> mBugBitmap;

public:
	BugRedundancy() = delete;

	/// Copy constructor (disabled)
	BugRedundancy(const BugRedundancy &) = delete;

	/// Assignment operator
	void operator=(const BugRedundancy &) = delete;

	BugRedundancy(Game *game);

	void Update(double elapsed);

	wxXmlNode *XmlSave(wxXmlNode *node);

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
	void Accept(ItemVisitor* visitor) override { visitor->VisitBugRedundancy(this); }

	/// override the item::split function and return true
	bool CanSplit() override;

	/// set splitable to false
	void NotSplitable() override {splitable = false;};


};

#endif //PROJECT_1_BUGGAMELIB_BUGREDUNDANCY_H
