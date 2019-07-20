#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

struct Player {
    Player(string n, int s) : name{n}, seed{s} {}
    string name;
    int seed;

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

    vector<Game> games;

public:
    Match(Player p1, Player p2, int matchId) : p1{p1}, p2{p2}, matchId{matchId} {}
    ~Match() {};

    // Adds score for next game
    void addGameScore(int score1, int score2) {
        games.emplace_back(score1, score2);
    }

    // Gets winner, or ""
    int getWinner() {
        int p1win = 0;
        int p2win = 0;
        int tie = 0;

        for (Game& g : games) {
            if (g.isDraw()) { ++tie;
            } else if (g.getWinner() == 1) { ++p1win;
            } else { ++p2win; }
        }

        if (p1win > p2win) { return 1; }
        else if (p2win > p1win) { return 2; }
        return 0;
    }

    int getLoser() {
        int p1win = 0;
        int p2win = 0;
        int tie = 0;

        for (Game& g : games) {
            if (g.isDraw()) { ++tie;
            } else if (g.getWinner() == 1) { ++p1win;
            } else { ++p2win; }
        }

        if (p1win < p2win) { return 1; }
        else if (p2win < p1win) { return 2; }
        return 0;
    }

    bool isDraw() {
        int p1win = 0;
        int p2win = 0;
        int tie = 0;

        for (Game& g : games) {
            if (g.isDraw()) { ++tie;
            } else if (g.getWinner() == 1) { ++p1win;
            } else { ++p2win; }
        }

        return p1win == p2win;
    }

    int getMatchId() {
        return matchId;
    }

    Player getP1() {
        return p1;
    }
    Player getP2() {
        return p2;
    }

    Player getPlayer(int p) {
        if (p == 1) return p1;
        return p2;
    }

    bool isCompetitor(Player p) {
        return p == p1 || p == p2;
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

    virtual bool hasNextMatch() = 0;
    virtual Match& getNextMatch() = 0;

    virtual void writeToFile(string fname) = 0;
    virtual void readToFile(string fname) = 0;
};

#endif 
