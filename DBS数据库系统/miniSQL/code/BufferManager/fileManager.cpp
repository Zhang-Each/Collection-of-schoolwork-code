//
// Created by 74096 on 2020/6/9.
//

#include "fileManager.h"

fileManager::fileManager()
= default;

fileManager::~fileManager()
= default;

bool fileManager::writeTableValue(char *p, vector<tableValue> *list, Table *table)
{
    // 读写二进制文件的时候需要考虑每条属性末尾的一个空格
    vector<dataType*>* typeList = table->tableAttribution;
    *p = 1;
    p++;
    for(int i = 0; i < table->columnCount; i++){
        switch ((*typeList)[i]->type)
        {
            case miniSQL_INT:
                fileManager::writeInt(p, (*list)[i].INT);
                p += 4;
                break;
            case miniSQL_FLOAT:
                fileManager::writeFloat(p, (*list)[i].FLOAT);
                p += 4;
                break;
            case miniSQL_CHAR:
                fileManager::writeChar(p, (*list)[i].CHAR, (*typeList)[i]->n);
                p += (*typeList)[i]->n;
                break;
        }
    }
    return true;
}

// 读取二进制文件中的数据
bool fileManager::readTableValue(char *p, vector<tableValue> *list, Table *table)
{
    vector<dataType*>* typeList = table->tableAttribution;
    p++;
    for(int i = 0; i < table->columnCount; i++){
        tableValue temp;
        switch ((*typeList)[i]->type)
        {
            case miniSQL_INT:
                fileManager::readInt(p, &(temp.INT));
                p += 4;
                break;
            case miniSQL_FLOAT:
                fileManager::readFloat(p, &(temp.FLOAT));
                p += 4;
                break;
            case miniSQL_CHAR:
                int len = (*typeList)[i]->n;
                temp.CHAR = new char[len];
                fileManager::readChar(p, temp.CHAR, len);
                p += len;
                break;
        }
        list->push_back(temp);
    }
    return true;
}

bool fileManager::writeInt(char *p, int x)
{
    memcpy(p, &x, 4);
    return true;
}
bool fileManager::writeFloat(char *p, float x)
{
    memcpy(p, &x, 4);
    return true;
}
bool fileManager::writeChar(char *p, char *data, int n)
{
    memcpy(p, data, n);
    return true;
}

bool fileManager::readInt(const char *p, int *x)
{
    memcpy(x, p, 4);
    return true;
}
bool fileManager::readFloat(const char *p, float *x)
{
    memcpy(x, p, 4);
    return true;
}
bool fileManager::readChar(const char *p, char *data, int n)
{
    memcpy(data, p, n);
    return true;
}