#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int toInt(string text) {
	int value;
	istringstream str(text);
	str >> value;
	return value;
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