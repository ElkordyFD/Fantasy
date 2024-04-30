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

	Player(int id, string username, string password, double budget, Team team)
		: id(id), username(username), password(password), budget(budget), team(team)
	{
	}
};