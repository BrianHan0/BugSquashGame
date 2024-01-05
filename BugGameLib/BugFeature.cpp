/**
 * @file BugFeature.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "BugFeature.h"

using namespace std;

/// Bug Filename
const wstring FeatureImageName = L"images/feature.png";
/// Bug splattered file name
const wstring FeatureSplatImageName = L"images/feature-splat.png";


/**
 * Constructor
 * @param game Game this bug is a member of
 */
BugFeature::BugFeature(Game *game) : Bug(game, FeatureImageName, FeatureSplatImageName)
{
}

/**
 * update this BugNull location
 * @param elapsed the time elapsed
 */
void BugFeature::Update(double elapsed)
{
	Bug::Update(elapsed);
}

