#ifndef _PLAYER_
#define _PLAYER_


#include <iostream>
#include "Team.h"
using namespace std;

class Player {
private:
	int id;
	string username;
	string password;
	double budget;
	Team team;

public:

	Player () {}

	Player (const string& line) {
		vector <string> information = splitString(line);

		id = toInt(information[0]);
		username = information[1];
		password = information[2];
		budget = toDouble(information[3]);
	}

	void read(const string& userName, int id) {
		setUsername(userName);
		setId(id);

		string str;

		cout << "Enter password: ";
		cin >> str;
		setPassword(str);

	}

	// make isFound method in team class that's better :)

	bool isFootballerInMyTeam(Footballer footballer) {
		for (int i = 0; i < team.getFootballers().size(); i++)
		{
			if (footballer == team.getFootballers().at(i)) {
				return true;
			}
		}
		return false; 
	}

	//  with for loop will be better

	void displayMyTeam() {

		if (team.isEmpty()) {
			cout << "No footballers yet!\n\n";
			return;
		}
			
		cout << "\nMy Team:\n";

		team.displayFootballers();
	}

	void buyFootballer( Footballer newFootballer) {

		if (isFootballerInMyTeam(newFootballer)) {
			cout << "\nThis Footballer Is Already In Your Team!" << endl;
			return;
		} 

		if (budget < newFootballer.getPrice()) {
			cout << "\nYour Budget Doesn't Allow! " << endl;
			return;
		}

		team.addFootballer(newFootballer);
		budget -= newFootballer.getPrice();
		cout << "Purchase Completed Successfully\n";

	}

	void sellFootballer(Footballer footballer) {

		if (!isFootballerInMyTeam(footballer)) {
			cout << "\nThis Footballer Is Not In Your Team! " << endl;
			return;
		}

		budget += footballer.getPrice();

		
		for (int i = 0; i < team.getFootballers().size() ; i++)
		{
			if (team.getFootballers().at(i) == footballer)
			{
				team.deleteFootballer(footballer , i);
			}
		}

		return;
	}

	const string toString() {
		ostringstream oss;
		oss << id << "," << username << "," << password << "," << budget;
		return oss.str();
	}


	void setId (const int& id){
		this->id = id;
	}

	void setUsername(const string& userName) {
		this->username = userName;
	}

	void setPassword(const string& password) {
		this->password = password;
	}

	void setBudget(const double& budget) {
		this->budget = budget;
	}

	void setDefaultBudget() {
		this->budget = 80000;
	}

	void setTeam(const Team& team) {
		this->team = team;
	}

	const string& getUserName() {
		return username;
	}

	const string& getPassword() {
		return password;
	}

	const int& getId() {
		return id;
	}

	const int& getBudget() {
		return budget;
	}

	const int& getMyTeamCount() {
		return team.getTeamCount();
	}


};

#endif // !_PLAYER_