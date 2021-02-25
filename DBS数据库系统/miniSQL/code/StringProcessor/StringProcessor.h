//
// Created by 74096 on 2020/5/24.
//

#ifndef CODE_stringProcessor_H
#define CODE_stringProcessor_H
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include"../GlobalVariable/GlobalVariable.h"
#include"../Table/Table.h"

using namespace std;


class stringProcessor {
public:
    //去空格的处理函数，其实应该还需要一个把多个空格替换成一个空格的函数，不过这里先考虑最简单的情况先不写了
    static void preTrim(string &s);
    //把字符串按某个符号进行切分的处理函数
    //s 是要处理的长字符串, unit是切分的标志
    static vector<string> Split(const string &s, const string &unit);
    // 对cmd命令的优化，包括去首尾空格和全部转换成小写，卸载这个类里提高了代码的复用性
    static string cmdOptimum(string& cmd);
    static void showOperation(vector<string> op);
    //用来删除命令中的括号
    //返回值说明：0表示语法错误，1表示有括号，是create或者insert语句，-1表示没有括号，是其他类型的SQL语句
    static int bracketProcessor(string& cmd);
    static int getCompareType(const string& x);
    static logicCompare* getLogic(string x, int compareType, vector<dataType*>* attribution);
    static pair<bool, int> intCheckAndChange(const string& val);
    static pair<bool, float> floatCheckAndChange(const string& val);
    static bool charCheckAndChange(string& val);
    static bool charCheck(string& val);
    static bool getRidQuo(string &x);
};

#endif //CODE_stringProcessor_H
