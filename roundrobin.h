#ifndef RR_H
#define RR_H

#include <unordered_map>
#include <algorithm>
#include "tournament.h"
#include <stdexcept>

using namespace std;

class RoundRobin : public Tournament {
    vector<Player> players;
    vector<Match> matches;
    
    bool progress;
    bool over;
public:
    RoundRobin(int firstTo = 1): Tournament{firstTo}, progress{false} {}
    virtual ~RoundRobin() {}

    void addCompetitor(string name, int seed) {
        if (!progress && !over) {
            players.emplace_back(name, seed);
        }
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
        if (inProgress()) {
            matches[matchId].addGameScore(score1, score2);

            if (!hasNextMatch()) {
                over = true;
                progress = false;
            }
        }
    }

    bool inProgress() {
        return progress;
    }

    void createTournament() {
        if (!inProgress() && !isOver()) {
            progress = true;
            int matchId = 0;

            matches.clear();
            sort(players.begin(), players.end());
            for (size_t i = 0; i < players.size() - 1; i++) {
                for (size_t j = i + 1; j < players.size(); j++) {
                    matches.emplace_back(
                            players[i],
                            players[j],
                            matchId++,
                            getFirstTo());
                }
            }
        }
    }

    vector<pair<int, string>> getWinners() {
        if (!isOver()) {
            return vector<pair<int, string>>();
        }
        unordered_map<string, int> scores;
        for (Match& m : matches) {
            Player winner = m.getPlayer(m.winner());
            ++scores[winner.name];
        }

        vector<pair<int, string>> ranks;

        for (Player p : players) {
            ranks.push_back(make_pair(scores[p.name], p.name));
        }

        sort(ranks.rbegin(), ranks.rend());
        vector<pair<int, string>> ret;

        int rank = 1;
        for (size_t i = 0; i < ranks.size(); i++) {
            if (i != 0 && ranks[i].first != ranks[i - 1].first) {
                rank = i + 1;
            }
            ret.push_back(make_pair(rank, ranks[i].second));
        }

        return ret;
    }

    bool isOver() {
        return over;
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
        // >:(
        throw out_of_range("there are no more matches");
    }

    void reset() {
        players.clear();
        matches.clear();
        progress = false;
    }

    void writeToFile(string fname) {}
    void readToFile(string fname) {}

    friend ostream& operator<<(ostream&, RoundRobin&);
};

class RRSeededTournament : public Tournament {
    RoundRobin* rr;
    Tournament* t;
public:
    RRSeededTournament(Tournament* other) : rr{new RoundRobin}, t{other} {
        t->reset();
    }

    virtual vector<pair<int, string>> getWinners() {
        return t->getWinners();
    }

    void addCompetitor(string name, int seed) {
        rr->addCompetitor(name, seed);
    }
    virtual void removeCompetitor(string name) {
        if (rr->inProgress()) {
            rr->removeCompetitor(name);
        } else if (t->inProgress()) {
            t->removeCompetitor(name);
        }
    }
    virtual void addGameScore(int matchId, int score1, int score2) {
        if (rr->inProgress()) {
            rr->addGameScore(matchId, score1, score2);
            if (rr->isOver()) {
                vector<string> players;
                for (auto pis : rr->getWinners()) {
                    players.push_back(pis.second);
                }
                t->createFromPlayers(players);
            }
        } else {
            t->addGameScore(matchId, score1, score2);
        }
    }
    virtual void createTournament() {
        if (!inProgress() && !isOver()) {
            rr->createTournament();
        }
    }

    virtual bool isOver() {
        return rr->isOver() && t->isOver();
    }
    virtual bool inProgress() {
        return rr->inProgress() || t->inProgress();
    }
    virtual void reset() {
        rr->reset();
        t->reset();
    }
    virtual bool hasNextMatch() {
        return rr->hasNextMatch() || t->hasNextMatch();
    }
    virtual Match& getNextMatch() {
        if (rr->hasNextMatch()) {
            return rr->getNextMatch();
        }
        return t->getNextMatch();
    }

    virtual void writeToFile(string fname) {};
    virtual void readToFile(string fname) {};
};

#endif
