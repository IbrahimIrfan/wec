#ifndef RR_H
#define RR_H

#include <algorithm>
#include "tournament.h"

using namespace std;

class RoundRobin : public Tournament {
    vector<Player> players;
    vector<Match> matches;

    size_t curMatch;

public:
    RoundRobin(): curMatch{0} {};
    virtual ~RoundRobin() {};

    void addCompetitor(string name, int seed) {
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
    void addGameScore(int matchId, int score1, int score2) {}

    void createTournament() {
        int matchId = 0;

        sort(players.begin(), players.end());
        for (size_t i = 0; i < players.size() - 1; i++) {
            for (size_t j = 1; j < players.size(); j++) {
                matches.emplace_back(
                        players[i],
                        players[j],
                        matchId++);
            }
        }
    }

    bool hasNextMatch() {
        return curMatch >= matches.size();
    }

    Match& getNextMatch() {
        return matches[curMatch];
    }

    void writeToFile(string fname) {}
    void readToFile(string fname) {}
};

#endif
