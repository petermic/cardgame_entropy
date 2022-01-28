#include "go_fish.h"

#include <random>
#include <iostream>
#include <chrono>
#include <unordered_set>

GoFish::GoFish(){
}

void GoFish::initialize(){
	d.shuffle();
	initial_deck_state = d;
	p1.draw_from(d,7);
	p2.draw_from(d,7);
	find_pairs(p1,matches1);
	find_pairs(p2,matches2);
}

void GoFish::find_pairs(Hand& h, Pile& p){
	if(debug) std::cout << "finding pairs\n";
	if(debug) std::cout << "size: " << h.size() << "\n";
	std::vector<Card> pairs;
	for(int i=0;i<h.size();i++){
		Card c = h.card_at(i);
		for(int j=0;j<h.size();j++){
			if(i>=j) continue;
			Card c2 = h.card_at(j);
			if(c.rank == c2.rank){
				pairs.push_back(c);
				pairs.push_back(c2);
			}
		}
	}
	for(Card c : pairs){
		h.play(c,p);
	}
	if(debug) std::cout << "post-find size: " << h.size() << "\n";
}

bool GoFish::take_card(Hand& you, Hand& them, Card c){
	bool found_card = false;
	Hand dup = them;
	for(Card hc : dup.cards){
		if(hc.rank == c.rank){
			found_card = true;
			if(debug) std::cout << "gave\n";
			if(debug) hc.show();
			you.take(hc,them);
			if(debug) std::cout << "you:\n";
			if(debug) you.show();
			if(debug) std::cout << "them:\n";
			if(debug) them.show();
		}
	}
	return found_card;
}

void GoFish::run(){
	std::default_random_engine r;
	while(d.size()>0 && p1.size()>0 && p2.size()>0){
		std::uniform_int_distribution<> p1d(0,p1.size()-1);
		if(debug) std::cout << "P1 hand:\n";
		if(debug) p1.show();
		if(debug) std::cout << "\n";
		int card = p1d(r);
		Card c = p1.card_at(card);
		if(debug) std::cout << "P1: Got any " << c.rank << "s?\n";
		if(!take_card(p1,p2,c)){
			if(debug) std::cout << "P2: Go Fish\n";
			p1.draw_from(d);
		}
		find_pairs(p1,matches1);

		std::uniform_int_distribution<> p2d(0,p2.size()-1);
		if(debug) std::cout << "P2 hand:\n";
		if(debug) p2.show();
		if(debug) std::cout << "\n";
		int card2 = p2d(r);
		Card c2 = p2.card_at(card2);
		if(debug) std::cout << "P2: Got any " << c2.rank << "s?\n";
		if(!take_card(p2,p1,c2)){
			if(debug) std::cout << "P2: Go Fish\n";
			p2.draw_from(d);
		}
		find_pairs(p2,matches2);
	}
}

void GoFish::end(){
	d.addto_top(matches1.draw(matches1.size()));
	d.addto_top(matches2.draw(matches2.size()));
	std::list<Card> p1list = p1.cards;
	std::list<Card> p2list = p2.cards;
	for(Card c : p1list) p1.play(c,d);
	for(Card c : p2list) p2.play(c,d);
	if(debug) std::cout << "setting final deck state\n";
	final_deck_state = d;
}
