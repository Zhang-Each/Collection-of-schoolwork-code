//
// Created by 74096 on 2020/6/1.
//


#include "recordManager.h"

#include <utility>
#include "../Table/tableFile.h"
#include "../GlobalVariable/GlobalVariable.h"


recordManager::recordManager()
{
    catalog = new catalogManager();
    buffer = new bufferManager();
}

recordManager::~recordManager()
{
    delete catalog;
    delete buffer;
}

bool recordManager::recordCreateTable(const string& tableName)
{
    string filePath = "dbFile/" + tableName + ".db";
    if(!fopen(filePath.c_str(), "rb")) {
        FILE* dataFile = fopen(filePath.c_str(), "ab+");
        char* data = new char[blockSize];
        fileManager::writeInt(data, 0);
        fileManager::writeInt(data + 4, 1);
        fileManager::writeInt(data + 8, 0);
        fileManager::writeInt(data + 12, -1);
        fwrite(data, blockSize, 1, dataFile);
        fclose(dataFile);
        delete[] data;
    }
    return true;
}

bool recordManager::recordDeleteTable(const string& tableName, vector<int>* list)
{
    auto* fileName = new tableFile(tableName);
    if(list->empty()) delete fileName;
    else {
        int length, deleteID, shiftID, i;
        length = int(list->size() - 1);
        deleteID = (*list)[0];
        shiftID = (*list)[1];
        for(i = 0; i < length; i++) {
            fileName->recordDelete(deleteID, fileName->getByID(deleteID) != fileName->getByID(shiftID));
            deleteID = (*list)[i + 1];
            shiftID = (*list)[i + 2];
        }
        fileName->recordDelete((*list)[length]);
        delete fileName;
    }
    return true;
}

bool recordManager::recordDropTable(const string& tableName)
{
    string filePath = "dbFile/" + tableName + ".db";
    buffer->clearBuffer();
    /* 清除buffer里面的内容。 */
    remove(filePath.c_str());
    return true;
}

vector<tableValue>* recordManager::recordGetByID(const string& tableName, int id)
{
    auto* filename = new tableFile(tableName);
    vector<tableValue>* values = filename->getRecord(id);
    delete filename;
    return values;
}

int recordManager::recordInsertTable(const string& tableName, vector<tableValue> *value)
{
    auto* filename = new tableFile(tableName);
    int result = filename->recordInsert(value);
    delete filename;
    return result;
}

vector<int>* recordManager::recordSelectTable(const string& tableName, vector<logicCompare> *conditions)
{
    if(!conditions) conditions = new vector<logicCompare>;
    auto* result = new vector<int>;
    Table* table = catalog->getTable(tableName);
    auto* fileName = new tableFile(tableName);
    int maxID = fileName->getMaxID(), i;
    for(i = 0; i <= maxID; i++) {
        vector<tableValue>* records = fileName->getRecord(i, false);
        if(records) {
            if(recordCheck(table, records, conditions)) result->push_back(i);
        }
        else continue;
    }
    delete table;
    delete fileName;
    return result;
}

vector<int>* recordManager::recordSelectTable(const string& tableName, vector<logicCompare> *conditions, int flag)
{
    if(!conditions) conditions = new vector<logicCompare>;
    auto* result = new vector<int>;
    Table* table = catalog->getTable(tableName);
    auto* fileName = new tableFile(tableName);
    int maxID = fileName->getMaxID(), i;
    for(i = 0; i <= maxID; i++) {
        vector<tableValue>* records = fileName->getRecord(i, false);
        if(records) {
            if(recordCheck(table, records, conditions, flag)) result->push_back(i);
        }
        else continue;
    }
    delete table;
    delete fileName;
    return result;
}

bool recordManager::recordCheck(Table *table, vector<tableValue>* record, vector<logicCompare>* conditions)
{
    for(auto condition: *conditions) {
        int position = table->searchPosition(condition.getValueName());
        dataType* attribution = table->tableAttribution->at(position);
        if(attribution->type == miniSQL_INT) {
            int parameterOne = (*record)[position].INT;
            int parameterTwo = condition.getImmediate().INT;
            if(!condition.checkCondition(logicCompare::compareInt(parameterOne, parameterTwo))) return false;
        }
        else if(attribution->type == miniSQL_FLOAT) {
            float parameterOne = (*record)[position].FLOAT;
            float parameterTwo = condition.getImmediate().FLOAT;
            if(!condition.checkCondition(logicCompare::compareFloat(parameterOne, parameterTwo))) return false;
        }
        else {
            int length = attribution->n;
            char* parameterOne = (*record)[position].CHAR;
            char* parameterTwo = condition.getImmediate().CHAR;
            if(!condition.checkCondition(logicCompare::compareChar(parameterOne, parameterTwo, length))) return false;
        }
    }
    return true;
}

bool recordManager::recordCheck(Table *table, vector<tableValue>* record, vector<logicCompare>* conditions, int flag)
{
    for(auto condition: *conditions) {
        int position = table->searchPosition(condition.getValueName());
        dataType* attribution = table->tableAttribution->at(position);
        if(attribution->type == miniSQL_INT) {
            int parameterOne = (*record)[position].INT;
            int parameterTwo = condition.getImmediate().INT;
            if(condition.checkCondition(logicCompare::compareInt(parameterOne, parameterTwo))) return true;
        }
        else if(attribution->type == miniSQL_FLOAT) {
            float parameterOne = (*record)[position].FLOAT;
            float parameterTwo = condition.getImmediate().FLOAT;
            if(condition.checkCondition(logicCompare::compareFloat(parameterOne, parameterTwo))) return true;
        }
        else {
            int length = attribution->n;
            char* parameterOne = (*record)[position].CHAR;
            char* parameterTwo = condition.getImmediate().CHAR;
            if(condition.checkCondition(logicCompare::compareChar(parameterOne, parameterTwo, length))) return true;
        }
    }
    return false;
}

bool recordManager::recordCheckDuplicate(const string& tableName, vector<tableValue>* record)
{
    Table* table = catalog->getTable(tableName);
    auto* fileName = new tableFile(tableName);
    int maxID, i, j;
    maxID = fileName->getMaxID();
    bool noDuplicate = true;
    for(i = 0; i <= maxID; i++) {
        vector<tableValue>* currentRecord = fileName->getRecord(i, false);
        if(currentRecord == nullptr) continue;
        int size = (*(table)->tableAttribution).size();
        for(j = 0; j < size; j++) {
            dataType* attribution = table->tableAttribution->at(j);
            if(!attribution->isPrimaryKey && ! attribution->isUnique) continue;
            else if(attribution->type == miniSQL_INT)
                noDuplicate = (*record)[j].INT != (*currentRecord)[j].INT;
            else if(attribution->type == miniSQL_FLOAT)
                noDuplicate = (*record)[j].FLOAT != (*currentRecord)[j].FLOAT;
            else {
                int length = attribution->getDataLength();
                noDuplicate = logicCompare::compareChar((*record)[j].CHAR, (*currentRecord)[j].CHAR, length) != EQUAL;
            }
            if (!noDuplicate) break;
        }
        if (!noDuplicate) break;
    }
    delete table;
    delete fileName;
    return noDuplicate;
}