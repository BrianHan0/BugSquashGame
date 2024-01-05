/**
 * @file Laptop.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "Laptop.h"

using namespace std;

/// Laptop filename
const wstring LaptopImageName = L"images/laptop.png";

/// Level name for laptop
std::string mLevelName;

/**
 * Constructor for laptop
 * @param game Game this laptop is a member of
 */
Laptop::Laptop(Game *game) : Item(game, LaptopImageName)
{
	mLaptopImage = make_unique<wxImage>(LaptopImageName, wxBITMAP_TYPE_ANY);
	mLaptopBitmap = make_unique<wxBitmap>(*mLaptopImage);
}

/**
 * Save this bug to an XML node
 * @param node The parent node we are going to be a child of
 * @return itemnode with Attribute added
 */
wxXmlNode* Laptop::XmlSave(wxXmlNode* node)
{
	auto itemNode = Item::XmlSave(node);

	itemNode->AddAttribute(L"type", L"laptop");

	return itemNode;
}

void Laptop::SetLevelName(std::string levelName)
{
	mLevelName = levelName;
}

/**
* Draw the game area
* @param graphics The graphics context to draw on
 */
void Laptop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	wxFont font(wxSize(0, 22),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_NORMAL);
	graphics->SetFont(font, wxColour(255, 255, 255));

	double wid = mLaptopImage->GetWidth();
	double hit = mLaptopImage->GetHeight();
	graphics->DrawBitmap(*mLaptopBitmap, GetX() - wid / 2, GetY() - hit / 2, wid, hit);

	double width = 0;
	double height = 0;
	graphics->GetTextExtent(mLevelName, &width, &height);
	graphics->DrawText(mLevelName, GetX() - width / 2, GetY() - height / 2);
}

/**
 * update this laptop location
 * @param elapsed the time elapsed
 */
void Laptop::Update(double elapsed)
{
	Item::Update(elapsed);
}



