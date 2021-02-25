//
// Created by 74096 on 2020/5/24.
//

#include "StringProcessor.h"
#include <cmath>

//去空格的处理函数，其实应该还需要一个把多个空格替换成一个空格的函数，不过这里先考虑最简单的情况先不写了
void stringProcessor::preTrim(string &s)
{
    if(s.empty())
        return ;
    else{
        s.erase(0, s.find_first_not_of(' '));
        s.erase(s.find_last_not_of(' ') + 1);
        return ;
    }
}

//把字符串按某个符号进行切分的处理函数
//s 是要处理的长字符串, unit是切分的标志
vector<string> stringProcessor::Split(const string &s, const string &unit)
{
    int start,len=unit.length();
    vector<string> result;
    if(s.empty()||s == unit)
        return result;
    string x = s;
    preTrim(x);
    start = x.find(unit);
    while(start != -1) {
        result.push_back(x.substr(0,start));
        x=x.substr(start+len);
        preTrim(x);
        start = x.find(unit);
    }
    if(x.length() >= 1)
        result.push_back(x);
    return result;
}

// 对cmd命令的优化，包括去首尾空格和全部转换成小写，卸载这个类里提高了代码的复用性
string stringProcessor::cmdOptimum(string& cmd)
{
    for(char & i : cmd) {
        if(i == '\t')
            i = ' ';
        if(i >= 'A'&&i <= 'Z')
            i += 32;
    }
    preTrim(cmd);
    cmd = cmd.substr(0, cmd.length()-1);
    preTrim(cmd);
    return cmd;
}

void stringProcessor::showOperation(vector<string> op)
{
//    for(int i=0; i < op.size(); i++) {
//        cout<<"Position "<<i<<" :"<<op[i]<<endl;
//    }
}

//用来删除命令中的括号
//返回值说明：0表示语法错误，1表示有括号，是create或者insert语句，-1表示没有括号，是其他类型的SQL语句
int stringProcessor::bracketProcessor(string& cmd)
{
    vector<int> left, right;
    for(int i = 0; i < cmd.length(); i++ ) {
        if(cmd[i] == '(') {
            left.push_back(i);
        }
        else if(cmd[i] == ')') {
            right.push_back(i);
        }
    }
    //左右括号数量不相同，说明语法错误
    if(left.size() != right.size())
        return 0;
    else if(left.empty() && right.empty())
        return -1;
    else {
        int len = left.size(); //共同的个数
        //这种情况下的括号是错位的
        return !(left[len - 1] >= right[len - 1] || right[0] <= left[0]);
    }

}

int stringProcessor::getCompareType(const string& x)
{
    int count = 0, result = -1;
    if(x.find(">=") != -1){
        count++;
        result = GREATEREQUAL;
    }
    else if(x.find("<=") != -1){
        count++;
        result = LESSEQUAL;
    }
    else if(x.find("<>") != -1){
        count++;
        result = NOTEQUAL;
    }
    else if(x.find('>') != -1){
        count++;
        result = GREATER;
    }
    else if(x.find('<') != -1){
        count++;
        result = LESS;
    }
    else if(x.find('=') != -1){
        count++;
        result = EQUAL;
    }
    if(count != 1)
        return -1;
    else return result;
}

logicCompare* stringProcessor::getLogic(string x, int compareType, vector<dataType*>* attribution)
{
    int pos = -1;
    // 分别代表关系符左右两边的东西，left是属性名，right是对应的值
    string left, right;
    switch (compareType)
    {
        case EQUAL:
            pos = x.find('=');
            break;
        case GREATER:
            pos = x.find('>');
            break;
        case LESS:
            pos = x.find('<');
            break;
        case GREATEREQUAL:
            pos = x.find(">=");
            break;
        case LESSEQUAL:
            pos = x.find("<=");
            break;
        case NOTEQUAL:
            pos = x.find("<>");
            break;
        default:
            cout<<"Run time error! Illegal logic type!"<<endl;
            return nullptr;
    }
    if(pos == -1){
        cout<<"Run time error! No logic operator!<<endl";
        return nullptr;
    }
    // 根据pos的位置来获取逻辑关系运算符两边的内容
    if(compareType == GREATER || compareType == LESS || compareType == EQUAL){
        left = x.substr(0, pos);
        right = x.substr(pos + 1);
    }
    else{
        left = x.substr(0, pos);
        right = x.substr(pos + 2);
    }
    preTrim(left);
    preTrim(right);
    tableValue temp{};
    int i, dataType, len;
    for(i = 0; i < attribution->size(); i++){
        if((*attribution)[i]->typeName == left){
            dataType = (*attribution)[i]->type;
            len = (*attribution)[i]->n;
            break;
        }
    }
    pair<bool, int> p;
    pair<bool, float> q;
    switch (dataType)
    {
        case miniSQL_INT:
            p  = intCheckAndChange(right);
            if(p.first){
                temp.INT = p.second;
            } else
                cout<<"Run time error! Not an int value in the SQL"<<endl;
            break;
        case miniSQL_FLOAT:
            q = floatCheckAndChange(right);
            if(q.first){
                temp.FLOAT = q.second;
            } else
                cout<<"Run time error! Not a float value in the SQL"<<endl;
            break;
        case miniSQL_CHAR:
            charCheckAndChange(right);
            temp.CHAR = new char[len];
            memcpy(temp.CHAR, right.c_str(), right.size() + 1);
            break;
        default:
            cout<<"Run time error! Illegal data value!"<<endl;
            return nullptr;
    }
    auto* result = new logicCompare(left, compareType, temp);
    return result;
}

pair<bool, int> stringProcessor::intCheckAndChange(const string& val)
{
    pair<bool, int> result(false, 0);
    // 检查是否有非数字出现，如果出现则不是int类型，返回错误
    for(char i : val){
        if(i < '0' || i > '9')
            return result;
    }
    int value = 0;
    for(char i : val){
        value = 10 * value + (i - '0');
    }
    result.first = true;
    result.second = value;
    return result;
}

pair<bool, float> stringProcessor::floatCheckAndChange(const string &val)
{
    pair<bool, float> result(false, 0);
    int pointCount = 0;
    for(char i : val){
        if(i == '.')
            pointCount++;
        else if(i < '0' || i > '9')
            return result;
    }
    if(pointCount > 1){
        return result;
    }
    if(pointCount == 0){
        result.first = true;
        result.second = strtod(val.c_str(),NULL);
        return result;
    }

    int pos = val.find('.');
    int value = 0;
    for(char i : val){
        if(i == '.')
            continue;
        else
            value = 10 * value + (i - '0');
    }
    result.first = true;
    result.second = value / pow(10, val.size() - pos - 1);
    return result;
}

bool stringProcessor::charCheckAndChange(string &val)
{
    // preTrim(val);
    bool check = stringProcessor::charCheck(val);

    if(check){
        val = val.substr(1, val.size() - 2);
        return true;
    }
    else
        return false;
}

bool stringProcessor::charCheck(string &val)
{
    // 只有当第一位和最后一位都是单引号或者双引号的时候才是正确的char类型
    // preTrim(val);
    int n = val.size();
    return (val[0] == '\'' && val[n - 1] == '\'') || (val[0] == '\"' && val[n - 1] == '\"');
}

bool stringProcessor::getRidQuo(string &x) {

    preTrim(x);
    if (!x.empty())
    {
        if (charCheckAndChange(x))x = x.substr(1, x.size() - 2);
    }
    return true;
}
