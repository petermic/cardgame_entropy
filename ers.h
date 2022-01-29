#ifndef ERS_H
#define ERS_H

#include "game.h"
#include "deck.h"

#include <deque>
#include <random>

class ERS : public Game {
public:
	ERS();
	Deck d;
	Pile p1;
	Pile p2;
	Pile pot;
	std::deque<Card> last_three_cards;
	std::default_random_engine r;
	std::uniform_int_distribution<int> s;
	void play_next(Pile& p);
	bool is_facecard_played();
	bool resolve_slap();
	bool try_play_facecard(Pile& atk, Pile& def);
	void resolve_facecard(Pile& atk, Pile& def);
	Pile* turn_ptr;
	void initialize();
	void run();
	void end();
	bool debug = true;
};

#endif
