#ifndef _FANTASY_
#define _FANTASY_



#include "PlayerMgr.h"
#include "TeamMgr.h"


int readInt(int low, int high) {
	cout << "\nEnter number in range " << low << " - " << high << ": ";
	int value;

	cin >> value;

	if (low <= value && value <= high)
		return value;

	cout << "ERROR: invalid number...Try again\n";
	return readInt(low, high);
}

int ShowReadMenu(const vector<string>& choices) {
	cout << "\nMenu:\n";
	for (int ch = 0; ch < (int)choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	return readInt(1, (int)choices.size());
}

class Fantasy {
private:
	PlayerMgr playerMgr;
	TeamMgr teamMgr;
	int week;


	void loadDatabase() {
		playerMgr.loadDatabase();
		playerMgr.loadPlayerTeam();
		teamMgr.loadDatabase();
	}

public:
	void Run() {
		loadDatabase();
		playerMgr.accessSystem();

		while (true) {
			// after signUp new data is Entered
			/*loadDatabase(true);*/

			int choice = ShowReadMenu({ "Buy","Sell","Replace","Display my team","Start round" });

			if (choice == 1)
				playerMgr.buyProccess();
			else if (choice == 2)
				playerMgr.sellProccess();
			else if (choice == 3) {
				playerMgr.replace();
			}
			else if (choice == 4) {
				Player player = playerMgr.getCurrentPlayer();
				player.displayMyTeam();
			} else {
				Player player = playerMgr.getCurrentPlayer();
				if (player.getMyTeamCount() < 11) {
					cout << "not enough players to start round!\n\n";
					continue;
				}
				else
					teamMgr.Match(week);
			}
			++week;

			if (week == 5)
				break;
		}
	}
};


#endif // !_FANTASY_