/**
 * @file BugGarbage.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "BugGarbage.h"

/// Bug file name
const std::wstring GarbageBugSpriteImageName = L"./images/blue-maize-bug.png";
/// Bug splattered file name
const std::wstring GarbageBugSplatImageName = L"images/blue-maize-splat.png";

/**
 * Constructor
 * @param game Game this bug is a member of
 */
BugGarbage::BugGarbage(Game *game) : Bug(game, GarbageBugSpriteImageName, GarbageBugSplatImageName)
{
}

/**
 * Save this bug to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* BugGarbage::XmlSave(wxXmlNode* node)
{
	auto itemNode = Item::XmlSave(node);

	itemNode->AddAttribute(L"type", L"garbage");


	return itemNode;
}

/**
 * update this BugGarbage location
 * @param elapsed the time elapsed
 */
void BugGarbage::Update(double elapsed)
{
	Bug::Update(elapsed);
}
