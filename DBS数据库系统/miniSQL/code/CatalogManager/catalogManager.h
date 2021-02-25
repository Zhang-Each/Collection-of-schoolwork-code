//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_CATALOGMANAGER_H
#define CODE_CATALOGMANAGER_H
#include<string>
#include<map>
#include<set>
#include<vector>

#include"../GlobalVariable/GlobalVariable.h"
#include"../Table/Table.h"
#include"../IndexManager/index.h"

using namespace std;

// 日志管理，各个member function的作用根据函数名就可以推测出来，今天晚上跑去吃鸡翅了所以更新的不是很多
class catalogManager {
private:
    static set<string> tableNameList;
    static map<string, index*> indexMap;
public:
    //每种操作对应的对于数据表和索引信息的文件的更新操作
    //用两个文件分别存储所有表和索引的名称等信息，用若干个文件每个分别存储一个表中的所有信息和一个索引的信息
    catalogManager();
    //~catalogManager();
    Table* getTable(const string& tableName);
    bool catalogCreateTable(const string& tableName, vector<dataType*>* attributions);
    bool catalogDropTable(const string& tableName);
    bool catalogUpdateTable(Table* table);
    bool catalogDropIndex(const string& indexName);
    bool catalogDropIndex(const string& tableName, const string& columnName);
    bool catalogCreateIndex(string& indexName, string& tableName, string& columnName);
    index* getIndex(const string& indexName);
    index* getIndex(const string& tableName, const string& columnName);
    void getIndexbyTable(const string& tableName, vector<index*>* indexVector);


};


#endif //CODE_CATALOGMANAGER_H
