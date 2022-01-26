#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "pile.h"

#include <list>

class Hand{
public:
	Hand();
	Hand(std::vector<Card> c);
	std::list<Card> cards;
	void play(Card c, Pile p);
	void play(int i, Pile p);
	void draw_from(Pile p);
	void draw_from(Pile p, int n);
};

#endif
