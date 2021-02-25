#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

void InitCode();
void code_output(string r);
int IsOperationCode(string x);//判断输入的是否为操作码

void R_Instruction1(string op);
void R_Instruction2(string op);
void R_Instruction3(string op);

void I_Instruction1(string op);
void I_Instruction2(string op);
void I_Instruction3(string op);


void J_Instruction(string op,int count);

vector<string> split(string r);
string number2bistr(string r, int k);
string offsetchange(int off);
