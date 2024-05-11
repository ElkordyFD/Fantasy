#ifndef _FANTASY_
#define _FANTASY_



#include "Admin.h"




class Fantasy {
private:
	Admin admin;
	int week;


public:
	void Run() {
		admin.loadDatabase();
		admin.accessSystem();


		bool fillPlayerTeam = true;
		while (true) {

			if(fillPlayerTeam)
				admin.loadPlayerTeam();

			int choice = ShowReadMenu({ "Buy","Sell","Replace","Display my team","Start round" });

			if (choice == 1)
				admin.buyProccess();
			else if (choice == 2)
				admin.sellProccess();
			else if (choice == 3) {
				admin.replace();
			}
			else if (choice == 4) {
				Player player = admin.getCurrentPlayer();
				player.displayMyTeam();
			} else {
				Player player = admin.getCurrentPlayer();
				if (player.getMyTeamCount() < 11) {
					cout << "not enough players to start round!\n\n";
					continue;
				}
				else {
					admin.Match(week);
					++week;
				}

			}
			fillPlayerTeam = false;

			if (week == 5)
				break;
		}
		// update database
	}
};


#endif // !_FANTASY_