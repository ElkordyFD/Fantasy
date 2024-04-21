#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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
	map<string, Footballer>footballers;
public:
	void loadScheduleFromDatabase() {
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/schedule.txt";
		schedule = readFileLines(path);
	}

	showMatchesPerWeek() {}

	result() {}

	goals() {}

	points() {}


	void Match() {
		// 1- week
		// 2- generate result
		// 3- generate footballers
		// 4- points
	}
};