#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include "Player.h"
#include"InputHandler.h"

using namespace std;

enum enOrderType { Buy = 1, Sell, Replace, displayTeam };


class PlayerMgr {
	static map <string, Player> players;
	map <string, Footballer> footballers;
	Player currentPlayer;
	int lastId;

	 void displayFootballers() {

		for (auto it : footballers)
		{
			cout << "\n" << it.second.getName() << "\t" << it.second.getPrice() << "\n";
		}
	}

	 void displayFootballerInfo(string footballerName) {
		cout << "\nName: " << footballerName << "\tPrice: " << footballers[footballerName].getPrice() << endl;
	}

	 string readFootballerName(string message) {
		cout << message << " ";
		string name;
		cin >> name;
		return name;
	}

	 bool exitToOrderMenu(string message) {
		 cout << message << endl;
		 short choice = InputHandler::inputInteger(1, 2);
		
		 return choice == 1; 
	 }

	 void buyProccess() {
		string footballerName;
		char ch = 'n';
		do
		{
			displayFootballers();
			footballerName = readFootballerName("Enter Name Of Footballer You Want to Buy: ");
			displayFootballerInfo(footballerName);

			cout << "\nDo You Want To Confirm Your Purchase? (y/n) ";
			cin >> ch;
			if (ch != 'y' || ch != 'Y')
			{
				if (exitToOrderMenu("Enter 1 to Exit or 2 To Buy Again"))
				{
					return;
				}
			}
		} while (ch != 'y' || ch != 'Y');
		currentPlayer.buyFootballer(footballers[footballerName]);
	}

	 void sellProccess() {

		string footballerName;
		char ch = 'n';
		do
		{
			currentPlayer.displayMyTeam();
			footballerName = readFootballerName("Enter Name Of Footballer You Want to Buy: ");
			displayFootballerInfo(footballerName);

			cout << "\nDo You Want To Confirm The Sale? (y/n) ";
			cin >> ch;

		} while (ch != 'y' || ch != 'Y');
		currentPlayer.sellFootballer(footballers[footballerName]);
	}
	
public: 
	PlayerMgr(Player curPlayer):currentPlayer(curPlayer){}

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
	};

	static void login() {};

	static void signup() {};

	 void loadFootballersFromDatabase() {
		string path = "C:\Fantasy_project\Fantasy\footballers.txt";
		vector<string> lines = readFileLines(path);

		for (const string& line : lines) {
			Footballer footballer(line);
			footballers[footballer.getName()] = footballer;
		}
	}

	 void menuOfOrders() {
		do
		{
			cout << "Choose Type Of Order: 1-Buy , 2-Sell , 3-Replace , 4-Display My Team \n";
			int noOrder = InputHandler::inputInteger(1, 4);
			
			enOrderType order = (enOrderType)noOrder;
			string footballerName; 

			switch (order)
			{
			case Buy:

				buyProccess();

				break;
			case Sell:

				sellProccess();

				break;
			case Replace:

				sellProccess();
				buyProccess();

				break;

			case displayTeam:

				currentPlayer.displayMyTeam();

				break;
			default:
				break;
			}

		} while (true);

	}
};