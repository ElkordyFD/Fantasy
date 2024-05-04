#include <iostream>
#include <map>
#include "Player.h"
#include"InputHandler.h"
using namespace std;


class PlayerMgr {

public:
	static map <string, Player> players;
	static Player currentPlayer;
	int lastId;
	
	static void seed();

	static void menu();

	static void login();

	static void signup();
};