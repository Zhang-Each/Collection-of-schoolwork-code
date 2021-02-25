#include "pdlist.h"
#include "PersonalDiary.h"
//print the diary in a period of time
void pdlist::listDiary(map<int, vector<string>> &diary)
{
	cout << "Do you want to select the period of list? yes or no" << endl;
	string choose;
	cin >> choose;
	//user can choose a time period or not
	//if yes, you should input a time period
	if (choose == "yes") {
		cout << "Please input the start and end date in the form 'yyyy-mm-dd' in a line splited with a ' '" << endl;
		string s, t;
		int start, end;
		cin >> s >> t;
		start = pdlist::change(s);
		end = pdlist::change(t);
		//cout << start << " " << end << endl;
		cout << "------Selcted Diary-------" << endl;
		map<int, vector<string>>::iterator m;
		for (m = diary.begin(); m != diary.end(); m++) {
			if (m->first >= start && m->first <= end) {
				cout << m->first << endl;
				for (int i = 0; i < m->second.size(); i++) {
					cout << m->second[i] << endl;
				}
			}
		}
	}
	//if not, print all the diary in the order of date
	else if (choose == "no") {
		cout << "-------All diary-------" << endl;
		map<int, vector<string>>::iterator m;
		for (m = diary.begin(); m != diary.end(); m++) {
			cout << m->first << endl;
			for (int i = 0; i < m->second.size(); i++) {
				cout << m->second[i] << endl;
			}
		}
	}
	//if input something else
	else {
		cout << "Syntax Error!" << endl;
	}
	cout << "List Command Finished" << endl;

}

int pdlist::change(string date)
{
	int result = 0;
	for (int i = 0; i < date.length(); i++) {
		if (date[i] != '-')
			result = result * 10 + (date[i] - '0');
	}
	return result;
}

int main()
{
	PersonalDiary solution;
	pdlist listCommand;
	//read from txt file 
	solution.read();
	//show the commands you can use
	//solution.showCommand();
	listCommand.listDiary(solution.diary);
	//write the diary to the txt file when the program end
	solution.end();
	system("pause");
	return 0;
}