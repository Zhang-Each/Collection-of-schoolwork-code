#include "PersonalDiary.h"

PersonalDiary::PersonalDiary()
{
	cout << "Welcome to the Personal Diary!" << endl;
}


//read the diary from the diary.txt
void PersonalDiary::read()
{
	//read the dairy from file
	ifstream fin("diary.txt");
	fin >> num;
	for (int i = 0; i < num; i++) {
		int date;
		string temp;
		vector<string> text;
		//use a redirection in txt file
		fin >> date;
		getline(fin, temp);
		while (getline(fin, temp)) {
			text.push_back(temp);
			// the end of each text will be . or EOF(-1)
			if (temp == "." || temp == "-1") {
				break;
			}
		}
		diary[date] = text;
	}

}

//write all the diary to the txt file when the program end 
void PersonalDiary::end()
{
	ofstream fout("diary.txt");
	fout << diary.size() << endl;
	
	map<int, vector<string>>::iterator m;
	for (m = diary.begin(); m != diary.end(); m++) {
		fout << m->first << endl;
		for (int i = 0; i < m->second.size(); i++) {
			fout << m->second[i] << endl;
		}
	}

	cout << "Write Successfully!" << endl;
}

//print some tips about the software
void PersonalDiary::showCommand()
{
	cout << "In this Personal-Diary, you can do the following operations:" << endl;
	cout << "pdadd: and an diary to the notebook." << endl;
	cout << "pdlist: show you diaries in the notebook." << endl;
	cout << "pdshow: show the content to you." << endl;
	cout << "pdremove:remove a diary from the notebook" << endl;
	cout << "You can input the commands you would like to operate in the CLI" << endl;
	cout << "Input an 'end' if you want to close the PersonalDiary" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
}
