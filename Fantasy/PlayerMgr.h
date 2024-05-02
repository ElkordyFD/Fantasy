#include <iostream>
#include <map>
using namespace std;
#include "Player.h"


class PlayerMgr {
private:
	map <string, Player> players;
	map <string, Footballer> footballers;
	Player currenPlayer;
	int lastId;
public:
	void loadFootballersFromDatabase() {
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/footballers.txt";
		vector<string> lines = readFileLines(path);

		for (const string &line : lines) {
			Footballer footballer(line);
			footballers[footballer.getName()] = footballer;
		}
	}
};