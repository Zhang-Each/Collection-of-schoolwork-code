//
// Created by 74096 on 2020/5/29.
//

#ifndef CODE_SHOWRESULT_H
#define CODE_SHOWRESULT_H
#include "../Table/Table.h"
#include"../GlobalVariable/GlobalVariable.h"
#include "../API/API.h"

extern API* api;
class showResult {
public:
    // 一些用来显示结果的static成员函数
    static void showDropTable(bool flag, const string& table);
    static void showDropIndex(bool flag, const string& index);
    static void showCreateTable(bool flag, const string& table);
    static void showCreateIndex(bool flag, const string& index);
    static void showInsert(bool flag, const string& table);
    static void showDelete(int flag, const string& table);
    static void showSelect(vector<vector<tableValue>*>* result, string tableName);
    static string beautify(int length, string op = " ");
};


#endif //CODE_SHOWRESULT_H
