#ifndef TRIVIALGAME_H
#define TRIVIALGAME_H

#include "game.h"
#include "deck.h"

class TrivialGame : public Game{
public:
	TrivialGame();
	Deck d;
	void initialize();
	void run();
	void end();
};

#endif
