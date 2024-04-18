#include <iostream>
#include <map>
using namespace std;
#include "Player.h"


class PlayerMgr {
	map <string, Player> players;
	Player currenPlayer;
	int lastId;

};