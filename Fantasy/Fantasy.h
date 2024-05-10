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


	void loadDatabase(bool fillPlayerTeam = false) {
		playerMgr.loadDatabase();
		teamMgr.loadDatabase();

		if (fillPlayerTeam) {
			playerMgr.loadPlayerTeam();
			week = 0;
		}
	}

public:
	void Run() {
		loadDatabase();
		playerMgr.accessSystem();

		while (true) {
			// after signUp new data is Entered
			loadDatabase(true);

			int choice = ShowReadMenu({ "Buy","Sell","Replace","Display my team","Exit" });

			if (choice == 1)
				playerMgr.buyProccess();
			else if (choice == 2)
				playerMgr.sellProccess();
			else if (choice == 3) {
				Player player = playerMgr.getCurrentPlayer();
				player.displayMyTeam();
			}
			else {
				teamMgr.Match(week);
			}
			++week;
		}
	}
};


#endif // !_FANTASY_