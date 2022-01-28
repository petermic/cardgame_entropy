#include "go_fish.h"
#include "entropy.h"
#include <iostream>

int main(){
	EntropyProcessor e_init;
	EntropyProcessor e_final;
	for(int i=0;i<1000;i++){
		GoFish s;
		s.initialize();
		s.run();
		s.end();
		e_init.process_deck(s.initial_deck_state);
		e_final.process_deck(s.final_deck_state);
		std::cout << i << "\n";
	}
	e_init.show();
	e_final.show();
	e_init.save("/root/cardgame_entropy/war_init.csv");
	e_final.save("/root/cardgame_entropy/war_final.csv");
	std::cout << "Initial entropy: " << e_init.compute_entropy() << "\n";
	std::cout << "Final entropy: " << e_final.compute_entropy() << "\n";
	return 0;
}
