  /**
 * @file TestGame.cpp
 * @author Sungu Han
 * Tests for Game
 */


#include <pch.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>
#include <gtest/gtest.h>
#include "BugFeature.h"
#include "BugGarbage.h"

const unsigned int RandomSeed = 1238197374;

using namespace std;


class GameTest : public ::testing::Test
{
protected:
	/**
	* Create a path to a place to put temporary files
	*/
	int Load(const wxString &filename)
	{
		int itemCount = 0;
		wxXmlDocument xmlDoc;
		if(!xmlDoc.Load(filename))
		{
			wxMessageBox(L"Unable to load Game file");
		}
		auto root = xmlDoc.GetRoot();

		auto child = root->GetChildren();
		for( ; child; child=child->GetNext())
		{
			auto childName = child->GetName();
			auto nestedChild = child->GetChildren();
			for( ; nestedChild; nestedChild = nestedChild->GetNext())
			{
				itemCount++;
			}
		}
		return itemCount;
	}

	/**
	* Read a file into a wstring and return it.
	* @param filename Name of the file to read
	* @return File contents
	*/
	wstring ReadFile(const wxString &filename)
	{
		ifstream t(filename.ToStdString());
		wstring str((istreambuf_iterator<char>(t)),
					istreambuf_iterator<char>());

		return str;
	}

	void TestEmpty(wxString filename)
	{
		cout << "Temp file: " << filename << endl;

		auto xml = ReadFile(filename);
		cout << xml << endl;
		ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
		ASSERT_TRUE(regex_search(xml, wregex(L"<game/>")));
	}

	/**
	*  Add levels to game
	*/
	void AddLevels(Game *game)
	{
		game->GetRandom().seed(RandomSeed);
	}
};


TEST_F(GameTest, Load) {

	// Create an aquarium
	Game game;

	auto file0 = Load("../data/level0.xml");
	ASSERT_EQ(file0, 7);

	auto file1 = Load("../data/level1.xml");
	ASSERT_EQ(file1, 12);

	auto file2 = Load("../data/level2.xml");
	ASSERT_EQ(file2, 24);

	auto file3 = Load("../data/level3.xml");
	ASSERT_EQ(file3, 30);
}