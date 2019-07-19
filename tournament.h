#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct Game {
    int score1;
    int score2;
    // returns 1 or 2

    int getWinner() {
        return score1 > score2 ? 1 : 2;
    }
    int getLoser() {
        return score1 < score2 ? 1 : 2;
    }

    bool isDraw() {
        return score1 == score2;
    }
};

class Match {
    string p1;
    string p2;

    int matchId;

    vector<Game> games;

public:
    Match(string p1, string p2, int matchId) : p1{p1}, p2{p2}, matchId{matchId} {}
    virtual ~Match();

    // Adds score for next game
    virtual void addGameScore(int score1, int score2);

    // Gets winner, or ""
    virtual string getWinner();
    virtual string getLoser();

    virtual bool isDraw();

    int getMatchId() {
        return matchId;
    }

    bool isCompetitor(string p) {
        return p == p1 || p == p2;
    }
};

class Tournament {

public:
    Tournament();
    virtual ~Tournament();

    void createFromPlayers(vector<string> name, bool seeded=true) {
        int seed = 0;
        for (string n : name) {
            if (seeded) {
                addCompetitor(n, seed);
            } else {
                addCompetitor(n);
            }
            ++seed;
        }

        createTournament();
    }

    virtual void addCompetitor(string name, int seed=rand()) = 0;
    virtual void addGameScore(int matchId, int score1, int score2) = 0;
    virtual void createTournament() = 0;

    virtual Match& getNextMatch() = 0;

    virtual void writeToFile(string fname) = 0;
    virtual void readToFile(string fname) = 0;
};

#endif 
