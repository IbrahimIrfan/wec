#ifndef SINGLE_H
#define SINGLE_H

#include "tournament.h"
#include "tree.h"

using namespace std;

class SingleElim : public Tournament {
	
	Tree tournTree;
	vector<Player&> players;
public:
    SingleElim();

    void addCompetitor(string name, int seed=rand()) override {
		players.emplace_back(Player(name, seed));
	}

    void addGameScore(int matchId, int score1, int score2) override {
	}

    void createTournament() override {
		tournTree.constructTree(players);
	}

    Match& getNextMatch() override {
		return tournTree->getNextMatch();
	}

    void writeToFile(string fname) override;
    void readToFile(string fname) override;
};

#endif
