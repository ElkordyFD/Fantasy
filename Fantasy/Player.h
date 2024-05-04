#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Team.h"
#include "Footballer.h"
using namespace std;


class Player {
private:
	int id;
	string username;
	string password;
	double budget;
	Team team;

	bool isFootballerInMyTeam(Footballer footballer) {
		auto it = find(team.getFootballers().begin(), team.getFootballers().end(), footballer);
		return it != team.getFootballers().end();
	}

public:

	/*Player(int id, string username, string password, Team team)
		: id(id), username(username), password(password), budget(budget), team(team) {}*/


	Player(int id, string username, string password)
		: id(id), username(username), password(password), budget(80000) {}



	void displayMyTeam() {
		cout << "\nMy Team:\n";
		while (!team.getFootballers().empty())
		{
			int count = 0;
			cout << count + 1 << "- Name: " << team.getFootballers().at(count).getName()
				<< "\tPrice: " << team.getFootballers().at(count).getPrice() << endl;
			count++;
		}
	}

	void buyFootballer(Footballer footballer) {
		if (isFootballerInMyTeam(footballer)) {
			cout << "\nThis Footballer Is Already In Your Team!" << endl;
			return;
		}
		else if (budget - footballer.getPrice() < 0)
		{
			cout << "\nYour Budget Doesn't Allow! " << endl;
			return;
		}

		team.getFootballers().push_back(footballer);
		budget -= footballer.getPrice();
		cout << "Purchase Completed Successfully" << endl;

	}

	void sellFootballer(Footballer footballer) {
		if (!isFootballerInMyTeam(footballer))
		{
			cout << "\nThis Footballer Is Not In Your Team! " << endl; 
			return;
		}
		budget += footballer.getPrice();
		auto it = find(team.getFootballers().begin(), team.getFootballers().end(), footballer);
		if (it != team.getFootballers().end()) {
			team.getFootballers().erase(it);
		}
	}

	
};