//
// Created by 74096 on 2020/6/9.
//

#include "tableFile.h"

tableFile::tableFile(string name) /* 构造函数，初始化catalog和buffer。 */
{
    tableName = name;
    catalog = new catalogManager();
    buffer = new bufferManager();

    /* Initialize the original data structure. */
    table = catalog->getTable(tableName);
    sizeOfRecord = table->size;
    recordNumOfBlock = table->numPerBlock;

    /* Read header information from buffer. */
    Block* headerOfBlock = buffer->getBlock(tableName, 0);
    fileManager::readInt(headerOfBlock->data, &emptyID);
    fileManager::readInt(headerOfBlock->data + 4, &blockNum);
    fileManager::readInt(headerOfBlock->data + 8, &recordNum);
    fileManager::readInt(headerOfBlock->data + 12, &maxID);
}

tableFile::~tableFile() /* 析构函数 */
{
    delete catalog;
    delete buffer;
}

int tableFile::recordInsert(vector<tableValue>* values)
{
    //cout << "INSER : ID = " << emptyId << endl;
    int blockId = (emptyID / recordNumOfBlock) + 1;
    int offset = emptyID % recordNumOfBlock;
    int ret = emptyID;

    maxID = max(maxID, emptyID);
    Block *block;
    if (blockId < blockNum)block = buffer->getBlock(tableName, blockId);
    else
    {
        buffer->appendNode(tableName);
        blockNum++;
        block=buffer->getBlock(tableName, blockNum-1);
    }
    recordNum++;
    offset = offset * sizeOfRecord;
    char *p = block->data + offset;

    if (recordNum-1==maxID)emptyID++;
    else
    {
        //cout << "MARK : " << int(*p) << endl;
        fileManager::readInt(p+1, &emptyID);
        //cout << "READ POINTER : " << emptyId << endl;
    }
    fileManager::writeTableValue(p, values, table);
    buffer->writeBlock(block);

    updateHeader();


    return ret;
}

bool tableFile::recordDelete(int id, bool commit)
{
    int blockID = (id / recordNumOfBlock) + 1;
    int offset = (id % recordNumOfBlock) * sizeOfRecord;
    if(id > maxID) {
        cout <<"Unexpected access to an unexisted record"<<endl;
    }; /* Here, the user is trying to access a non-existent record. */


    /* Find the block and the pointer. */
    Block* block = buffer->getBlock(tableName, blockID);
    char* pointer = block->data + offset;
    char flag=*pointer;

    if(flag==0) {
        cout <<"Unexpected access to an unexisted record"<<endl;
    };/* Report that the record is non-existent. */

    /* Reset the variables. */
    *pointer = 0;
    pointer++;
    fileManager::writeInt(pointer, emptyID);
    emptyID = id;
    recordNum--;

    if(commit) { /* Committing a deletion is aviliable. */
        buffer->writeBlock(block);
        updateHeader();
    }
    else block->pin = true; /* To lock this block. */
    return true;
}

vector<tableValue>* tableFile::getRecord(int id, bool isNull)
{
    int blockID = (id / recordNumOfBlock) + 1;
    int offset = id % recordNumOfBlock;

    if(id > maxID){
        cout <<"Unexpected access to an unexisted record"<<endl; /* Here, the user is trying to access a non-existent record. */
    }

    Block * block = buffer->getBlock(tableName, blockID);
    offset *= sizeOfRecord;

    char *p = block->data + offset;
    char mark;
    memcpy(&mark, p, 1);
    if (mark == 0)
    {
        if (isNull)
            cout <<"Unexpected access to an unexisted record"<<endl;
        return nullptr;
    }
    auto * recordContent = new vector<tableValue>;
    fileManager::readTableValue(p, recordContent,table);
    return recordContent;

//        /* Find the block and the pointer. */
//        Block* block = buffer->getBlock(tableName, blockID);
//        char* pointer = block->data + offset;
//        char flag;
//
//        /* Verify if the record is null. */
//        memcpy(&flag, pointer, 1);
//        if(!flag && isNull) {
//            cout <<"Unexpected access to an unexisted record"<<endl;
//            return nullptr;
//        }
//
//        auto* recordsContents = new vector<tableValue>;
//        if(fileManager::readTableValue(pointer, recordsContents, table)) return recordsContents;

}

bool tableFile::updateHeader()
{
    Block* headerOfBlock = buffer->getBlock(tableName, 0);
    fileManager::writeInt(headerOfBlock->data, emptyID);
    fileManager::writeInt(headerOfBlock->data + 4, blockNum);
    fileManager::writeInt(headerOfBlock->data + 8, recordNum);
    fileManager::writeInt(headerOfBlock->data + 12, maxID);
    buffer->writeBlock(headerOfBlock);
    return true;
}

int tableFile::getByID(int id)
{
    return id / recordNumOfBlock + 1;
}

int tableFile::getMaxID()
{
    return maxID;
}