#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

struct Player {
    Player(string n, int s) : name{n}, seed{s}, wins{0} {}
    string name;
    int seed;
    int wins;

    bool operator<(Player& other) const{
        return seed < other.seed;
    }
    bool operator<=(Player& other) const{
        return seed <= other.seed;
    }
    bool operator>(Player& other) const {
        return seed > other.seed;
    }
    bool operator>=(Player& other) const {
        return seed >= other.seed;
    }
    bool operator==(Player& other) const {
        return name == other.name;
    }
};

struct Game {
    Game(int s1, int s2): score1{s1}, score2{s2} {}

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
    Player p1;
    Player p2;

    int matchId;
    int firstTo;

    vector<Game> games;

    int p1wins() {
        int q = 0;
        for (Game g : games) {
            if (g.getWinner() == 1) {
                ++q;
            }
        }
        return q;
    }
    int p2wins() {
        int q = 0;
        for (Game g : games) {
            if (g.getWinner() == 2) {
                ++q;
            }
        }
        return q;
    }
    int ties() {
        int q = 0;
        for (Game g : games) {
            if (g.isDraw()) {
                ++q;
            }
        }
        return q;
    }

public:
    Match(Player p1, Player p2, int matchId, int firstTo=1) : p1{p1}, p2{p2}, matchId{matchId}, firstTo{firstTo} {}
    ~Match() {};

    // Adds score for next game
    void addGameScore(int score1, int score2) {
        if (!isOver()) {
            games.emplace_back(score1, score2);
        }
    }

    int getMatchId() { return matchId; }

    int winner() {
        if (!isOver()) return 0;
        if (p1wins() > p2wins()) {
            return 1;
        } else {
            return 2;
        }
        return 0;
    }
    int loser() {
        if (!isOver()) return 0;
        if (p1wins() < p2wins()) {
            return 1;
        } else {
            return 2;
        }
    }

	// for use with completing partial matches in single elim
    void setP1(Player p) { p1 = p; }
    void setP2(Player p) { p2 = p; }

    int getFirstTo() { return firstTo; }
    Player getP1() { return p1; }
    Player getP2() { return p2; }
    Player getPlayer(int p) {
        if (p == 1) return p1;
        return p2;
    }

    bool isCompetitor(Player p) { return p == p1 || p == p2; }

    bool isOver() {
        return p1wins() >= firstTo ||
               p2wins() >= firstTo;
    }

    friend ostream& operator<<(ostream& os, Match& m);
};

ostream& operator<<(ostream& os, Match& m) {
    return os << "Match "
              << m.matchId
              << ": "
              << m.p1.name
              << " vs. "
              << m.p2.name
              << endl;
}

class Tournament {
public:
    Tournament() {};
    virtual ~Tournament() {};

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

    virtual vector<string> getWinners() = 0;

    virtual void addCompetitor(string name, int seed=rand()) = 0;
    virtual void removeCompetitor(string name) = 0;
    virtual void addGameScore(int matchId, int score1, int score2) = 0;
    virtual void createTournament() = 0;

    virtual bool isOver() = 0;
    virtual bool hasNextMatch() = 0;
    virtual Match& getNextMatch() = 0;

    virtual void writeToFile(string fname) = 0;
    virtual void readToFile(string fname) = 0;

    virtual void print() = 0;
};

#endif 
