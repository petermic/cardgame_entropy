#ifndef GO_FISH_H
#define GO_FISH_H

#include "game.h"
#include "deck.h"
#include "hand.h"

class GoFish : public Game {
public:
	GoFish();
	Deck d;
	Hand p1;
	Hand p2;
	Pile matches1;
	Pile matches2;
	bool debug = false;
	void find_pairs(Hand& h, Pile& p);
	bool take_card(Hand& you, Hand& them, Card c);
	void initialize();
	void run();
	void end();
};

#endif
