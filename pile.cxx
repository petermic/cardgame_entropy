#include "pile.h"

#include <algorithm>
#include <chrono>
#include <random>

Pile::Pile(){
}

Pile::Pile(std::vector<Card> ncards){
	for(Card card : ncards){
		cards.push_back(card);
	}
}

size_t Pile::size(){
	return cards.size();
}

void Pile::shuffle(){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cards.begin(),cards.end(),std::default_random_engine(seed));
}

void Pile::sort(){
	std::sort(cards.begin(),cards.end(),
			[](Card a, Card b){
				return (a.id < b.id);
			});
}

void Pile::show(){
	for(Card card : cards){
		card.show();
	}
}

Card Pile::draw(){
	Card c = cards[0];
	cards.pop_front();
	return c;
}

std::vector<Card> Pile::draw(int n){
	if(n>cards.size()) n=cards.size();
	std::vector<Card> cs;
	for(int i=0;i<n;i++){
		cs.push_back(draw());
	}
	return cs;
}

void Pile::addto_top(Card c){
	cards.push_front(c);
}

void Pile::addto_top(std::vector<Card> cs){
	for(Card c : cs) addto_top(c);
}

void Pile::addto_bottom(Card c){
	cards.push_back(c);
}

void Pile::addto_bottom(std::vector<Card> cs){
	for (Card c : cs) addto_bottom(c);
}
