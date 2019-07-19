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
};

class Match {
    string p1;
    string p2;

    vector<Game> games;

public:
    Match(string p1, string p2) : p1{p1}, p2{p2} {}
    virtual ~Match();

    // Adds score for next game
    virtual void addGameScore(int score1, int score2);

    // Gets winner, or ""
    virtual string getWinner();
    virtual string getLoser();

    bool isCompetitor(string p) {
        return p == p1 || p == p2;
    }
};

class Tournament {

public:
    Tournament();
    virtual ~Tournament();

    virtual void addCompetitor(string name, int seed=rand());
    virtual void addGameScore(int matchId, int score1, int score2);
    virtual int getNextGame();

    virtual void writeToFile(string fname);
    virtual void readToFile(string fname);
};

#endif 
