#include "hand.h"

Hand::Hand(){}

Hand::Hand(std::vector<Card> c){
	for(Card card : c){
		cards.push_back(card);
	}
}

size_t Hand::size(){
	return cards.size();
}

void Hand::show(){
	for(Card c : cards) c.show();
}

void Hand::play(Card c, Pile& p){
	cards.remove(c);
	p.addto_top(c);
}

void Hand::play(std::vector<Card> cs, Pile& p){
	for(Card c : cs) play(c,p);
}

void Hand::play(int i,Pile& p){
	Card c = card_at(i);
	play(c,p);
}

void Hand::draw_from(Pile& p){
	Card c = p.draw();
	cards.push_back(c);
}

void Hand::draw_from(Pile& p, int n){
	std::vector<Card> cs = p.draw(n);
	for(Card c : cs) cards.push_back(c);
}

void Hand::give(Card c, Hand& h){
	if(has_card(c)){
		cards.remove(c);
		h.cards.push_back(c);
	}
}

void Hand::take(Card c, Hand& h){
	if(h.has_card(c)){
		h.cards.remove(c);
		cards.push_back(c);
	}
}

bool Hand::has_card(Card c){
	bool ans = false;
	for(Card cc : cards){
		if(cc == c) ans = true;
	}
	return ans;
}

Card Hand::card_at(int i){
	std::list<Card>::iterator it = cards.begin();
	std::advance(it,i);
	Card c = *it;
	return c;
}
