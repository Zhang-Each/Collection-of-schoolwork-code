#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<fstream>
#include<stdlib.h>

#include "main.h"
using namespace std;

map<string, int> position;
map<string, string> reg_code;
map<string, string> op_code;
string shamt = "00000";

ofstream fp("result.txt");

int main()
{
	cout << "Input end to exit and put one MIPS instruction in ont line" << endl;
	cout << "Before you input the instruction you should read the document otherwise you will get an error" << endl;
	string op;
	int i,count = 1;
	InitCode();
	while (cin >> op) {
		for (i = 0; i < op.size(); i++) {
			if (op[i] >= 'A'&&op[i] <= 'Z') {
				op[i] = op[i] - 'A' + 'a';
			}
		}
		if (op == "end")
			return 0;
		int x = IsOperationCode(op);
		if (x == 1 ) {
			R_Instruction1(op);
		}
		else if (x == 2 ) {
			R_Instruction2(op);
		}
		else if (x == 3) {
			R_Instruction3(op);
		}
		else if (x == 4) {
			I_Instruction1(op);
		}
		else if (x == 5) {
			I_Instruction2(op);
		}
		else if (x == 6) {
			I_Instruction3(op);
		}
		else if (x == 7) {
			J_Instruction(op,count);
		}
		else if (x == 8) {
			if (op == "eret") {
				cout << "0100 0001 0000 0000 0000 0000 0001 1000" << endl;
				if (fp.is_open()) {
					fp << "0100 0001 0000 0000 0000 0000 0001 1000" << endl;
				}
			}
			else {
				cout << "0000 0000 0000 0000 0000 0000 0000 1100" << endl;
				if (fp.is_open()) {
					fp << "0100 0001 0000 0000 0000 0000 0001 1000" << endl;
				}
			}
		}
		else if (x == 0) {
			position[op] = count;
			string op2;
			cin >> op2;
			int y = IsOperationCode(op2);
			if (op == "end")
				return 0;
			if (y == 1) {
				R_Instruction1(op2);
			}
			else if (y == 2) {
				R_Instruction2(op2);
			}
			else if (y == 3) {
				R_Instruction3(op2);
			}
			else if (y == 4) {
				I_Instruction1(op2);
			}
			else if (y == 5) {
				I_Instruction2(op2);
			}
			else if (y == 6) {
				I_Instruction3(op2);
			}
			else if (y == 7) {
				J_Instruction(op2,count);
			}
			else if (y == 8) {
				if (op == "eret") {
					cout << "0100 0001 0000 0000 0000 0000 0001 1000" << endl;
					if (fp.is_open()) {
						fp << "0100 0001 0000 0000 0000 0000 0001 1000" << endl;
					}
				}
				else {
					cout << "0000 0000 0000 0000 0000 0000 0000 1100" << endl;
					if (fp.is_open()) {
						fp << "0100 0001 0000 0000 0000 0000 0001 1000" << endl;
					}
				}
			}
			else {
				cout << "error!" << endl;
			}
		}

		count++;
	}
	system("pause");
	return 0;
}


//对输入的若干操作数进行切分
//碰到$时跳过，碰到逗号时换操作数，碰到#表示注释直接结束
vector<string> split(string r)
{
	vector<string> result(3);
	//cout << r;
	int i = 0, j = 0;
	/*
	for (i = 0; i < r.length(); i++) {
		if (r[i] == '(' || r[i] == ')') {
			r[i] = ',';
		}
	}
	*/
	for (i = 0; i < r.length(); i++) {
		if (r[i] == ',' || r[i] == '(')
			j++;
		else if (r[i] == ')')
			break;
		else if (r[i] == '$')
			continue;
		else if (r[i] != '#')
			result[j].push_back(r[i]);
		else
			break;
	}
	return result;
}

//将十进制数的字符串转化成16进制，k是需要转化的位数
//k在R型指令中转换成shamt是5，在I型指令中转换成immediate是16
string number2bistr(string r, int k)
{
	int num = atoi(r.c_str());
	//cout << num << endl;
	if (num >= 32 && k<=5)
		return "11111";
	string result;
	vector<int> bin;
	while (num != 0) {
		bin.push_back(num % 2);
		num = num / 2;
	}
	for (int i = 0; i < k - bin.size(); i++)
		result += '0';
	for (int i = bin.size() - 1; i >= 0; i--) {
		if (bin[i] == 1)
			result += '1';
		else
			result += '0';
	}
	//cout << result << endl;
	return result;
}

string offsetchange(int off)
{
	int i,is_negative = 0;
	if (off < 0) {
		is_negative = 1;
		off = -off;
	}
	vector<int> bin;
	string result;
	while (off != 0) {
		bin.push_back(off % 2);
		off /= 2;
	}
	for (i = 0; i < 26 - bin.size(); i++) {
		result += '0';
	}
	for (i = bin.size() - 1; i >= 0; i--) {
		if (bin[i] == 1)
			result += '1';
		else
			result += '0';
	}
	// cout << result << endl;
	if (is_negative == 1) {
		for (i = 0; i < result.length(); i++) {
			if (result[i] == '0')
				result[i] = '1';
			else
				result[i] = '0';
		}
	}

	return result;
}

//输出结果的机器码
void code_output(string r)
{
	for (int i = 0; i < r.size(); i++) {
		cout << r[i];
		if (i % 4 == 3) {
			cout << " ";
		}
	}
	char *copy = new char[r.length() + 1];
	for (int i = 0; i < r.length(); i++) {
		copy[i] = r[i];
	}
	copy[r.length()] = '\n';
	
//fstream fp("result.txt");
	if (fp.is_open()) {
		fp << r << endl;
	}
	cout << endl;
}

//R-Instruction translation into machine code
void R_Instruction1(string op)
{
	string r;
	cin >> r;
	vector<string> result = split(r);
	string machine_code = "000000";
	machine_code += reg_code[result[1]] + reg_code[result[2]] + reg_code[result[0]] + shamt + op_code[op];
	code_output(machine_code);
}

void R_Instruction2(string op)
{
	string r;
	cin >> r;
	vector<string> result = split(r);
	string machine_code = "000000" + reg_code[result[1]] + "00000" + reg_code[result[0]];

	string shamt2 = number2bistr(result[2], 5);

	machine_code += shamt2 + op_code[op];
	code_output(machine_code);
}

void R_Instruction3(string op)
{
	string r;
	cin >> r;
	vector<string> result = split(r);
	string machine_code = "000000" + reg_code[result[0]] + "000000000000000001000";
	code_output(machine_code);
}

void I_Instruction1(string op)
{
	string r;
	cin >> r;
	vector<string> result = split(r);
	string machine_code = op_code[op] + reg_code[result[1]] + reg_code[result[0]];
	string immediate = number2bistr(result[2], 16);
	machine_code += immediate;
	code_output(machine_code);

}

void I_Instruction2(string op)
{
	string r;
	cin >> r;
	vector<string> result = split(r);
	string machine_code = "00111100000" + reg_code[result[0]];
	string immediate = number2bistr(result[1], 16);
	machine_code += immediate;
	//cout << immediate << endl;
	//cout << result[0] << endl;
	//cout << result[1] << endl;
	code_output(machine_code);
}


void I_Instruction3(string op)
{
	//lw $s1,10($s2)
	string r;
	cin >> r;
	vector<string> result = split(r);
	//cout << result[0] << endl;
	//cout << result[1] << endl;
	//cout << result[2] << endl;
	string machine_code = op_code[op] + reg_code[result[2]] + reg_code[result[0]];
	string immediate = number2bistr(result[1], 16);
	machine_code += immediate;
	//cout << immediate << endl;
	code_output(machine_code);
}


void J_Instruction(string op, int count)
{
	string r, s;
	cin >> r;
	s = r + ':';
	if (position[s] >= 1) {
		int offset = -4 * (count - position[s] + 1);
		//cout << offset << endl;
		string immediate = offsetchange(offset);
		string machine_code = op_code[op] + immediate;
		code_output(machine_code);
	}
	else {
		string immediate = number2bistr(r, 26);
		string machine_code = op_code[op] + immediate;
		code_output(machine_code);
	}
}

//我们使用stl中的map来存储MIPS指令和32个寄存器代表的机器码
//目前只实现了有严格标准定义的31条指令
void InitCode()
{
	op_code["eret"] = "011000";
	op_code["systemcall"] = "001100";

	//R-instruction set 1
	op_code["add"] = "100000";
	op_code["addu"] = "100001";
	op_code["sub"] = "100010";
	op_code["subu"] = "100011";
	op_code["mul"] = "000010";
	op_code["mult"] = "011000";
	op_code["multu"] = "011001";
	op_code["div"] = "011010";
	op_code["divu"] = "011011";

	op_code["and"] = "100100";
	op_code["or"] = "100101";
	op_code["nor"] = "100111";
	op_code["slt"] = "101010";
	op_code["sltu"] = "101011";
	op_code["sllv"] = "000100";
	op_code["srlv"] = "000110";
	op_code["srav"] = "000111";

	//R-instruction set 2
	op_code["sll"] = "000000";
	op_code["srl"] = "000010";
	op_code["sra"] = "000011";
	//R-instruction set 3
	op_code["jr"] = "0010000";
	op_code["jalr"] = "001001";

	//I-instruction set 1
	op_code["addi"] = "001000";
	op_code["andui"] = "001001";
	op_code["andi"] = "001100";
	op_code["ori"] = "101011";
	op_code["xori"] = "001110";
	op_code["beq"] = "000100";
	op_code["bne"] = "000101";

	op_code["slti"] = "001010";
	op_code["sltiu"] = "001011";

	//I-instruction set 2
	op_code["lui"] = "001111";

	//I-instruction set 3
	op_code["lw"] = "100011";
	op_code["lwx"] = "100011";
	op_code["lh"] = "100001";
	op_code["lhx"] = "100001";
	op_code["lhu"] = "100101";
	op_code["lhux"] = "100101";
	op_code["sw"] = "101011";
	op_code["swx"] = "101011";
	op_code["sh"] = "101001";
	op_code["shx"] = "101001";

	//J-instruction set
	op_code["j"] = "000010";
	op_code["jal"] = "000011";

	//regester code
	reg_code["zero"] = "00000";
	reg_code["at"] = "00001";
	reg_code["v0"] = "00010";
	reg_code["v1"] = "00011";

	reg_code["a0"] = "00100";
	reg_code["a1"] = "00101";
	reg_code["a2"] = "00110";
	reg_code["a3"] = "00111";

	reg_code["t0"] = "01000";
	reg_code["t1"] = "01001";
	reg_code["t2"] = "01010";
	reg_code["t3"] = "01011";
	reg_code["t4"] = "01100";
	reg_code["t5"] = "01101";
	reg_code["t6"] = "01110";
	reg_code["t7"] = "01111";

	reg_code["s0"] = "10000";
	reg_code["s1"] = "10001";
	reg_code["s2"] = "10010";
	reg_code["s3"] = "10011";
	reg_code["s4"] = "10100";
	reg_code["s5"] = "10101";
	reg_code["s6"] = "10110";
	reg_code["s7"] = "10111";

	reg_code["t8"] = "11000";
	reg_code["t9"] = "11001";

	reg_code["k0"] = "11010";
	reg_code["k1"] = "11011";

	reg_code["gp"] = "11100";
	reg_code["sp"] = "11101";
	reg_code["fp"] = "11110";
	reg_code["ra"] = "11111";
}


//当参数是操作码是会返回一个正数
//否则返回0
int IsOperationCode(string x)
{
	if (x == "add" || x == "addu" || x == "sub" || x == "subu" || x == "mul" || x == "mult" || x == "multu" || x == "div" || x == "divu" || x == "and" || x == "or" || x == "nor" || x == "slt" || x == "sltu" || x == "sllv" || x == "srlv" || x == "srav") {
		return 1;
	}
	else if (x == "sll"||x=="srl"||x=="sra") {
		return 2;
	}
	else if (x == "jr"||x=="jalr") {
		return 3;
	}
	else if (x == "addi" || x == "andui" || x == "andi" || x == "ori" || x == "xor" || x == "beq" || x == "bne" || x == "slti" || x == "sltiu") {
		return 4;
	}
	else if (x == "lui") {
		return 5;
	}
	else if (x == "lw" || x == "lwx" || x == "lh" || x == "lhx" || x == "lhu" || x == "lhux" || x == "sw" || x == "swx" || x == "sh" || x == "shx"||x=="slti"||x=="sltiu") {
		return 6;
	}
	else if (x == "j" || x == "jal") {
		return 7;
	}
	else if (x == "eret" || x == "systemcall") {
		return 8;
	}
	else
		return 0;
}
