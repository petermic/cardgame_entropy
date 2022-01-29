#ifndef PILE_H
#define PILE_H

#include "card.h"

#include <vector>
#include <deque>
#include <string>

class Pile{
public:
	Pile();
	Pile(std::vector<Card>);
	std::string name;
	std::deque<Card> cards;
	size_t size();
	void shuffle();
	void sort();
	void show();
	Card draw();
	std::vector<Card> draw(int n);
	void addto_top(Card c);
	void addto_top(std::vector<Card> cs);
	void addto_bottom(Card c);
	void addto_bottom(std::vector<Card> cs);
};

#endif
