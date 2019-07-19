#ifndef RR_H
#define RR_H

#include "tournament.h"

using namespace std;

class RoundRobin : public Tournament {

public:
    RoundRobin();

    virtual void addCompetitor(string name, int seed=rand());
    virtual void addGameScore(int matchId, int score1, int score2);
    virtual void createTournament();

    virtual Match& getNextMatch();

    virtual void writeToFile(string fname);
    virtual void readToFile(string fname);
};

#endif
