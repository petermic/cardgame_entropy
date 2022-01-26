#include "pile.h"

class Deck : public Pile {
public:
	Deck(){
		for(int i=0;i<52;i++) cards.push_back(Card(i));
	}
};
