/**
 * @file DeleteCloseBugs.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "DeleteCloseBugs.h"
#include "BugGarbage.h"
#include "BugFeature.h"
#include "BugNull.h"
#include "BugRedundancy.h"
#include "Scoreboard.h"
#include "Game.h"

/// Minimum distance a bug can be to the program before it is deleted
double minDistance = 50;

/**
 * Deletes the feature if it is close enough to the program
 * @param feature The feature visited
 */
void DeleteCloseBugs::VisitBugFeature(BugFeature *feature)
{
	if (feature->DistanceToProgram() < minDistance)
	{
		feature->SetMarkedForDelete(2);
	}
}

/**
 * Deletes the bug if it is close enough to the program
 * @param bug The bug visited
 */
void DeleteCloseBugs::VisitBugGarbage(BugGarbage *bug)
{
	if (bug->DistanceToProgram() < minDistance)
	{
		bug->SetMarkedForDelete(1);
	}
}

/**
 * Deletes the bug if it is close enough to the program
 * @param bug The bug visited
 */
void DeleteCloseBugs::VisitBugNull(BugNull *bug)
{
	if (bug->DistanceToProgram() < minDistance)
	{
		bug->SetMarkedForDelete(1);
	}
}

/**
 * Deletes the bug if it is close enough to the program
 * @param bug The bug visited
 */
void DeleteCloseBugs::VisitBugRedundancy(BugRedundancy *bug)
{
	if (bug->DistanceToProgram() < minDistance)
	{
		bug->SetMarkedForDelete(1);
	}
}
