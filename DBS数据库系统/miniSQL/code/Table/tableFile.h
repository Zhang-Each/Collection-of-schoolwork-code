//
// Created by 74096 on 2020/6/9.
//

#ifndef CODE_TABLEFILE_H
#define CODE_TABLEFILE_H

#include "../BufferManager/bufferManager.h"
#include "../CatalogManager/catalogManager.h"
#include "../BufferManager/fileManager.h"
#include "../Table/Table.h"


class tableFile {
public:
    tableFile(string fileName);
    ~tableFile();
    int recordInsert(vector<tableValue>* values);
    bool recordDelete(int id, bool commit = true);
    vector<tableValue>* getRecord(int id, bool isNull = true);
    bool updateHeader();
    int getByID(int id);
    int getMaxID();
private:
    int sizeOfRecord;
    int recordNumOfBlock;
    int emptyID, blockNum, recordNum, maxID;
    string tableName;
    catalogManager * catalog;
    bufferManager * buffer;
    Table * table;
};


#endif //CODE_TABLEFILE_H