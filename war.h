#ifndef WAR_H
#define WAR_H

#include "game.h"
#include "deck.h"

class War : public Game {
public:
	War();
	Deck d;
	Pile p1;
	Pile p2;
	Pile wp1;
	Pile wp2;
	void initialize();
	void run();
	void end();
	bool debug = false;
private:
	enum Outcome{
		P1Wins,
		P2Wins,
		Tie
	};
	Outcome compare(Card a, Card b);
};

#endif
