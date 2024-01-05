/**
 * @file BugNull.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "BugNull.h"

/// Bug file name
const std::wstring NullBugSpriteImageName = L"./images/scarlet-gray-bug.png";
/// Bug splattered file name
const std::wstring NullBugSplatImageName = L"images/scarlet-gray-splat.png";

/**
 * Constructor
 * @param game Game this bug is a member of
 */
BugNull::BugNull(Game *game) : Bug(game, NullBugSpriteImageName, NullBugSplatImageName)
{
}

/**
 * Save this bug to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* BugNull::XmlSave(wxXmlNode* node)
{
	auto itemNode = Item::XmlSave(node);

	itemNode->AddAttribute(L"type", L"null");


	return itemNode;
}

/**
 * update this BugNull location
 * @param elapsed the time elapsed
 */
void BugNull::Update(double elapsed)
{
	Bug::Update(elapsed);
}

