#include <memory>

#include "tournament.h"
#include "roundrobin.h"

using namespace std;

const string seperator = "---------------------------------------";

int main(int argc, char *argv[]) {
	while (true) {
		cout << "Welcome to Yeet" << endl;
		cout << seperator << endl;

		cout << "Please enter which tournament style you would like" << endl;
		cout << "Single Elimination, Enter: 1" << endl;
		cout << "Double Elimination, Enter: 2" << endl;
		cout << "Round-Robin,        Enter: 3" << endl;
		cout << "Swiss Format,       Enter: 4" << endl;
		
		int tournamentType;
		cin >> tournamentType;

		unique_ptr<Tournament> tournament;

		switch (tournamentType) {
			case 0:	tournament = make_unique<SingleElim>();

		}


	}

    delete t;
}
