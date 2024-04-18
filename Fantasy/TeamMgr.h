#include <iostream>
#include "Team.h"
using namespace std;
#include <map>

class TeamMgr {
private:
	map <string, Team> teams;
	map <string, Footballer> footballers;
public:
	void loadDatabase() {}

	pair<int, int> result(Team team1, Team team2) {
		pair<int, int> goals;
		goals.first = rand() % 6;
		goals.second = rand() % 6;
		return goals;
	}

	vector<string> goals(pair<int, int> goal, vector<string>footballer1, vector<string>footballer2) {
		vector<string> footballers;
		int randomVariable;
		while (goal.first--) {
			randomVariable = rand() % 11;
			footballers.push_back(footballer1[randomVariable]);
		}
		while (goal.second--) {
			randomVariable = rand() % 11;
			footballers.push_back(footballer2[randomVariable]);
		}
	}
	void points(vector<string>footballers) {

	}
	void game() {

	}
};