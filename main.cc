#include <memory>

#include "tournament.h"
#include "roundrobin.h"

using namespace std;

const string seperator = "---------------------------------------";

int main(int argc, char *argv[]) {
	while (true) {
		cout << "Welcome to Yeet" << endl;

		cout << seperator << endl;

		cout << "Please enter which tournament style you would like." << endl;
		cout << "Single Elimination, Enter: 1" << endl;
		cout << "Double Elimination, Enter: 2" << endl;
		cout << "Round-Robin,        Enter: 3" << endl;
		cout << "Swiss Format,       Enter: 4" << endl;
		cout << "Exit program,       Enter: 5" << endl;

		cout < seperator << endl;
		
		int tournamentType;
		cin >> tournamentType;

		unique_ptr<Tournament> tournament;

		switch (tournamentType) {
			case 1:	
				tournament = make_unique<SingleElim>(); 
				break;
			case 2: 
				tournament = make_unique<DoubleElim>(); 
				break;
			case 3: 
				tournament = make_unique<RoundRobin>(); 
				break;
			case 4:
				tournament = make_unique<SwissFormat>(); 
				break;
			case 5:
				cout << "Bye!" << endl;
				return 0;
		}

		if (tournament == nullptr) {
			cout << "Invalid tournament type!" << endl;
			continue;
		}


		cout << "Would you like the tournament to be seeded? Enter: yes/no" << endl; 
		string seededInput;
		cin >> seededInput;

		bool seeded = false;

		if (seededInput == "yes") {
			seededInput = true;
		}

		vector competitors;

		while(competitors.empty()) {
			cout << "Please enter the name of your competitors, and then enter "
				"\"complete\" when you are done." << endl;
			vector competitors;

			string nameInput;
			cin >> nameInput;

			while(nameInput != "complete") {
				competitors.emplace_back(nameInput);
			}

			if (competitors.empty()) {
				cout << "Please enter one or more competitors" << endl;
			}
		}

		tournament->createFromPlayers(competitors, seeded);

		cout << "A the of input commands are: " << endl;
		// cout << "add $(player) - adds a competitor to the tournament" << endl;
		cout << "remove $(player) - removes the competitor from the 
			tournament" << endl;
		cout << "match - displays the next match" << endl;
		cout << "playmatch $(player1) $(score1) $(player2) $(score2) -"
			"plays the next match using scores" << endl;
		cout << "output - displays the entire tournament" << endl;
		cout << "quit - exits the tournament" << endl;

		cout << "Note for the commands, $(...) indicates an input, you do 
			not need to enter the $ char, the ( char, or the ) char." << endl;

		cout << "Beginning tournament" << endl; 

		while (tournament->hasNextMatch()) {
			string command;
			cin >> command;

			if (command == "remove") {
				string player;
				cin >> player;

				tournament->removeCompetitor(player);
			} else if (command == "match") {
				cout << tournament->getNextMatch() << endl;
			} else if (command == "playmatch") {
				string p1, p2;
				int s1, s2;

				cin >> p1 >> s1 >> p2 >> s2;

				int matchId = tournament->getNextMatch()->getMatchId();

				if (p1 == tournament->getNextMatch()->getP1() && 
					p2 == tournament->getNextMatch()->getP2()) {
					tournament->addGameScore(matchId, s1, s2);
				} else if (p1 == tournament->getNextMatch()->getP2() && 
						   p2 == tournament->getNextMatch()->getP1()) {
					tournament->addGameScore(matchId, s2, s1);
				} else {
					cout << "Invalid players entered!" << endl;
				}
			} else if (command == "output") {
				tournament->print();
			} else if (command == "quit") {
				cout << "Ending tournament. Returning to main menu!" << endl;
				break;
			} else {
				cout << "Unknown command!" << endl;
			}
		}

		cout << "Tournament has ended. The end result is:" << endl;
		tournament->print();
	}
    // Tournament* t = new RoundRobin();

    // t->createFromPlayers(vector<string>{
    //         "Ibrahim",
    //         "Callum",
    //         "Max",
    //         "Bob"
    //     });

    // delete t;
}
