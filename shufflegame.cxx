#include "shufflegame.h"

ShuffleGame::ShuffleGame(){}

void ShuffleGame::initialize(){
	initial_deck_state = d;
}

void ShuffleGame::run(){
	d.shuffle();
}

void ShuffleGame::end(){
	final_deck_state = d;
}
