#include <iostream>
#include <vector>
#include <fstream>
#include "Team.h"
using namespace std;
#include <map>


vector<string> readFileLines(const string& path) {
	vector<string> lines;

	fstream file_handler(path.c_str());

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return lines;
	}
	string line;

	while (getline(file_handler, line)) {
		if (line.size() == 0)    // if line is empty
			continue;
		lines.push_back(line);
	}

	file_handler.close();
	return lines;
}
vector<string> splitString(const string& str, const string& delimiter = ",") {
	string s = str;
	vector<string> strs;

	int pos = 0;
	string substr;
	while ((pos = (int)s.find(delimiter)) != -1) {
		substr = s.substr(0, pos);
		strs.push_back(substr);
		s.erase(0, pos + delimiter.length());
	}
	strs.push_back(s);
	return strs;
}


class TeamMgr {
private:
	vector<string>schedule;
public:
	void loadDatabase() {
		schedule = readFileLines("Path");
	}

	void showMatchesPerWeek(int week) {
		vector<string> weekMatches = splitString(schedule[week]);
		for (string match : weekMatches)
			cout << match << '\t';
	}

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
	void Match() {
		// 1- week
		// 2- generate result
		// 3- generate footballers
		// 4- points
	}
};