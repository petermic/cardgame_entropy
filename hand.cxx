#include "hand.h"

Hand::Hand(){}

Hand::Hand(std::vector<Card> c){
	for(Card card : c){
		cards.push_back(card);
	}
}

void Hand::play(Card c, Pile p){
	cards.remove(c);
	p.addto_top(c);
}

void Hand::play(int i,Pile p){
	std::list<Card>::iterator it = cards.begin();
	std::advance(it,i);
	Card c = *it;
	cards.remove(c);
	p.addto_top(c);
}

void Hand::draw_from(Pile p){
	Card c = p.draw();
	cards.push_back(c);
}

void Hand::draw_from(Pile p, int n){
	for(int i=0;i<n;i++) draw_from(p);
}
