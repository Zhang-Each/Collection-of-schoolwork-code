#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
typedef unsigned int dwrd;

string trans1(string integer);
string ftoa(dwrd x);
string add(string integer, int bit, int adder);
string trans2(string decimal);
dwrd atof(string str);
string form1(string str, int start, int end);
string divide(string str);
string form2(string str, int start, int end);
string form2(string str, int start, int end);
dwrd fadd(dwrd x, dwrd y);
dwrd fsub(dwrd x, dwrd y);
dwrd fmul(dwrd x, dwrd y);
dwrd fdiv(dwrd x, dwrd y);

string ftoa(dwrd x)
{
    string result;
    dwrd sx = x >> 31;
    dwrd ex = (x >> 23) & 0xFF;
    dwrd mx = (x & 0x7FFFFF) | 0x800000;
    if(ex == 0) {
	if(mx == 0) result = "0";
	else {
	    
	}
    }
    else if(ex == 0xFF) {
	if(mx == 0) {
	    if(!sx) result = "INF";
	    else result = "-INF";
	}
	else result = "NaN";
    }
    else if(ex >= 127) {
	dwrd e = ex - 127;
	string integer = "1";
	string decimal = ".";
	int i = 0;
	while(i < 24) {
	    if(i < e) {
		if((mx >> (22 - i)) & 1) integer += "1";
		else integer += "0";
	    }
	    else {
		if((mx >> (22 - i)) & 1) decimal += "1";
		else decimal += "0";
	    }
	    i++;
	}
	if(!sx) result = trans1(integer) + "." + trans2(decimal);
	else result = "-" + trans1(integer) + "." + trans2(decimal);
    }
    else {
	dwrd e = 127 - ex;
	string decimal = ".";
	int i = 0, j = 0;
	while(i < e) {
	    decimal += "0";
	    i++;
	}
	while(j < 24) {
	    if((mx >> (22 - j)) & 1) decimal += "1";
	    else decimal += "0";
	    j++;
	}
	if(!sx) result = "0." + trans2(decimal);
	else result = "-0." + trans2(decimal);
    }
    return result;
}

string trans1(string integer)
{
    string result = "00000000000000000000000000000000000000"; /*38位*/
    int i = 0;
    reverse(integer.begin(), integer.end());
    while(i < integer.length()) {
	if(integer[i] == '1') {
	    dwrd temp = 1 << i;
	    int j = 0;
	    while(temp) {
		int adder = temp % 10;
		result = add(result, j, adder);
		j++;
		temp /= 10;
	    }
	}
	i++;
    }
    i = 37;
    while(i >= 0) {
	if(result[i] == '0') result[i] = '\0';
	else break;
	i--;
    }
    reverse(result.begin(), result.end());
    return result;
}

string add(string integer, int bit, int adder)
{
    if(integer[bit] + adder - '0' <= 9) integer[bit] += adder;
    else {
	integer[bit] = (integer[bit] + adder - '0') % 10 + '0';
	integer = add(integer, bit + 1, 1);
    }
    return integer;
}

string trans2(string decimal)
{
    int i = 1, j = 0;
    unsigned long res = 0, temp = 5;
    string result;
    while(i < decimal.length() && i <= 18) {
	if(decimal[i] == '1') res += temp;
	res *= 10;
	i++;
	temp *= 5;
    }
    int bit = 0;
    while(res) {
	result += res % 10 + '0';
	res /= 10;
	bit++;
    }
    bit = i - bit;
    while(j < bit) {
	result += '0';
	j++;
    }
    reverse(result.begin(), result.end());
    return result;
}

dwrd atof(string str)
{
    string binary;
    dwrd s, e, m = 0;
    if(str[0] == '-') {
	s = 1;
	str.erase(str.begin());
    }
    else s = 0;
    int i = 1, temp = (int)str.find('.');
    if(temp == -1) binary = form1(str, 0, (int)str.length() - 1);
    else {
	binary = form1(str, 0, temp) + '.' + form2(str, temp + 1, int(str.length()));
    }
    if(binary.find('.') != -1) {
	e = (dwrd)binary.find('.') + 126;
	binary.erase(binary.find('.'), 1);
    }
    else e = (dwrd)binary.find('.') + 126;
    int len = (int)binary.length();
    while(i < 24 && i < len) {
	if(binary[i] == '1') m += 1 << (23 - i);
	i++;
    }
    return (s << 31) | (e << 23) | m;
}

string form1(string str, int start, int end)
{
    string newstr = str.substr(start, end);
    string integer;
    int i = 0;
    while(newstr.length() != 0) {
	if((newstr[newstr.length() - 1] - '0') % 2) integer += '1';
	else integer += '0';
	newstr = divide(newstr);
	i++;
    }
    reverse(integer.begin(), integer.end());
    return integer;
}

string divide(string str)
{
    string result;
    int i = 0, carry = 0;
    while(i < str.length()) {
	if(str[i] == '1') {
	    if(carry == 0) result += '0';
	    else result += '5';
	    carry = 1;
	}
	else if((str[i] - '0') % 2) {
	    result += (str[i] - '0' + carry * 10) / 2 + '0';
	    carry = 1;
	}
	else {
	    result += (str[i] - '0' + carry * 10) / 2 + '0';
	    carry = 0;
	}
	i++;
    }
    if(result[0] == '0') result.erase(0, 1);
    return result;
}

string form2(string str, int start, int end)
{
    string newstr = str.substr(start, end);
    string decimal, temp;
    int k = 1;
    while(k < 24) {
	int i = (int)newstr.length() - 1, carry = 0;
	while(i >= 0) {
	    if(newstr[i] - '0' <= 4) {
		temp += 2 * (newstr[i] - '0') + '0' + carry;
		carry = 0;
	    }
	    else {
		temp += (2 * (newstr[i] - '0')) % 10 + '0' + carry;
		carry = 1;
	    }
	    i--;
	}
	if(carry == 1) temp += '1';
	if(temp.length() > newstr.length()) {
	    decimal += '1';
	    temp.erase(temp.end() - 1);
	}
	else decimal += '0';
	reverse(temp.begin(), temp.end());
	newstr = temp;
	temp.clear();
	k++;
    }
    return decimal;
}

dwrd fadd(dwrd x, dwrd y)
{
    if(x == 0) return y;
    else if(y == 0) return x;
    if((x << 1) < (y << 1)) return fadd(y , x);
    dwrd ex = (x >> 23) & 0xFF;
    dwrd ey = (y >> 23) & 0xFF;
    dwrd mx = (x & 0x7FFFFF) | 0x800000;
    dwrd my = (y & 0x7FFFFF) | 0x800000;
    my >>= (ex - ey);
    if((x ^ y) & 0x80000000) {
	mx -= my;
	if(mx == 0) return 0;
	mx <<= 1;
	ex--;
    }
    else {
	mx += my;
	if (mx == 0) return 0;
	while (mx & 0xFF000000) {
	    mx >>= 1;
	    ex++;
	}
    }
    return (x & 0x80000000) | (ex << 23) | (mx & 0x7FFFFF);
}

dwrd fsub(dwrd x, dwrd y)
{
    return fadd(x, y ^ 0x80000000);
}

dwrd fmul(dwrd x, dwrd y)
{
    if(x == 0 || y == 0) return 0;
    dwrd ex = (x >> 23) & 0xFF;
    dwrd ey = (y >> 23) & 0xFF;
    dwrd mx = (x & 0x7FFFFF) | 0x800000;
    dwrd my = (y & 0x7FFFFF) | 0x800000;
    dwrd s = (x >> 31) ^ (y >> 31);
    dwrd e = ex + ey - 127;
    dwrd result = 0;
    while(my != 0) {
	result >>= 1;
	if(my & 1) result += mx;
	my >>= 1;
    }
    while(result & 0xFF000000) {
	result >>= 1;
	e++;
    }
    return (s << 31) | (e << 23) | (result & 0x7FFFFF);
}

dwrd fdiv(dwrd x, dwrd y)
{
    if(x == 0) return 0;
    if (y == 0) return (x & 0x80000000) | 0x7F800000;
    dwrd ex = (x >> 23) & 0xFF;
    dwrd ey = (y >> 23) & 0xFF;
    dwrd mx = (x & 0x7FFFFF) | 0x800000;
    dwrd my = (y & 0x7FFFFF) | 0x800000;
    dwrd s = (x >> 31) ^ (y >> 31);
    dwrd e = ex - ey + 127;
    dwrd result = 0;
    while(mx < my) {
	mx <<= 1;
	e--;
    }
    while(!(result & 0xFF800000)) {
	if(mx < my) result <<= 1;
	else {
	    mx -= my;
	    result = (result << 1) | 1;
	}
	mx <<= 1;
    }
    return (s << 31) | (e << 23) | (result & 0x7FFFFF);
}

int main()
{
    string num1, num2;
	cout<<"Please input 2 float number in a line"<<endl;
    cin >> num1 >> num2;
    cout << "num1 = " << ftoa(atof(num1)) << endl;
    cout << "num2 = " << ftoa(atof(num2)) << endl;
    cout << "add = " << ftoa(fadd(atof(num1), atof(num2))) << endl;
    cout << "sub = " << ftoa(fsub(atof(num1), atof(num2))) << endl;
    cout << "mul = " << ftoa(fmul(atof(num1), atof(num2))) << endl;
    cout << "div = " << ftoa(fdiv(atof(num1), atof(num2))) << endl;
    return 0;
}