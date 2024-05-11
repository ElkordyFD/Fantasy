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

	Team(const string& line) {
		vector<string> information = splitString(line);

		id = toInt(information[0]);
		name = information[1];
		points = toInt(information[2]);


		for (int i{ 3 }; i < (int)information.size(); i++) {
			Footballer footballer;
			footballer.setName(information[i]);
			footballers.push_back(footballer);
		}

	}

	const string& getName() {
		return name;
	}

	const int& getId() {
		return id;
	}

	// to check
	void setName(const string& name) {
		this->name = name;
	}

	void setFootballers(const vector<Footballer>& FootBallers) {
		footballers = FootBallers;
	}

	vector<Footballer>& getFootballers() {
		return footballers;
	}



	void addFootballer(const Footballer& newFootballer) {
		footballers.push_back(newFootballer);
	}

	void deleteFootballer(Footballer& myFootballer) {
		auto it = find(footballers.begin(), footballers.end(), myFootballer);
		if (it != footballers.end())
			footballers.erase(it);
	}

	/*void deleteFootballer(const Footballer& myFootballer , int index) {
		footballers.erase(footballers.begin() + index);
	}*/


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

	string toString() {
		ostringstream oss;
		oss << id << "," << name << "," << points;

		for (Footballer footballer : footballers)
			oss << "," << footballer.getName();

		return oss.str();
	}
};

#endif // !_TEAM_