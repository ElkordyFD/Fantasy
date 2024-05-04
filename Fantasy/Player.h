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
	int idCounter = 0;
	Player(string username, string password)
		: id(++idCounter), username(username), password(password), budget(80000)
	{
	}

	string getPassword() {
		return password;
	}

	
};