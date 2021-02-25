#include<vector>
#include<string>
#include<iostream>
#include<map>

using namespace std;

////the class implentment the list function
class pdlist
{
public:
	void listDiary(map<int, vector<string>> &diary);
	//a function to change the format of date
	int change(string date);
};

