#ifndef SHUFFLEGAME_H
#define SHUFFLEGAME_H

#include "game.h"
#include "deck.h"

class ShuffleGame : public Game {
public:
	ShuffleGame();
	Deck d;
	void initialize();
	void run();
	void end();
};

#endif
