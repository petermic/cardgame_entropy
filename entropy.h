#ifndef ENTROPY_H
#define ENTROPY_H

#include "pile.h"

#include <string>

class EntropyProcessor{
public:
	EntropyProcessor();
	int pair_dist[52][52];
	size_t n_decks;
	void process_deck(Pile p);
	void show();
	double compute_entropy();
	void save(std::string filename);
};

#endif
