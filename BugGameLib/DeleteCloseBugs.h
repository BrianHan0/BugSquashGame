/**
 * @file DeleteCloseBugs.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_DELETECLOSEBUGS_H
#define PROJECT_1_BUGGAMELIB_DELETECLOSEBUGS_H

#include "ItemVisitor.h"
#include "Bug.h"

/**
 * A class for Deleteing Bugs : derived from ItemVisitor
 */
class DeleteCloseBugs : public ItemVisitor
{
private:
	virtual void VisitBugFeature(BugFeature* feature) override;
	virtual void VisitBugGarbage(BugGarbage* bug) override;
	virtual void VisitBugNull(BugNull* bug) override;
	virtual void VisitBugRedundancy(BugRedundancy* bug) override;

public:

};

#endif //PROJECT_1_BUGGAMELIB_DELETECLOSEBUGS_H
