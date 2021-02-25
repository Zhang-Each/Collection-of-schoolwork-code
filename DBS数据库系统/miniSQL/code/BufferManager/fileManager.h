//
// Created by 74096 on 2020/6/9.
//

#ifndef CODE_FILEMANAGER_H
#define CODE_FILEMANAGER_H
#include<fstream>
#include<string>
#include<vector>
#include"../Table/Table.h"
#include"../GlobalVariable/GlobalVariable.h"

using namespace std;

// 一个用于读写二进制文件的类
class fileManager {
public:
    fileManager();
    ~fileManager();
    static bool writeTableValue(char *p, vector<tableValue>* list, Table* table);
    static bool readTableValue(char *p, vector<tableValue>* list, Table *table);

    static bool writeInt(char *p, int x);
    static bool writeFloat(char *p, float x);
    static bool writeChar(char *p, char *data, int n);

    static bool readInt(const char *p, int *x);
    static bool readFloat(const char *p, float *x);
    static bool readChar(const char *p, char *data, int n);
};


#endif //CODE_FILEMANAGER_H
