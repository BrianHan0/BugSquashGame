/**
 * @file Item.cpp
 * @author Sungu Han
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;

/**
* Destructor
*/
Item::~Item()
{
}

/**
 * Constructor for the laptop class
 * @param game The game this item is a member of
 * @param filename The filename this string is associated with
 */
Item::Item(Game *game, const std::wstring &filename) : mGame(game)
{
	mImageItem = std::make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
}



 /**
   * Constructor for the bug class
   * @param game The game this item is a member of
   * @param filename The filename this string is associated with
  * @param splatFilename The file name of the bug splat
  */
Item::Item(Game *game, const std::wstring &filename,const std::wstring &splatFilename) : mGame(game)
{
	mImageItem = std::make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
	mSplatImageItem = std::make_shared<wxImage>(splatFilename, wxBITMAP_TYPE_ANY);
}

/**
 * Draws the item
 * @param graphics Graphics that is drawn on
 */
void Item::Draw(shared_ptr<wxGraphicsContext> graphics)
{
	if(IsSplat()){
		mItemBitmap = graphics->CreateBitmapFromImage(*mSplatImageItem);
		double wid = mSplatImageItem->GetWidth();
		double hit = mSplatImageItem->GetHeight();
		graphics->DrawBitmap(mItemBitmap,
							 int(GetX() - wid / 2), int(GetY() - hit / 2), wid, hit);
	}
	else
	{
		mItemBitmap = graphics->CreateBitmapFromImage(*mImageItem);
		double wid = mImageItem->GetWidth();
		double hit = mImageItem->GetHeight();
		if(hit == 700.00){
			mIsSprite = true;
		}
		if(hit == 600.00){
			mIsSprite = true;
		}
		if(mIsSprite){
			if(hit == 600.00){
				DrawSpriteImageSixHundred(graphics);
			}
			if(hit == 700.00){
				DrawSpriteImageSevenHundred(graphics);
			}

		}
		else
		{
			graphics->DrawBitmap(mItemBitmap,
								 int(GetX() - wid / 2), int(GetY() - hit / 2), wid, hit);
		}
	}
}


/**
 * Compute the distance from this item to another item
 * @param item Item we are computing the distance to
 * @return Distance in pixels
 */
double Item::DistanceTo(std::shared_ptr<Item> item)
{
	auto dx = item->GetX() - GetX();
	auto dy = item->GetY() - GetY();
	return sqrt(dx * dx + dy * dy);
}

/**
 * Change location of item
 * @param item
 */
void Item::ChangeLocation(std::shared_ptr<Item> item)
{
	item->mX += 10;
	item->mY += 10;
}
/**
 * Draw the image
 * @param graphics image to draw
 */
void Item::DrawSpriteImageSevenHundred(std::shared_ptr<wxGraphicsContext> graphics){
	auto map = graphics->CreateSubBitmap(mItemBitmap,0,mSpriteImageLocY,100,100);
	graphics->PushState();
	graphics->Translate(mX, mY);
	graphics->Rotate(mAngle);
	graphics->DrawBitmap(map, -100/2, -100/2, 100, 100);
	graphics->PopState();
	mSpriteImageLocY += 100;
	if(mSpriteImageLocY >= 600){
		mSpriteImageLocY = 0;
	}
}


/**
 * Draw the image
 * @param graphics image to draw
 */
void Item::DrawSpriteImageSixHundred(std::shared_ptr<wxGraphicsContext> graphics){
	auto map = graphics->CreateSubBitmap(mItemBitmap,0,mSpriteImageLocY,100,100);
	graphics->PushState();
	graphics->Translate(mX, mY);
	graphics->Rotate(mAngle);
	graphics->DrawBitmap(map, -100/2, -100/2, 100, 100);
	graphics->PopState();
	mSpriteImageLocY += 100;
	if(mSpriteImageLocY >= 500){
		mSpriteImageLocY = 0;
	}
}

/**
 * Draw a fat bug
 * @param graphics image to draw
 */
void Item::DrawFatBug(std::shared_ptr<wxGraphicsContext> graphics){
	auto map = graphics->CreateSubBitmap(mItemBitmap,0,0,100,100);
	graphics->PushState();
	graphics->Translate(mX, mY);
	graphics->Rotate(mAngle);
	graphics->DrawBitmap(map, -100/2, -100/2, 125, 125);
	graphics->PopState();
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(double x, double y)
{
	double wid = mImageItem->GetWidth();
	double hit = mImageItem->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the image center
	// Adding half the size makes x, y relative to theimage top corner
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	// If the location is transparent, we are not in the drawn
	// part of the image
	return !mImageItem->IsTransparent((int)testX, (int)testY);}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode *Item::XmlSave(wxXmlNode *node)
{
	auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
	node->AddChild(itemNode);

	itemNode->AddAttribute(L"x", wxString::FromDouble(mX));
	itemNode->AddAttribute(L"y", wxString::FromDouble(mY));

	return itemNode;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
	node->GetAttribute(L"x", L"0").ToDouble(&mX);
	node->GetAttribute(L"y", L"0").ToDouble(&mY);
}