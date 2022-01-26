#include "war.h"

#include <iostream>

War::War(){}

void War::initialize(){
	d.shuffle();
	initial_deck_state = d;
	p1.addto_top(d.draw(26));
	p2.addto_top(d.draw(26));
}

War::Outcome War::compare(Card a, Card b){
	if(a.rank == b.rank) return Outcome::Tie;
	if(a.rank==1) return Outcome::P1Wins;
	if(b.rank==1) return Outcome::P2Wins;
	if((a.rank>b.rank) && b.rank>1) return Outcome::P1Wins;
	if((a.rank<b.rank) && a.rank>1) return Outcome::P2Wins;
}

void War::run(){
	int turn_counter = 0;
	while(p1.size()>0 && p2.size()>0){
		if(debug) std::cout << "P1 size: " << p1.size() << "\n";
		if(debug) std::cout << "P2 size: " << p2.size() << "\n";
		if(turn_counter>100000){
			std::cout << "reached max turns\n";
			break;
		}
		Card p1c = p1.draw();
		if(debug) p1c.show();
		Card p2c = p2.draw();
		if(debug) p2c.show();
		Outcome r = compare(p1c,p2c);
		if(r==Outcome::P1Wins){
			if(debug) std::cout << "P1 wins\n\n";
			p1.addto_bottom({p1c,p2c});
		}
		if(r==Outcome::P2Wins){
			if(debug) std::cout << "P2 wins\n\n";
			p2.addto_bottom({p1c,p2c});
		}
		if(r==Outcome::Tie){
			if(debug) std::cout << "WAR!\n";
			bool at_war = true;
			wp1.addto_top(p1c);
			wp2.addto_top(p2c);
			if(p1.size()==0 || p2.size()==0) continue;
			wp1.addto_top(p1.draw(3));
			wp2.addto_top(p2.draw(3));
			if(p1.size()==0 || p2.size()==0) continue;
			while(at_war){
				Card p1war = p1.draw();
				if(debug) p1war.show();
				Card p2war = p2.draw();
				if(debug) p2war.show();
				Outcome s = compare(p1war,p2war);
				wp1.addto_top(p1war);
				wp2.addto_top(p2war);
				if(s==Outcome::P1Wins){
					if(debug) std::cout << "P1 wins\n\n";
					at_war = false;
					p1.addto_bottom(wp1.draw(wp1.size()));
					p1.addto_bottom(wp2.draw(wp2.size()));
				}
				if(s==Outcome::P2Wins){
					if(debug) std::cout << "P2 wins\n\n";
					at_war = false;
					p2.addto_bottom(wp1.draw(wp1.size()));
					p2.addto_bottom(wp2.draw(wp2.size()));
				}
				if(p1.size()==0 || p2.size()==0) at_war = false;
			}
		}
		turn_counter++;
	}
}

void War::end(){
	d.addto_top(p1.draw(p1.size()));
	d.addto_top(p2.draw(p2.size()));
	d.addto_top(wp1.draw(wp1.size()));
	d.addto_top(wp2.draw(wp2.size()));
	final_deck_state = d;
}
