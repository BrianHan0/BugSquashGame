/**
 * @file ItemVisitor.h
 * @author Sungu Han
 *
 *
 */

#ifndef PROJECT_1_BUGGAMELIB_ITEMVISITOR_H
#define PROJECT_1_BUGGAMELIB_ITEMVISITOR_H

class Laptop;
class BugFeature;
class BugGarbage;
class BugNull;
class BugRedundancy;

/**
 * A visitor that visits the items in the game
 */
class ItemVisitor
{
protected:
	/// Constructor
	ItemVisitor() {}

public:
	virtual ~ItemVisitor() {}

	/**
	 * Visit a Laptop item
	 * @param laptop The Laptop being visited
	 */
	virtual void VisitLaptop(Laptop* laptop) {}

	/**
	 * Visit a Feature item
	 * @param feature The Feature being visited
	 */
	virtual void VisitBugFeature(BugFeature* feature) {}

	/**
	 * Visit a Garbage Bug item
	 * @param bug The bug being visited
	 */
	virtual void VisitBugGarbage(BugGarbage* bug) {}

	/**
	 * Visit a Null Bug item
	 * @param bug The bug being visited
	 */
	virtual void VisitBugNull(BugNull* bug) {}

	/**
	 * Visit a Redundancy Fly item
	 * @param bug The bug being visited
	 */
	virtual void VisitBugRedundancy(BugRedundancy* bug) {}

};

#endif //PROJECT_1_BUGGAMELIB_ITEMVISITOR_H
