#ifndef SWISS_H
#define SWISS_H

#include "tournament.h"
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <math.h>

using namespace std;

class Swiss : public Tournament {
	vector<Player> players;
    vector<shared_ptr<Match>> matches;
    unordered_map<string, int> scores;
    unordered_map<string, bool> givenBye;

public:
    Swiss(int firstTo = 1): Tournament{firstTo} {}
    ~Swiss() {}

    vector<pair<int, string>> getWinners() {
        vector<pair<int, string>> winners;
        return winners;
    }

    void addCompetitor(string name, int seed=rand()) override {
		players.emplace_back(name, seed);
        scores[name] = 0;
        givenBye[name] = false;
	}

    void removeCompetitor(string name) {};

    void addGameScore(int matchId, int score1, int score2) override {
        shared_ptr<Match> m = matches[matchId];
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
        int numRounds = ceil(log2(players.size()));
        sort(players.rbegin(), players.rend());
        givenBye[players[players.size()-1].name] = true;
        scores[players[players.size()-1].name]++;

        for (int i = 0; i < players.size() / 2; i++) {
            matches.push_back(make_shared<Match>(players[i], players[players.size()/2 + i], i));
        }

        for (int i = 1; i < numRounds; i++) {
            for (int j = 0; j < players.size() / 2; j++) {
                matches.push_back(shared_ptr<Match>(nullptr));
            }
        }
	}

    bool comparePlayers(const Player& p1, const Player& p2) {
        return scores[p1.name] < scores[p2.name];
    }

    bool hasNextMatch() override {
        for (shared_ptr<Match> m : matches) {
            if (m == nullptr) return true;
            if (!m->isOver()) return true;
        }
        return false;
    }

    Match& getNextMatch() override {
        for (int i = 0; i < matches.size(); i++) {
            if (matches[i] == nullptr) {
                // gen next round
                vector<pair<int, int>> playerScores;
                for (int index = 0; index < players.size(); index++) {
                    playerScores.push_back(make_pair(scores[players[index].name], index));
                }
                sort(playerScores.rbegin(), playerScores.rend(),
                [](pair<int, int> a, pair<int, int> b) -> bool {
                    return a.first < b.first;
                });

                for (int j = 0; j < players.size()/2; j++) {
                    matches[i+j] = make_shared<Match>(
                        players[playerScores[j].second],
                        players[playerScores[players.size()/2 + j].second],
                        i+j
                    );
                }
            }

            if (!matches[i]->isOver()) {
                return *matches[i];
            }
        }
	}

    bool isOver() override {
        return false;
    }

    bool inProgress() override {
        return true;
    }

    void reset() override {

    }

    void print() override {
        for (shared_ptr<Match> m : matches) {
            if (m != nullptr) {
                cout << *m;
            }
        }
    }

    void writeToFile(string fname) override {};
    void readToFile(string fname) override {};
};

#endif
