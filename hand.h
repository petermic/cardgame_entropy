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
	size_t size();
	void show();
	void play(Card c, Pile& p);
	void play(std::vector<Card> c, Pile& p);
	void play(int i, Pile& p);
	void draw_from(Pile& p);
	void draw_from(Pile& p, int n);
	void give(Card c, Hand& h);
	void take(Card c, Hand& h);
	bool has_card(Card c);
	Card card_at(int i);
};

#endif
