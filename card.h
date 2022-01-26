#ifndef CARD_H
#define CARD_H

#include <map>
#include <string>

enum Suit {
	Spades,
	Clubs,
	Hearts,
	Diamonds
};

static std::map<Suit,std::string> suit_names{
	{Suit::Spades, "Spades"},
	{Suit::Clubs, "Clubs"},
	{Suit::Hearts, "Hearts"},
	{Suit::Diamonds, "Diamonds"}
};

static std::map<int,std::string> face_names{
	{11,"Jack"},
	{12,"Queen"},
	{13,"King"},
	{1,"Ace"}
};

class Card {
public:
	Suit suit;
	int rank;
	Card(int id);
	void show();
	int id;
	bool operator==(Card a){
		return (suit == a.suit && rank == a.rank);
	}
};

#endif
