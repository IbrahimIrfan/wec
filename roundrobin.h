#ifndef RR_H
#define RR_H

#include <unordered_map>
#include <algorithm>
#include "tournament.h"

using namespace std;

class RoundRobin : public Tournament {
    vector<Player> players;
    vector<Match> matches;

public:
    RoundRobin() {}
    virtual ~RoundRobin() {}

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
    void addGameScore(int matchId, int score1, int score2) {
        if (!matches[matchId].isOver()) {
            matches[matchId].addGameScore(score1, score2);
        }
    }

    void createTournament() {
        int matchId = 0;

        matches.clear();
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

    vector<string> getWinners() {
        if (!isOver()) {
            return vector<string>();
        }
        unordered_map<string, int> scores;
        for (Match& m : matches) {
            m.getPlayer(m.winner());
        }
    }

    bool isOver() {
        return !hasNextMatch();
    }

    bool hasNextMatch() {
        for (Match& m : matches) {
            if (!m.isOver()) {
                return true;
            }
        }
        return false;
    }

    Match& getNextMatch() {
        for (Match& m : matches) {
            if (!m.isOver()) {
                return m;
            }
        }
    }

    void writeToFile(string fname) {}
    void readToFile(string fname) {}

    void print() override {
        for (auto& match : matches) {
            cout << match << endl;
        }
    }
};

#endif
