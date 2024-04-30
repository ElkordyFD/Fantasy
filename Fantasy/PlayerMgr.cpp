#include<iostream>
#include"PlayerMgr.h"

class PlayerMgr {


	static void menu() {
		int choice;
		cout << "[1] Login\n[2] Register";
		choice = InputHandler::inputInteger(1, 2);

		switch (choice) {
		case 1:
			break;
		case 2:
			break;
		}

	}

	static void login() {


	}

	static void signup() {

	}
};