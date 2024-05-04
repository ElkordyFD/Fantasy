#include<iostream>
#include"PlayerMgr.h"


static void seed() {
	PlayerMgr::players.insert(make_pair("Moaz", Player::Player("Moaz", "123")));
	PlayerMgr::players.insert(make_pair("Ezz", Player::Player("Ezz", "123")));
	PlayerMgr::players.insert(make_pair("AbuNawwaf", Player::Player("AbuNawwaf", "123")));
	PlayerMgr::players.insert(make_pair("AbuTaqiy", Player::Player("AbuTaqiy", "123")));
	
}

static void menu() {
	seed();
	int choice;
	cout << "[1] Login\n[2] Register";
	choice = InputHandler::inputInteger(1, 2);

	string username, pass;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> pass;

	map<string, Player>::iterator it;

	switch (choice) {
	case 1:
		it = PlayerMgr::players.find(username);
		while (it == PlayerMgr::players.end()) {
			cout << "Invalid username.\nUsername: ";
			cin >> username;
			it = PlayerMgr::players.find(username);
		}

		break;
	case 2:
		break;
	}

}

void promptCredentials(bool toLogin) {
	string username, password;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	if (toLogin) {
		login(username, password);
	}
	else {

	}
}


static void login(string username, string password) {
	map<string, Player>::iterator it;
	it = PlayerMgr::players.find(username);

	//in case wrong username
	if (it == PlayerMgr::players.end()) {
		cout << "Invalid username.";
		cout << "[1] Retry\n[2] Back";
		int choice = InputHandler::inputInteger(1, 2);
		switch (choice) {
		case 1:
			promptCredentials(true);
			break;
		case 2:
			menu();
		}
	}
	//in case valid username
	else {
		if (it->second.getPassword() == password) {
			PlayerMgr::currentPlayer = it->second;
		}
	}
}

static void signup() {
	string username, pass;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> pass;
}
