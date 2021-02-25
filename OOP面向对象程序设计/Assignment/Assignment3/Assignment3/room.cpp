#include<iostream>
#include<vector>
#include<string>
#include"room.h"
using namespace std;

//the construct function, set all the direction = 0
room::room()
{
	monster = 0;
	princess = 0;
	int i;
	for (i = 0; i < 4; i++) {
		direct[i] = 0;
	}
	//cout << "1" << endl;
}

room::~room()
{
	//delete[] direct;
	cout << "Rooms are cleaned!" << endl;
}

// judge whether the princess is in the room
bool room::isPricess()
{
	if (princess == true)
		return true;
	else
		return false;
}

// judge whether the monster is in the room
bool room::isMonster()
{
	if (monster == true)
		return true;
	else
		return false;
}

//set the direct of a room
//a,b,c,d can be 0 or 1
void room::setDirect(int a, int b, int c, int d)
{
	direct[0] = a;
	direct[1] = b;
	direct[2] = c;
	direct[3] = d;
}

void room::printInfo()
{
	int i,count=0;
	vector<string> op = { "east","south","west","north" };
	for (i = 0; i < 4; i++) {
		if (direct[i] == true)
			count++;
		//the number of direction of a room
	}

	//print the direction of this room
	cout << "There are " << count << " exits: ";
	for (i = 0; i < 4; i++) {
		if (direct[i] == true) {
			cout << op[i] << " ";
		}
	}
	cout << "\nPlease input your choice with 'go ' in English." << endl;
}

void room::printDirect()
{
	int i;
	vector<string> op = { "east","south","west","north" };
	for (i = 0; i < 4; i++) {
		if (direct[i])
			cout << op[i] << " ";
	}
	cout << endl;
}