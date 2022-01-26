#include "card.h"

#include <string>
#include <iostream>

Card::Card(int n){
	id = n;
	rank = n % 13 + 1;
	switch(n/13){
		case 0:
			suit = Suit::Spades;
		break;
		case 1:
			suit = Suit::Clubs;
		break;
		case 2:
			suit = Suit::Hearts;
		break;
		case 3:
			suit = Suit::Diamonds;
		break;
	}
}

void Card::show(){
	std::string out = "";
	if(rank>1 && rank<=10){
		out += std::to_string(rank);
	}
	else{
		out += face_names[rank];
	}
	out += " of ";
	out += suit_names[suit];
	std::cout << out << "\n";
}
