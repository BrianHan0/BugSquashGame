/**
 * @file BugTest.cpp
 * @author Sungu Han
 */
#include <pch.h>
#include "BugTest.h"
#include "gtest/gtest.h"
#include <BugFeature.h>
#include <Game.h>
#include <BugNull.h>
using namespace std;

TEST(BugTest, Construct){
	Game game;
	BugFeature bugFeat(&game);
}

TEST(BugTest, HitTest) {
	Game game;

	ASSERT_EQ(game.HitTest(100, 200), nullptr) <<
												   L"Testing empty aquarium";
	shared_ptr<BugFeature> bug = make_shared<BugFeature>(&game);
	game.Add(bug);
	// Give it a location
	// Always make the numbers different, in case they are mixed up
	bug->SetLocation(100,200);
	ASSERT_TRUE(game.HitTest(100, 200) == bug) <<
													 L"Testing fish at 100, 200";

	ASSERT_TRUE(game.HitTest(400, 400) == bug) <<
											   L"Testing fish at 100, 200";


}

TEST(BugTest, Clear){
	Game game;
	BugFeature bugFeat(&game);
	bugFeat.SetLocation(100, 200);
	ASSERT_TRUE(bugFeat.HitTest(100, 200));
	game.Clear();
	ASSERT_FALSE(game.HitTest(100, 200));
}

TEST(BugTest, Click){
	Game game;
	//BugNull bugNull(&game);
	//bugNull.SetLocation(100,200);
	//ASSERT_TRUE(bugNull.HitTest(100, 200));
}

