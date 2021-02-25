//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_RECORDMANAGER_H
#define CODE_RECORDMANAGER_H
#include<fstream>
#include<vector>
#include<string>
#include<set>
#include"../CatalogManager/catalogManager.h"
#include"../BufferManager/bufferManager.h"

using namespace std;

class recordManager {
public:
    recordManager();
    ~recordManager();
    bool recordCreateTable(const string& tableName);
    bool recordDropTable(const string& tableName);
    bool recordDeleteTable(const string& tableName, vector<int>* list);
    int recordInsertTable(const string& tableName, vector<tableValue>* value);
    bool recordCheck(Table* table, vector<tableValue>* record, vector<logicCompare>* conditions);
    bool recordCheck(Table* table, vector<tableValue>* record, vector<logicCompare>* conditions, int flag);
    bool recordCheckDuplicate(const string& tableName, vector<tableValue>* record);
    vector<int> * recordSelectTable(const string& tableName, vector<logicCompare>* conditions);
    vector<int> * recordSelectTable(const string& tableName, vector<logicCompare>* conditions, int flag);
    vector<tableValue>* recordGetByID(const string& tableName, int id);
private:
    catalogManager* catalog;
    bufferManager* buffer;
};


#endif //CODE_RECORDMANAGER_H
