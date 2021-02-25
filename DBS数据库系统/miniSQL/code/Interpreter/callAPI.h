

#ifndef CODE_CALLAPI_H
#define CODE_CALLAPI_H
#include<iostream>
#include<string>
#include<vector>
#include"../StringProcessor/StringProcessor.h"
#include "../GlobalVariable/GlobalVariable.h"
#include "../API/API.h"

extern API* api;

using namespace std;

class callAPI {
public:
    // 这两个分别调用drop表和索引的API，比较容易写
    static bool callDropTableAPI(const string& tableName);
    static bool callDropIndexAPI(const string& indexName);
    static bool callCreateIndexAPI(const string& index, const string& table, const string& attribute);
    static bool callInsertAPI(const string& table, string& value);
    static bool callCreateTableAPI(const string& table, string& element);
    static vector<vector<tableValue>*>* callSelectAPI(string& table, string& condition);
    // 调用delete API的静态成员函数，condition是where后面的全部内容
    // 1表示成功，0表示失败，-1表示异常
    static int callDeleteAPI(string& tableName, string& condition);
};


#endif //CODE_CALLAPI_H
