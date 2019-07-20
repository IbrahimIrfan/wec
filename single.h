#ifndef SINGLE_H
#define SINGLE_H

#include "tournament.h"
#include "tree.h"
#include<vector>
#include<iostream>

using namespace std;

class SingleElim : public Tournament {
	Tree tournTree;
	vector<Player> players;
public:
    SingleElim() {}
    ~SingleElim() {}

    void addCompetitor(string name, int seed=rand()) override {
		players.emplace_back(name, seed);
	}

    void removeCompetitor(string name) {
        for (auto it = players.begin(); it != players.end(); ++it) {
            if (it->name == name) {
                players.erase(it);
                return;
            }
        }
    }

    void addGameScore(int matchId, int score1, int score2) override {
		tournTree.addGameScore(matchId, score1, score2);
	}

    void createTournament() override {
		tournTree.constructTree(players);
	}

	bool isOver() override {
        return !tournTree.hasNextMatch();
	}

	bool inProgress() override {
        return tournTree.hasNextMatch();
	}

	bool hasNextMatch() override {
		return tournTree.hasNextMatch();
	}

	void reset() override {
		//TODO
		return;
	}

    vector<pair<int, string>> getWinners() override {
		//TODO
		return vector<pair<int, string>>();
	}

    Match& getNextMatch() override {
		return tournTree.getNextMatch();
	}

    void writeToFile(string fname) override {}
    void readToFile(string fname) override {}

    void print() override {
        tournTree.print();
    }
};

#endif
