#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

typedef unsigned int word;
#include"calculate.h"

int main()
{
	cout << "Welcome to the integer calculator developed by zyc" << endl;
	cout << "Please input 2 unsigned integer in a line" << endl;
	Word a, b;
	cin >> a >> b;
	calculate x(a, b);
	x.run();
	system("pause");
	return 0;
}