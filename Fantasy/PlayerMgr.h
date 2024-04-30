#include <iostream>
#include <map>
#include "Player.h"
#include"InputHandler.h"
using namespace std;


class PlayerMgr {
	static map <string, Player> players;
	Player currentPlayer;
	int lastId;
	
	

	static void menu();

	static void login();

	static void signup();
};