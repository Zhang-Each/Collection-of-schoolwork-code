//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_INDEXMANAGER_H
#define CODE_INDEXMANAGER_H

#include <fstream>
#include"../BufferManager/bufferManager.h"
#include"../IndexManager/index.h"
#include "../Table/Table.h"
#include "../CatalogManager/catalogManager.h"
#include "BPTree.h"

//索引管理，包括基本的查找、插入、删除、创建等操作
class indexManager {
public:
    indexManager();
    int find(basic_string<char> indexName, const char* key);
    bool insert(const char* indexName, const char* key, int value);
    bool remove(const char* indexName, const char* key);
    bool createIndex(const char* indexName);
    bool dropIndex(const char* indexName);
private:
    bufferManager *buffer;
};


#endif //CODE_INDEXMANAGER_H
