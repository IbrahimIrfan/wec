#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

#include "tournament.h"
#include "roundrobin.h"
#include "single.h"

using namespace std;

const string seperator = "---------------------------------------";

int main(int argc, char *argv[]) {
	while (true) {
        cout << separator << endl;
		cout << "Welcome to Yeet" << endl;

		cout << seperator << endl;

		cout << "Please enter which tournament style you would like." << endl;
		cout << "Single Elimination, Enter: 1" << endl;
		cout << "Double Elimination, Enter: 2" << endl;
		cout << "Round-Robin,        Enter: 3" << endl;
		cout << "Swiss Format,       Enter: 4" << endl;
		cout << "Exit program,       Enter: 5" << endl;

		cout << seperator << endl;
		
		int tournamentType;
		cin >> tournamentType;


		cout << "Matches will be first to 'X' games:" << endl;
		int numRounds;
		cin >> numRounds;

		if (numRounds < 1) {
			cout << "Invalid number of games to win entered!" << endl;
			continue;
		}


		Tournament* tournament;

		switch (tournamentType) {
			// case 1:	
			// 	tournament = make_unique<SingleElim>(); 
			// 	break;
			// case 2: 
			// 	tournament = make_unique<DoubleElim>(); 
			// 	break;
			case 3: 
				tournament = new RoundRobin(numRounds);
				break;
			// case 4:
			// 	tournament = make_unique<SwissFormat>(); 
			// 	break;
			case 5:
				cout << "Bye!" << endl;
				return 0;
		}

		if (tournament == nullptr) {
			cout << "Invalid tournament type!" << endl;
			continue;
		} 


		cout << "Will the list of competitors be in order of seeding? Enter: yes/no" << endl; 
		string seededInput;
		cin >> seededInput;

		bool seeded = false;

		if (seededInput == "yes") {
			seededInput = true;
		} else {
            cout << "Do you want to do a round robin to determine seeding? Enter: yes/no" << endl; 
            cin >> seededInput;

            if (seededInput == "yes") {
                tournament = new RRSeededTournament(tournament, numRounds);
            }
        }

		vector<string> competitors;

		while(competitors.empty()) {
			cout << "Please enter the name of your competitors, and then enter "
				"\"complete\" when you are done." << endl;

			string nameInput;
			getline(cin, nameInput);
			getline(cin, nameInput);

			while(nameInput != "complete") {
				competitors.emplace_back(nameInput);
				getline(cin, nameInput);
			}

			if (competitors.size() <= 1) {
				cout << "Please enter two or more competitors. There are currently " <<
					competitors.size() << "competitors entered.";
			}
		}
		tournament->createFromPlayers(competitors, seeded);

		cout << seperator << endl;

		cout << "A the of input commands are: " << endl;
		// cout << "add $(player) - adds a competitor to the tournament" << endl;
		cout << "remove $(player)                                    - "
			"removes the competitor from the tournament" << endl;
		cout << "match                                               - "
			"displays the next match" << endl;
		cout << "playmatch $(player1) $(score1) $(player2) $(score2) - "
			"plays the next match using scores" << endl;
		cout << "output                                              - "
			"displays the entire tournament" << endl;
		cout << "quit                                                - "
			"exits the tournament" << endl;

		cout << "Note for the commands, $(...) indicates an input, you do "
			"not need to enter the $ char, the ( char, or the ) char." << endl;

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
				string p1;
				string p2;
				int s1;
				int s2;

				cin >> p1 >> s1 >> p2 >> s2;

                Match& match = tournament->getNextMatch();
                int matchId = match.getMatchId();

                bool outputMatchScore = false;

				if (p1 == tournament->getNextMatch().getP1().name && 
					p2 == tournament->getNextMatch().getP2().name) {
					tournament->addGameScore(matchId, s1, s2);

                    outputMatchScore = true;
				} else if (p1 == tournament->getNextMatch().getP2().name && 
						   p2 == tournament->getNextMatch().getP1().name) {
					tournament->addGameScore(matchId, s2, s1);

                    outputMatchScore = true;
				} else {
					cout << "Invalid players entered!" << endl;
				}
                
                if (outputMatchScore) {
                    cout << endl;
                    if (match.isOver()) {
                        cout << "Match " << matchId << " is over. " << match.getPlayer(match.winner()).name << " wins!" << endl;
                    }
                    cout << match << endl << endl;
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
        cout << endl << "Final standings:" << endl;;

        for (auto p : tournament->getWinners()) {
            cout << p.first << ". " << p.second << endl;
        }
        cout << endl;
	}
}
