//
// Created by 74096 on 2020/6/1.
//

#ifndef CODE_BUFFERMANAGER_H
#define CODE_BUFFERMANAGER_H
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include"fileManager.h"


using namespace std;

// 其实是一个由单个block 组合而成的链表
struct bufferNode{
   Block* block;
    bufferNode *last, *next;
    explicit bufferNode(Block* temp){
        block = temp;
        last = next = nullptr;
    }
    ~bufferNode(){
        remove();
    }
    void remove() const{
        if(next != nullptr)
            last->next = next;
        if(last != nullptr)
            next->last = last;
    }
};


class bufferManager {
private:
    static int blockCount;
    static bufferNode *head, *tail;
    static map<string, bufferNode*> nodeMap;
    Block* loadBlock(const string& fileName, int id);
    bool deleteNode(bufferNode *node);
public:
    static const int maxBlockNumber;
    bufferManager();
    Block* getBlock(const string& fileName, int id);
    bool writeBlock(const string& fileName, int id);
    bool writeBlock(Block* block);
    bool accessNode(bufferNode* node);
    bool appendNode(const string& fileName);
    bool clearBuffer();
};


#endif //CODE_BUFFERMANAGER_H
