#include <iostream>
#include <sstream>
using namespace std;

int toInt(string text) {
	int value;
	istringstream str(text);
	str >> value;
	return value;
}

class Footballer {
private:
	string name;
	int price;
	string teamName;
	int points;
public:
	Footballer (string line) {
		vector<string>information = splitString(line);
		name = information[0];
		price = toInt(information[1]);
		teamName = information[2];
		points = toInt(information[3]);

	}

	const string& getTeamName() {
		return teamName;
	}
	const string& getName() {
		return name;
	}
};