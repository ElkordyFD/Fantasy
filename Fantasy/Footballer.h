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

	int& getPoints() {
		return points;
	}

	int& getPrice() {
		return price;
	}

	void setPrice(const int& price) {
		this->price = price;
	}

	void setPoint(const int& point) {
		this->points = point;
	}

	void setName(const string& name) {
		this->name = name;
	}

	void setTeamName(const string& teamName) {
		this->teamName = teamName;
	}
};