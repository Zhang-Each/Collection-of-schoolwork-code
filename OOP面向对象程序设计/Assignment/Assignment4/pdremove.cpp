#include "pdremove.h"
#include "PersonalDiary.h"

int pdremove::removeDiary(map<int, vector<string>> &diary)
{
	int remove = -1;
	cout << "Please input the date you want to remove in the form 'yyyy-mm-dd'." << endl;
	string s;
	cin >> s;
	int date = pdremove::change(s);
	map<int, vector<string>>::iterator m;
	//delete the diary of that day
	for (m = diary.begin(); m != diary.end();) {
		if (m->first == date) {
			diary.erase(m++); //erase is a method of map to delete a record by its key
			remove = 0;
		}
		else {
			m++;
		}
	}
	return remove;
}

//a function to change the date from string in a special format to integer
int pdremove::change(string date)
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
	pdremove removeCommand;
	//read from txt file 
	solution.read();
	//show the commands you can use
	//solution.showCommand();
	removeCommand.removeDiary(solution.diary);
	//write the diary to the txt file when the program end
	solution.end();
	system("pause");
	return 0;
}