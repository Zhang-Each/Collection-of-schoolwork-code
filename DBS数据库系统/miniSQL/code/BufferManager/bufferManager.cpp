//
// Created by 74096 on 2020/6/1.
//

#include "bufferManager.h"
const int bufferManager::maxBlockNumber = maxBufferSize;
int bufferManager::blockCount = 0;
bufferNode* bufferManager::head = nullptr;
bufferNode* bufferManager::tail = nullptr;
map<string, bufferNode*> bufferManager::nodeMap;


bufferManager::bufferManager()
{
    // 初始化一个block的链表
    if(head == nullptr && tail == nullptr)
    {
        head = new bufferNode(nullptr);
        tail = new bufferNode(nullptr);
        head->last = head;
        head->next = tail;
        tail->next = tail;
        tail->last = head;
    }
}

Block * bufferManager::getBlock(const string& fileName, int id)
{
    string blockName = fileName + '_' + to_string(id);
    if(nodeMap.count(blockName) != 0){
        bufferNode* temp = nodeMap[blockName];
        accessNode(temp);
        return temp->block;
    }
    // 如果没有，就需要在数据文件中找到对应的block
    if(blockCount == maxBlockNumber){
        bufferNode* temp = head->next;
        // 找到一个优先级最低的block进行替换
        while(temp != tail && temp->block->pin)
            temp = temp->next;
        if(temp == tail)
            cout<<"Run time error! Buffer OverLoad!"<<endl;
        else
            deleteNode(temp);
    }
    return loadBlock(fileName, id);
}

// 访问之后把node转移到链表的末尾(tail结点的前面)
// 这里用链表中的顺序来表示block结点的优先级，越是靠前的结点距离上次被访问就越久，被删除的优先级越高
bool bufferManager::accessNode(bufferNode *node)
{
    node->remove();
    tail->last->next = node;
    node->last = tail->last;
    tail->last = node;
    node->next = tail;
    return true;
}

bool bufferManager::appendNode(const string& fileName)
{
    char *data = new char[blockSize];
    string path = "dbFile/" + fileName + ".db";
    FILE* fp = fopen(path.c_str(), "ab");
    fwrite(data, blockSize, 1, fp);
    fclose(fp);
    delete[] data;
    return true;
}

bool bufferManager::clearBuffer()
{
    while(tail != head->next){
        if(!deleteNode(head->next))
            return false;
    }
    return true;
}

bool bufferManager::writeBlock(Block *block)
{
    block->isChanged = true;
    string filePath = "dbFile/" + block->fileName + ".db";
    FILE* fp = fopen(filePath.c_str(), "rb+");
    if(fp == nullptr){
        cout<<"Run time error! Can't write block!"<<endl;
    }
    fseek(fp, block->blockID*blockSize, SEEK_SET);
    fwrite(block->data, blockSize, 1, fp);
    fclose(fp);
    return true;
}

bool bufferManager::writeBlock(const string& fileName, int id)
{
    Block* temp = getBlock(fileName, id);
    return writeBlock(temp);
}

bool bufferManager::deleteNode(bufferNode *node)
{
    string name = node->block->fileName + "_" + to_string(node->block->blockID);
    nodeMap.erase(name);
    delete node;
    blockCount--;
    return true;
}

Block * bufferManager::loadBlock(const string& fileName, int id)
{
    auto* temp = new Block(fileName, id);
    string filePath = "dbFile/" + fileName + ".db";
    FILE* fp = fopen(filePath.c_str(), "rb");
    if(fp == nullptr){
        cout<<"Run time error! Can't read block!"<<endl;
    }
    int check = fseek(fp, id*blockSize, SEEK_SET);
    if(check == -1){
        cout<<"Run time error! Can't read block!"<<endl;
    }
    fread(temp->data, blockSize, 1, fp);
    fclose(fp);

    auto* t = new bufferNode(temp);
    accessNode(t);
    nodeMap[fileName + "_" + to_string(id)] = t;
    blockCount++;
    return temp;
}

