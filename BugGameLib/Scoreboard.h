/**
 * @file Scoreboard.h
 * @author Sungu Han
 *
 * Class to deal with scores
 */

#ifndef PROJECT_1_BUGGAMELIB_SCOREBOARD_H
#define PROJECT_1_BUGGAMELIB_SCOREBOARD_H


class Game;

/**
 * The main scoreboard class
 */

class Scoreboard
{
private:
	/// The scoreboard of this game
	Game* mGame;

public:

	Scoreboard(Game* game);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	/// increment the fixed score
	void IncrementFixedScore();

	/// increment the missed score
	void IncrementMissedScore();

	/// increment the oops score
	void IncrementOopsScore();

	void ResetScoreboard();
};

#endif //PROJECT_1_BUGGAMELIB_SCOREBOARD_H
