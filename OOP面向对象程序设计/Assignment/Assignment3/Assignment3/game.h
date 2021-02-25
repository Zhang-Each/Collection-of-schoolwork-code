#include<iostream>
#include<vector>
#include<string>
#include"room.h"
using namespace std;

struct position {
	int x, y;
};

class game {
private:
	//the game has 16 rooms in total
	room Room[4][4];
	//the (x,y) of player, monster and princess
	position player, monster, prin;
	int findPrincess;

public:
	game();
	~game();
	//function to start the game
	void play();
	//set the position of monster and princess
	void setMandP();
	//set the direct of each room
	void setDirect();
	//print the game information
	void printInfomation();
	void printRooms();
	//to judge if meet the monster
	bool meetMonster();
	// to judge whether save the princess
	bool savePrincess();
	//whether return to the lobby
	bool returnLobby();
	bool checkDirect(string op);
};