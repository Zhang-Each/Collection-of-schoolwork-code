//
// Created by 74096 on 2020/5/30.
//

#ifndef CODE_TABLE_H
#define CODE_TABLE_H
#include<iostream>
#include<string>
#include<vector>

#include"../GlobalVariable/GlobalVariable.h"
using namespace std;



// 表示数据类型的类，成员变量的含义根据变量名很好理解
class dataType{
public:
    int type, n;
    string typeName;
    bool isUnique, isPrimaryKey, hasIndex;
    dataType(int input_type, int input_n, string input_typeName, bool input_isUnique = false, bool input_isPrimaryKey = false, bool input_hasIndex = false);
    //获取数据长度的方法
    int getDataLength();
    // 这是一个可以看data type内部情况的成员函数，用于在测试的时候使用
    void showDataType();
};

//表示一张表的类
class Table{
public:
    string tableName;
    //这里primaryKey表示对应的主键的属性的下标
    int columnCount, primaryKey, numPerBlock, size;
    vector<dataType*>* tableAttribution;
    vector<string>* indexAttribution;
    Table(string name, vector<dataType*>* attribute, vector<string>* index);
    //这里好像也可以改成引用
    dataType* searchAttribution(const string& name);
    dataType* searchAttribution(const char* name);
    int searchPosition(const string& name);
    int searchPosition(const char* name);
    void dropIndex(const string& indexName);
};


#endif //CODE_TABLE_H
