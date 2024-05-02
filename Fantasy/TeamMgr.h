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
		vector <string> lines = readFileLines(path);

		for (const string& line : lines) {
			Footballer footballer(line);
			footballers[footballer.getTeamName()].push_back(footballer);

		}
	}

	void modifyFootballerPoints(vector<Footballer>& teamFootballers, vector<Footballer>& footballersWhoScored) {
		const int points = 5;
		for (int i{ 0 }; i < footballersWhoScored.size(); i++) {
			for (int j{ 0 }; j < teamFootballers.size(); j++) {
				if (footballersWhoScored[i].getName() == teamFootballers[j].getName()) {
					int newPoints = teamFootballers[j].getPoints() + points;
					teamFootballers[j].setPoint(newPoints);
				}
			}
		} 

	}

	void setCleanSheetPoints(Footballer &goalKepper) {
		const int points = 10;
		int newPoints = goalKepper.getPoints() + points;
		goalKepper.setPoint(newPoints);
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

	vector <Footballer> getFootballersWhoScored(int goals, string teamName) {
		vector <Footballer>footballer = footballers[teamName];

		vector <Footballer>footballername;
		while (goals--) {
			int idx = rand() % 11;
			footballername.push_back(footballer[idx]);
		}
		return footballername;
	}




	 void modifyPoints (vector<Footballer>& teamFootballers,vector<Footballer>& footballersWhoScored, int oppositeGoal) {
		 if (footballersWhoScored.size())
			modifyFootballerPoints(teamFootballers, footballersWhoScored);

		 if(!oppositeGoal)
			setCleanSheetPoints(teamFootballers[0]);
	 }



	 void modifyFootballerPrice(vector<Footballer>& footballers) {
		 const int points = 5; const int price = 500;

		 for (Footballer& footballer : footballers) {
			 int goal = footballer.getPoints() / points;
			 int newPrice = (goal * price) + footballer.getPrice();
			 footballer.setPrice(newPrice);
		 }
	 }

	 void resetPoints() {
		 for (int i{ 0 }; i < footballers.size(); i++)
			 reset(footballers[round[i]]);
	 }

	 void reset(vector<Footballer>& footballers) {
		 const int zero = 0;
		 for (Footballer& footballer : footballers) {
			 footballer.setPoint(zero);
		 }
	 }



	 void showFootballersWhoScored(vector<Footballer> footballers1, vector<Footballer> footballers2) {
		
		 int maxSize = max(footballers1.size(), footballers2.size());

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
		 
		 round = splitString(schedule[week]);

		 resetPoints();

		 for (int i{ 0 }, index{ 0 }; i < (round.size() / 2); i++, index += 2) {
			 cout << setw(10) << left << round[index] << setw(10) << left << "  V.S  " << round[index + 1] << "\n";
			 pair <int, int> result = showResult();
			 vector<Footballer> footballesWhoScoredFromTeam1 = getFootballersWhoScored(result.first, round[index]);
			 modifyPoints(footballers[round[index]], footballesWhoScoredFromTeam1, result.second);
			 vector<Footballer> footballesWhoScoredFromTeam2 = getFootballersWhoScored(result.second, round[index + 1]);
			 modifyPoints(footballers[round[index + 1]],footballesWhoScoredFromTeam2, result.first);

			 showFootballersWhoScored(footballesWhoScoredFromTeam1, footballesWhoScoredFromTeam2);

			 modifyFootballerPrice(footballers[round[index]]); modifyFootballerPrice(footballers[round[index + 1]]);
			 cout << "\n************************\n\n";

		 }
	 }

	 void showFoot(string teamName) {
		 for (Footballer f : footballers[teamName])
			 cout << f.getName() << " " << f.getPoints() << " " << f.getPrice() << "\n";
		 cout << "\n\n";
	 }
};