#include "tournament.h"
#include "roundrobin.h"

using namespace std;

int main(int argc, char *argv[]) {
    Tournament* t = new RoundRobin();
    delete t;
}
