#include <cstdlib>

#include "tournament.h"
#include "roundrobin.h"
#include "single.h"

using namespace std;

int main(int argc, char *argv[]) {
    Tournament* t = new RRSeededTournament(new RoundRobin);

    t->createFromPlayers(vector<string>{
            "Ibrahim",
            "Callum",
            "Max",
            "Bob"
        });

    while (!t->isOver()) {
        Match& m = t->getNextMatch();
        t->addGameScore(m.getMatchId(), rand(), rand());
        cout << m << endl;
    }

    vector<pair<int, string>> winners = t->getWinners();

    int pos = 1;
    for (auto s : winners) {
        cout << s.first << ". " << s.second << endl;
        ++pos;
    }

    delete t;
}
