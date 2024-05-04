#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Footballer.h"
using namespace std;
#include <map>


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


class TeamMgr {
private:
	vector <string> schedule;
	map <string,vector <Footballer>> footballers;
	vector <string> round;

	
	void loadScheduleFromDatabase() {
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/schedule.txt";
		schedule = readFileLines(path);
	}

	void loadFootballersFromDatabase() {
		string path = "C:/Users/wizbe/OneDrive/Desktop/FantasyDatabase/footballers.txt";
		vector <string> lines;
		lines = readFileLines(path);

		for (const string& line : lines) {
			Footballer footballer(line);
			footballers[footballer.getTeamName()].push_back(footballer);

		}
	}

public:

	void loadDatabase() {
		loadScheduleFromDatabase();
		loadFootballersFromDatabase();
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

	vector <Footballer> showFootballers(int goals, string teamName) {
		vector <Footballer>footballer = footballers[teamName];

		vector <Footballer>footballername;
		while (goals--) {
			int position = rand() % 11;
			footballername.push_back(footballer[position]);
		}
		return footballername;
	}

	 void modifyFootballerPoints (vector<Footballer> footballers) {

		 for (Footballer &footballer : footballers) {
			 footballer.getPoints() += 5;
		 }
	 }

	 void modifyFootballerPrice(vector<Footballer> footballers) {

		 for (Footballer& footballer : footballers) {
			 footballer.getPrice() += 500;
		 }
	 }

	 


	 void Match(int week) {
		 round = splitString(schedule[week]);
		 for (int i{ 0 }, index{ 0 }; i < (round.size() / 2); i++, index += 2) {
			 cout << setw(10) << left << round[index] << setw(10) << left << "  V.S  " << round[index + 1] << "\n";
			 pair <int, int> result = showResult();
			 vector<Footballer> team1;
			 vector<Footballer> team2;
			 team1 = showFootballers(result.first, round[index]);
			 /*modifyFootballerPoints(footballers);
			 modifyFootballerPrice(footballers);*/
			 team2 = showFootballers(result.second, round[index + 1]);
			 /*modifyFootballerPoints(footballers);
			 modifyFootballerPrice(footballers);*/
			 int maxSize = max(team1.size(), team2.size());

			 for (int i{ 0 }; i < maxSize; i++) {
				 if (i < team1.size())
					 cout << setw(20) << left << team1[i].getName();
				 else
					 cout << setw(20) << left << " ";
				 if (i < team2.size())
					 cout << team2[i].getName();
				 else
					 cout << " ";
				 cout << "\n";

			 }
			 cout << "\n************************\n\n";
		 }
	 }
};