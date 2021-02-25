#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

typedef int Word;
typedef unsigned int word;

class calculate
{
private:
	word num1, num2;
	string bin1, bin2;

public:
	calculate(Word a,Word b);
	//~calculate();
	string numTostr(word x);
	word strTonum(string x);
	word madd(string x, string y);
	word msub(string x, string y);
	word mmul(string x, string y);
	word mdiv(string x, string y);
	void run();

};

