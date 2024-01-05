/**
 * @file BugRedundancy.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "BugRedundancy.h"

/// The bug base image
const std::wstring RedundancyFlyImageName = L"./images/redundancy-fly-base.png";

/// The bug top image
const std::wstring RedundancyFlyTopImageName = L"images/redundancy-fly-top.png";

/// The left wing image
const std::wstring RedundancyFlyLeftWingImageName = L"images/redundancy-fly-lwing.png";

/// The right wing image
const std::wstring RedundancyFlyRightWingImageName = L"images/redundancy-fly-rwing.png";

/// The splat image
const std::wstring RedundancyFlySplatImageName = L"images/redundancy-fly-splat.png";

/// Wing flapping period in seconds
const double WingPeriod = 0.2;

/// Starting rotation angle for wings in radians
const double WingRotateStart = 0.0;

/// End rotation angle for wings in radians
const double WingRotateEnd = 1.5;

/// How many sets of wings does this bug have?
const int NumberOfSetsOfWings = 4;

/// Number of virtual pixels between each of the wing sets
const int WingSetXOffset = 12;

/// X position relative to center of bug for the first (back) wing set
const int FirstWingSetX = -36;

/// Y position relative to center of bug for the right wings. The negative
/// of this is the Y position for the left wings.
const int WingSetY = 5;

/**
 * Constructor
 * @param game Game this bug is a member of
 */
BugRedundancy::BugRedundancy(Game *game) : Bug(game, RedundancyFlyImageName,RedundancyFlySplatImageName)
{
	mBugImage = std::make_unique<wxImage>(RedundancyFlyImageName , wxBITMAP_TYPE_ANY);
	mBugBitmap = std::make_unique<wxBitmap>(*mBugImage);
}

/**
 * Save this bug to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* BugRedundancy::XmlSave(wxXmlNode* node)
{
	auto itemNode = Item::XmlSave(node);

	itemNode->AddAttribute(L"type", L"redundancy");


	return itemNode;
}

/**
 * update this BugRedundancy location
 * @param elapsed the time elapsed
 */
void BugRedundancy::Update(double elapsed)
{
	Bug::Update(elapsed);
}

/**
 * Checks if bug can be split
 * @return true if able to split, false otherwise
 */
bool BugRedundancy::CanSplit()
{
	if (splitable)
	{
		return true;
	}
	else
	{
		return false;
	}
}

