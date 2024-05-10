#ifndef _TEAM_
#define _TEAM_



#include <iostream>
#include <vector>
#include "Footballer.h"
using namespace std;

class Team {
private:

	int id;
	string name;
	int points;
	vector<Footballer> footballers;

public:
	Team () {}

	Team(const vector<string>& information,const vector<Footballer>& footballers) {

		id = toInt(information[0]);
		name = information[1];
		points = toInt(information[2]);

		this->footballers = footballers;

	}

	const string& getName() {
		return name;
	}

	const int& getId() {
		return id;
	}

	vector<Footballer> getFootballers() {
		return footballers;
	}

	void addFootballer(const Footballer& newFootballer) {
		footballers.push_back(newFootballer);
	}

	void deleteFootballer(const Footballer& myFootballer , int index) {
		footballers.erase(footballers.begin() + index);
	}


	bool isFound(Footballer footballer) {
		auto it = find(footballers.begin(), footballers.end(), footballer);
		return it != footballers.end();
	}

	void displayFootballers() {
		for (int i{ 0 }; i < (int)footballers.size(); i++) {
			cout << "Name: " << footballers[i].getName() << "\tPrice: " << footballers[i].getPrice() << endl;
		}
	}

	bool isEmpty() {
		return footballers.size() == 0;
	}

	const int& getTeamCount() {
		return footballers.size();
	}
};

#endif // !_TEAM_