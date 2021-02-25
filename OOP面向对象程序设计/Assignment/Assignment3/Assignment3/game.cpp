#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<time.h>

#include"game.h"

using namespace std;

game::game()
{
	//(0,0) is the start room, the lobby
	player.x = 0;
	player.y = 0;
	findPrincess = 0;
	game::setMandP();
	game::setDirect();
}

game::~game()
{
	cout << "The game is deleted" << endl;
}

void game::play()
{
	int count = 0;
	while (true) {
		// check if meet the monster, if meet, game over
		if (meetMonster()) {
			cout << "You meet the monster, game is over!" << endl;
			return;
		}
		//check if meet the princess
		if (savePrincess()) {
			if(count==0)
				cout << "You have save the princess! Hurry up to escape the castle!" << endl;
			count++;
		}
		if (returnLobby()) {
			cout << "You have success! Now you can exit the game! " << endl;
			return;
		}
		game::printInfomation();
		string x1, x2;
		cin >> x1 >> x2;
		//execute the 'go' operation  
		if (x1 == "go") {
			if (!checkDirect(x2)) {
				cout << "Can't go there! Please Try again!" << endl;
			}
			else if (x2 == "east") {
				player.x++;
			}
			else if (x2 == "west") {
				player.x--;
			}
			else if (x2 == "south") {
				player.y--;
			}
			else if (x2 == "north") {
				player.y++;
			}

		}
		else {
			cout << "Command Error! Please Try again!" << endl;
		}
	}
}

//randomly set the position of monster and the princess
void game::setMandP()
{
	cout << "Let's find the princess and save her! Be careful to the monster!" << endl;
	srand(time(0));
	prin.x = rand() % 4;
	prin.y = rand() % 4;

	while (prin.x == 0 && prin.y == 0) {
		prin.x = rand() % 4;
		prin.y = rand() % 4;
	}

	monster.x = rand() % 4;
	monster.y = rand() % 4;
	//cout << "The position of princess is" << prin.x << " " << prin.y << endl;
	//cout << "The position of monster is" << monster.x << " " << monster.y << endl;
}


// set the direction of each room
void game::setDirect()
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (i == 0 && j == 0)
				Room[i][j].setDirect(1, 0, 0, 1);
			else if (i == 0 && j == 3)
				Room[i][j].setDirect(1, 1, 0, 0);
			else if (i == 3 && j == 0)
				Room[i][j].setDirect(1, 0, 0, 1);
			else if (i == 3 && j == 3)
				Room[i][j].setDirect(0, 1, 1, 0);
			else if (i == 0 && (j == 1 || j == 2))
				Room[i][j].setDirect(1, 1, 0, 1);
			else if (j == 0 && (i == 1 || i == 2))
				Room[i][j].setDirect(1, 0, 1, 1);
			else if (i == 3 && (j == 1 || j == 2))
				Room[i][j].setDirect(0, 1, 1, 1);
			else if (j == 3 && (i == 1 || i == 2))
				Room[i][j].setDirect(1, 1, 1, 0);
			else
				Room[i][j].setDirect(1, 1, 1, 1);
		}
	}
}

void game::printInfomation()
{
	//if player is in the lobby, print lobby
	if (player.x == 0 && player.y == 0) {
		cout << "Welcome to the Lobby!";
	}
	else
		//print the lable of number if not in lobby
		cout << "Welcome to the room" << " [" << player.x << "--" << player.y << "]";
	Room[player.x][player.y].printInfo();
}

//a test member function using when developing the game
void game::printRooms()
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			Room[i][j].printDirect();
		}
	}
}

//check whether meet monster
bool game::meetMonster()
{
	if (player.x == monster.x&&player.y == monster.y)
		return true;
	else
		return false;
}

//check whether save the princess
bool game::savePrincess()
{
	if (findPrincess)
		return true;
	//if find the postion of the pricess
	if (player.x == prin.x&&player.y == prin.y)
	{
		findPrincess = 1;
		//now the princess is safe so put her in (-1,-1)
		prin.x = -1;
		prin.y = -1;
		return true;
	}
	else
		return false;
}

// the win condtion of the game 
bool game::returnLobby()
{
	if (player.x == 0 && player.y == 0 && findPrincess == 1)
		return true;
	else
		return false;
}

//check the input operation is right or not
bool game::checkDirect(string op)
{
	int opcode;
	if (op == "east")
		opcode = 0;
	else if (op == "south")
		opcode = 1;
	else if (op == "west")
		opcode = 2;
	else if (op == "north")
		opcode = 3;
	else
		return false;
	if (!Room[player.x][player.y].direct[opcode])
		return false;
	else
		return true;
}