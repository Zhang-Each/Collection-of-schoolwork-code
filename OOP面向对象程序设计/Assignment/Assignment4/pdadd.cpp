#include "pdadd.h"
#include "PersonalDiary.h"

void pdadd::addDiary(map<int, vector<string>> &diary)
{
	cout << "Please input the date in the form year,month,day such as '2020-04-10' " << endl;
	int i,date=0;
	string s;
	cin >> s;
	//change the date into integer
	for (i = 0; i < s.length(); i++) {
		if (s[i] != '-') {
			date = 10 * date + (s[i] - '0');
		}
	}
	//check if elready have a diary that day
	//you can stop adding a diary or cover the old one
	if (diary[date].size() >= 1) {
		cout << "You have a diary in this day, do you want to recover it? Input yes or no" << endl;
		string choose;
		cin >> choose;
		if (choose == "no") {
			cout << "The add command is finished" << endl;
			return;
		}
	}
	//insert one record to the map or cover the old one
	cout << "Please input you diary in lines, use a '.' or EOF in the start of a line to stop." << endl;
	vector<string> text;
	string line;
	while (cin >> line) {
		text.push_back(line);
		if (line == "." || line == "-1") {
			break;
		}
	}
	diary[date] = text;
	cout << "Add Command Finished" << endl;
}

int main()
{
	PersonalDiary solution;
	pdadd addCommand;
	//read from txt file 
	solution.read();
	//show the commands you can use
	//solution.showCommand();

	addCommand.addDiary(solution.diary);
	//write the diary to the txt file when the program end
	solution.end();
	system("pause");
	return 0;
}