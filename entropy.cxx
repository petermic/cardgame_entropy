#include "entropy.h"

#include <iostream>
#include <fstream>
#include <cmath>

EntropyProcessor::EntropyProcessor(){
	for(int i=0;i<52;i++){
		for(int j=0;j<52;j++){
			pair_dist[i][j]=0;
		}
	}
	n_decks = 0;
}

void EntropyProcessor::process_deck(Pile p){
	for(int i=0;i<p.size()-1;i++){
		Card c = p.cards[i];
		Card c2 = p.cards[i+1];
		pair_dist[c.id][c2.id]++;
	}
	n_decks++;
}

void EntropyProcessor::show(){
	std::cout << "Entropy histogram:\n";
	for(int i=0;i<52;i++){
		for(int j=0;j<52;j++){
			std::cout << pair_dist[i][j] << " ";
		}
		std::cout << "\n";
	}
}

double EntropyProcessor::compute_entropy(){
	double normalizer = 52*n_decks;
	double H = 0;
	for(int i=0;i<52;i++){
		for(int j=0;j<52;j++){
			double p = (double)pair_dist[i][j]/normalizer;
			if(p>0) H += -p*log2(p);
		}
	}
	return H;
}

void EntropyProcessor::save(std::string filename){
	std::ofstream outfile;
	std::cout << "saving to " << filename << "\n";
	outfile.open(filename.c_str());
	double normalizer = 52*n_decks;
	for(int i=0;i<52;i++){
		for(int j=0;j<52;j++){
			double p = (double)pair_dist[i][j]/normalizer;
			outfile << p << ",";
		}
		outfile << std::endl;
	}
	outfile << std::flush;
	outfile.close();
}
