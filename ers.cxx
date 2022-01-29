#include "ers.h"

#include <iostream>
#include <random>

ERS::ERS(){
	p1.name = "P1";
	p2.name = "P2";
	s = std::uniform_int_distribution<int>(1,2);
}

void ERS::initialize(){
	d.shuffle();
	initial_deck_state = d;
	p1.addto_top(d.draw(26));
	p2.addto_top(d.draw(26));
	if(debug){
		std::cout << "P1 pile:\n";
		p1.show();
		std::cout << "P2 pile:\n";
		p2.show();
		std::cout << "\n";
	}
}

void ERS::play_next(Pile& p){
	Card c = p.draw();
	if(debug) c.show();
	pot.addto_top(c);
	if(last_three_cards.size()==3) last_three_cards.pop_back();
	last_three_cards.push_front(c);
}

bool ERS::is_facecard_played(){
	if(pot.size()==0) return false;
	return (last_three_cards[0].rank>10) || (last_three_cards[0].rank==1);
}

bool ERS::try_play_facecard(Pile& atk, Pile& def){
	if(def.size()==0) return false;
	if(debug) std::cout << def.name << " tries:\n";
	play_next(def);
	bool slapped = resolve_slap();
	if(slapped) return true;
	bool success = is_facecard_played();
	if(success){
		if(debug) std::cout << "pass to " << atk.name << "\n";
		resolve_facecard(def,atk);
	}
	return success;
}

void ERS::resolve_facecard(Pile& atk, Pile& def){
	int rnk = last_three_cards[0].rank;
	if(rnk==11){
		if(!try_play_facecard(atk,def)){
			if(debug) std::cout << atk.name << " won\n";
			atk.addto_bottom(pot.draw(pot.size()));
			last_three_cards.clear();
			turn_ptr = &atk;
		}
	}
	if(rnk==12){
		bool rnd1 = try_play_facecard(atk,def);
		if(rnd1) return;
		bool rnd2 = try_play_facecard(atk,def);
		if(!rnd2){
			if(debug) std::cout << atk.name << " won\n";
			atk.addto_bottom(pot.draw(pot.size()));
			last_three_cards.clear();
			turn_ptr = &atk;
		}
	}
	if(rnk==13){
		bool rnd1 = try_play_facecard(atk,def);
                if(rnd1) return;
                bool rnd2 = try_play_facecard(atk,def);
                if(rnd2) return;
		bool rnd3 = try_play_facecard(atk,def);
		if(!rnd3){ 
			if(debug) std::cout << atk.name << " won\n";
			atk.addto_bottom(pot.draw(pot.size()));
			last_three_cards.clear();
			turn_ptr = &atk;
		}
	}
	if(rnk==1){
		bool rnd1 = try_play_facecard(atk,def);
                if(rnd1) return;
                bool rnd2 = try_play_facecard(atk,def);
                if(rnd2) return;
                bool rnd3 = try_play_facecard(atk,def);
		if(rnd3) return;
		bool rnd4 = try_play_facecard(atk,def);
		if(!rnd4){ 
			if(debug) std::cout << atk.name << "won\n";
			atk.addto_bottom(pot.draw(pot.size()));
			last_three_cards.clear();
			turn_ptr = &atk;
		}
	}
}

bool ERS::resolve_slap(){
	bool slap;
	if(last_three_cards.size()<2) slap = false;
	else if(last_three_cards.size()==2) slap = (last_three_cards[0].rank == last_three_cards[1].rank);
	else slap = (last_three_cards[0].rank == last_three_cards[1].rank) ||
		(last_three_cards[0].rank == last_three_cards[2].rank);
	if(slap){
		if(debug) std::cout << "SLAP\n";
		int winner = s(r);
		if(winner==1){
			if(debug) std::cout << "P1 wins\n";
			p1.addto_bottom(pot.draw(pot.size()));
			turn_ptr = &p2;
		}
		if(winner==2){
			if(debug) std::cout << "P2 wins\n";
			p2.addto_bottom(pot.draw(pot.size()));
			turn_ptr = &p1;
		}
		last_three_cards.clear();
	}
	return slap;
}

void ERS::run(){
	turn_ptr = &p1;
	while(p1.size()>0 && p2.size()>0){
		if(debug) std::cout << "P1 size: " << p1.size() << "\n";
		if(debug) std::cout << "P2 size: " << p2.size() << "\n"; 
		if(debug) std::cout << "pot size: " << pot.size() << "\n\n";
		if(turn_ptr == &p1){
			if(debug) std::cout << "P1 turn\n";
			play_next(p1);
			if(resolve_slap()) continue;
			if(is_facecard_played()) resolve_facecard(p1,p2);
			else turn_ptr = &p2;
			if(debug) std::cout << std::endl;

		}
		else{
			if(debug) std::cout << "P2 turn\n";
			play_next(p2);
			if(resolve_slap()) continue;
			if(is_facecard_played()) resolve_facecard(p2,p1);
			else turn_ptr = &p1;
			if(debug) std::cout << std::endl;
		}
		if(debug) std::cout << "end turn\n";
	}
}

void ERS::end(){
	if(debug) std::cout << "cleaning up\n";
	d.addto_top(pot.draw(pot.size()));
	d.addto_top(p1.draw(p1.size()));
	d.addto_top(p2.draw(p2.size()));
	final_deck_state = d;
	if(debug) std::cout << "final deck size: " << d.size() << "\n";
	if(debug) std::cout << "done\n";
}
