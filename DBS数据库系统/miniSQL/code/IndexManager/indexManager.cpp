//
// Created by 74096 on 2020/6/1.
//

#include "indexManager.h"

indexManager::indexManager()
{
    buffer = new bufferManager();
}

//根据索引文件路径删除索引文件
void deleteFile(string filePath)
{
    remove(filePath.c_str());
}

//在索引文件中根据key查找对应的value，并将其作为结果返回
int indexManager::find(basic_string<char> indexName, const char* key)
{
    BPTree* tree = new BPTree(("index/" + string(indexName)).c_str());
    int ret = tree->find(key);
    delete tree;
    return ret;
}

//在索引中插入键值对
bool indexManager::insert(const char* indexName, const char* key, int value)
{
    BPTree* tree = new BPTree(("index/" + string(indexName)).c_str());
    bool ret = tree->add(key, value);
    if (!ret) cout<<"Insertion causes duplicate key in a B+ Tree"<<endl;
    delete tree;
    return ret;
}

//在索引中删除key
bool indexManager::remove(const char* indexName, const char* key)
{
    BPTree* tree = new BPTree(("index/" + string(indexName)).c_str());
    bool ret = tree->remove(key);
    if (!ret) cout<<"B+ Tree does not have the key to be deleted"<<endl;
    delete tree;
    return ret;
}

//创建一个新的索引
bool indexManager::createIndex(const char* indexName)
{
    catalogManager* manager = new catalogManager();
    index* index = manager->getIndex(string(indexName));
    if (index == nullptr)
        return false;
    Table* table = manager->getTable(index->getTableName());
    if (table == nullptr)
        return false;

    //获取数据长度和数据类型
    dataType* temp = table->searchAttribution(index->getColumnName());
    int keyLength = temp->getDataLength();
    int dataType = temp->type;
    BPTree::createFile(("index/" + string(indexName)).c_str(), keyLength, dataType);
    return true;
}

//删除索引
bool indexManager::dropIndex(const char* indexName)
{
    string filePath = string("dbFile/") + string("index/") + string(indexName) + string(".db");
    deleteFile(filePath);
    buffer->clearBuffer();
    return true;
}

