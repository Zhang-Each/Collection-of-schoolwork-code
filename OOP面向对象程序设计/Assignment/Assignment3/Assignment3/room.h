#include<iostream>
#include<vector>
#include<string>

using namespace std;

//class of room
class room {
private:
	bool monster, princess;
public:
	//direct[0] --direct[3] mean east/south/west/north 
	bool direct[4];
	room();
	~room();
	bool isPricess();
	bool isMonster();
	void printInfo();
	//set the origin direction of each room
	void setDirect(int a, int b, int c, int d);
	//print the possible direct of the room
	void printDirect();
};
