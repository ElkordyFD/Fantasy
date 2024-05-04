#include <iostream>
#include <vector>
#include "Footballer.h"
using namespace std;

class Team {
private:
	int id;
	string name;
	vector<Footballer> Footballers;
public:
	vector<Footballer> getFootballers() {
		return Footballers;
	}
};