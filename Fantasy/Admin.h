
#ifndef _ADMIN_
#define _ADMIN_



#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include "Player.h"
#include "Footballer.h"
#include "Team.h"


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



class Admin {
private:
	vector <string> schedule;
	map <string, vector <Footballer>> mainFootballers;
	vector <string> round;
	map <int, Team> playersTeams;
	map <string, Player> players;
	map <string, Footballer> footballers;
	Player currentPlayer;
	int lastId;

public:

	void loadFootballersFromDatabase() {
		footballers.clear();
		string path = "../data/footballers.txt";
		vector<string> lines = readFileLines(path);

		for (const string& line : lines) {
			Footballer footballer(line);
			footballers[footballer.getName()] = footballer;
		}
	}

	void loadPlayersFromDatabase() {
		players.clear();
		string path = "../data/Players.txt";
		vector<string> lines = readFileLines(path);

		for (const string& line : lines) {
			Player player(line);
			lastId = max(lastId, player.getId());
			players[player.getUserName()] = player;
		}
	}

	void loadPlayersTeamsFromDatabase() {
		playersTeams.clear();
		string path = "../data/PlayerTeams.txt";
		vector<string> lines = readFileLines(path);


		for (const string& line : lines) {
			Team team(line);
			playersTeams[team.getId()] = team;
		}
	}

	void loadScheduleFromDatabase() {
		schedule.clear();
		string path = "../data/schedule.txt";
		schedule = readFileLines(path);
	}

	void loadMainFootballersFromDatabase() {
		footballers.clear();
		string path = "../data/footballers.txt";
		vector <string> lines = readFileLines(path);

		for (const string& line : lines) {
			Footballer footballer(line);
			mainFootballers[footballer.getTeamName()].push_back(footballer);

		}
	}




	// TeamMgr

	void modifyFootballerPoints(vector<Footballer>& footballersWhoScored) {
		const int points = 5;

		for (Footballer footballer : footballersWhoScored) {
			for (auto& f : footballers) {
				if (f.second.getName() == footballer.getName()) {
					int newPoints = f.second.getPoints() + points;
					f.second.setPoint(newPoints);
				}
			}
		}
	}

	void resetPoints() {
		const int zero = 0;
		for (int i{ 0 }; i < round.size(); i++) {
			for (auto& it : footballers)
				it.second.setPoint(0);
		}
	}

	void modifyFootballerPrice() {
		const int points = 5; const int price = 500;

		for (int i{ 0 }; i < round.size(); i++) {
			for (auto& footballer : footballers) {
				int goal = footballer.second.getPoints() / points;
				int newPrice = (goal * price) + footballer.second.getPrice();
				footballer.second.setPrice(newPrice);
			}
		}

	}

	void showMatchesPerWeek(int week) {
		round = splitString(schedule[week]);
		for (int i{ 0 }; i < round.size() / 2; i++) {
			cout << round[i] << "  V.S  " << round[i + 1] << "\n";
		}
		cout << '\n';
	}

	pair <int, int> showResult() {
		int goals1 = rand() % 6;
		int goals2 = rand() % 6;
		cout << setw(13) << left << goals1 << setw(10) << left << ":" << goals2 << "\n\n";
		pair<int, int>result = make_pair(goals1, goals2);
		return result;

	}

	vector <Footballer> getFootballersWhoScored(int goals, string teamName) {
		vector <Footballer>footballer = mainFootballers[teamName];

		vector <Footballer>footballerName;
		while (goals--) {
			int idx = rand() % 11;
			footballerName.push_back(footballer[idx]);
		}
		return footballerName;
	}

	void modifyPoints(vector<Footballer>& footballersWhoScored1, vector<Footballer>& footballersWhoScored2) {

		if (footballersWhoScored1.size())
			modifyFootballerPoints(footballersWhoScored1);

		if (footballersWhoScored2.size())
			modifyFootballerPoints(footballersWhoScored2);

	}

	void showFootballersWhoScored(vector<Footballer> footballers1, vector<Footballer> footballers2) {

		int maxSize = max((int)footballers1.size(), (int)footballers2.size());

		for (int i{ 0 }; i < maxSize; i++) {
			if (i < footballers1.size())
				cout << setw(20) << left << footballers1[i].getName();
			else
				cout << setw(20) << left << " ";
			if (i < footballers2.size())
				cout << footballers2[i].getName();
			else
				cout << " ";
			cout << "\n";

		}
	}


	void Match(int week) {

		cout << "\n\n************************\n\n";



		round = splitString(schedule[week]);

		resetPoints();

		for (int i{ 0 }, index{ 0 }; i < (round.size() / 2); i++, index += 2) {
			cout << setw(10) << left << round[index] << setw(10) << left << "  V.S  " << round[index + 1] << "\n";
			pair <int, int> result = showResult();

			vector<Footballer> footballesWhoScoredFromTeam1 = getFootballersWhoScored(result.first, round[index]);
			vector<Footballer> footballesWhoScoredFromTeam2 = getFootballersWhoScored(result.second, round[index + 1]);

			modifyPoints(footballesWhoScoredFromTeam1, footballesWhoScoredFromTeam2);
			showFootballersWhoScored(footballesWhoScoredFromTeam1, footballesWhoScoredFromTeam2);

			cout << "\n************************\n\n";

		}


		modifyFootballerPrice();
		modify();

	}

	void updateFootballersDatabase() {

		vector<string> myFootballers;
		string path = "../data/footballers.txt";

		for (auto it : footballers) 
			myFootballers.push_back(it.second.toString());

		WriteFileLines(path, myFootballers, false);
	}

	void modify() {
		for (Footballer& footballer : currentPlayer.getTeam().getFootballers()) {
			string name = footballer.getName();
			footballer = footballers[name];
		}
	}


	// PlayerMgr

	void accessSystem() {
		int choice = ShowReadMenu({ "Login","SignUp" });

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
			if (players.count(username)) {
				cout << "Already used. Try again\n";
				continue;
			}
			break;
		}
		currentPlayer.read(username, ++lastId);
		currentPlayer.setBudget(budget);
		players[currentPlayer.getUserName()] = currentPlayer;

		updateNewPlayerDatabase(currentPlayer);
	}

	void updateNewPlayerDatabase(Player& player) {
		string path = "../data/Players.txt";

		string str = player.toString();
		vector<string> line(1, str);
		WriteFileLines(path, line);
	}

	void displayFootballers() {

		// delete auto and write Footballer

		for (auto it : footballers)
			cout << "\n" << it.second.getName() << "\t" << it.second.getPrice() << "\n";
	}

	void displayFootballerInfo(const string& footballerName) {

		Footballer currentFootballer = footballers[footballerName];
		cout << "\nName: \t" << footballerName << "\tPrice: " << currentFootballer.getPrice() << '\n';
	}


	// playerTeams
	void updatePlayerTeamsDatabase() {
		vector<string>Teams;
		string path = "../data/PlayerTeams.txt";

		for (auto it : playersTeams)
			Teams.push_back(it.second.toString());

		WriteFileLines(path, Teams, false);
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

			while (!isFoundFootballer(footballerName)) {
				cout << "Incorrect name! Try again.\n";
				cin >> footballerName;
			}

			displayFootballerInfo(footballerName);


			cout << "\nDo You Want To Confirm Your Purchase? (y/n) ";
			char answer;
			cin >> answer;

			if (answer == 'y' || answer == 'Y') {
				Footballer footballer = footballers[footballerName];
				addFootballer(footballer);
				currentPlayer.buyFootballer(footballer);
			}


			choice = ShowReadMenu({ "Exit","BuyAgain" });

		} while (choice != 1);

		//currentPlayer.buyFootballer(footballers[footballerName]);
	}

	void sellProccess() {

		string footballerName;
		int choice;

		do {
			if (currentPlayer.getMyTeamCount() == 0) {
				cout << "\nYou have no players to sell!";
			}
			else {

				currentPlayer.displayMyTeam();

				cout << "\nEnter Name Of Footballer You Want to Sell : ";

				cin >> footballerName;

				while (!isFoundFootballer(footballerName)) {
					cout << "\nIncorrect name! Try again.\n";
					cin >> footballerName;
				}

				displayFootballerInfo(footballerName);

				Footballer footballer = footballers[footballerName];

				cout << "\nDo You Want To Confirm The Sale? (y/n) ";

				char answer;
				cin >> answer;

				if (answer == 'y' || answer == 'Y') {

					deleteFootballer(footballer);
					currentPlayer.sellFootballer(footballer);
				}

			}
			choice = ShowReadMenu({ "Exit","Sell Again" });

		} while (choice != 1);
	}

	void replace() {
		sellProccess();
		buyProccess();
	}

	const Player& getCurrentPlayer() {
		return currentPlayer;
	}

	void addFootballer(Footballer footballer) {
		int id = currentPlayer.getId();
		Team& team = playersTeams[id];
		team.addFootballer(footballer);
	}

	void deleteFootballer(Footballer& footballer) {
		int id = currentPlayer.getId();
		Team& team = playersTeams[id];
		team.deleteFootballer(footballer);
	}


	// load player team when login

	void loadPlayerTeam() {
		int id = currentPlayer.getId();
		Team team = playersTeams[id];
		modifyTeamPlayers(team);
		currentPlayer.setTeam(team);
	}

	void modifyTeamPlayers(Team& team) {
		vector<Footballer> myFootballers = team.getFootballers();
		for (int i{ 0 }; i < myFootballers.size(); i++) {
			string footballerName = myFootballers[i].getName();
			myFootballers[i] = footballers[footballerName];
		}
		team.setFootballers(myFootballers);
	}



	// load Database
	void loadDatabase() {
		loadScheduleFromDatabase();
		loadMainFootballersFromDatabase();
		loadPlayersFromDatabase();
		loadFootballersFromDatabase();
		loadPlayersTeamsFromDatabase();
	}

	void updateDatabase() {
		updatePlayerTeamsDatabase();
		updateFootballersDatabase();
	}
};

#endif // !_ADMIN_