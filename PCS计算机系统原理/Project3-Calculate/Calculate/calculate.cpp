#include "calculate.h"

#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

calculate::calculate(Word a, Word b)
{
	//change to a suitable value for the 8-bit calculate
	while (a < 0 || b < 0) {
		if (a < 0)
			a += 256;
		if (b < 0)
			b += 256;
	}

	if (a > 256) {
		a = 256;
	}
	if (b > 256) {
		b = 256;
	}
	num1 = a;
	num2 = b;
	bin1 = numTostr(num1);
	bin2 = numTostr(num2);
	cout << bin1 << endl;
	cout << bin2 << endl;
}

word calculate::strTonum(string x)
{
	int change[8] = { 128,64,32,16,8,4,2,1 };
	int i,result = 0;
	for (i = 0; i < x.size(); i++) {
		if (x[i] == '1')
			result += change[i];
	}
	return result;
}

void calculate::run()
{

	cout << "The result of add is " << madd(bin1, bin2) << endl;
	cout << "The result of add in binary is " << numTostr(madd(bin1, bin2)) << endl;

	cout << "The result of sub is " << msub(bin1, bin2) << endl;
	cout << "The result of sub in binary is " << numTostr(msub(bin1, bin2)) << endl;

	cout << "The result of mul is " << mmul(bin1, bin2) << endl;
	cout << "The result of mul in binary is " << numTostr(mmul(bin1, bin2)) << endl;

	cout << "The result of div is " << mdiv(bin1, bin2) << endl;
	cout << "The result of div in binary is " << numTostr(mdiv(bin1, bin2)) << endl;
}

string calculate::numTostr(word x)
{
	vector<int> bin;
	while (x != 0) {
		bin.push_back(x % 2);
		x /= 2;
	}
	string result = "";
	for (int i = 0; i < 8 - bin.size(); i++) {
		result += '0';
	}
	for (int i = bin.size() - 1; i >= 0; i--) {
		if (bin[i])
			result += '1';
		else
			result += '0';
	}
	return result;
}


word calculate::madd(string x, string y)
{
	int i,a,b,bit,cf = 0;
	vector<char> bin;
	for (i = 7; i >= 0; i--) {
		a = x[i] - '0', b = y[i] - '0';
		bit = a + b + cf;
		if (bit % 2 == 0) {
			bin.push_back('0');
		}
		else {
			bin.push_back('1');
		}
		if (bit >= 2) {
			cf = 1;
		}
		else {
			cf = 0;
		}
	}
	string result = "";
	for (i = 7; i >= 0; i--) {
		result += bin[i];
	}
	
	return strTonum(result);
}


word calculate::msub(string x, string y)
{
	int i, a, b, bit, cf = 0;
	for (i = 0; i < 8; i++) {
		if (y[i] == '1')
			y[i] = '0';
		else
			y[i] = '1';
	}
	y = numTostr(madd(y, "00000001"));

	//cout << y << endl;

	vector<char> bin;
	for (i = 7; i >= 0; i--) {
		a = x[i] - '0', b = y[i] - '0';
		bit = a + b + cf;
		if (bit % 2 == 0) {
			bin.push_back('0');
		}
		else {
			bin.push_back('1');
		}
		if (bit >= 2) {
			cf = 1;
		}
		else {
			cf = 0;
		}
	}
	string result = "";
	for (i = 7; i >= 0; i--) {
		result += bin[i];
	}

	//cout << "The result of sub in binary is " << result << endl;
	return strTonum(result);
}

word calculate::mmul(string x, string y)
{
	int i, j;
	string result = "00000000";
	for (i = 0; i < strTonum(x); i++) {
		result = numTostr(madd(result, y));
	}
	return strTonum(result);
}


word calculate::mdiv(string x, string y)
{
	word count = 0;
	while (strTonum(x) >= strTonum(y)) {
		x = numTostr(msub(x, y));
		count++;
	}
	return count;
}


