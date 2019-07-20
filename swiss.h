#ifndef SWISS_H
#define SWISS_H

#include "tournament.h"
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

class Swiss : public Tournament {
	vector<Player> players;
    vector<Match*> matches;
    unordered_map<string, int> scores;
    unordered_map<string, bool> givenBye;

public:
    Swiss();

    void addCompetitor(string name, int seed=rand()) override {
		players.emplace_back(name, seed);
        scores[name] = 0;
        givenBye[name] = false;
	}

    void addGameScore(int matchId, int score1, int score2) override {
        Match *m = matches[matchId];
        if (m == nullptr) return;

        if (!m->isOver()) {
            m->addGameScore(score1, score2);
        }

        if (m->isOver()) {
            string winnerName = m->getPlayer(m->winner()).name;
            scores[winnerName]++;
        }

	}

    void createTournament() override {

	}

    bool hasNextMatch() override {
        for (Match *m : matches) {
            if (!m->isOver()) {
                return true;
            }
        }
        return false;
    }

    Match& getNextMatch() override {

	}

    void writeToFile(string fname) override;
    void readToFile(string fname) override;
};

#endif
