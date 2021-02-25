#include "pdshow.h"
#include "PersonalDiary.h"

//show a content of all the diary ordered by date
void pdshow::showDiary(map<int, vector<string>> &diary)
{
	map<int, vector<string>>::iterator m;
	cout << "----------Content--------" << endl;
	for (m = diary.begin(); m != diary.end(); m++) {
		int day, month, year;
		day = m->first % 100;
		year = m->first / 10000;
		month = (m->first - 10000 * year) / 100;
		cout << year << "-" << month << "-" << day << endl;
	}
	cout << "Content Show Finished." << endl;
}

int main()
{
	PersonalDiary solution;
	pdshow showCommand;
	//read from txt file 
	solution.read();
	//show the commands you can use
	//solution.showCommand();
	showCommand.showDiary(solution.diary);
	//write the diary to the txt file when the program end
	solution.end();
	system("pause");
	return 0;
}