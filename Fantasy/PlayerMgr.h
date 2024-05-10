#ifndef _PLAYER_MGR_
#define _PLAYER_MGR_



#include <iostream>
#include <map>
#include <fstream>
#include "Player.h"



using namespace std;


void WriteFileLines(const string& path, const vector<string>& lines, bool append = true) {
	auto status = ios::in | ios::out | ios::app;

	if (!append)
		status = ios::in | ios::out | ios::trunc;	// overwrite

	fstream file_handler(path.c_str(), status);

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return;
	}
	for (const auto& line : lines)
		file_handler << line << "\n";

	file_handler.close();
}
vector<string> readFileLines(const string& path) {
	vector<string> lines;

	fstream file_handler(path.c_str());

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return lines;
	}
	string line;

	while (getline(file_handler, line)) {
		if (line.size() == 0)    // if line is empty
			continue;
		lines.push_back(line);
	}

	file_handler.close();
	return lines;
}

class PlayerMgr {
private:
	map <int, Team> playersTeams;
	map <string, Player> players;
	map <string, Footballer> footballers;
	Player currentPlayer;
	int lastId;

	void loadFootballersFromDatabase() {
		footballers.clear();
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/footballers.txt";
		vector<string> lines = readFileLines(path);

		for (const string& line : lines) {
			Footballer footballer(line);
			footballers[footballer.getName()] = footballer;
		}
	}

	void loadPlayersFromDatabase() {
		players.clear();
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/Players.txt";
		vector<string> lines = readFileLines(path);

		for (const string& line : lines) {
			Player player(line);
			lastId = max(lastId, player.getId());
			players[player.getUserName()] = player;
		}
	}

	void loadPlayersTeamsFromDatabase() {
		playersTeams.clear();
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/PlayerTeams.txt";
		vector<string> lines = readFileLines(path);

		for (const string& line : lines) {
			Team team(line);
			playersTeams[team.getId()] = team;
		}
	}

public:

	void loadDatabase() {
		loadPlayersFromDatabase();
		loadFootballersFromDatabase();
		loadPlayersTeamsFromDatabase();
	}

	int readInt(int low, int high) {
		cout << "\nEnter number in range " << low << " - " << high << ": ";
		int value;

		cin >> value;

		if (low <= value && value <= high)
			return value;

		cout << "ERROR: invalid number...Try again\n";
		return readInt(low, high);
	}

	int ShowReadMenu(const vector<string>& choices) {
		cout << "\nMenu:\n";
		for (int ch = 0; ch < (int)choices.size(); ++ch) {
			cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
		}
		return readInt(1, (int)choices.size());
	}

	void accessSystem() {
		int choice = ShowReadMenu({"Login","SignUp"});

		if (choice == 1)
			doLogin();
		else
			doSignUp();

	}

	void doLogin() {
		// LoadDatabase();	// in case user added from other parallel run

		string userName, password;

		while (true) {

			cout << "Enter user name & password: ";
			cin >> userName >> password;

			if (!players.count(userName)) {
				cout << "\nInvalid user name or password. Try again\n\n";
				continue;
			}

			Player playerExist = players[userName];

			if (playerExist.getPassword() != password) {
				cout << "\nInvalid user name or password. Try again\n\n";
				continue;
			}
			currentPlayer = playerExist;
			break;
		}

	}

	void doSignUp() {
		const double budget = 80000;
		string username;
		while (true) {
			cout << "Enter UserName. (No spaces): ";
			cin >> username;
			if (!players.count(username)) {
				cout << "Already used. Try again\n";
				continue;
			}
			break;
		}
		currentPlayer.read(username, ++lastId);
		currentPlayer.setBudget(budget);
		players[currentPlayer.getUserName()] = currentPlayer;

		updateDatabase(currentPlayer);
	}

	void updateDatabase(Player& player) {
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/Players.txt";

		string str = player.toString();
		vector<string> line(1, str);
		WriteFileLines(path,line);
	}

	void displayFootballers() {

		// delete auto and write Footballer

		for (auto it : footballers)
			cout << "\n" << it.second.getName() << "\t" << it.second.getPrice() << "\n";
	}

	void displayFootballerInfo(const string& footballerName) {

		Footballer currentFootballer = footballers[footballerName];
		cout << "\nName: \t" << footballerName << "Price: " << currentFootballer.getPrice() << '\n';
	}

	// to check footballer is exist or not
	bool isFoundFootballer(const string& name) {
		if (!footballers.count(name))
			return 0;
		return 1;
	}

	void buyProccess() {
		string footballerName;
		int choice;

		do {
			displayFootballers();

			cout << "Enter Name Of Footballer You Want to Buy : ";
			cin >> footballerName;
				
			displayFootballerInfo(footballerName);

			cout << "\nDo You Want To Confirm Your Purchase? (y/n) ";
			char answer;
			cin >> answer;

			if (answer == 'y' || answer == 'Y') {
				Footballer footballer = footballers[footballerName];
				currentPlayer.addFootballer(footballer);
			}

			choice = ShowReadMenu({ "Exit","BuyAgain" });

		} while (choice != 1);

		//currentPlayer.buyFootballer(footballers[footballerName]);
	}

	void sellProccess() {

		string footballerName;
		int choice;

		do {

			currentPlayer.displayMyTeam();

			cout << "Enter Name Of Footballer You Want to Sell : ";
			cin >> footballerName;

			displayFootballerInfo(footballerName);

			cout << "\nDo You Want To Confirm The Sale? (y/n) ";

			char answer;
			cin >> answer;

			if (answer == 'y' || answer == 'Y') {
				Footballer footballer = footballers[footballerName];
				currentPlayer.sellFootballer(footballer);
			}

			choice = ShowReadMenu({ "Exit","SellAgain" });

		} while (choice != 1);
	}

	const Player& getCurrentPlayer(){
		return currentPlayer;
	}

	void loadPlayerTeam() {
		int id = currentPlayer.getId();
		Team team = playersTeams[id];
		currentPlayer.setTeam(team);
	}
};


#endif // !_PLAYER_MGR_