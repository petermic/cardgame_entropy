#ifndef GAME_H
#define GAME_H

#include "pile.h"

class Game {
public:
	Game(){};
	virtual void initialize()=0;
	virtual void run()=0;
	virtual void end()=0;
	Pile initial_deck_state;
	Pile final_deck_state;
};

#endif
