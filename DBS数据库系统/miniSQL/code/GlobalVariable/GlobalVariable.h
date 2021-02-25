//
// Created by 74096 on 2020/5/30.
//

#ifndef CODE_GLOBALVARIABLE_H
#define CODE_GLOBALVARIABLE_H
//#include"../Table/Table.h"
#include<cstring>
#include<string>

using namespace std;

//一些重要的全局变量的定义

//三种数据类型的标识符
#define miniSQL_INT 3772
#define miniSQL_FLOAT 3162
#define miniSQL_CHAR 3501

//每个block的大小，设置为4KB，也可以改成8KB,反正推荐的是4KB或8KB
#define blockSize 4096
//缓冲区最大的大小，4MB
#define maxBufferSize 1024
//对于数据表的一些基本的限制,包括属性最多32种，char类型的值最大长度是255字节，一个表最多有10000行
#define maxAttributionSize 32
#define maxCharSize 255
#define maxRowSize 10000

//用于select里面的大小比较,这几个变量面馆看起来比较丑
#define EQUAL 0
#define NOTEQUAL 1
#define LESS 2
#define GREATER 3
#define LESSEQUAL 4
#define GREATEREQUAL 5

struct tableValue{
public:
    int INT;
    float FLOAT;
    char* CHAR;
};

class Block{
public:
    string fileName;
    int blockID;
    //pin表示一个block被锁了，不能被删除
    //is changed代表这个block是否被进行了修改
    bool pin, isChanged;
    char data[blockSize];
    Block(const string& name, const int& id){
        fileName = name;
        blockID = id;
        pin = false;
        isChanged = false;
    }
};

class logicCompare{
private:
    string valName;
    tableValue immediate;
public:
    string getValueName();
    tableValue getImmediate();
    bool checkCondition(int result);
    logicCompare(string& name, int op, tableValue imm);
    static int compareInt(int a, int b);
    static int compareFloat(float a, float b);
    static int compareChar(const char* a, const char*b, int length);

    int operation;
};



#endif //CODE_GLOBALVARIABLE_H
