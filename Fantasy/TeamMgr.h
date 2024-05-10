
#ifndef _TEAM_MGR_
#define _TEAM_MGR_



#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Footballer.h"
using namespace std;
#include <map>


class TeamMgr {
private:
	vector <string> schedule;
	map <string, vector <Footballer>> footballers;
	vector <string> round;

	void loadScheduleFromDatabase() {
		schedule.clear();
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/schedule.txt";
		schedule = readFileLines(path);
	}

	void loadFootballersFromDatabase() {
		footballers.clear();
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/footballers.txt";
		vector <string> lines = readFileLines(path);

		for (const string& line : lines) {
			Footballer footballer(line);
			footballers[footballer.getTeamName()].push_back(footballer);

		}
	}

	void modifyFootballerPoints(string teamName, vector<Footballer>& footballersWhoScored) {
		const int points = 5;

		for (Footballer footballer : footballersWhoScored) {
			for (Footballer& teamFootballers : footballers[teamName]) {
				if (teamFootballers.getName() == footballer.getName()) {
					int newPoints = teamFootballers.getPoints() + points;
					teamFootballers.setPoint(newPoints);
				}
			}
		}
	}

	void setCleanSheetPoints(string teamName) {
		const int points = 10;

		// goalKeppers
		footballers[teamName][0].setPoint(points);
	}

	void resetPoints() {
		const int zero = 0;
		for (int i{ 0 }; i < round.size(); i++) {
			for (Footballer& footballer : footballers[round[i]])
				footballer.setPoint(zero);
		}
	}

	void modifyFootballerPrice() {
		const int points = 5; const int price = 500;

		for (int i{ 0 }; i < round.size(); i++) {
			for (Footballer& footballer : footballers[round[i]]) {
				int goal = footballer.getPoints() / points;
				int newPrice = (goal * price) + footballer.getPrice();
				footballer.setPrice(newPrice);
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
		vector <Footballer>footballer = footballers[teamName];

		vector <Footballer>footballerName;
		while (goals--) {
			int idx = rand() % 11;
			footballerName.push_back(footballer[idx]);
		}
		return footballerName;
	}

	void modifyPoints(vector<Footballer>& footballersWhoScored1, string teamName1, vector<Footballer>& footballersWhoScored2, string teamName2, pair<int, int> result) {

		if (footballersWhoScored1.size())
			modifyFootballerPoints(teamName1, footballersWhoScored1);

		if (footballersWhoScored2.size())
			modifyFootballerPoints(teamName2, footballersWhoScored2);

		if (!result.first)
			setCleanSheetPoints(teamName2);

		if (!result.second)
			setCleanSheetPoints(teamName1);

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



public:

	void loadDatabase() {
		loadScheduleFromDatabase();
		loadFootballersFromDatabase();
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

			modifyPoints(footballesWhoScoredFromTeam1, round[index], footballesWhoScoredFromTeam2, round[index + 1], result);
			showFootballersWhoScored(footballesWhoScoredFromTeam1, footballesWhoScoredFromTeam2);

			cout << "\n************************\n\n";

		}

		modifyFootballerPrice();

		updateDatabase();


	}

	// method for test TeamMgr :)
	void showFoot(string teamName) {
		for (Footballer footballer : footballers[teamName])
			cout << footballer.getName() << " " << footballer.getPoints() << " " << footballer.getPrice() << "\n";
		cout << "\n\n";
	}

	// still in progress
	void updateDatabase() {

		vector<string> myFootballers;
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/footballers.txt";

		for (pair<string,vector<Footballer>> it : footballers) {
			for (Footballer footballer : it.second)
				myFootballers.push_back(footballer.toString());
		}

		WriteFileLines(path,myFootballers,false);
	}
};

#endif // !_TEAM_MGR_