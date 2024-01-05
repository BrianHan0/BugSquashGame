/**
 * @file Message.h
 * @author Sungu Han
 *
 * Class deals with beginning and ending
 * messages for the game
 */

#ifndef PROJECT_1_BUGGAMELIB_MESSAGE_H
#define PROJECT_1_BUGGAMELIB_MESSAGE_H

using namespace std;

class Game;

/**
* Class for the beginning and ending message, draws the messages
*/
class Message
{
private:
	/// The scoreboard of this game
	Game* mGame;

public:
	void Draw(shared_ptr<wxGraphicsContext> graphics, int currentLevel, bool end);
};

#endif //PROJECT_1_BUGGAMELIB_MESSAGE_H
