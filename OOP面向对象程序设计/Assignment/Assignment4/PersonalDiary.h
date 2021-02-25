#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>

using namespace std;

//a class to init the program
class PersonalDiary
{
public:
	int num;
	//use a map to store the diary by date
	map<int, vector<string>> diary;
public:
	PersonalDiary();
	void read();//read the diary from txt file when program start
	void showCommand();
	void end();//write the diary to txt file when program end
};