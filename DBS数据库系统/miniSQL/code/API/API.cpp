//
// Created by 74096 on 2020/6/1.
//

#include <sstream>
#include "API.h"

API::API()
{
    buffer = new bufferManager();
    Index = new indexManager();
    catalog = new catalogManager();
    record = new recordManager();
}

API::~API()
{
    delete buffer;
    delete Index;
    delete catalog;
    delete record;
}

Table* API::getTable(const string &tableName)
{
    return catalog->getTable(tableName);
}

bool API::createTable(const string& tableName, vector<dataType*>* attribution)
{
    if(!catalog->catalogCreateTable(tableName, attribution))
        return false;
    if(!record->recordCreateTable(tableName))
        return false;
    for(auto i : *attribution){
        if(i->isPrimaryKey){
            createIndex(string("primary_index_of_") + tableName, tableName, i->typeName);
            return true;
        }
    }
    return false;
}

bool API::createIndex(string indexName, string tableName, string attribution)
{
    if(!catalog->catalogCreateIndex(indexName, tableName, attribution))
        return false;
    if(!Index->createIndex(indexName.c_str()))
        return false;
    Table* table = catalog->getTable(tableName);
    int pos = table->searchPosition(attribution);
    dataType* temp = table->tableAttribution->at(pos);
    char* key = new char[temp->getDataLength()];
    vector<int>* ids = record->recordSelectTable(tableName, nullptr);
    int i;
    for(i = 0; i < ids->size(); i++)
    {
        vector<tableValue>* record_value = record->recordGetByID(tableName, ids->at(i));
        writeKey(temp, key, record_value->at(pos));
        Index->insert(indexName.c_str(), key, ids->at(i));
    }
    return true;
}

bool API::dropTable(const string& tableName)
{
    Table *table = getTable(tableName);
    for(const auto& colName: *(table->indexAttribution))
    {
        class index* temp = catalog->getIndex(tableName, colName);
        dropIndex(temp->getName());
    }
    if(!catalog->catalogDropTable(tableName))return false;
    if(!record->recordDropTable(tableName))return false;

    delete table;
    return true;
}

bool API::dropIndex(const string& indexName)
{
    if(!catalog->catalogDropIndex(indexName))
        return false;
    return Index->dropIndex(indexName.c_str());
}

bool API::insertValue(const string& tableName, vector<string> valueList)
{
    Table * table = catalog->getTable(tableName);

    if (table == nullptr)return false;
    vector<dataType*> * attrList = table->tableAttribution;
    auto* isNULL = new vector<bool>;
    for (int i = 0; i < valueList.size(); i++)
        isNULL->push_back(valueList[i].empty());
    bool allHaveIndex = true;
    for (int i = 0; i < table->tableAttribution->size(); i++)
    {
        dataType* attr = (*(table->tableAttribution))[i];
        if (!attr->isPrimaryKey && !attr->isUnique) continue;
        if ((*isNULL)[i])
        {
            cout<<"Run time error! Empty Value!"<<endl;
            return false;
        }
        class index* index = catalog->getIndex(tableName, attr->typeName);
        if (index == nullptr)
            allHaveIndex = false;
    }

    auto * value = new vector<tableValue>;
    tableValue x{};

    int size = attrList->size();
    if (size != valueList.size())
    {
        cout<<"Run time error! Values not match"<<endl;
        return false;
    }

    //vector<tableValue>* value
    for (int i = 0; i < size; i++)
    {
        x.CHAR = nullptr;
        if ((*attrList)[i]->type == miniSQL_INT)
        {
            if (!stringProcessor::intCheckAndChange(valueList[i]).first)
            {
                cout<<"Run time error! Value type error!"<<endl;
                return false;
            }
            else
            {
                stringstream tran;
                tran << valueList[i];
                tran >> x.INT;
                value->push_back(x);
            }
        }
        else if ((*attrList)[i]->type == miniSQL_FLOAT)
        {
            if (!stringProcessor::floatCheckAndChange(valueList[i]).first)
            {
                cout<<"Run time error! Value type error!"<<endl;
                return false;
            }
            else
            {
                stringstream tran;
                tran << valueList[i];
                tran >> x.FLOAT;
                value->push_back(x);
            }
        }
        else
        {
            if (!stringProcessor::charCheckAndChange(valueList[i]))
            {
                cout<<"Run time error! Value type error!"<<endl;
                return false;
            }
            else
            {
                stringProcessor::getRidQuo(valueList[i]);
                int maxLen = (*attrList)[i]->n;
                if (valueList[i].size() > maxLen)
                {
                    cout<<"Run time error! Value is longer than the max len!"<<endl;
                }
                x.CHAR = new char[maxLen];
                memcpy(x.CHAR, valueList[i].c_str(), valueList[i].size()+1);
                value->push_back(x);
            }
        }
    }

    bool noDuplicate = true;
    if (allHaveIndex)
    {
        for (int i = 0; i < table->tableAttribution->size(); i++)
        {
            dataType* attr = table->tableAttribution->at(i);
            if (!attr->isPrimaryKey && !attr->isUnique) continue;
            class index* index = catalog->getIndex(tableName, attr->typeName);
            char* key = new char[attr->getDataLength()];
            writeKey(attr, key, value->at(i));
            int pos = Index->find(index->getName(), key);
            if (pos >= 0)
            {
                noDuplicate = false;
                break;
            }
        }
    }
    else
        noDuplicate = record->recordCheckDuplicate(tableName, value);

    if (!noDuplicate)
    {
        cout<<"Run time error! Duplicate attibution!"<<endl;
        return false;
    }
    int id = record->recordInsertTable(tableName, value);
    for (int i = 0; i < table->tableAttribution->size(); i++)
    {
        dataType* attr = table->tableAttribution->at(i);
        if (!attr->isPrimaryKey && !attr->isUnique) continue;
        class index* index = catalog->getIndex(tableName, attr->typeName);
        if (index != nullptr)
        {
            char* key = new char[attr->getDataLength()];
            writeKey(attr, key, value->at(i));
            Index->insert(index->getName().c_str(), key, id);
        }
    }

    char *temp;
    for (int i = 0; i < size; i++)
    {
        temp = (*value)[i].CHAR;
        delete temp;
    }
    delete value;
    delete table;
    return id >= 0;
}

int API::deleteValue(const string& tableName, vector<logicCompare>* conditions)
{
    return remove(tableName, conditions);
}

vector<vector<tableValue>*>* API::select(const string& tableName, vector<logicCompare>* condtions)
{
    Table* table = catalog->getTable(tableName);
    if(table == nullptr){
        cout<<"Run time error! There is no table!"<<endl;
        return nullptr;
    }
    for(auto logic: *condtions){
        if(table->searchAttribution(logic.getValueName()) == nullptr){
            cout<<"Run time error! Attribution not found!"<<endl;
            return nullptr;
        }
    }
    auto* result = new vector<vector<tableValue>*>;
    vector<int>* ids = new vector<int>;
    int selectNumber = findRecord(tableName, condtions, result, ids);
    return result;
}

vector<vector<tableValue>*>* API::select(const string& tableName, vector<logicCompare>* condtions, int flag)
{
    Table* table = catalog->getTable(tableName);
    if(table == nullptr){
        cout<<"Run time error! There is no table!"<<endl;
        return nullptr;
    }
    for(auto logic: *condtions){
        if(table->searchAttribution(logic.getValueName()) == nullptr){
            cout<<"Run time error! Attribution not found!"<<endl;
            return nullptr;
        }
    }
    auto* result = new vector<vector<tableValue>*>;
    vector<int>* ids = new vector<int>;
    int selectNumber = findRecord(tableName, condtions, result, ids, flag);
    return result;
}

int API::findRecord(const string &tableName, vector<logicCompare> *conditions, vector<vector<tableValue> *> *results, vector<int> *ids)
{
    Table* table = catalog->getTable(tableName);
    for(auto logic: *conditions){
        if(logic.operation != EQUAL)
            continue;
        class index* temp_index = catalog->getIndex(tableName, logic.getValueName());
        if(temp_index == nullptr)
            continue;
        dataType* attr = table->searchAttribution(logic.getValueName());
        char* key = new char[attr->getDataLength()];
        if(attr->type == miniSQL_INT)
            fileManager::writeInt(key, logic.getImmediate().INT);
        else if(attr->type == miniSQL_FLOAT)
            fileManager::writeFloat(key, logic.getImmediate().FLOAT);
        else
            fileManager::writeChar(key, logic.getImmediate().CHAR, attr->n);
        int id = Index->find(temp_index->getName(), key), ret;
        if(id < 0)
            ret = 0;
        else{
            vector<tableValue>* val = record->recordGetByID(tableName, id);
            if(record->recordCheck(table, val, conditions)){
                results->push_back(val);
                ids->push_back(id);
                ret = 1;
            }
            else ret = 0;
        }
        return ret;
    }
    auto* t = new vector<int>;
    t = record->recordSelectTable(tableName, conditions);
    for(auto id: *t){
        ids->push_back(id);
        results->push_back(record->recordGetByID(tableName, id));
    }
    return ids->size();
}

int API::findRecord(const string &tableName, vector<logicCompare> *conditions, vector<vector<tableValue> *> *results, vector<int> *ids, int flag)
{
    auto* t = new vector<int>;
    t = record->recordSelectTable(tableName, conditions, flag);
    for(auto id: *t){
        ids->push_back(id);
        results->push_back(record->recordGetByID(tableName, id));
    }
    return ids->size();
}

void API::writeKey(dataType *attribution, char *key, tableValue v)
{
    if(attribution->type == miniSQL_INT)
        fileManager::writeInt(key, v.INT);
    else if(attribution->type == miniSQL_FLOAT)
        fileManager::writeFloat(key, v.FLOAT);
    else
        fileManager::writeChar(key, v.CHAR, attribution->getDataLength());
}

int API::remove(string tableName, vector<logicCompare> *conditions)
{
    Table* table = getTable(tableName);
    if(table == nullptr){
        cout<<"Run time error! There is no table!"<<endl;
        return 0;
    }
    auto* result = new vector<vector<tableValue>*>;
    auto* ids = new vector<int>;
    int selectNumber = findRecord(tableName, conditions, result, ids);
    for(auto indexCol: *(table->indexAttribution)){
        int pos = table->searchPosition(indexCol);
        dataType* temp = (*(table->tableAttribution))[pos];
        char *key = new char[temp->getDataLength()];
        class index* temp_index = catalog->getIndex(table->tableName, indexCol);
        for(auto t: *result){
            writeKey(temp, key, t->at(pos));
            Index->remove(temp_index->getName().c_str(), key);
        }
    }
    record->recordDeleteTable(tableName, ids);
    return selectNumber;
}